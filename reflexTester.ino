#include <LiquidCrystal.h> //Dołączenie bilbioteki
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Informacja o podłączeniu nowego wyświetlacza
 
#define odczytBTN A0
 
#define BTN1    1023
#define BTN2    896
#define BTN3    768
#define BTN4    640
#define BTN5    512
#define BTN6    384
#define BTN7    256
#define BTN8    128
 
 
 
double aktualnyCzas = 0;
double zapamietanyCzas = 0;
double roznicaCzasu = 0;
double sredniCzas = 0;
 
int latchPin = 8;
//Pin połączony z SH_CP rejestru 74HC595
int clockPin = 12;
////Pin połączony z DS rejestru 74HC595
int dataPin = 11;
 
byte data = 0;
 
int wylosowanyNumer=random(8);
 
boolean wejscie=true;
boolean zmiennaDoNapisow=false;
boolean zmiennaDoOdliczania=false;
boolean ocenaPoziomu=false;
boolean startGry=false;
 
boolean czyPrzyciskWcisniety(int analogowaWar, int przyciskuWar) {
  return abs(przyciskuWar - analogowaWar) <= 30;
}
 
int czerwone[] = {1,3,5,7};
int zielone[] = {2, 4, 6, 0};
int g=0;
 
 
 
 
void setup() {
  pinMode(odczytBTN, INPUT);
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  lcd.begin(16, 2); //Deklaracja typu
 
 
}
 
 
 
 
void loop() {
int btnData = analogRead(odczytBTN);
 
 if(wejscie)
 {
      intro();
      zmiennaDoNapisow=true;
      wejscie=false;
     
 }
 
  if (zmiennaDoNapisow)
  {
    g=0;
   wstep();
   if( czyPrzyciskWcisniety(btnData, BTN1))
    {
      zmiennaDoNapisow=false;
      zmiennaDoOdliczania=true;
      lcd.clear();
    }
  }
 
  if (zmiennaDoOdliczania)
  {
    start();
    zmiennaDoOdliczania=false;
    startGry=true;
  }
 
  if(startGry)
  {
    if(g==0)
    {
    zapamietanyCzas=millis();
    }
    switch(wylosowanyNumer)
    {
       case 0: zaswiecDiode(0);  if(czyPrzyciskWcisniety(btnData, BTN8)) { zgasDiode(0);  wylosowanyNumer=random(8);  g++; delay(200);} break;
       case 1: zaswiecDiode(1);  if(czyPrzyciskWcisniety(btnData, BTN1)) { zgasDiode(1);  wylosowanyNumer=random(8);  g++; delay(200);} break;
       case 2: zaswiecDiode(2);  if(czyPrzyciskWcisniety(btnData, BTN2)) { zgasDiode(2);  wylosowanyNumer=random(8);  g++; delay(200);} break;
       case 3: zaswiecDiode(3);  if(czyPrzyciskWcisniety(btnData, BTN3)) { zgasDiode(3);  wylosowanyNumer=random(8);  g++; delay(200);} break;
       case 4: zaswiecDiode(4);  if(czyPrzyciskWcisniety(btnData, BTN4)) { zgasDiode(4);  wylosowanyNumer=random(8);  g++; delay(200);} break;
       case 5: zaswiecDiode(5);  if(czyPrzyciskWcisniety(btnData, BTN5)) { zgasDiode(5);  wylosowanyNumer=random(8);  g++; delay(200);} break;
       case 6: zaswiecDiode(6);  if(czyPrzyciskWcisniety(btnData, BTN6)) { zgasDiode(6);  wylosowanyNumer=random(8);  g++; delay(200);} break;
       case 7: zaswiecDiode(7);  if(czyPrzyciskWcisniety(btnData, BTN7)) { zgasDiode(7);  wylosowanyNumer=random(8);  g++; delay(200);} break;
    }
    Serial.println(g);
    delay(50);
   if(g==10)
   {
   startGry=false;
   aktualnyCzas=millis();
    czas();
    ocenaPoziomu=true;
   }
  }
  if(ocenaPoziomu)
  {
    poziomy();
    ocenaPoziomu=false;
    zmiennaDoNapisow=true;
   
  }
 
 
 
}
 
void wstep()
{
   lcd.setCursor(0, 0); //Ustawienie kursora
    lcd.print("Tester refleksu ");
    lcd.setCursor(0, 1); //Ustawienie kursora
    lcd.print("Wcisnij przycisk"); //Wyświetlenie tekstu
    lcd.blink(); //Włącznie kursora
    zaswiecDiode(1);
   
}
 
void start()
{
  for (int j = 3; j > 0; j--)
    {
    lcd.setCursor(0, 0); //Ustawienie kursora
    lcd.print(j);
    lcd.blink(); //Włącznie kursora
    delay(1000);
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("START!"); //Wyświetlenie tekstu
 
}
 
void czas()
{
    roznicaCzasu=aktualnyCzas-zapamietanyCzas;
    sredniCzas=roznicaCzasu/1000;
 
    lcd.clear();
    lcd.setCursor(0, 0); //Ustawienie kursora
    lcd.print("Sredni czas: ");
    lcd.setCursor(0, 1); //Ustawienie kursora
    lcd.print(sredniCzas); //Wyświetlenie tekstu
 
    delay(5000);
 
}
 
void poziomy()
{
   if((roznicaCzasu>0)&&(roznicaCzasu<6500))
        {
          lcd.clear();
    lcd.setCursor(0, 0); //Ustawienie kursora
    lcd.print("Poziom: ROBERT ");
    delay(5000);
 
        roznicaCzasu=0;
   
         
        }
 
        else if((roznicaCzasu>=6500)&&(roznicaCzasu<11000))
        {
          lcd.clear();
          lcd.setCursor(0, 0); //Ustawienie kursora
          lcd.print("Poziom: SREDNIAK ");
          delay(5000);
 
          roznicaCzasu=0;
        }
 
        else if( roznicaCzasu>=11000)
        {
          lcd.clear();
          lcd.setCursor(0, 0); //Ustawienie kursora
          lcd.print("Poziom: EMERYT ");
          delay(5000);
 
          roznicaCzasu=0;
        }
 
        else
        {
          lcd.clear();
          lcd.setCursor(0, 0); //Ustawienie kursora
          lcd.print("DZIWNY POMIAR ");
          delay(5000);
 
          roznicaCzasu=0;
             
        }
}
 
void zaswiecDiode(int p) {
 
  int pin;
  pin = 1<< p;
 
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, pin);
  digitalWrite(latchPin, HIGH);
 
}
 
void zgasDiode(int p) {
 
  int pin;
  pin = 0<< p;
 
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, pin);
  digitalWrite(latchPin, HIGH);
 
}
 
 
 
 
void intro()
{
  blinkAll(1,500);
  for (int j = 1; j < 8; j++) {
    zaswiecDiode(j);
    delay(300);
  }
  zaswiecDiode(0);
   delay(300);
  blinkAll(2,500);  
 
  for(int i=0; i<4; i++)
  {
    zaswiecDiode(czerwone[i]);
    delay(300);
  }
 
  for(int i=0; i<4; i++)
  {
    zaswiecDiode(zielone[i]);
    delay(300);
  }
 
  for(int i=3; i>=0; i--)
  {
    zaswiecDiode(czerwone[i]);
    delay(300);
  }
 
  for(int i=3; i>=0; i--)
  {
    zaswiecDiode(zielone[i]);
    delay(300);
  }
 
  blinkAll(2,500);  
}
 
 
 
void blinkAll(int n, int d) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  digitalWrite(latchPin, HIGH);
  delay(200);
  for (int x = 0; x < n; x++) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, 255);
    digitalWrite(latchPin, HIGH);
    delay(d);
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, 0);
    digitalWrite(latchPin, HIGH);
    delay(d);
  }
}
