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

// Color definitions
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define BITCOIN 0xFD20

/////////////////////////////////////////////////////////////////////////// Interrup
int taster_okay =  13;
int taster_f1 =  12;

/////////////////////////////////////////////////////////////////////////// Intervall der Steuerung
unsigned long previousMillis_btckurs = 0;
unsigned long interval_btckurs = 15000; 

/////////////////////////////////////////////////////////////////////////// Variablen
int program_point  = 0;
float wasser_liter = 0.25;

/////////////////////////////////////////////////////////////////////////// Funktionsprototypen
//void callback                (char*, byte*, unsigned int);
void loop                      ();
void setup                     ();
void startwerte                ();
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
 
  //Display a simple splash screen
  tft.fillScreen(BLACK);
  tft.setTextSize(2);
  tft.setTextColor(WHITE,BLACK);
  tft.setCursor(6, 35); // links - höhe
  tft.println("SilverPulser");
  tft.setCursor(60, 75);
  tft.println("v1.0");
  delay(1500);
  tft.fillScreen(BLACK);
  tft.setCursor(70, 35); // links - höhe
  tft.println("by");
  tft.setCursor(16, 75);
  tft.println("Ruesselheim");
  delay(1500);
  tft.fillScreen(BLACK);

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
  return zwi_speich;
}

/////////////////////////////////////////////////////////////////////////// Elektrolyse
void startwerte () {

  //tft.fillScreen(BLACK);
  tft.setTextSize(2);
  tft.setTextColor(BLUE,BLACK);
  tft.setCursor(49, 35); // links - höhe
  tft.println("Setup");
  tft.setTextColor(BITCOIN,BLACK);
  tft.setCursor(32, 75);
  tft.println("Press OK");

   if (lese_tasten() == 1) {
    delay(500);
    program_point = 1;
    tft.fillScreen(BLACK);
  }

}

/////////////////////////////////////////////////////////////////////////// Wassermenge abfragen
void wassermenge () {

  //tft.fillScreen(BLACK);
  tft.setTextSize(2);
  tft.setTextColor(BLUE,BLACK);
  tft.setCursor(3, 35); // links - höhe
  tft.println("Wassermenge");
  tft.setTextColor(BLUE,BLACK);
  tft.setCursor(3, 75);
  tft.println("Liter ");
  tft.setCursor(75, 75);
  tft.println(wasser_liter);
  delay(200);


  // Taste okay
   if (lese_tasten() == 1) {
    //delay(500);
    //program_point = 2;
    //tft.fillScreen(BLACK);
  }

  // Wassermenge erhöhen + 
  if (lese_tasten() == 2) {
    wasser_liter += 0.05 ;
    delay(300);
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

}


}