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

// Pause in milliseconds between screens, change to 0 to time font rendering
#define WAIT 500

/////////////////////////////////////////////////////////////////////////// Taster
int taster_okay =  13;
int taster_f1 =  12;
int taster_f2 =  14;

/////////////////////////////////////////////////////////////////////////// ADC 
int adc_wasser_leitfaehigkeit = 15;

/////////////////////////////////////////////////////////////////////////// Intervall der Steuerung
unsigned long previousMillis_btckurs = 0;
unsigned long interval_btckurs = 15000; 

/////////////////////////////////////////////////////////////////////////// Variablen
int program_point  = 0;
float wasser_liter = 0.10;
int ppm_wert = 1;
int var_umpolzeit = 10;
int adc_wert_wasser_leitfaehigkeit = 0;
int elektrolyse_ma = 10; // Angaben in mA

int messung_wasser_status = 0;
int wasser_schwellwert = 100;
int wasser_schwellwert_leitungswasser = 1000;
int wasser_schwellwert_kurzschluss = 4250;

int dauer_in_minuten;

/////////////////////////////////////////////////////////////////////////// Funktionsprototypen
//void callback                (char*, byte*, unsigned int);
void loop                      ();
void setup                     ();
void startwerte                ();
void ppm_setup                 ();
void umpolzeit                 ();
void setup_uebersicht          ();
void wasser_testen_1           ();
void wasser_testen_2           ();
void tft_text                  (int x, int y, int size, char *text, uint16_t color);
void elektrolyse               ();
void elektrolyse_umkehren      ();
void elektrolyse_ende          ();
uint8_t lese_tasten            (void);

//**************************************************************************** void SETUP
void setup() {

  // Serielle Kommunikation starten
  Serial.begin(115200);

  // Taster initalisieren
  pinMode(taster_okay, INPUT);  // Taster OK
  pinMode(taster_f1, INPUT);  // Taster F1
  pinMode(taster_f2, INPUT);  // Taster F2

  // Setup TFT Display
  tft.init();
  tft.setRotation(3); // Richtung des Textes

  //Display a simple splash screen
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.drawString("SilverPulser", 4, 20, 4);
  tft.drawString("v1.0", 40, 65, 4);
  delay(2500);
  tft.fillScreen(TFT_BLACK);
  tft.drawString("by", 50, 20, 4);
  tft.drawString("nix", 35, 65, 4);
  delay(2500);
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

  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.drawString("Setup", 40, 20, 4);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.drawString("Weiter - ", 35, 90, 2);
  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.drawString("ok", 95, 90, 2);
  //delay(WAIT);
 
 
   if (lese_tasten() == 1) {
    delay(500);
    program_point = 1;
    tft.fillScreen(TFT_BLACK);
  }

}

/////////////////////////////////////////////////////////////////////////// Wassermenge abfragen
void wassermenge () {

  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.drawString("Wassermenge", 4, 0, 2);

  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.drawString("Liter", 4, 30, 4);

  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.setCursor(60,30,4); // links - höhe - groesse
  tft.println(wasser_liter);  

  tft.setTextColor(TFT_BLUE,TFT_BLACK);
  tft.drawString("F1 + | F2 -", 60, 60, 2);  
  
  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.drawString("Weiter - ", 35, 90, 2);
  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.drawString("ok", 95, 90, 2);
  
  // Wassermenge erhöhen + 
  if (lese_tasten() == 2) {
    if (wasser_liter == 2.50) {
    } else {
    wasser_liter += 0.10 ;
    delay(500);
    }
  }

  // Wassermenge erhöhen + 
  if (lese_tasten() == 3) {
    // Wassermenge beschränken
    if (wasser_liter <= 0.10) {
    } else {
    wasser_liter -= 0.10 ;
    delay(500);
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

  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.drawString("PPM Wert", 4, 0, 2);

  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.drawString("PPM", 4, 30, 4);

  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.setCursor(63,30,4); // links - höhe - groesse
  tft.println(ppm_wert);  

  tft.setTextColor(TFT_BLUE,TFT_BLACK);
  tft.drawString("F1 + | F2 -", 63, 60, 2);  
  
  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.drawString("Weiter - ", 35, 90, 2);
  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.drawString("ok", 95, 90, 2);


  // Wassermenge erhöhen + 
  if (lese_tasten() == 2) {
    if (ppm_wert == 100) {
    } else {
    ppm_wert += 1 ;
    delay(500);
    }
  }

  // Wassermenge erhöhen + 
  if (lese_tasten() == 3) {
    // Wassermenge beschränken
    if (ppm_wert <= 10) {
    } else {
    ppm_wert -= 1 ;
    delay(500);
    }

  }

   if (lese_tasten() == 1) {
    delay(500);
    program_point = 3;
    tft.fillScreen(TFT_BLACK);
  }  

}

/////////////////////////////////////////////////////////////////////////// PPM Setup
void umpolzeit() {

  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.drawString("Umpolzeit", 4, 0, 2);

  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.drawString("Sekunden", 4, 30, 2);

  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.setCursor(80,30,4); // links - höhe - groesse
  tft.println(var_umpolzeit);  

  tft.setTextColor(TFT_BLUE,TFT_BLACK);
  tft.drawString("F1 + | F2 -", 63, 60, 2);  
  
  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.drawString("Weiter - ", 35, 90, 2);
  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.drawString("ok", 95, 90, 2);


  // Wassermenge erhöhen + 
  if (lese_tasten() == 2) {
    if (var_umpolzeit == 30) {
    } else {
    var_umpolzeit += 1 ;
    delay(500);
    }
  }

  // Wassermenge erhöhen + 
  if (lese_tasten() == 3) {
    // Wassermenge beschränken
    if (var_umpolzeit <= 10) {
    } else {
    var_umpolzeit -= 1 ;
    delay(500);
    }

  }

   if (lese_tasten() == 1) {
    delay(500);
    program_point = 4;
    tft.fillScreen(TFT_BLACK);
  }  

}

/////////////////////////////////////////////////////////////////////////// PPM Setup
void setup_uebersicht() {


  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.drawString("Setup", 4, 0, 2);

  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.drawString("Wasser", 4, 25, 2);

  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.setCursor(70,25,2); // links - höhe - groesse
  tft.println(wasser_liter);  

  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.drawString("PPM", 4, 50, 2);

  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.setCursor(70,50,2); // links - höhe - groesse
  tft.println(ppm_wert); 

  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.drawString("Umpolung", 4, 75, 2);

  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.setCursor(70,75,2); // links - höhe - groesse
  tft.println(var_umpolzeit); 
  

  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.drawString("START - ok", 4, 98, 2);

  tft.setTextColor(TFT_BLUE,TFT_BLACK);
  tft.drawString("Neu - F1", 86, 98, 2);


  if (lese_tasten() == 1) {
    delay(500);
    program_point = 5;
    tft.fillScreen(TFT_BLACK);
  } 

  if (lese_tasten() == 2) {
    delay(500);
    program_point = 1;
    tft.fillScreen(TFT_BLACK);
  } 



}

/////////////////////////////////////////////////////////////////////////// Wasser testen 1
void wasser_testen_1() {

  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.drawString("Wassertest", 5, 0, 4);

  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.drawString("Bitte die Elektroden", 1, 30, 2);
  tft.drawString("in destiliertes Wasser", 1, 50, 2);
  tft.drawString("eintauchen.", 1, 70, 2);

  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.drawString("Weiter - ", 35, 90, 2);
  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.drawString("ok", 95, 90, 2);  



  if (lese_tasten() == 1) {
    delay(1000);
    program_point = 6;
    tft.fillScreen(TFT_BLACK);
  } 

}

/////////////////////////////////////////////////////////////////////////// Wasser testen 2
void wasser_testen_2() {

  tft.setTextColor(TFT_BLUE,TFT_BLACK);
  tft.drawString("Wassertest", 5, 0, 4);

  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.drawString("Teste Wasserqualität", 1, 30, 2);

  // Relais 24 Volt aufschalten
 
  // ADC Werte auslesen
  //Mittelwert
      for (int i = 1; i <= 10; i++) {
          adc_wert_wasser_leitfaehigkeit = adc_wert_wasser_leitfaehigkeit + analogRead(adc_wasser_leitfaehigkeit);
          delay(20);
 
      }

    adc_wert_wasser_leitfaehigkeit = adc_wert_wasser_leitfaehigkeit / 10;

     Serial.println(adc_wert_wasser_leitfaehigkeit);

  // Wasserqualität auswerten
  if (adc_wert_wasser_leitfaehigkeit > wasser_schwellwert && adc_wert_wasser_leitfaehigkeit < wasser_schwellwert_leitungswasser) {

    tft.setTextColor(TFT_GREEN,TFT_BLACK);
    tft.drawString("Wasser ist okay!          ", 1, 60, 2);
    tft.drawString("                          ", 1, 80, 2);
    tft.drawString("Vorgang starten <ok>      ", 1, 100, 2);
    delay(25);

    if (lese_tasten() == 1) {
    delay(250);
    program_point = 7;
    tft.fillScreen(TFT_BLACK);
  }  

  } 

// Messen ob wasser vorhanden ost  

  if (adc_wert_wasser_leitfaehigkeit < wasser_schwellwert) {

    tft.setTextColor(TFT_RED,TFT_BLACK);
    tft.drawString("Wasser nicht okay!        ", 1, 60, 2);
    tft.drawString("                          ", 1, 80, 2);
    tft.drawString("Erneut messen <F1>        ", 1, 100, 2);
    delay(25);

      if (lese_tasten() == 2) {
        delay(250);
        program_point = 5;
        tft.fillScreen(TFT_BLACK);
      } 
  }  

// Auf Leitungswasser prüfen

  if (adc_wert_wasser_leitfaehigkeit > wasser_schwellwert_leitungswasser) {

    tft.setTextColor(TFT_RED,TFT_BLACK);
    tft.drawString("Leitungswasser erkannt!   ", 1, 60, 2);
    tft.drawString("Nur destilliertes Wasser!!", 1, 80, 2);
    tft.drawString("Erneut messen <F1>        ", 1, 100, 2);
    delay(25);

      if (lese_tasten() == 2) {
        delay(250);
        program_point = 5;
        tft.fillScreen(TFT_BLACK);
      } 
  } 

// Auf Kurzschluss prüfen

  if (adc_wert_wasser_leitfaehigkeit > wasser_schwellwert_kurzschluss) {

    tft.setTextColor(TFT_RED,TFT_BLACK);
    tft.drawString("Kurzschluss erkannt       ", 1, 60, 2);
    tft.drawString("Bitte Elektroden pruefen  ", 1, 80, 2);
    tft.drawString("Erneut messen <F1>        ", 1, 100, 2);
    delay(25);

      if (lese_tasten() == 2) {
        delay(250);
        program_point = 5;
        tft.fillScreen(TFT_BLACK);
      } 
  } 


}


/////////////////////////////////////////////////////////////////////////// Elektrolyse
void elektrolyse () {

  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.drawString("Elektrolyse", 2, 0, 4);

  // Elektrolysedauer berechnen
  dauer_in_minuten = (((((107.87*elektrolyse_ma*1)/96485)/100)*ppm_wert)*13400)*wasser_liter;
  
   tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.drawString("Dauer in Min", 2, 35, 2);
  tft.setCursor(88,35,2);
  tft.println(dauer_in_minuten);  

  // Timer ablaufen lassen
  unsigned long previousMillis_elektrolyse = 0; // Windstärke prüfen
  unsigned long interval_elektrolyse = 30000; 
  

  if (millis() - previousMillis_elektrolyse > interval_elektrolyse) {
      previousMillis_elektrolyse = millis(); 
      // Windstärke prüfen
      Serial.println("Elektrolyse ... läuft");
      
      program_point = 8;
      tft.fillScreen(TFT_BLACK);
     
  } else {

  }
  

/*

PPM Berechnen

m = M * I * t / (z * F)

M = Molare Masse 107,87
I = Strom in A
t = Zeit in Sekunden
z = Ladungszahl 1
F = Faraday Konstante 96485

1,0787




*/




}

/////////////////////////////////////////////////////////////////////////// Elektrolyse umkehr
void elektrolyse_ende () {

  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.drawString("Fertig", 40, 20, 4);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.drawString("Weiter - ", 35, 90, 2);
  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.drawString("ok", 95, 90, 2);  

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
  
  Serial.println("Case 3 - Umpolzeit");
  umpolzeit ();

break;

case 4:
  
  Serial.println("Case 4 - Werte anzeigen");
  setup_uebersicht ();

break;

case 5:
  
  Serial.println("Case 5 - Wasserqualität prüfen");
  wasser_testen_1 ();

break;

case 6:
  
  Serial.println("Case 6 - Messung starten");
  wasser_testen_2 ();

break;

case 7:
  
  Serial.println("Case 7 - Elektrolyse starten");
  elektrolyse ();

break;

case 8:
  
  Serial.println("Case 7 - Fertig");
  elektrolyse_ende ();

break;

}


}