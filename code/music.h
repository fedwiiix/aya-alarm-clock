// Les notes de musique 
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS  455
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GSH  830
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

#define piezzo PIN_BUZZER // Le buzzer sur le Pin D2

// Le compteur pour la fonction beep
int compteur = 0;

void beep(int note, int duree)
{
  // chante
  tone(piezzo, note, duree);
  delay(duree);
  noTone(piezzo); 
  delay(50); 
  compteur++;
}

void firstSection()
{
  beep(NOTE_A4, 500);
  beep(NOTE_A4, 500);    
  beep(NOTE_A4, 500);
  beep(NOTE_F4, 350);
  beep(NOTE_C5, 150);  
  beep(NOTE_A4, 500);
  beep(NOTE_F4, 350);
  beep(NOTE_C5, 150);
  beep(NOTE_A4, 650); 
  delay(500); 
  beep(NOTE_E5, 500);
  beep(NOTE_E5, 500);
  beep(NOTE_E5, 500);  
  beep(NOTE_F5, 350);
  beep(NOTE_C5, 150);
  beep(NOTE_GS4, 500);
  beep(NOTE_F4, 350);
  beep(NOTE_C5, 150);
  beep(NOTE_A4, 650); 
  delay(500);
}
 
void secondSection()
{
  beep(NOTE_A5, 500);
  beep(NOTE_A4, 300);
  beep(NOTE_A4, 150);
  beep(NOTE_A5, 500);
  beep(NOTE_GSH, 325);
  beep(NOTE_G5, 175);
  beep(NOTE_FS5, 125);
  beep(NOTE_F5, 125);    
  beep(NOTE_FS5, 250); 
  delay(325); 
  beep(NOTE_AS, 250);
  beep(NOTE_DS5, 500);
  beep(NOTE_D5, 325);  
  beep(NOTE_CS5, 175);  
  beep(NOTE_C5, 125);  
  beep(NOTE_AS4, 125);  
  beep(NOTE_C5, 250);   
  delay(350);
}

void Starwars() 
{    
  firstSection();  
  secondSection(); 
  //Variant 1
  beep(NOTE_F4, 250);  
  beep(NOTE_GS4, 500);  
  beep(NOTE_F4, 350);  
  beep(NOTE_A4, 125);
  beep(NOTE_C5, 500);
  beep(NOTE_A4, 375);  
  beep(NOTE_C5, 125);
  beep(NOTE_E5, 650); 
  delay(500);  
  secondSection(); 
  //Variant 2
  beep(NOTE_F4, 250);  
  beep(NOTE_GS4, 500);  
  beep(NOTE_F4, 375);  
  beep(NOTE_C5, 125);
  beep(NOTE_A4, 500);  
  beep(NOTE_F4, 375);  
  beep(NOTE_C5, 125);
  beep(NOTE_A4, 650); 
  delay(650);
  compteur = 0;
}

//******* GameOfThrones ****************
void GameOfThrones()
  {
    for(int i=0; i<3; i++)
    {
    beep(NOTE_G4, 500);     
    beep(NOTE_C4, 500);    
    beep(NOTE_DS4, 250);    
    beep(NOTE_F4, 250);    
    }
    for(int i=0; i<3; i++)
    {
    beep(NOTE_G4, 500);    
    beep(NOTE_C4, 500);    
    beep(NOTE_E4, 250);    
    beep(NOTE_F4, 250);    
    }
        beep(NOTE_G4, 500);
        beep(NOTE_C4, 500);        
        beep(NOTE_DS4, 250);
        beep(NOTE_F4, 250);
        beep(NOTE_D4, 500);        
    for(int i=0; i<2; i++)
    {
    beep(NOTE_G3, 500);
    beep(NOTE_AS3, 250);
    beep(NOTE_C4, 250);
    beep(NOTE_D4, 500);    
    }//
        beep(NOTE_G3, 500);
        beep(NOTE_AS3, 250);
        beep(NOTE_C4, 250);
        beep(NOTE_D4, 1000);
        beep(NOTE_F4, 1000);
        beep(NOTE_AS3, 1000);
        beep(NOTE_DS4, 250);
        beep(NOTE_D4, 250);
        beep(NOTE_F4, 1000);
        beep(NOTE_AS3, 1000);
        beep(NOTE_DS4, 250);
        beep(NOTE_D4, 250);
        beep(NOTE_C4, 500);
    for(int i=0; i<2; i++)
    {
    beep(NOTE_GS3, 250);
    beep(NOTE_AS3, 250);
    beep(NOTE_C4, 500);
    beep(NOTE_F3, 500);    
    }
          beep(NOTE_G4, 1000);
          beep(NOTE_C4, 1000);
          beep(NOTE_DS4, 250);
          beep(NOTE_F4, 250);
          beep(NOTE_G4, 1000);
          beep(NOTE_C4, 1000);
          beep(NOTE_DS4, 250);
          beep(NOTE_F4, 250);
          beep(NOTE_D4, 500);          
    for(int i=0; i<3; i++)
    {
    beep(NOTE_G3, 500);
    beep(NOTE_AS3, 250);
    beep(NOTE_C4, 250);
    beep(NOTE_D4, 500);
    }
  compteur = 0;
}


//******* Happy Birthday ****************
void HappyBirthday()
{
  beep(NOTE_G3, 200);
  beep(NOTE_G3, 200);
  beep(NOTE_A3, 500);
  beep(NOTE_G3, 500);
  beep(NOTE_C4, 500);
  beep(NOTE_B3, 1000);
  beep(NOTE_G3, 200);
  beep(NOTE_G3, 200);
  beep(NOTE_A3, 500);
  beep(NOTE_G3, 500);
  beep(NOTE_D4, 500);
  beep(NOTE_C4, 1000);
  beep(NOTE_G3, 200);
  beep(NOTE_G3, 200);
  beep(NOTE_G4, 500);
  beep(NOTE_E4, 500);
  beep(NOTE_C4, 500);
  beep(NOTE_B3, 500);
  beep(NOTE_A3, 750);
  beep(NOTE_F4, 200);
  beep(NOTE_F4, 200);
  beep(NOTE_E4, 500);
  beep(NOTE_C4, 500);
  beep(NOTE_D4, 500);
  beep(NOTE_C4, 1000); 
  compteur = 0;
}


//******* Harry Potter ****************
void HarryPotter()
{
  beep(NOTE_B4, 333);  
  beep(NOTE_E5, 500);   
  beep(NOTE_G5, 166);    
  beep(NOTE_FS5, 333);    
  beep(NOTE_E5, 666);
  beep(NOTE_B5, 333);   
  beep(NOTE_A5, 1000);    
  beep(NOTE_FS5, 1000);    
  beep(NOTE_E5, 500);   
  beep(NOTE_G5, 166);    
  beep(NOTE_FS5, 333);    
  beep(NOTE_DS5, 666);    
  beep(NOTE_F5, 333);    
  beep(NOTE_B4, 1666);    
  beep(NOTE_B4, 333);    
  beep(NOTE_E5, 500);    
  beep(NOTE_G5, 166);    
  beep(NOTE_FS5, 333);    
  beep(NOTE_E5, 666);    
  beep(NOTE_B5, 333);    
  beep(NOTE_D6, 666);    
  beep(NOTE_CS6, 333);    
  beep(NOTE_C6, 666);    
  beep(NOTE_GS5, 333);    
  beep(NOTE_C6, 500);    
  beep(NOTE_B5, 166);    
  beep(NOTE_AS5, 333); 
  beep(NOTE_AS4, 666);    
  beep(NOTE_G5, 333);    
  beep(NOTE_E5, 1666);    
  beep(NOTE_G5, 333);    
  beep(NOTE_B5, 666);    
  beep(NOTE_G5, 333);    
  beep(NOTE_B5, 666);    
  beep(NOTE_G5, 333);    
  beep(NOTE_C6, 666);    
  beep(NOTE_B5, 333);    
  beep(NOTE_AS5, 666);    
  beep(NOTE_FS5, 333);    
  beep(NOTE_G5, 500);    
  beep(NOTE_B5, 166);    
  beep(NOTE_AS5, 333);    
  beep(NOTE_AS4, 666);    
  beep(NOTE_B4, 333);    
  beep(NOTE_B5, 1666);    
  beep(NOTE_G5, 333);    
  beep(NOTE_B5, 666);    
  beep(NOTE_G5, 333);    
  beep(NOTE_B5, 666);    
  beep(NOTE_G5, 333);    
  beep(NOTE_D6, 666);    
  beep(NOTE_CS6, 333);    
  beep(NOTE_C6, 666);    
  beep(NOTE_GS5, 333);    
  beep(NOTE_C6, 500);    
  beep(NOTE_B5, 166);    
  beep(NOTE_AS5, 333);    
  beep(NOTE_AS4, 666);    
  beep(NOTE_G5, 333);    
  beep(NOTE_E5, 1666);    
  compteur = 0;
}


//******* Pirate des caraïbes ****************
void Pirate()
{  
  beep(NOTE_E4, 125);
  beep(NOTE_G4, 125);
  beep(NOTE_A4, 250);
  beep(NOTE_A4, 125);
  delay(50); 
  beep(NOTE_A4, 125);
  beep(NOTE_B4, 125); 
  beep(NOTE_C5, 250); 
  beep(NOTE_C5, 125);
  delay(50);
  beep(NOTE_C5, 125);
  beep(NOTE_D5, 125);
  beep(NOTE_B4, 250);
  beep(NOTE_B4, 125);
  delay(50);
  beep(NOTE_A4, 125);
  beep(NOTE_G4, 125);
  beep(NOTE_A4, 375);
  delay(50);  
  beep(NOTE_E4, 125);
  beep(NOTE_G4, 125);
  beep(NOTE_A4, 250);
  beep(NOTE_A4, 125);
  delay(50);
  beep(NOTE_A4, 125);
  beep(NOTE_B4, 125);
  beep(NOTE_C5, 250);
  beep(NOTE_C5, 125);
  delay(50);
  beep(NOTE_C5,125); 
  beep(NOTE_D5, 125);
  beep(NOTE_B4, 250);
  beep(NOTE_B4, 125);
  delay(50);
  beep(NOTE_A4, 125); 
  beep(NOTE_G4, 125);
  beep(NOTE_A4, 375);
  delay(50);    
  beep(NOTE_E4, 125);
  beep(NOTE_G4, 125);
  beep(NOTE_A4, 250);
  beep(NOTE_A4, 125);
  delay(50);
  beep(NOTE_A4, 125);
  beep(NOTE_C5, 125);
  beep(NOTE_D5, 250);
  beep(NOTE_D5, 125);
  delay(50);
  beep(NOTE_D5, 125); 
  beep(NOTE_E5, 125);
  beep(NOTE_F5,250);
  beep(NOTE_F5, 125);
  delay(50);
  beep(NOTE_E5, 125); 
  beep(NOTE_D5, 125);
  beep(NOTE_E5, 125);
  beep(NOTE_A4, 250);
  delay(50);  
  beep(NOTE_A4,125); 
  beep(NOTE_B4, 125);
  beep(NOTE_C5, 250);
  beep(NOTE_C5, 125);
  delay(50);
  beep(NOTE_D5, 250);
  beep(NOTE_E5, 125);
  beep(NOTE_A4, 250);
  delay(50);
  beep(NOTE_A4, 125);
  beep(NOTE_C5, 125);
  beep(NOTE_B4, 250);
  beep(NOTE_B4, 125);
  delay(50);
  beep(NOTE_C5, 125);
  beep(NOTE_A4, 125);
  beep(NOTE_B4, 375);
  delay(200);
  beep(NOTE_A4, 250); 
  beep(NOTE_A4, 125);     
  beep(NOTE_E4, 125);
  beep(NOTE_G4, 125);
  beep(NOTE_A4, 250);
  beep(NOTE_A4, 125);
  delay(50); 
  beep(NOTE_A4, 125);
  beep(NOTE_B4, 125); 
  beep(NOTE_C5, 250); 
  beep(NOTE_C5, 125);
  delay(50);
  beep(NOTE_C5, 125);
  beep(NOTE_D5, 125);
  beep(NOTE_B4, 250);
  beep(NOTE_B4, 125);
  delay(50);
  beep(NOTE_A4, 125);
  beep(NOTE_G4, 125);
  beep(NOTE_A4, 375);
  delay(50);  
  beep(NOTE_E4, 125);
  beep(NOTE_G4, 125);
  beep(NOTE_A4, 250);
  beep(NOTE_A4, 125);
  delay(50);
  beep(NOTE_A4, 125);
  beep(NOTE_B4, 125);
  beep(NOTE_C5, 250);
  beep(NOTE_C5, 125);
  delay(50);
  beep(NOTE_C5,125); 
  beep(NOTE_D5, 125);
  beep(NOTE_B4, 250);
  beep(NOTE_B4, 125);
  delay(50);
  beep(NOTE_A4, 125); 
  beep(NOTE_G4, 125);
  beep(NOTE_A4, 375);
  delay(50);    
  beep(NOTE_E4, 125);
  beep(NOTE_G4, 125);
  beep(NOTE_A4, 250);
  beep(NOTE_A4, 125);
  delay(50);
  beep(NOTE_A4, 125);
  beep(NOTE_C5, 125);
  beep(NOTE_D5, 250);
  beep(NOTE_D5, 125);
  delay(50);
  beep(NOTE_D5, 125); 
  beep(NOTE_E5, 125);
  beep(NOTE_F5, 250);
  beep(NOTE_F5, 125);
  delay(50);
  beep(NOTE_E5, 125); 
  beep(NOTE_D5, 125);
  beep(NOTE_E5, 125);
  beep(NOTE_A4, 250);
  delay(50);  
  beep(NOTE_A4,125); 
  beep(NOTE_B4, 125);
  beep(NOTE_C5, 250);
  beep(NOTE_C5, 125);
  delay(50);
  beep(NOTE_D5, 250);
  beep(NOTE_E5, 125);
  beep(NOTE_A4, 250);
  delay(50);
  beep(NOTE_A4, 125);
  beep(NOTE_C5, 125);
  beep(NOTE_B4, 250);
  beep(NOTE_B4, 125);
  delay(50);
  beep(NOTE_C5, 125);
  beep(NOTE_A4, 125);
  beep(NOTE_B4, 375);
  delay(200);
  beep(NOTE_E5, 250);
  delay(400);
  beep(NOTE_F5, 250);
  delay(400); 
  beep(NOTE_E5, 125);
  beep(NOTE_E5, 125);
  delay(50);
  beep(NOTE_G5, 125);
  delay(50);
  beep(NOTE_E5, 125);  
  beep(NOTE_D5, 125);
  delay(400);    
  beep(NOTE_D5, 250);
  delay(400);
  beep(NOTE_C5, 250);
  delay(400);  
  beep(NOTE_B4, 125);  
  beep(NOTE_C5, 125);
  delay(50);
  beep(NOTE_B4, 125);
  delay(50);
  beep(NOTE_A4,  500);    
  beep(NOTE_E5, 250);  
  delay(400);
  beep(NOTE_F5, 250);
  delay(400);    
  beep(NOTE_E5, 125);
  beep(NOTE_E5, 125);
  delay(50);
  beep(NOTE_G5, 125);
  delay(50);
  beep(NOTE_E5, 125);
  beep(NOTE_D5, 125);
  delay(400);  
  beep(NOTE_D5, 250);
  delay(400);
  beep(NOTE_C5, 250);
  delay(400);  
  beep(NOTE_B4, 125);
  beep(NOTE_C5, 125);
  delay(50);
  beep(NOTE_B4, 125);
  delay(50);
  beep(NOTE_A4, 500);
  compteur = 0;
}


//******* Mario ****************
void mario()
{
  beep(NOTE_E7, 120);
  beep(NOTE_E7, 120);
  delay(120);  
  beep(NOTE_E7, 120);
  delay(120);  
  beep(NOTE_C7, 120);
  beep(NOTE_E7, 120);
  delay(120);  
  beep(NOTE_G7, 120);
  delay(240);    
  beep(NOTE_G6, 120);
  delay(360); 
  beep(NOTE_C7, 120);
  delay(240); 
  beep(NOTE_G6, 120);
  delay(240);  
  beep(NOTE_E6, 120);
  delay(240);    
  beep(NOTE_A6, 120);
  delay(120);  
  beep(NOTE_B6, 120);
  delay(120);  
  beep(NOTE_AS6, 120);
  beep(NOTE_A6, 120);
  delay(120); 
  beep(NOTE_G6, 90);
  beep(NOTE_E7, 90);
  beep(NOTE_G7, 90);
  beep(NOTE_A7, 120);
  delay(120);  
  beep(NOTE_F7, 120);
  beep(NOTE_G7, 120);
  delay(120);  
  beep(NOTE_E7, 120);
  delay(120);  
  beep(NOTE_C7, 120);
  beep(NOTE_D7, 120);
  beep(NOTE_B6, 120);
  delay(240);  
  beep(NOTE_C7, 120);
  delay(240);  
  beep(NOTE_G6, 120);
  delay(240);    
  beep(NOTE_E6, 120);
  delay(240);     
  beep(NOTE_A6, 120);
  delay(120);  
  beep(NOTE_B6, 120);
  delay(120);  
  beep(NOTE_AS6, 120);
  beep(NOTE_A6, 120);
  delay(120); 
  beep(NOTE_G6, 90);
  beep(NOTE_E7, 90);
  beep(NOTE_G7, 90);
  beep(NOTE_A7, 120);
  delay(120);  
  beep(NOTE_F7, 120);
  beep(NOTE_G7, 120);
  delay(120);  
  beep(NOTE_E7, 120);
  delay(120);  
  beep(NOTE_C7, 120);
  beep(NOTE_D7, 120);
  beep(NOTE_B6, 120);
  delay(240);  
  beep(NOTE_C4, 120);
  beep(NOTE_C5, 120);
  beep(NOTE_A3, 120);
  beep(NOTE_A4, 120);
  beep(NOTE_AS3, 120);
  beep(NOTE_AS4, 120);
  delay(90);    
  beep(NOTE_C4, 120);
  beep(NOTE_C5, 120);
  beep(NOTE_A3, 120);
  beep(NOTE_A4, 120);
  beep(NOTE_AS3, 120);
  beep(NOTE_AS4, 120);
  delay(90);    
  beep(NOTE_F3, 120);
  beep(NOTE_F4, 120);
  beep(NOTE_D3, 120);
  beep(NOTE_D4, 120);
  beep(NOTE_DS3, 120);
  beep(NOTE_DS4, 120);
  delay(90);   
  beep(NOTE_F3, 120);
  beep(NOTE_F4, 120);
  beep(NOTE_D3, 120);
  beep(NOTE_D4, 120);
  beep(NOTE_DS3, 120);
  beep(NOTE_DS4, 120);
  delay(120);    
  beep(NOTE_DS4, 180);
  beep(NOTE_CS4, 180);
  beep(NOTE_D4, 180);
  beep(NOTE_CS4, 60);
  beep(NOTE_DS4, 60);
  beep(NOTE_DS4, 60);
  beep(NOTE_GS3, 60);
  beep(NOTE_G3, 60);
  beep(NOTE_CS4, 60);
  beep(NOTE_C4, 180);
  beep(NOTE_FS4, 180);
  beep(NOTE_F4, 180);
  beep(NOTE_E3, 180);
  beep(NOTE_AS4, 180);
  beep(NOTE_A4, 180);
  beep(NOTE_GS4, 100);
  beep(NOTE_DS4, 100);
  beep(NOTE_B3, 100);
  beep(NOTE_AS3, 100);
  beep(NOTE_A3, 100);
  beep(NOTE_GS3, 100);
  delay(90);  
  compteur = 0;
}

//******* McGyver ****************
void McGyver()
{
  beep(NOTE_B4, 200);
  beep(NOTE_E5, 200);
  beep(NOTE_A5, 200);
  beep(NOTE_B5, 200);
  beep(NOTE_A5, 400);
  beep(NOTE_E5, 200);
  beep(NOTE_B4, 200);
  delay(200);
  beep(NOTE_E5, 200);
  beep(NOTE_A5, 200);
  beep(NOTE_B5, 200);
  beep(NOTE_A5, 200);
  beep(NOTE_E5, 200);
  beep(NOTE_B4, 400);
  delay(200);
  beep(NOTE_E5, 200);
  beep(NOTE_A5, 200);
  beep(NOTE_B5, 200);
  beep(NOTE_A5, 400);
  beep(NOTE_E5, 200);
  beep(NOTE_B4, 200);
  delay(200);
  beep(NOTE_A5, 200);
  beep(NOTE_D6, 200);
  beep(NOTE_C6, 200);
  beep(NOTE_D6, 200);
  beep(NOTE_C6, 200);
  beep(NOTE_B5, 200);
  beep(NOTE_A5, 200);
  beep(NOTE_B4, 200);
  beep(NOTE_E5, 200);
  beep(NOTE_A5, 200);
  beep(NOTE_B5, 200);
  beep(NOTE_A5, 400);
  beep(NOTE_E5, 200);
  beep(NOTE_B4, 200);
  delay(200);
  beep(NOTE_E5, 200);
  beep(NOTE_A5, 200);
  beep(NOTE_B5, 200);
  beep(NOTE_A5, 200);
  beep(NOTE_E5, 200);
  beep(NOTE_B4, 400);
  delay(200);
  beep(NOTE_E5, 200);
  beep(NOTE_A5, 200);
  beep(NOTE_B5, 200);
  beep(NOTE_A5, 400);
  beep(NOTE_E5, 200);
  beep(NOTE_B4, 200);
  delay(200);
  beep(NOTE_A5, 200);
  beep(NOTE_D6, 200);
  beep(NOTE_C6, 200);
  beep(NOTE_D6, 200);
  beep(NOTE_C6, 200);
  beep(NOTE_B5, 200);
  beep(NOTE_A5, 200);
  beep(NOTE_B5, 400);
  delay(200);
  beep(NOTE_B5, 800);
  delay(200);
  beep(NOTE_B5, 400);
  delay(200);
  beep(NOTE_A5, 400);
  beep(NOTE_D6, 600);
  beep(NOTE_B5, 400);
  delay(200);
  beep(NOTE_B5, 800);
  delay(200);
  beep(NOTE_B5, 200);
  delay(200);
  beep(NOTE_A5, 800);
  delay(400);
  beep(NOTE_C6, 200);
  beep(NOTE_C6, 200);
  beep(NOTE_C6, 200);
  beep(NOTE_C6, 200);
  beep(NOTE_C6, 200);
  beep(NOTE_C6, 200);
  beep(NOTE_B5, 800);
  delay(100);
  beep(NOTE_FS5, 200);
  beep(NOTE_A5, 200);
  delay(200);
  beep(NOTE_G5, 800);
  delay(200);
  beep(NOTE_C6, 200);
  beep(NOTE_C6, 200);
  delay(200);
  beep(NOTE_B5, 400);
  beep(NOTE_A5, 200);
  beep(NOTE_B5, 200);
  beep(NOTE_A5, 200);
  beep(NOTE_G5, 200);
  delay(200);
  beep(NOTE_E6, 400);
  beep(NOTE_A5, 800);
  delay(100);
  beep(NOTE_C6, 200);
  beep(NOTE_C6, 200);
  delay(200);
  beep(NOTE_B5, 800);
  delay(200);
  beep(NOTE_FS5, 200);
  beep(NOTE_A5, 200);
  delay(200);
  beep(NOTE_G5, 800);
  delay(200);
  beep(NOTE_C6, 200);
  beep(NOTE_C6, 200);
  delay(200);
  beep(NOTE_B5, 400);
  beep(NOTE_A5, 200);
  beep(NOTE_B5, 200);
  beep(NOTE_A5, 200);
  beep(NOTE_G5, 200);
  delay(200);
  beep(NOTE_E6, 400);
  beep(NOTE_A5, 800);
  beep(NOTE_B5, 800);
  delay(50);
  beep(NOTE_C6, 200);
  beep(NOTE_B5, 200);
  beep(NOTE_A5, 200);
  beep(NOTE_C6, 400);
  beep(NOTE_B5, 200);
  beep(NOTE_A5, 200);
  beep(NOTE_D6, 200);
  beep(NOTE_C6, 200);
  beep(NOTE_B5, 200);
  beep(NOTE_D6, 400);
  beep(NOTE_C6, 200);
  beep(NOTE_B5, 200);
  beep(NOTE_E6, 400);
  beep(NOTE_D6, 200);
  beep(NOTE_E6, 200);
  beep(NOTE_FS6, 400);
  beep(NOTE_B5, 400);
  beep(NOTE_G6, 400);
  delay(200);
  beep(NOTE_FS6, 400);
  beep(NOTE_F6, 400);
  beep(NOTE_B5, 400);
  beep(NOTE_G6, 200);
  beep(NOTE_E6, 200);
  beep(NOTE_B5, 200);
  beep(NOTE_FS6, 200);
  beep(NOTE_D6, 200);
  beep(NOTE_A5, 200);
  beep(NOTE_E6, 200);
  beep(NOTE_C6, 200);
  beep(NOTE_G5, 200);
  beep(NOTE_D6, 200);
  beep(NOTE_B5, 200);
  beep(NOTE_G5, 200);
  beep(NOTE_C6, 200);
  beep(NOTE_E5, 200);
  beep(NOTE_B5, 200);
  beep(NOTE_D5, 200);
  beep(NOTE_C6, 200);
  beep(NOTE_B5, 200);
  beep(NOTE_A5, 200);
  beep(NOTE_G5, 200);
  beep(NOTE_AS5, 400);
  beep(NOTE_A5, 400);
  beep(NOTE_G6, 200);
  beep(NOTE_G5, 200);
  beep(NOTE_D6, 200);
  beep(NOTE_G5, 200);
  beep(NOTE_DS6, 200);
  beep(NOTE_DS5, 200);
  beep(NOTE_AS5, 200);
  beep(NOTE_A5, 200);
  beep(NOTE_G5, 200);
  beep(NOTE_G4, 200);
  beep(NOTE_D5, 200);
  beep(NOTE_G4, 200);
  beep(NOTE_DS5, 200);
  beep(NOTE_G4, 200);
  beep(NOTE_AS4, 200);
  beep(NOTE_A4, 200);
  beep(NOTE_G4, 200);
  beep(NOTE_G4, 200);
  beep(NOTE_G4, 200);
  beep(NOTE_G4, 200);
  beep(NOTE_G4, 200);
  beep(NOTE_G4, 200);
  beep(NOTE_G4, 200);
  delay(200);
  compteur = 0;
}


//******* IndianaJones ****************
void IndianaJones()
{
  beep(NOTE_E5, 240);
  delay(120);
  beep(NOTE_F5, 120);
  beep(NOTE_G5, 120);
  delay(120);
  beep(NOTE_C6, 960);
  delay(180);
  beep(NOTE_D5, 240);
  delay(120);
  beep(NOTE_E5, 120);
  beep(NOTE_F5, 960);
  delay(360);
  beep(NOTE_G5, 240);
  delay(120);
  beep(NOTE_A5, 120);
  beep(NOTE_B5, 120);
  delay(120);
  beep(NOTE_F6, 960);
  delay(240);
  beep(NOTE_A5, 240);
  delay(120);
  beep(NOTE_B5, 120);
  beep(NOTE_C6, 480);
  beep(NOTE_D6, 480);
  beep(NOTE_E6, 480);
  beep(NOTE_E5, 240);
  delay(120);
  beep(NOTE_F5, 120);
  beep(NOTE_G5, 120);
  delay(120);
  beep(NOTE_C6, 960);
  delay(240);
  beep(NOTE_D6, 240);
  delay(120);
  beep(NOTE_E6, 120);
  beep(NOTE_F6, 1440);
  beep(NOTE_G5, 240);
  delay(120);
  beep(NOTE_G5, 120);
  beep(NOTE_E6, 360);
  delay(120);
  beep(NOTE_D6, 240);
  delay(120);
  beep(NOTE_G5, 120);
  beep(NOTE_E6, 360);
  delay(120);
  beep(NOTE_D6, 240);
  delay(120);
  beep(NOTE_G5, 120);
  beep(NOTE_F6, 360);
  delay(120);
  beep(NOTE_E6, 240);
  delay(120);
  beep(NOTE_D6, 120);
  beep(NOTE_C6, 480);
  compteur = 0;
}


//******* StarWars coté force ****************
void StarWars2()
{
  beep(NOTE_F5, 166);
  beep(NOTE_F5, 166);
  beep(NOTE_F5, 166);
  beep(NOTE_AS5, 999);
  beep(NOTE_F6, 999);
  beep(NOTE_DS6, 166);
  beep(NOTE_D6, 166);
  beep(NOTE_C6, 166);
  beep(NOTE_AS6, 999);
  beep(NOTE_F6, 499);
  beep(NOTE_DS6, 166);
  beep(NOTE_D6, 166);
  beep(NOTE_C6, 166);
  beep(NOTE_AS6, 999);
  beep(NOTE_F6, 499);
  beep(NOTE_DS6, 166);
  beep(NOTE_D6, 166);
  beep(NOTE_DS6, 166);
  beep(NOTE_C6, 666);
  delay(333);
  beep(NOTE_F5, 166);
  beep(NOTE_F5, 166);
  beep(NOTE_F5, 166);
  beep(NOTE_AS5, 999);
  beep(NOTE_F6, 999);
  beep(NOTE_DS6, 166);
  beep(NOTE_D6, 166);
  beep(NOTE_C6, 166);
  beep(NOTE_AS6, 999);
  beep(NOTE_F6, 499);
  beep(NOTE_DS6, 166);
  beep(NOTE_D6, 166);
  beep(NOTE_C6, 166);
  beep(NOTE_AS6, 999);
  beep(NOTE_F6, 499);
  beep(NOTE_DS6, 166);
  beep(NOTE_D6, 166);
  beep(NOTE_DS6, 166);
  beep(NOTE_C6, 666);  
  compteur = 0;
}


//******* BonBruteTruand ****************
void BonBruteTruand()
{
  beep(NOTE_AS5, 133);
  beep(NOTE_DS6, 133);
  beep(NOTE_AS5, 133);
  beep(NOTE_DS6, 133);
  beep(NOTE_AS5, 802);
  beep(NOTE_FS5, 400);
  beep(NOTE_GS5, 400);
  beep(NOTE_DS5, 1071);
  beep(NOTE_AS5, 133);
  beep(NOTE_DS6, 133);
  beep(NOTE_AS5, 133);
  beep(NOTE_DS6, 133);
  beep(NOTE_AS5, 802);
  beep(NOTE_FS5, 400);
  beep(NOTE_GS5, 400);
  beep(NOTE_CS6, 1071);
  beep(NOTE_AS5, 133);
  beep(NOTE_DS6, 133);
  beep(NOTE_AS5, 133);
  beep(NOTE_DS6, 133);
  beep(NOTE_AS5, 802);
  beep(NOTE_FS5, 400);
  beep(NOTE_F5, 199);
  beep(NOTE_DS5, 199);
  beep(NOTE_CS5, 1071);
  beep(NOTE_AS5, 133);
  beep(NOTE_DS6, 133);
  beep(NOTE_AS5, 133);
  beep(NOTE_DS6, 133);
  beep(NOTE_AS5, 802);
  beep(NOTE_GS5, 400);
  beep(NOTE_DS5, 1071);  
  compteur = 0;
}


//******* Entertainement ****************
void Entertainement()
{
  beep(NOTE_D5, 214);
  beep(NOTE_DS5, 214);
  beep(NOTE_E5, 214);
  beep(NOTE_C6, 428);
  beep(NOTE_E5, 214);
  beep(NOTE_C6, 428);
  beep(NOTE_E5, 214);
  beep(NOTE_C6, 1284);
  beep(NOTE_C6, 214);
  beep(NOTE_D6, 214);
  beep(NOTE_DS6, 214);
  beep(NOTE_E6, 214);
  beep(NOTE_C6, 214);
  beep(NOTE_D6, 214);
  beep(NOTE_E6, 428);
  beep(NOTE_B5, 214);
  beep(NOTE_D6, 428);
  beep(NOTE_C6, 856);
  delay(428);
  beep(NOTE_D5, 214);
  beep(NOTE_DS5, 214);
  beep(NOTE_E5, 214);
  beep(NOTE_C6, 428);
  beep(NOTE_E5, 214);
  beep(NOTE_C6, 428);
  beep(NOTE_E5, 214);
  beep(NOTE_C6, 1284);
  delay(214);
  beep(NOTE_A5, 214);
  beep(NOTE_G5, 214);
  beep(NOTE_FS5, 214);
  beep(NOTE_A5, 214);
  beep(NOTE_C6, 214);
  beep(NOTE_E6, 428);
  beep(NOTE_D6, 214);
  beep(NOTE_C6, 214);
  beep(NOTE_A5, 214);
  beep(NOTE_D6, 856);  
  compteur = 0;
}


//******* 20thCenFox ****************
void twentyCentFox()
{
  beep(NOTE_B5, 107);
  delay(214);
  beep(NOTE_B5, 107);
  beep(NOTE_B5, 107);
  beep(NOTE_B5, 856);
  delay(107);
  beep(NOTE_C6, 107);
  delay(53);
  beep(NOTE_B5, 107);
  delay(53);
  beep(NOTE_C6, 107);
  delay(53);
  beep(NOTE_B5, 107);
  delay(53);
  beep(NOTE_C6, 107);
  delay(53);
  beep(NOTE_B5, 107);
  delay(214);
  beep(NOTE_B5, 107);
  beep(NOTE_B5, 107);
  beep(NOTE_B5, 107);
  delay(53);
  beep(NOTE_B5, 107);
  delay(53);
  beep(NOTE_B5, 107);
  delay(53);
  beep(NOTE_B5, 107);
  delay(53);
  beep(NOTE_B5, 107);
  delay(53);
  beep(NOTE_B5, 107);
  delay(53);
  beep(NOTE_B5, 107);
  delay(53);
  beep(NOTE_GS5, 107);
  delay(53);
  beep(NOTE_A5, 107);
  delay(53);
  beep(NOTE_B5, 107);
  delay(214);
  beep(NOTE_B5, 107);
  beep(NOTE_B5, 107);
  beep(NOTE_B5, 856);
  delay(428);
  beep(NOTE_E5, 214);
  beep(NOTE_GS5, 214);
  beep(NOTE_B5, 214);
  beep(NOTE_CS6, 1712);
  beep(NOTE_FS5, 214);
  beep(NOTE_A5, 214);
  beep(NOTE_CS6, 214);
  beep(NOTE_E6, 1712);
  beep(NOTE_A5, 214);
  beep(NOTE_CS6, 214);
  beep(NOTE_E6, 214);
  beep(NOTE_E6, 1712);
  beep(NOTE_B5, 214);
  beep(NOTE_GS5, 214);
  beep(NOTE_A5, 214);
  beep(NOTE_B5, 856);  
  compteur = 0;
}


//******* looney ****************
void looney()
{
  beep(NOTE_C6, 428);
  beep(NOTE_F6, 214);
  beep(NOTE_E6, 214);
  beep(NOTE_D6, 214);
  beep(NOTE_C6, 214);
  beep(NOTE_A5, 642);
  beep(NOTE_C6, 214);
  beep(NOTE_F6, 214);
  beep(NOTE_E6, 214);
  beep(NOTE_D6, 214);
  beep(NOTE_DS6, 214);
  beep(NOTE_E6, 642);
  beep(NOTE_E6, 214);
  beep(NOTE_E6, 214);
  beep(NOTE_C6, 214);
  beep(NOTE_D6, 214);
  beep(NOTE_C6, 214);
  beep(NOTE_E6, 214);
  beep(NOTE_C6, 214);
  beep(NOTE_D6, 214);
  beep(NOTE_A5, 214);
  beep(NOTE_C6, 214);
  beep(NOTE_G5, 214);
  beep(NOTE_AS5, 214);
  beep(NOTE_A5, 214);
  beep(NOTE_F5, 214);  
  compteur = 0;
}


//******* BarbieGirl ****************
void BarbieGirl()
{
  beep(NOTE_GS5, 240);
  beep(NOTE_E5, 240);
  beep(NOTE_GS5, 240);
  beep(NOTE_CS6, 240);
  beep(NOTE_A5, 480);
  delay(480);
  beep(NOTE_FS5, 240);
  beep(NOTE_DS5, 240);
  beep(NOTE_FS5, 240);
  beep(NOTE_B5, 240);
  beep(NOTE_GS5, 480);
  beep(NOTE_FS5, 240);
  beep(NOTE_E5, 240);
  delay(480);
  beep(NOTE_E5, 240);
  beep(NOTE_CS5, 240);
  beep(NOTE_FS5, 480);
  beep(NOTE_CS5, 480);
  delay(480);
  beep(NOTE_FS5, 240);
  beep(NOTE_E5, 240);
  beep(NOTE_GS5, 480);
  beep(NOTE_FS5, 480);
  compteur = 0;
}


//******* Greensleaves ****************
void Greensleaves()
{
  beep(NOTE_G5, 428);
  beep(NOTE_AS5, 856);
  beep(NOTE_C6, 428);
  beep(NOTE_D6, 642);
  beep(NOTE_DS6, 214);
  beep(NOTE_D6, 428);
  beep(NOTE_C6, 856);
  beep(NOTE_A5, 428);
  beep(NOTE_F5, 642);
  beep(NOTE_G5, 214);
  beep(NOTE_A5, 428);
  beep(NOTE_AS5, 856);
  beep(NOTE_G5, 428);
  beep(NOTE_G5, 642);
  beep(NOTE_F5, 214);
  beep(NOTE_G5, 428);
  beep(NOTE_A5, 856);
  beep(NOTE_F5, 428);
  beep(NOTE_D5, 856);
  beep(NOTE_G5, 428);
  beep(NOTE_AS5, 856);
  beep(NOTE_C6, 428);
  beep(NOTE_D6, 642);
  beep(NOTE_E6, 214);
  beep(NOTE_D6, 428);
  beep(NOTE_C6, 856);
  beep(NOTE_A5, 428);
  beep(NOTE_F5, 642);
  beep(NOTE_G5, 214);
  beep(NOTE_A5, 428);
  beep(NOTE_AS5, 642);
  beep(NOTE_A5, 214);
  beep(NOTE_G5, 428);
  beep(NOTE_FS5, 642);
  beep(NOTE_E5, 214);
  beep(NOTE_FS5, 428);
  beep(NOTE_G5, 856);
  compteur = 0;
}


//******* James Bond *******************

void Bond()
{
  beep(NOTE_CS6, 187);
  beep(NOTE_DS6, 93);
  beep(NOTE_DS6, 93);
  beep(NOTE_DS6, 187);
  beep(NOTE_DS6, 375);
  beep(NOTE_CS6, 187);
  beep(NOTE_CS6, 187);
  beep(NOTE_CS6, 187);
  beep(NOTE_CS6, 187);
  beep(NOTE_E6, 93);
  beep(NOTE_E6, 93);
  beep(NOTE_E6, 187);
  beep(NOTE_E6, 375);
  beep(NOTE_DS6, 187);
  beep(NOTE_DS6, 187);
  beep(NOTE_DS6, 187);
  beep(NOTE_CS6, 187);
  beep(NOTE_DS6, 93);
  beep(NOTE_DS6, 93);
  beep(NOTE_DS6, 187);
  beep(NOTE_DS6, 375);
  beep(NOTE_CS6, 187);
  beep(NOTE_CS6, 187);
  beep(NOTE_CS6, 187);
  beep(NOTE_CS6, 187);
  beep(NOTE_E6, 93);
  beep(NOTE_E6, 93);
  beep(NOTE_E6, 187);
  beep(NOTE_E6, 375);
  beep(NOTE_DS6, 187);
  beep(NOTE_D6, 187);
  beep(NOTE_CS6, 187);
  beep(NOTE_CS7, 187);
  beep(NOTE_C7, 1125);
  beep(NOTE_GS6, 187);
  beep(NOTE_FS6, 187);
  beep(NOTE_GS6, 1125);
  compteur = 0;
}


