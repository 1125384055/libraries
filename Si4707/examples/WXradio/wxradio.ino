#include <Wire.h>
#include <Si4707.h>
const int senPin = 5;
const int rstPin = 4;
Si4707 wb(rstPin, senPin);
unsigned long tuneFrequency = 162550;   // Fulton SAME: 013121  Atlanta KEC80 162.550
int rxVolume = 63;  // Maximum loudness (should be between 0 and 63)

void setup() {
  Serial.begin(9600);
  if (!wb.begin()) while(1);
  if (wb.setWBFrequency(tuneFrequency)) {Serial.println(F("Tune Success!"));}
  else Serial.println(F("Tune unsuccessful"));
  printMenu();n
}

void loop() {
  while( !Serial.available() ) ; char c = Serial.read();
  switch (c) {
    case 'u': wb.tuneWBFrequency(1);    break;
    case 'i': wb.tuneWBFrequency(10);   break;
    case 'd': wb.tuneWBFrequency(-1);   break; 
    case 'f': wb.tuneWBFrequency(-10);  break;
    case '1': wb.setMuteVolume(1);      break;
    case '0': wb.setMuteVolume(0);      break;
    case '9': wb.setVolume(++rxVolume); break; 
    case '2': wb.setVolume(--rxVolume); break;
    case 'h': default: printMenu();     break;
  }
}

void printMenu() {
  Serial.println(F("Si4707 Weather Band Radio 162.4 - 162.55 MHz"));
  Serial.print((float) wb.getWBFrequency() * 0.0025, 3); Serial.print(F(" MHz"));
  wb.printSAMEStatus();
  Serial.print(F(" | Offset ")); Serial.print(wb.getFreqOffset());
  Serial.print(F(" | Volume ")); Serial.print(rxVolume);
  Serial.print(F(" | RSSI ")); Serial.print(wb.getRSSI());  
  Serial.print(F(" | SNR ")); Serial.println(wb.getSNR());
  Serial.print(F("Menu:  (h)"));
  Serial.print(F("\t Tune 2.5kHz (u) up | (d) down"));
  Serial.println(F("\t Tune 25 kHz (i) up | (f) down"));
  Serial.print(F("\t Mute (1) on | (0) off"));
  Serial.println(F("\t Volume (2) down | (9) up"));
  Serial.println("--------------------");
}
