#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735

/////////////////////////////////////////////////////////////////////////// TFT Konfig
#define TFT_CS         4
#define TFT_RST        16                                            
#define TFT_DC         5
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

//#define COLOR3 ST7735_YELLOW
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

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

  /////////////////////////////////////////////////////////////////////////// TFT initialisieren
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
  
  // TFT einfärben
  tft.fillScreen(BLACK);

  // Serielle Kommunikation starten
  Serial.begin(115200);


    // TFT einfärben
   tft.fillScreen(BLACK);
   tft.setCursor(13,30);
   tft.setTextColor(RED,BLACK);
   tft.setTextSize(1);
   tft.print("Start");

   delay(1500);

}

/////////////////////////////////////////////////////////////////////////// TFT - Text schreiben
void tft_text(int x, int y, int size, char *text, uint16_t color) {
  tft.setTextWrap(true);
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(size);
  tft.print(text);
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