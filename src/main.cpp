#include <Arduino.h>
#include <TFT_eSPI.h> 

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