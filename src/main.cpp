#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <SPI.h>

/////////////////////////////////////////////////////////////////////////// TFT Setup
/*
#define TFT_MISO 19
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS   15  // Chip select control pin
#define TFT_DC    2  // Data Command control pin
#define TFT_RST   4  // Reset pin (could connect to RST pin)

Display

#define TFT_WIDTH  128
#define TFT_HEIGHT 160

*/

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library
// Maximum number of generations until the screen is refreshed
#define MAX_GEN_COUNT 500

// The ESP8266 has plenty of memory so we can create a large array
// 2 x 2 pixel cells, array size = 5120 bytes per array, runs fast
#define GRIDX 80
#define GRIDY 64
#define CELLXY 2
#define GEN_DELAY 10 // Set a delay between each generation to slow things down

//Current grid and newgrid arrays are needed
uint8_t grid[GRIDX][GRIDY];

//The new grid for the next generation
uint8_t newgrid[GRIDX][GRIDY];

//Number of generations
uint16_t genCount = 0;


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
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(0, 0);

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