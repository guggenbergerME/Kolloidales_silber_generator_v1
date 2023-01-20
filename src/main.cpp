#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>

/////////////////////////////////////////////////////////////////////////// TFT Setup
/*
PIN - Belegung
TFT           ESP WROOM32
****          ************
GND           GND
VCC           VCC
SCL           D18
SDA           D23
RES           D4
DC            D2
CS            D6
BLK           NC

libdeps/esp32/TFT_eSPI/User_Setup.h
#define TFT_WIDTH  128
#define TFT_HEIGHT 160
#define ST7735_REDTAB
*/

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

/////////////////////////////////////////////////////////////////////////// Interrup
int taster_okay =  13;
int taster_f1 =  12;
int taster_f2 =  14;

/////////////////////////////////////////////////////////////////////////// Intervall der Steuerung
unsigned long previousMillis_btckurs = 0;
unsigned long interval_btckurs = 15000; 

/////////////////////////////////////////////////////////////////////////// Variablen
int program_point  = 0;
float wasser_liter = 0.50;
float ppm_wert = 65;

/////////////////////////////////////////////////////////////////////////// Funktionsprototypen
//void callback                (char*, byte*, unsigned int);
void loop                      ();
void setup                     ();
void startwerte                ();
void ppm_setup                 ();
void tft_text                  (int x, int y, int size, char *text, uint16_t color);
void elektrolyse               ();
void elektrolyse_umkehren      ();
uint8_t lese_tasten            (void);

//**************************************************************************** void SETUP
void setup() {

  // Serielle Kommunikation starten
  Serial.begin(115200);

  // Setup TFT Display
  tft.init();
  tft.setRotation(3); // Richtung des Textes

  // Taster initalisieren
  pinMode(taster_okay, INPUT);  // Taster OK
  pinMode(taster_f1, INPUT);  // Taster F1
  pinMode(taster_f2, INPUT);  // Taster F2
 
  //Display a simple splash screen
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.setCursor(6, 35); // links - höhe
  tft.println("SilverPulser");
  tft.setCursor(60, 75);
  tft.println("v1.0");
  delay(1500);
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(70, 35); // links - höhe
  tft.println("by");
  tft.setCursor(16, 75);
  tft.println("Ruesselheim");
  delay(1500);
  tft.fillScreen(TFT_BLACK);

}

/////////////////////////////////////////////////////////////////////////// TFT - Text schreiben
void tft_text(int x, int y, int size, char *text, uint16_t color) {

}

/////////////////////////////////////////////////////////////////////////// Taster auslesen
uint8_t lese_tasten(void) {               // function reads switches and returns 1-7
  uint8_t zwi_speich = 0;
  if (digitalRead(taster_okay) == HIGH)
    zwi_speich = 1;

  if (digitalRead(taster_f1) == HIGH)
    zwi_speich += 2;

  if (digitalRead(taster_f2) == HIGH)
    zwi_speich += 3;

  return zwi_speich;
}

/////////////////////////////////////////////////////////////////////////// Elektrolyse
void startwerte () {

  //tft.fillScreen(BLACK);
  tft.setTextSize(2);
  tft.setTextColor(TFT_BLUE,TFT_BLACK);
  tft.setCursor(49, 35); // links - höhe
  tft.println("Setup");
  tft.setTextColor(TFT_RED,TFT_BLACK);
  tft.setCursor(32, 75);
  tft.println("Press OK");

   if (lese_tasten() == 1) {
    delay(500);
    program_point = 1;
    tft.fillScreen(TFT_BLACK);
  }

}

/////////////////////////////////////////////////////////////////////////// Wassermenge abfragen
void wassermenge () {

  //tft.fillScreen(BLACK);
  tft.setTextSize(2);
  tft.setTextColor(TFT_BLUE,TFT_BLACK);
  tft.setCursor(4, 15); // links - höhe
  tft.println("Wassermenge");
  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.setCursor(3, 50);
  tft.println("Liter ");
  tft.setCursor(75, 50);
  tft.println(wasser_liter);
  tft.setTextColor(TFT_RED,TFT_BLACK);
  tft.setCursor(3, 90);
  tft.println("OK -> weiter ");
  delay(200);


  // Taste okay
   if (lese_tasten() == 1) {
    //delay(500);
    //program_point = 2;
    //tft.fillScreen(BLACK);
  }

  // Wassermenge erhöhen + 
  if (lese_tasten() == 2) {
    if (wasser_liter == 2.50) {
    } else {
    wasser_liter += 0.10 ;
    delay(150);
    }
  }

  // Wassermenge erhöhen + 
  if (lese_tasten() == 3) {
    // Wassermenge beschränken
    if (wasser_liter <= 0.10) {
    } else {
    wasser_liter -= 0.10 ;
    delay(150);
    }

  }

   if (lese_tasten() == 1) {
    delay(500);
    program_point = 2;
    tft.fillScreen(TFT_BLACK);
  }  

}

/////////////////////////////////////////////////////////////////////////// PPM Setup
void ppm_setup() {
//tft.fillScreen(BLACK);
  tft.setTextSize(2);
  tft.setTextColor(TFT_BLUE,TFT_BLACK);
  tft.setCursor(4, 15); // links - höhe
  tft.println("PPM Wert");
  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.setCursor(3, 50);
  tft.println("PPM ");
  tft.setCursor(75, 50);
  tft.println(ppm_wert);
  tft.setTextColor(TFT_RED,TFT_BLACK);
  tft.setCursor(3, 90);
  tft.println("OK -> weiter ");
  delay(200);


  // Wassermenge erhöhen + 
  if (lese_tasten() == 2) {
    if (ppm_wert == 100) {
    } else {
    ppm_wert += 1 ;
    delay(150);
    }
  }

  // Wassermenge erhöhen + 
  if (lese_tasten() == 3) {
    // Wassermenge beschränken
    if (ppm_wert <= 10) {
    } else {
    ppm_wert -= 1 ;
    delay(150);
    }

  }

   if (lese_tasten() == 1) {
    delay(500);
    program_point = 3;
    tft.fillScreen(TFT_BLACK);
  }  

}

/////////////////////////////////////////////////////////////////////////// Elektrolyse
void elektrolyse () {

}

/////////////////////////////////////////////////////////////////////////// Elektrolyse umkehr
void elektrolyse_umkehren () {

}

/////////////////////////////////////////////////////////////////////////// VOID LOOP
void loop() {

// Programmablauf
switch(program_point) {

case 0:
  
  Serial.println("Case 0 - Startwerte");
  startwerte();

break;

case 1:
  
  Serial.println("Case 1 - Wassermenge abfragen");
  wassermenge ();

break;

case 2:
  
  Serial.println("Case 2 - PPM");
  ppm_setup ();

break;

case 3:
  
  Serial.println("Case 3 - XXX");
  //ppm_setup ();

break;

}


}