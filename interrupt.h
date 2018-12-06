
void serialEvent1Alarms() {
  if (Serial1.available()) {
    message = Serial1.readString();
    //Serial1.println(message);

    if(message.equals("CAPTCLOCK")){

      h = dht.readHumidity();
      t = dht.readTemperature();
      Serial1.print("{ \"BMPTemperature\":\"");
      Serial1.print(capteur.readTempC(), 2);
      Serial1.print("\",\"BMPPressure\":\"");
      Serial1.print(capteur.readFloatPressure()/10, 2);
      Serial1.print("\",\"BMPHumidity\":\"");
      Serial1.print(capteur.readFloatHumidity(), 2);
      float brightness=analogRead(photocellPin);
      Serial.print("\",\"Brightness\":\"");
      Serial.print( (brightness*100/1024) , 2);

      if (isnan(h) || isnan(t)) {
        Serial1.print("\",\"Humidity\":\"0.00\",\"Temperature\":\"0.00\" }");
      }else{
        Serial1.print("\",\"Humidity\":\""); 
        Serial1.print(h);
        Serial1.print("\",\"Temperature\":\""); 
        Serial1.print(t);
        Serial1.println("\"}");
      }
      
    }else if(message.equals("2OCLOCK")){

      DateTime now = RTC.now();
      RTC.adjust(DateTime(now.year(), now.month(), now.day(), 2, 0, 0));
      
    }else if(message=="GETALARMS"){         //******************************************** try get alarms
      if(globalModifAlarm==0){
        Serial1.println("NOALARMSCHANGE");
      }else{
        savePublishAlarms(0);
      }
    }else if(message.equals("GETALARMSOK")){ //******************************************** get ok
      Serial1.println("SENDALARMSOK");
      globalModifAlarm=0;
      
    }else if (message.substring(0, 11) == "{\"alarmes\":" or message.substring(0, 11) == "{ \"alarmes\""){ //***** try send

      char res = getJsonAlarm(message+'\0');
      if(nbAlarm==0){
        Serial1.println("NOALARMS");                    
        if(getSdAlarm("ALARMS.TXT")!=0){                // reset alarms
          if(getSdAlarm("SAVE.TXT")!=0){
              Serial1.println("GETALARMSERROR");
          }
        }
      }else if(res==0){
        savePublishAlarms(0);
        Mode=11;
      }else{
        Serial1.println("GETALARMSERROR");
        if(getSdAlarm("ALARMS.TXT")!=0){                // reset alarms
          if(getSdAlarm("SAVE.TXT")!=0){
              Serial1.println("GETALARMSERROR");
          }
        }
      }
    }else if(message.equals("SENDALARMSOK")){ //******************************************** send ok
      Serial1.println("GETALARMSOK");
      savePublishAlarms(1);
      globalModifAlarm=0;
    }
      //{"alarmes":[{"action":"sonnerie","repeter":"0000000","heure":"09:00","status":"1","appareil":"33","cmd":"On","modDate":""},{"action":"sonnerie","repeter":"0111110","heure":"08:30","status":"1","appareil":"","cmd":"","modDate":""},{"action":"sonnerie","repeter":"0111110","heure":"08:45","status":"1","appareil":"","cmd":"","modDate":""}]}
  }
}



void messageScreen(String msg, char type){    // type 0 for error, 1 for msg
  tft.reset();  
  tft.fillScreen(BLACK);  
  
  if(type==1)
    tft.drawBitmap(30,50,clockImg,64,64,RED);
  else
    tft.drawBitmap(30,50,warning,64,64,RED);
  
  tft.setCursor(110, 80);
  tft.setTextColor(color1);
  char n=0;
  for(int i=0;i<msg.length();i++){
     tft.print(msg[i]);
     if(msg[i]=='\n'){
      tft.setCursor(50, 140+n*25);
      n++;
     }
  }
  Mode=11;                      // 11-10 to return mode 0 display screen
  if(type==1){
    for(i=0;i<500;i++)
      delay(1000);
    tft.fillScreen(BLACK); 
  }else{
    while(Mode==11){
      delay(1000);
    }
  }
  
  
}



  
  
