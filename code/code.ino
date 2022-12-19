//#include <EEPROM.h>

#include <Adafruit_GFX.h>    // Core graphics library
//#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

#include <Fonts/FreeSerif12pt7b.h>  //font
#include <Fonts/FreeSerif24pt7b.h>
//#include <Fonts/Dmd13x20Clock.h>

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF945 //0xF800
#define	GREEN   0x3626 //0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GREY   0x52AA 
uint16_t g_identifier;

#define color1 0x0359
#define color2 0x7FF1
#define color3 0xFD00
#define color4 0xF806 // menu icon color

//************************************************************** TouchScreen conf
#include <TouchScreen.h>
#if defined(__SAM3X8E__)
#undef __FlashStringHelper::F(string_literal)
#define F(string_literal) string_literal
#endif

// most mcufriend shields use these pins and Portrait mode:
uint8_t YP = A1;  // must be an analog pin, use "An" notation!
uint8_t XM = A2;  // must be an analog pin, use "An" notation!
uint8_t YM = 7;   // can be a digital pin
uint8_t XP = 6;   // can be a digital pin
uint8_t SwapXY = 0;

uint16_t TS_LEFT = 900; // coordinates
uint16_t TS_RT  = 150;
uint16_t TS_TOP = 925;
uint16_t TS_BOT = 140;

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 260 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 260);
TSPoint tp;
#define MINPRESSURE 20
#define MAXPRESSURE 1000
#define SWAP(a, b) {uint16_t tmp = a; a = b; b = tmp;}

int16_t BOXSIZE;
int16_t PENRADIUS = 3;
uint16_t identifier, oldcolor, currentcolor;
uint8_t Orientation = 1;    //PORTRAIT
uint16_t xpos, ypos;  //screen coordinates

int lcdledPin = 12; 
/**************************************************************/
#include <SD.h>
File myFile;
/**************************************************************/
#include <Wire.h>
#include <RTClib.h>
RTC_DS1307 RTC;
/***************************************************************/
#include "SparkFunBME280.h" //Library allows either I2C or SPI, so include both.
#include "SPI.h"
BME280 capteur;
/***************************************************************/
#include "DHT.h"
#define DHTPIN 22     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
float h, t;
DHT dht(DHTPIN, DHTTYPE);
/***************************************************************/
int photocellReading, photocellPin = 8; // light
const byte PIN_BUZZER = 24;
/***************************************************************/
unsigned long previousMillis = 0, currentMillis;
#include <SoftwareSerial.h>
SoftwareSerial HC12(22, 23); // HC-12 TX Pin, HC-12 RX Pin
/***************************************************************/
#include <ArduinoJson.h>
StaticJsonDocument<200> doc;
JsonObject root;

//String json = "{\"alarmes\":[{\"action\": \"Musique\",\"repeter\": \"0111110\",\"heure\": \"08:30\",\"status\": \"1\",\"appareil\": \"33\",\"cmd\": \"\",\"modDate\":\"\"},{\"action\": \"Sonnerie\",\"repeter\": \"0111110\",\"heure\": \"08:45\",\"status\": \"1\",\"appareil\": \"33\",\"cmd\": \"\",\"modDate\":\"\"},{\"action\": \"Bip\",\"repeter\": \"1000000\",\"heure\": \"10:45\",\"status\": \"1\",\"appareil\": \"33\",\"cmd\": \"\",\"modDate\":\"\"}]}";
String action[30]={};
String repeter[30]={};
String heure[30]={};
String stats[30]={};
String appareil[30]={};
String cmd[30]={};
String modDate[30]={};
int nbAlarm=0;

String message;
int Min, Hour,Mode=0;
int i,j;

int modifAlarm=0,globalModifAlarm=1, modifAlarmId;
int nextAlarmHour, nextAlarmMin, nextAlarmDay, nextAlarmHourRep, nextAlarmMinRep,nextAlarmIdRep, nextAlarmId, nextAlarmActiveRep=0;

int disableNextAlarm = 0;

/***************************************************************/

String Day[7]={"Dim","Lun","Mar","Mer","Jeu","Ven","Sam"};
String longDay[8]={"Dimanche","Lundi","Mardi","Mercredi","Jeudi","Vendredi","Samedi"};
String Month[12]={"Janvier","Fevrier","Mars","Avril","Mai","Juin","Juillet","Aout","Septembre","Octobre","Novembre","decembre"};
String modChoiseAlarm[]={"Bip","Sonnerie","Musique"};

void setDate(int day);
void displaySelectDayScreen();

void serialEvent1Alarms();
void wakeUpNow();
void initTime();
void displayTemp();
void displayDate();
void tftLight();

void getNextAlarm(int h,int m,int d);
void alarmActive();
void alarmSing(String type);

void displayChoiseScreen();
void messageScreen(String msg, char type);
void changeClock();
void setModifTime();

char getSdAlarm(String alarmsFile);
char getJsonAlarm(String jsonStr);
char parseJsonAlarm(char *json);
void savePublishAlarms(int mod);
void displayAlarm(int Begin);

void displayModifAlarm();
void setTimeModifAlarm();
void addModifAlarm();
void removeAlarm(int alarm);

// songs
void beep(int note, int duree);
void Starwars();
void GameOfThrones();
void HappyBirthday();
void HarryPotter();
void Pirate();
void mario();
void McGyver();
void StarWars2();
void BonBruteTruand();
void IndianaJones();
void twentyCentFox();
void looney();
void Entertainement();
void BarbieGirl();
void Greensleaves();
void Bond();
void (*song[])(void)= {Starwars,GameOfThrones,HappyBirthday,HarryPotter,Pirate,mario,McGyver,StarWars2,BonBruteTruand,IndianaJones,twentyCentFox,looney,Entertainement,BarbieGirl,Greensleaves,Bond};

#include "icon.h"
#include "interrupt.h"
#include "alarms.h"
#include "func.h"
#include "music.h"

void setup(void) {
  Serial.begin(9600);
  //Serial.println(F("TFT LCD test"));
  //Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());
  uint16_t tmp;
  static uint16_t identifier;
  //    tft.reset();                //we can't read ID on 9341 until begin()
  g_identifier = tft.readID();
  switch (Orientation) {            // adjust for different aspects
      case 0:   break;              //no change,  calibrated for PORTRAIT
      case 1:   tmp = TS_RT,  TS_RT = TS_BOT, TS_BOT = TS_LEFT, TS_LEFT = TS_TOP, TS_TOP = tmp;  break;
      case 2:   SWAP(TS_LEFT, TS_RT);  SWAP(TS_TOP, TS_BOT); break;
      case 3:   tmp = TS_LEFT, TS_LEFT = TS_TOP, TS_TOP = TS_RT, TS_RT = TS_BOT, TS_BOT = tmp;  break;
  }
  //Serial.print("ID = 0x");  Serial.println(g_identifier, HEX);
  if (g_identifier == 0x00D3 || g_identifier == 0xD3D3) g_identifier = 0x9481; // write-only shield
  if (g_identifier == 0xFFFF) g_identifier = 0x9341; 
  ts = TouchScreen(XP, YP, XM, YM, 260); 
  tft.begin(0x65);                                      //to enable HX8352B driver code  
  tft.setRotation(Orientation);                         // lcd reset 
  tft.fillScreen(BLACK);
  tft.setFont(&FreeSerif12pt7b); 
  
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  pinMode(XP, OUTPUT);
  pinMode(YM, OUTPUT);

/************************************************************************************************************/
  if (!SD.begin(5)) {
    Serial.println("initialization SD failed!");
    messageScreen("initialization SD failed!",0);
  }
/************************************************************************************************************/
  Wire.begin();
  RTC.begin();
  // RTC.adjust(DateTime(__DATE__, __TIME__));  // set time to computer clock
/************************************************************************************************************/
  
  capteur.settings.commInterface = I2C_MODE;    // bmp180 captor configuration
  capteur.settings.I2CAddress = 0x76;
  capteur.settings.runMode = 3; 
  capteur.settings.tStandby = 0;
  capteur.settings.filter = 0;
  capteur.settings.tempOverSample = 1 ;
  capteur.settings.pressOverSample = 1;
  capteur.settings.humidOverSample = 1;
  delay(10);                                    // wait 2 ms
  capteur.begin();
  
  dht.begin();                                  // dht22 begin
  pinMode(lcdledPin, OUTPUT);
  digitalWrite(lcdledPin, HIGH);
/************************************************************************************************************/
  pinMode(PIN_BUZZER, OUTPUT);                  // play music with buzzer 
  tone(PIN_BUZZER, 940); 
  delay(10);
  noTone(PIN_BUZZER);
  randomSeed(analogRead(7));                    // init random to choose music
/************************************************************************************************************/
  pinMode(3, INPUT);
  pinMode(2, INPUT);
  attachInterrupt(1, wakeUpNow, HIGH);
  attachInterrupt(0, wakeUpNow, HIGH);

  tft.fillScreen(BLACK);
  savePublishAlarms(0);

  Mode=0;
  displaySelectDayScreen();
}
/************************************************************************************************************/
void loop(void) {
  Serial.println(Mode);

  if(Mode==0)
    initTime();
  if(Mode==1)
    displayChoiseScreen();
  if(Mode==2)
    displayModifAlarm();
  if(Mode==3)
    displayAlarm(alarmPos);
  if(Mode==4)
    changeClock();

  if(Mode>9){
    Mode-=10;
    if(Mode==1)
      Mode=0;
    else
      Mode=1;
    digitalWrite(lcdledPin, 1);
  }
    
}
int bp=0;
void wakeUpNow() {

  bp++;
  if(bp%2){
    if(nextAlarmActiveRep){
      nextAlarmActiveRep=0;
      tft.reset();
      tft.drawBitmap(20,10,notification,32,32,YELLOW);
      messageScreen("Alarme Desactive",1);
      Mode=0;
    }else{
      if(Mode==1){
        Mode=0;
      }else if(Mode!=0){
        Mode=1;
      }else if(Mode==0){
        Mode=1;
      }
      delay(1000);
    }
  }

}
