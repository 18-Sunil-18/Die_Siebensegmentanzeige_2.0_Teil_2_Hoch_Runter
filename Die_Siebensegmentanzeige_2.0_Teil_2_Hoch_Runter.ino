byte segmente[10] = { B01000000,    // 0
                      B01111001,    // 1
                      B00100100,    // 2
                      B00110000,    // 3
                      B00011001,    // 4
                      B00010010,    // 5
                      B00000010,    // 6
                      B01111000,    // 7
                      B00000000,    // 8
                      B00010000};   // 9

// -----------------------------------------------------------------

int taktPin = 8;    // SH_CP
int speicherPin = 9;    // ST_CP
int datenPin = 10;    // DS
int zaehler = 0;    // Zählvariable

int EingangHoch = A0,
    EingangRunter = A1;

#define DELAY0 500

// -----------------------------------------------------------------

// Funktion zum Übertragen der Informationen
void sendeBytes(int wert){
  digitalWrite(speicherPin, LOW);
  shiftOut(datenPin,taktPin, MSBFIRST, wert >> 8);
  shiftOut(datenPin,taktPin, MSBFIRST, wert & 255);
  digitalWrite(speicherPin, HIGH);
}

// -----------------------------------------------------------------

void zeigeWert(int wert){
  byte zehner = int(wert / 10);   // Ziffer der Zehnerstelle berechnen
  byte einer = wert - zehner * 10;    // Ziffer der Einerstelle berechnen
  sendeBytes(segmente[zehner] << 8 | segmente[einer]);    // Zehner und Einer
}

// -----------------------------------------------------------------

void HochZaehlen(){
  zeigeWert(zaehler);   // Wert anzeigen
  delay(DELAY0);   // Kurze Pause
  zaehler++;    // Inkrementierung (+1)
  if(zaehler > 99) zaehler=0;   // Wert > 99 ?
}

// -----------------------------------------------------------------

void RunterZaehlen(){
  zeigeWert(zaehler);   // Wert anzeigen
  delay(DELAY0);   // Kurze Pause
  zaehler--;    // Inkrementierung (-1)
  if(zaehler < 0) zaehler=99;   // Wert > 99 ?
}

// -----------------------------------------------------------------

void setup() {
  pinMode(taktPin, OUTPUT);
  pinMode(speicherPin, OUTPUT);
  pinMode(datenPin, OUTPUT);
  pinMode(EingangHoch, INPUT);
  pinMode(EingangRunter, INPUT);
}

// -----------------------------------------------------------------

void loop() {
  if(analogRead(EingangHoch) >= 1010){
    HochZaehlen();
  }
  if(analogRead(EingangRunter) >= 1010){
    RunterZaehlen();
  }
}
