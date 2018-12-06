
//********************************************************************************************
//                                    display time
//********************************************************************************************

void initTime(){
  
  tft.reset();                                            // get time
  tft.fillScreen(BLACK);
  tft.setTextColor(color2);
  DateTime now = RTC.now();
  Min=now.minute();
  Hour=now.hour();

  tft.setTextSize(1);                                   // set date
  tft.setCursor(100, 230);
  tft.print( longDay[now.dayOfWeek()]+" "+now.day()+" "+Month[now.month()-1] );
  
  tft.setFont(&FreeSerif24pt7b);                        // display date
  tft.setTextSize(3);
  tft.setRotation(1);
  tft.setTextColor(color1);   
  tft.setCursor(40, 140);
  tft.fillRect(40, 40, 174, 120, BLACK);
  if(Hour<10)
    tft.print(" ");
  tft.print(Hour);
  tft.setCursor(180, 130);
  tft.print(":");
  tft.setCursor(215, 140);
  if(Min<10)
    tft.print("0");
  tft.print(Min);
  tft.setFont(&FreeSerif12pt7b);
  tft.setTextColor(color2);
  tft.setTextSize(1);
  
  displayTemp();                                      // display temp, get good lum and get next alarms
  tftLight();
  getNextAlarm(Hour,Min,now.dayOfWeek());

  if(modifAlarm==1){                                        // update if alarms modified
    savePublishAlarms(1);
    Mode=modifAlarm=0;
    globalModifAlarm=1;
  }

//******************************************************************************************************** time

  currentMillis = millis();
  previousMillis = currentMillis - now.second()*1000;
  while(Mode==0){

    serialEvent1Alarms();

    currentMillis = millis();                                             // wait 59 sec befor get next time
    //Serial.println(currentMillis - previousMillis);
    if (currentMillis - previousMillis >= 59000) {
      delay(500);
      DateTime now = RTC.now();

      if(now.minute()!=Min){                                              // if minute change
        previousMillis = currentMillis;
    
        Min=now.minute();
        tft.setRotation(1);
        tft.setFont(&FreeSerif24pt7b);
        tft.setTextSize(3);
        tft.setTextColor(color1);
        
        if(now.hour()!=Hour){
          if(Hour==0){
            tft.fillScreen(BLACK);
            tft.setFont(&FreeSerif12pt7b);
            tft.setTextColor(color2);
            tft.setTextSize(1);
            tft.setCursor(100, 220);
            tft.print( longDay[now.dayOfWeek()]+" "+now.day()+" "+Month[now.month()-1] );
            
            getNextAlarm(Hour,Min,now.dayOfWeek());
            
            tft.setFont(&FreeSerif24pt7b);
            tft.setTextSize(3);
            tft.setTextColor(color1);
          }
          Hour=now.hour();   
          tft.setCursor(40, 140);
          tft.fillRect(40, 40, 174, 120, BLACK);
          if(Hour<10)
            tft.print(" ");
          tft.print(Hour);
          tft.setCursor(180, 130);
          tft.print(":");
        }
        int unit = Min % 10;
        if(unit==0){
          tft.fillRect(215, 40, 140, 120, BLACK);
          tft.setCursor(215, 140);
          if(Min<10)
            tft.print("0");
          tft.print(Min);
          
        }else{
          tft.fillRect(285, 40, 75, 110, BLACK);
          tft.setCursor(285, 140);
          tft.print(unit);
        }
        tft.setFont(&FreeSerif12pt7b);
        tft.setTextColor(color2);
        tft.setTextSize(1);
      
        if(unit%5)
          displayTemp();
        tftLight();
        
        if(nextAlarmDay == now.dayOfWeek() && nextAlarmHour == Hour && nextAlarmMin == Min ){     // check alarm
          
          for(i=0;i<7;i++){                                                                       // check if alarm recurrence
            if(repeter[nextAlarmId][i]=='1')
              i=10;
          }
          if(i==7){                                                                               // disable alarm
            stats[nextAlarmId]="0";
            savePublishAlarms(1);
          }
      
          nextAlarmMinRep=nextAlarmMin;                                                           // push alarm in repeat alarm
          nextAlarmHourRep=nextAlarmHour;
          nextAlarmIdRep=nextAlarmId;
          nextAlarmActiveRep=1;
    
          getNextAlarm(Hour,Min,now.dayOfWeek());                                                 // get next alarm
          tft.drawBitmap(20,10,notification,32,32,YELLOW);                                        // notify the alarm is active
        }
        if(nextAlarmActiveRep>0 && nextAlarmHourRep == Hour && nextAlarmMinRep == Min ){  
          
          nextAlarmActiveRep++;                                                                   // repeat 5 time
          if(nextAlarmActiveRep>=5){
            nextAlarmActiveRep=0;
            tft.drawBitmap(20,10,notification,32,32,RED);
          }
            
          nextAlarmMinRep+=5;                                                                     // set 5 miute after for repeat alarm
          if(nextAlarmMinRep>59){
            nextAlarmHourRep++;
            if(nextAlarmHourRep>11)
              nextAlarmActiveRep=0;
            nextAlarmMinRep-=60;
          }     
          alarmSing(action[nextAlarmIdRep]);                                                      // sing alarm
        }
        
      }
    }
  }
}
//******************************************************************************************************** temp

void displayTemp(){
  
  h = dht.readHumidity();
  t = dht.readTemperature();

  tft.fillRect(20, 175, 360, 25, BLACK);
  tft.setTextSize(1);
  tft.setCursor(50, 195);
  tft.print(t,1); // tft.print(capteur.readTempC(), 2);
  tft.print("*C       ");
  tft.print(capteur.readFloatPressure()/100, 1);
  tft.print("Pa       ");
  tft.print(h,1);
  tft.print("%");
}

void tftLight(){
  photocellReading = analogRead(photocellPin);
  //Serial.println(photocellReading);
  if (photocellReading < 10) {
    analogWrite(lcdledPin, 1);
  } else if (photocellReading < 100) {
    analogWrite(lcdledPin, 40);  
  } else if (photocellReading < 100) {
    analogWrite(lcdledPin, 80); 
  } else if (photocellReading < 300) {
    //analogWrite(lcdledPin, 150); 
    digitalWrite(lcdledPin,1);
  } else {
    digitalWrite(lcdledPin,1);
  }
}

//********************************************************************************************
//                                    sing alarm
//******************************************************************************************** 

#define  C     261    // 261 Hz 
#define  D     294    // 294 Hz 
#define  E     329    // 329 Hz 
#define  F     349    // 349 Hz 
#define  G     392    // 392 Hz 
#define  A     440    // 440 Hz 
#define  B     493    // 493 Hz 
#define  CC     523    // 523 Hz 
int bip[] = {C,D,E,F,G,A,B,CC,0};

void alarmSing(String type){

  if(type=="Sonnerie"){
    i = random(16);
    song[i]();
    
  }else if(type=="Musique"){

    Serial1.println("ALARMMUSIC");
    int i = 0;
    tone(PIN_BUZZER, bip[i],150);
    delay(150);
    while (bip[i] != 0){
      tone(PIN_BUZZER, bip[i],150);
      delay(90);
      noTone(PIN_BUZZER);
      i++;
    }
  }else{ //bip
    int i = 0;
    tone(PIN_BUZZER, bip[i],150);
    delay(150);
    while (bip[i] != 0){
      tone(PIN_BUZZER, bip[i],150);
      delay(90);
      noTone(PIN_BUZZER);
      i++;
    }
  }
}
//********************************************************************************************
//                                    Choise Screen
//********************************************************************************************

void displayChoiseScreen(){

  alarmPos=0;
  tft.reset();
  tft.fillScreen(BLACK);
  tft.setTextColor(color1);
  tft.fillScreen(BLACK);
  //tft.fillRect(25, 40, 100, 120, color1);
  tft.fillRoundRect(25, 40, 100, 120,20, GREY);
  tft.setCursor(15, 190);
  tft.print("Ajouter une");
  tft.setCursor(32, 215);
  tft.print("Alarmes");
  
  tft.fillRoundRect(150, 40, 100, 120,20, GREY);
  tft.setCursor(156, 190);
  tft.print("Afficher");
  tft.setCursor(142, 215);
  tft.print("les Alarmes");
  
  tft.fillRoundRect(275, 40, 100, 120,20, GREY);
  tft.setCursor(278, 190);
  tft.print("Modifier");
  tft.setCursor(288, 215);
  tft.print("l'heure");

  tft.drawBitmap(45,70,alarm,64,64,color4);
  tft.drawBitmap(172,70,event,64,64,color4);
  tft.drawBitmap(293,70,clockImg,64,64,color4);

  previousMillis = millis();
  while(Mode==1){
    currentMillis = millis();
    if (currentMillis - previousMillis >= 8000) {
      //previousMillis = currentMillis;
      Mode=0;  
    }    
    tp = ts.getPoint();   //tp.x, tp.y are ADC values
    if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE) {
      if (SwapXY != (Orientation & 1)) SWAP(tp.x, tp.y);
      xpos = map(tp.x, TS_LEFT, TS_RT, tft.width(), 0);
      ypos = map(tp.y, TS_TOP, TS_BOT, tft.height(), 0);
      //Serial.print(xpos);      Serial.print(" - ");      Serial.println(ypos);

      if(xpos<134){
        modifAlarmId=nbAlarm;
        Mode=2;
        tft.reset();
      }else if(xpos<266){
        Mode=3;
        tft.reset();
      }else{
        Mode=4;
        tft.reset();
      }
    }
  }
}

//********************************************************************************************
//                                    change clock
//********************************************************************************************

int hourModif=0, minModif=0, timeSelectModif;
void changeClock(){

  DateTime now = RTC.now();
  minModif=now.minute();
  hourModif=now.hour();
  
  tft.reset();  
  tft.fillScreen(BLACK);
  tft.setRotation(1);

  tft.setTextColor(color2);
  tft.setTextSize(1);
  tft.setCursor(10, 25);
  tft.print("Changer l'heure :"); 
  tft.setTextColor(RED); 
  tft.setCursor(85, 60);
  tft.print( longDay[now.dayOfWeek()]+" "+now.day()+" "+Month[now.month()-1] );
  
  tft.setFont(&FreeSerif24pt7b);
  tft.setTextSize(2);
  tft.setRotation(1);
  tft.setTextColor(color1);
  tft.setCursor(170, 150);
  tft.print(":");
  timeSelectModif=1;
  setModifTime();
  timeSelectModif=0;
  setModifTime();

  tft.setFont(&FreeSerif12pt7b);
  tft.setTextSize(3);
  tft.fillCircle(390, 120, 40, GREY);
  tft.setCursor(360, 135);
  tft.print("+");
  tft.setTextSize(1);

  previousMillis = millis(); 

  while(Mode==4){

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
        
  //************************************************************************************* change hour            
        if(ypos>100 && ypos<192){
          if(xpos>70 && xpos<192 ){  // choose min or hour
            timeSelectModif=0;
            setModifTime();
          }else if(xpos>192 && xpos<315 ){
            timeSelectModif=1;
            setModifTime();
          }else if(xpos>315 ){
            
            DateTime now = RTC.now();
            RTC.adjust(DateTime(now.year(), now.month(), now.day(), hourModif, minModif, 0));  
            Mode=0;
          }
        }else if(ypos>195){  // change hour
          if(!timeSelectModif){
            hourModif= (10+xpos)*23/380;
            if(hourModif>23 || hourModif<0)
              hourModif=0;
          }else{
            minModif= (10+xpos)*60/370-4;
            if(minModif>59 || minModif<0)
              minModif=0;
          }
          setModifTime();  
        }
    }
  }
}
//******************************************************************************************************** set time

void setModifTime(){
  tft.reset();
  tft.setFont(&FreeSerif24pt7b);
  tft.setTextSize(2);
  tft.setRotation(1);
  tft.setTextColor(color1);

  if(!timeSelectModif){
    tft.fillRect( 75,80, 95, 80, BLACK);
    tft.setCursor(75, 150);
    if(hourModif<10)
      tft.print("0");
    tft.print(hourModif);
  }else{
    tft.fillRect( 200,80, 95, 80, BLACK);
    tft.setCursor(200, 150);
    if(minModif<10)
      tft.print("0");
    tft.print(minModif);
  }
  tft.setFont(&FreeSerif12pt7b);
  tft.setTextSize(1);
}


