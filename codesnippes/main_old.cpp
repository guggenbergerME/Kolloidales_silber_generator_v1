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
/*
// The ESP8266 has plenty of memory so we can create a large array
// 2 x 2 pixel cells, array size = 5120 bytes per array, runs fast
#define GRIDX 80
#define GRIDY 64
#define CELLXY 2

// 1 x 1 pixel cells, array size = 20480 bytes per array
//#define GRIDX 160
//#define GRIDY 128
//#define CELLXY 1

#define GEN_DELAY 10 // Set a delay between each generation to slow things down

//Current grid and newgrid arrays are needed
uint8_t grid[GRIDX][GRIDY];

//The new grid for the next generation
uint8_t newgrid[GRIDX][GRIDY];

//Number of generations
uint16_t genCount = 0;
*/
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


/////////////////////////////////////////////////////////////////////////// Intervall der Steuerung
unsigned long previousMillis_btckurs = 0;
unsigned long interval_btckurs = 15000; 

/////////////////////////////////////////////////////////////////////////// Funktionsprototypen
//void callback                (char*, byte*, unsigned int);
void loop                      ();
void setup                     ();
void startwerte                ();
void tft_text                  (int x, int y, int size, char *text, uint16_t color);
void elektrolyse               ();
void elektrolyse_umkehren      ();

//**************************************************************************** void SETUP
void setup() {

  // Serielle Kommunikation starten
  Serial.begin(115200);

  //Set up the display
  Serial.println("Display test");
  tft.init();
  tft.setRotation(2);
 
  //Display a simple splash screen
  tft.fillScreen(BLACK);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.setCursor(40, 5);
  tft.println(F("Arduino"));
  tft.setCursor(35, 25);
  tft.println(F("Cellular"));
  tft.setCursor(35, 45);
  tft.println(F("Automata"));

   delay(1500);

}

/////////////////////////////////////////////////////////////////////////// TFT - Text schreiben
void tft_text(int x, int y, int size, char *text, uint16_t color) {

}

/////////////////////////////////////////////////////////////////////////// Elektrolyse
void startwerte () {
  /*
  1 Wassermenge abfragen 0,1 Liter schritte

  2 Elektrolyse stärke 50 ppm

  3 Dauer der Elektrolyse berechnen

  4 Prozess starten

  */

}

/////////////////////////////////////////////////////////////////////////// Elektrolyse
void elektrolyse () {

}

/////////////////////////////////////////////////////////////////////////// Elektrolyse umkehr
void elektrolyse_umkehren () {

}

/////////////////////////////////////////////////////////////////////////// VOID LOOP
void loop() {

  ///////////////////////////////////////////////////////////////////////// BTC Kurs abfragen
  if (millis() - previousMillis_btckurs > interval_btckurs) {
      previousMillis_btckurs = millis();   // aktuelle Zeit abspeichern
      // BTC Kurs abfragen

    }


}