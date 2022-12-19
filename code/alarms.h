int alarmPos=0;
int datePos[]={10,62,116,168,225,272,326,384};

//********************************************************************************************
//                                    get next Alarm
//********************************************************************************************

void getNextAlarm(int h,int m,int d){

  int nowDay, e;
  nextAlarmHour=24;
  nextAlarmMin=60;
  nextAlarmDay=7;
  nextAlarmId=-1;
  
  for(int j=0;j<7;j++){ 
    nowDay=d+j;
    if(nowDay>=7)
      nowDay-=7;

      for(i=0;i<nbAlarm;i++){ 
        if(stats[i]=="1"){
          if(j<2){
            for(e=0;e<7;e++){ 
              if(repeter[i][e]=='1')
                e=10;
            }
          }
          if(repeter[i][nowDay]=='1' || (j<2 && e==7)){

            int alarmeHour=heure[i].substring(0, 2).toInt();
            int alarmeMin=heure[i].substring(3, 5).toInt();                          
          if( (((alarmeHour==nextAlarmHour && alarmeMin<nextAlarmMin) || alarmeHour<nextAlarmHour) && ((alarmeHour==h && alarmeMin>m) || alarmeHour>h) &&  nowDay==d ) || ( ((alarmeHour==nextAlarmHour && alarmeMin<nextAlarmMin) || alarmeHour<nextAlarmHour) &&  nowDay!=d) || ((j==0 && e==7) && nextAlarmHour != nowDay && ((alarmeHour==h && alarmeMin>m) || alarmeHour>h) && ((alarmeHour==nextAlarmHour && alarmeMin<nextAlarmMin) || alarmeHour<nextAlarmHour) ) || ((j==1 && e==7) && nextAlarmHour != nowDay && ((alarmeHour==nextAlarmHour && alarmeMin<nextAlarmMin) || alarmeHour<nextAlarmHour) ) ){

              nextAlarmHour = alarmeHour;
              nextAlarmMin = alarmeMin;
              nextAlarmDay = nowDay;
              nextAlarmId = i;
          }
        }
      }
    }
    if(nextAlarmDay==nowDay)
      j=7;
  }

  if(nextAlarmId!=-1){
    if(disableNextAlarm==1){
      tft.fillRect(20, 0, 360, 30, BLACK);  
      tft.setCursor(75, 20);
      tft.print("Prochaine alarme desactivee");
    }else{
      tft.fillRect(20, 0, 360, 30, BLACK);  
      tft.setCursor(75, 20);
      tft.print("Alarme ");
      tft.print(nextAlarmId+1);
      tft.print(" : ");
      tft.print( longDay[nextAlarmDay]);
      tft.print(" a ");
      tft.print(nextAlarmHour);
      tft.print(":");
      if(nextAlarmMin<10)
        tft.print("0");
      tft.print(nextAlarmMin);
      tft.drawBitmap(20,10,notification,32,32,RED);
    }
  }else{
    tft.fillRect(20, 0, 360, 30, BLACK);  
    tft.setCursor(130, 20);
    tft.print("Aucune Alarme");
  }
}

//********************************************************************************************
//                                    get post Alarm
//********************************************************************************************

char getSdAlarm(String alarmsFile){

  /*int pos=0;                  // EEPROM read 
  char jsonE[3000];
  do{
     jsonE[pos]=EEPROM.read(pos);
     Serial.print(pos);
     Serial.println(jsonE[pos]);
     pos++;
  }while(jsonE[pos-1]!='\0' );*/

  myFile = SD.open(alarmsFile);                                   // get alarms from sd
  if (myFile) {
    //Serial.println("ALARMS.TXT");
    myFile.seek(0);
    while (myFile.available()) {
      message = myFile.readStringUntil('\n');
    }
    myFile.close();
  } else {
    Serial.println("error opening .txt");
    messageScreen("error opening "+alarmsFile+".TXT",0);
    return 1;
  }
  return getJsonAlarm(message);
} 

char getJsonAlarm(String jsonStr){                                  // transform alarm json to table
  //Serial.println(jsonStr);
  char jsonPart[200];
  nbAlarm=i=j=0;
  do{
    if(jsonStr[i]=='{' || (jsonStr[i-1]==']' && jsonStr[i]=='}')){
      jsonPart[j-1]='\0';
      //Serial.println(jsonPart);
      if(i>20){
        if( parseJsonAlarm(jsonPart) )
          return 1;
        nbAlarm++;
      }
      jsonPart[0]='{';
      j=0;
    }else{
      jsonPart[j]=jsonStr[i];
    }
    i++;
    j++;
  }while( jsonStr[i]!='\0' );

  modifAlarm=1;
  return 0;
}

char parseJsonAlarm(char* json){ 
  //Serial.println(json);
  DeserializationError error = deserializeJson(doc, json);                // Deserialize the JSON document

  if (error) {  // Test if parsing succeeds.
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return 1;
    //messageScreen("deserializeJson() failed",0);
  }else{
    root = doc.as<JsonObject>();
    action[nbAlarm]= root["action"].as<String>();                         // add in db
    repeter[nbAlarm]= root["repeter"].as<String>();
    heure[nbAlarm]= root["heure"].as<String>();
    stats[nbAlarm]= root["status"].as<String>();
    appareil[nbAlarm]= root["appareil"].as<String>();
    cmd[nbAlarm]=root["cmd"].as<String>();
    modDate[nbAlarm]=root["modDate"].as<String>();
    return 0;
  } 
}

void savePublishAlarms(int mod){                                            // save alarm on sd
  
  String jsonExt = "{\"alarmes\":[";
  for(i=0;i<nbAlarm;i++){ 
    jsonExt+="{\"action\":\""+action[i]+"\",\"repeter\":\""+repeter[i]+"\",\"heure\":\""+heure[i]+"\",\"status\":\""+stats[i]+"\",\"appareil\":\""+action[i]+"\",\"cmd\":\""+cmd[i]+"\",\"modDate\":\""+modDate[i]+"\"}";
    jsonExt+=",";
  }
  while(jsonExt[jsonExt.length()-1]==',') {             // remove all end ,
    jsonExt=jsonExt.substring(0,jsonExt.length()-1);
  }
  jsonExt += "]}";
 
  //Serial.println(jsonExt);
  if(mod==1){
    SD.remove("ALARMS.TXT");
    myFile = SD.open("ALARMS.TXT", FILE_WRITE);
    if (myFile) {
      //Serial.print("Writing txt");
      myFile.println(jsonExt);
      myFile.close();
    } else {
      Serial.println("error opening ALARMS.TXT");
      messageScreen("error opening ALARMS.TXT\n Write Error",0);
    }
    delay(1000);
    SD.remove("SAVE.TXT");                       // save to bypass reding error 
    myFile = SD.open("SAVE.TXT", FILE_WRITE);
    if (myFile) {
      //Serial.print("Writing txt");
      myFile.println(jsonExt);
      myFile.close();
    } else {
      Serial.println("error opening SAVE.TXT");
      messageScreen("error opening \nSAVE.TXT\n Write Error",0);
    }
  }else{
    //Serial1.println(jsonExt);
  }
  /*//Serial.println(jsonExt.length());                 // EEPROM write 
  if(mod){
    int pos=0;    
    while(jsonExt[pos]!='\0'){
       EEPROM.write(pos, jsonExt[pos]);
       Serial.print(pos);
       Serial.println(jsonExt[pos]);
       pos++;
    }
    EEPROM.update(pos,'\0');  // Save the NULL terminator
  }*/
}

//********************************************************************************************
//                                    display Alarm
//********************************************************************************************

void displayAlarm(int Begin){
  alarmPos=Begin;

  tft.reset();  
  tft.fillScreen(BLACK);
  tft.setRotation(1);

  for(int e=0;e<4;e++){                                       // display title
    if(e+Begin<nbAlarm){
      tft.setTextColor(color2);
      tft.setTextSize(1);
      tft.setCursor(20, (e)*60+20);
      tft.print("Alarme "+String(e+Begin+1)+" : ");
      tft.print(heure[e+Begin]);

      tft.setCursor(5, (e)*60+52);                            // status of days
      for(int j=0;j<7;j++){
        if(repeter[e+Begin][j]=='1')
          tft.setTextColor(GREEN);
        else
          tft.setTextColor(RED);
        tft.print(Day[j]+" ");
      }
      if(e!=Begin+3)
        tft.drawLine(10, (e)*60+58, 363, (e)*60+58, GREY);    // scrollbar
  
      if(stats[e+Begin]=="1")
        tft.fillRoundRect( 320,(e)*60+4, 50, 50,8, GREEN);    // status bp
      else
        tft.fillRoundRect( 320,(e)*60+4, 50, 50,8, RED); 
    }
  }  
  tft.fillRoundRect( 385,10, 8, 220,2, GREY);

  previousMillis = millis();
  while(Mode==3){

    currentMillis = millis();                                 // wait 30 sec befor get next time
    if (currentMillis - previousMillis >= 30000)
      Mode=0;
  
    tp = ts.getPoint();   //tp.x, tp.y are ADC values
    if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE) {
        if (SwapXY != (Orientation & 1)) SWAP(tp.x, tp.y);
        xpos = map(tp.x, TS_LEFT, TS_RT, tft.width(), 0);
        ypos = map(tp.y, TS_TOP, TS_BOT, tft.height(), 0);
        //Serial.print(xpos);      Serial.print(" - ");      Serial.println(ypos);
        previousMillis = millis();
        
  //************************************************************************************* up / down             
        if(xpos>370){
          if(ypos>120 && alarmPos<nbAlarm-4){             // down
              alarmPos+=4;
              displayAlarm(alarmPos);
          }else if(alarmPos!=0){                          // up
            alarmPos-=4;
            if(alarmPos<0)
              alarmPos=0;
            displayAlarm(alarmPos);
          }else{                                          // not possible
            tft.reset();
            tft.fillRoundRect( 385,10, 8, 220,2, RED);
            delay(100);
            tft.fillRoundRect( 385,10, 8, 220,2, GREY);
          }
  //************************************************************************************* active       
        }else if(xpos>320){
          for(int j=0;j<4;j++){
            if(ypos>4+60*j && ypos<(4+60*(j+1)) && alarmPos+j<nbAlarm){
              tft.reset();  
              if(stats[alarmPos+j]=="1"){
                stats[alarmPos+j]="0";
                tft.fillRoundRect( 320,(j)*60+4, 50, 50,8, RED);
              }else{
                stats[alarmPos+j]="1";
                tft.fillRoundRect( 320,(j)*60+4, 50, 50,8, GREEN);
              }
              DateTime now = RTC.now();
              modDate[alarmPos+j]=String(now.day())+"-"+String(now.month())+"-"+String(now.year());
              modifAlarm=1;
            }
          }   
  //************************************************************************************* Modify
        }else{
          for(int j=0;j<4;j++){
            if(ypos>4+60*j && ypos<(4+60*(j+1)) && alarmPos+j<nbAlarm){
              for(int i=0;i<7;i++){
                Mode=2;
                modifAlarmId = alarmPos+j;
              }
            }
          }
        }
    }
  }
}

//********************************************************************************************
//                                    displayModifAlarm
//********************************************************************************************

String recurenceModifAlarm, modModifAlarm;
int hourModifAlarm, minModifAlarm, timeSelectModifAlarm;

void displayModifAlarm(){

  if(modifAlarmId==nbAlarm){
    recurenceModifAlarm="0000000", modModifAlarm=modChoiseAlarm[0];
    hourModifAlarm=minModifAlarm=0;
  }else{
    recurenceModifAlarm=repeter[modifAlarmId], modModifAlarm=action[modifAlarmId];
    hourModifAlarm=heure[modifAlarmId].substring(0, 2).toInt(), minModifAlarm=heure[modifAlarmId].substring(3, 5).toInt();
  }
    tft.reset();  
    tft.fillScreen(BLACK);
    tft.setRotation(1);
  
    tft.setTextColor(color2);                   // display title
    tft.setTextSize(1);
    tft.setCursor(10, 20);
    if(modifAlarmId==nbAlarm){
      tft.print("Nouvelle alarme :");  
    }else{
      tft.print("Modifier l'alarme ");
      tft.print(modifAlarmId+1);
      tft.print(" :");
    
      tft.fillRoundRect( 295,3, 85, 30,8, GREY);  // bp remove
      tft.setCursor(310, 23);
      tft.print("Suppr");
    }  
    tft.setCursor(27, 60);                        // choose days
    for(int j=0;j<7;j++){
      if(recurenceModifAlarm[j]=='1')
        tft.setTextColor(GREEN);
      else
        tft.setTextColor(RED);
      tft.print(Day[j]+"  ");
    }
    for(int j=0;j<3;j++){                           // choose mode
      tft.setCursor(0, 110+j*30);
      if(modModifAlarm==modChoiseAlarm[j])
        tft.setTextColor(GREEN);
      else
        tft.setTextColor(RED);
      tft.print(modChoiseAlarm[j]);
    }
    tft.setFont(&FreeSerif12pt7b);                  // bp add
    tft.setTextColor(color1);
    tft.setTextSize(3);     
    tft.fillCircle(390, 140, 40, GREY);
    tft.setCursor(360, 155);
    tft.print("+");
    tft.setTextSize(1);

    tft.setFont(&FreeSerif24pt7b);                  // time display
    tft.setTextSize(2);
    tft.setRotation(1);
    tft.setTextColor(color1);
    tft.setCursor(200, 170);
    tft.print(":");
    timeSelectModifAlarm=1;
    setTimeModifAlarm();
    timeSelectModifAlarm=0;
    setTimeModifAlarm();

    previousMillis = millis();
  while(Mode==2){ 

    currentMillis = millis();                                 // wait 30 sec befor get next time
    if (currentMillis - previousMillis >= 30000)
      Mode=0;

    
    tp = ts.getPoint();   //tp.x, tp.y are ADC values
    if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE) {
        if (SwapXY != (Orientation & 1)) SWAP(tp.x, tp.y);
        xpos = map(tp.x, TS_LEFT, TS_RT, tft.width(), 0);
        ypos = map(tp.y, TS_TOP, TS_BOT, tft.height(), 0);
        // Serial.print(xpos);      Serial.print(" - ");      Serial.println(ypos);
        previousMillis = millis();
          
  //************************************************************************************* remove
        if(ypos<30 && xpos>310){                    
          tft.reset();  
          tft.fillScreen(BLACK);                              // screen yes/no remove
          tft.setTextColor(color1);
          tft.setCursor(100, 40);
          tft.print("Voulez-vous vraiment");
          tft.setCursor(90, 65);
          tft.print("supprimer cette alarme?");
          tft.fillRoundRect( 40,100, 125, 100,20, RED);
          tft.fillRoundRect( 230,100, 125, 100,20, GREEN);
          tft.setFont(&FreeSerif24pt7b);
          tft.setTextSize(1);
          tft.setCursor(60, 160);
          tft.print("Non");
          tft.setCursor(255, 160);
          tft.print("Oui");
          tft.setTextColor(color1);
          tft.setFont(&FreeSerif12pt7b);
          
          Mode=100;
          while(Mode==100){
            tp = ts.getPoint();   //tp.x, tp.y are ADC values
            if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE) {
              if (SwapXY != (Orientation & 1)) SWAP(tp.x, tp.y);
              xpos = map(tp.x, TS_LEFT, TS_RT, tft.width(), 0);
              ypos = map(tp.y, TS_TOP, TS_BOT, tft.height(), 0);
              //Serial.print(xpos);      Serial.print(" - ");      Serial.println(ypos);
              if(xpos>200){
                removeAlarm(modifAlarmId);
              }
              Mode=3;
              alarmPos=modifAlarmId-3;
              if(alarmPos<0)
                alarmPos=0;
            }  
          }
  //************************************************************************************* date           
        }else if(ypos>30 && ypos<60){
          for(int i=0;i<7;i++){
            if(xpos>datePos[i] && xpos<datePos[i+1]){
  
                if(recurenceModifAlarm[i]=='1')
                  recurenceModifAlarm[i]='0';
                else
                  recurenceModifAlarm[i]='1';
                tft.reset();
                tft.setCursor(27, 60);
                for(int e=0;e<7;e++){
                  if(recurenceModifAlarm[e]=='1')
                    tft.setTextColor(GREEN);
                  else
                    tft.setTextColor(RED);
                  tft.print(Day[e]+"  ");
                }
                break;
            }
          }
  //************************************************************************************* change hour and mode           
        }else if(ypos>100 && ypos<190){

          if( xpos<80 ){                          // choose mode
            for(int j=0;j<3;j++){
              tft.reset();
              tft.setCursor(0, 110+j*30);
              if( ypos>110+j*30-10 && ypos<110+j*30+20 ){ 
                tft.setTextColor(GREEN);
                modModifAlarm=modChoiseAlarm[j];
              }else{
                tft.setTextColor(RED);
              }
              tft.print(modChoiseAlarm[j]);
            }
          }else if( xpos<202 ){                     // choose min
            timeSelectModifAlarm=0;
            setTimeModifAlarm();
          }else if(xpos>202 && xpos<315 ){
            timeSelectModifAlarm=1;
            setTimeModifAlarm();
          }else if(xpos>315 ){
            addModifAlarm();
          }
        }else if(ypos>195){                         // change hour
          if(!timeSelectModifAlarm){
            hourModifAlarm= (10+xpos)*23/380;
            if(hourModifAlarm>23 || hourModifAlarm<0)
              hourModifAlarm=0;
          }else{
            minModifAlarm= (10+xpos)*60/370-4;
            if(minModifAlarm>59 || minModifAlarm<0)
              minModifAlarm=0;
          }
          setTimeModifAlarm();  
        }
    }
  }
}

void setTimeModifAlarm(){

  tft.reset();
  tft.setFont(&FreeSerif24pt7b);
  tft.setTextSize(2);
  tft.setRotation(1);
  tft.setTextColor(color1);

  if(!timeSelectModifAlarm){
    tft.fillRect( 105,100, 95, 80, BLACK);
    tft.setCursor(105, 170);
    if(hourModifAlarm<10)
      tft.print("0");
    tft.print(hourModifAlarm);
  }else{
    tft.fillRect( 230,100, 95, 80, BLACK);
    tft.setCursor(230, 170);
    if(minModifAlarm<10)
      tft.print("0");
    tft.print(minModifAlarm);
  }
  tft.setFont(&FreeSerif12pt7b);
  tft.setTextSize(1);
}

void addModifAlarm(){

    String h="";
    if(hourModifAlarm<10)
      h="0"+String(hourModifAlarm);
    else
      h=String(hourModifAlarm);
    if(minModifAlarm<10)
      h+=":0"+String(minModifAlarm);
    else
      h+=":"+String(minModifAlarm);
      
    action[modifAlarmId]=modModifAlarm;
    repeter[modifAlarmId]= recurenceModifAlarm;
    heure[modifAlarmId]= h;
    stats[modifAlarmId]= 1;
    if(modifAlarmId==nbAlarm){
      appareil[modifAlarmId]="";
      cmd[modifAlarmId]="";
    }
    DateTime now = RTC.now();
    modDate[modifAlarmId]=String(now.day())+"-"+String(now.month())+"-"+String(now.year());

    if(modifAlarmId==nbAlarm)
      nbAlarm+=1;
    modifAlarm=1;

  Mode=3;                                   // display
  alarmPos=modifAlarmId-2;
  if(alarmPos<0)
    alarmPos=0;
}

void removeAlarm(int alarm){
  
  for(i=alarm;i<nbAlarm;i++){
    action[i]=action[i+1];
    repeter[i]=repeter[i+1];
    heure[i]=heure[i+1];
    stats[i]=stats[i+1];
    appareil[i]=appareil[i+1];
    cmd[i]=cmd[i+1];
    modDate[i]=modDate[i+1];
  }
  nbAlarm--;
  modifAlarm=1;
}


