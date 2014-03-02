
#include <LiquidCrystal.h>
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
#define melodyPin 12


int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7, 
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0, 

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12, 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12, 

  12, 12, 12, 12,
  12, 12, 12, 12, 
  12, 12, 12, 12, 
  12, 12, 12, 12, 

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(20, 21, 14, 15, 16, 17);

byte nave[8] = { 0b11111,
0b01110,
0b00100,
0b00000,
0b00000,
0b00000,
0b00000,
0b00000};

byte character[8] = { 0b01110,
0b11111,
0b01010,
0b01110,
0b00100,
0b01110,
0b00100,
0b01010};

byte death[8] = { 0b00000, // vetor de bytes correspondentes
0b11111,  // ao desenho do coração
0b11111,
0b10101,
0b01110,
0b01110,
0b01010,
0b00000
};

byte cls[8] = { 0b00000, // vetor de bytes correspondentes
0b00000,  // ao desenho do coração
0b00000,
0b00000,
0b00000,
0b00000,
0b00000,
0b00000
};

const int vry = 6; 
const int vrx = 7; 
const int primeiraLinhaDeAtque = 3;

int charPosition = 0;

int navesAtivas  [16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int linhaDeAtque [16] = {primeiraLinhaDeAtque,primeiraLinhaDeAtque,
                         primeiraLinhaDeAtque,primeiraLinhaDeAtque,
                         primeiraLinhaDeAtque,primeiraLinhaDeAtque,
                         primeiraLinhaDeAtque,primeiraLinhaDeAtque,
                         primeiraLinhaDeAtque,primeiraLinhaDeAtque,
                         primeiraLinhaDeAtque,primeiraLinhaDeAtque,
                         primeiraLinhaDeAtque,primeiraLinhaDeAtque,
                         primeiraLinhaDeAtque,primeiraLinhaDeAtque};

int jogando = 0;

void checkCollision (){

  if (linhaDeAtque[charPosition] >= 7){
    killChar();
  }
}

void killChar (){
  lcd.setCursor(charPosition,1);
  lcd.write(3);

}

void killNave (int collumn){
  navesAtivas[collumn]  = 0;
  linhaDeAtque[collumn] = primeiraLinhaDeAtque;
  lcd.setCursor(collumn,0);
  lcd.write(9);
}

void updateCharPosition (){
  int posy  = digitalRead(vry);
  if (posy == 0){
    lcd.setCursor(charPosition,1);
    lcd.print(" ");
    charPosition = (charPosition+1)%16;
    lcd.setCursor(charPosition,1);
    lcd.write(2);
        }
            
}

void createRandomNave (){
  int  randNumber = random(0, 16);
  navesAtivas[randNumber]  = 1;
}

void printNave (int position){
  lcd.setCursor(position,0);
  lcd.write(1);
}

void updateNavePosition () {

  int i;
  
  for (i = 0; i < 16; i++)
  {
    if(navesAtivas[i] == 1){
      int lAtque = linhaDeAtque[i];
      if(lAtque > 7){
        killNave(i);
                                createRandomQntNave();
      }else if(lAtque < 7){ 
        clearNave();
        nave[lAtque] = 0b00100;
        
        /* Cria Objeto de Nave Atualizada */

        lcd.createChar(1, nave);
        printNave(i);

        linhaDeAtque[i] = linhaDeAtque[i] +1;
      }else { // Quando está na posição 9 deverá acontecer colisão mas não pode ser printado
        linhaDeAtque[i] = linhaDeAtque[i] +1;
      }
      

    }
  }
}

void createRandomQntNave () {
  int i = 0;                    
  int  randNumber = random(0, 6);       
  for (i = 0; i < randNumber; i++){
    createRandomNave();
  }
}

void clearNave (){
    nave[0] = 0b11111;
    nave[1] = 0b01110;
    nave[2] = 0b00100;
    nave[3] = 0b00000;
    nave[5] = 0b00000;
    nave[6] = 0b00000;
    nave[7] = 0b00000;
    nave[8] = 0b00000;
}

void clearNaveRow (){

  int i;
  
  for (i = 0; i < 16; i++){
    lcd.setCursor(i,0);
    lcd.print(" ");
  }
  
}

void clearCharRow () {

  int i;
  
  for (i = 0; i < 16; i++){
    lcd.setCursor(i,1);
    lcd.print(" ");
  }
}

void game (){

  checkCollision();
  clearNaveRow ();
  updateNavePosition();
  updateCharPosition();
  delay(200);
}


void singMarioMusic(){      
   // iterate over the notes of the melody:
   

     Serial.println(" 'Mario Theme'");
     int size = sizeof(melody) / sizeof(int);
     for (int thisNote = 0; thisNote < size; thisNote++) {

       // to calculate the note duration, take one second
       // divided by the note type.
       //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
       int noteDuration = 1000/tempo[thisNote];

       buzz(melodyPin, melody[thisNote],noteDuration);

       // to distinguish the notes, set a minimum time between them.
       // the note's duration + 30% seems to work well:
       int pauseBetweenNotes = noteDuration * 1.30;
       delay(pauseBetweenNotes);

       // stop the tone playing:
       buzz(melodyPin, 0,noteDuration);

    }
  
}

void buzz(int targetPin, long frequency, long length) {
  
  long delayValue = 1000000/frequency/2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length/ 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to 
  //// get the total number of cycles to produce
  for (long i=0; i < numCycles; i++){ // for the calculated length of time...
    digitalWrite(targetPin,HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin,LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
  

}



void iniciaJogo () {
  clearNaveRow();
  clearCharRow();

  lcd.setCursor(0,1);
  lcd.write(2);
}

void setup()
{
  pinMode(vry, INPUT);
  pinMode(vrx, INPUT);
  pinMode(12, OUTPUT);//buzzer

  lcd.begin(16, 2);
  lcd.createChar(1, nave); // envia nosso character p/ o display
  lcd.createChar(2, character); // envia nosso character p/ o display
  lcd.createChar(3, death);
  lcd.createChar(9, cls);

  randomSeed(6);
  createRandomNave ();
  createRandomNave ();

  /* Desenha o personagem na primeira posição*/

  lcd.setCursor(0,0);
  lcd.print("Bem Vindo!");
  lcd.setCursor(0,1);
  lcd.print("Game Teste!");
  singMarioMusic();
  
  iniciaJogo ();
  
 
}

void loop()
{
  
    game();
  
}