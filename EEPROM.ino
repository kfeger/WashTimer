/*
   Hier werden die Werte im EEPROM geprüft
   und die Werte für die Entfernung abgelegt.
   Mit einem Poti kann die Schaltentfernung eingestellt werden.
   Adresse 0: 0x55, Adresse 1: 0xaa sind Prüfbytes
*/

void CheckEE(void) {
  int CheckValue = 0;
  CheckValue = (EEPROM.read(0) << 8) | EEPROM.read(1);
  if (CheckValue == 0x55aa) {
    Serial.println("EEPROM ok");
  }
  else {
    Serial.println("EEPROM NICHT ok, schreibe Default");
    EEPROM.write(0, 0x55);
    EEPROM.write(1, 0xaa);
    EEPROM.write(2, 25);  // default 25cm, 255cm
  }
}

/*
   Hier wird der Sollwert der Entfernung zum Einschalten
   des WashTimer gesetzt und ins EEPROM gespeichert.
*/
void SetDistance(void) {
  byte SollEntfernung;
  long LastSave, LastShow;
  LastShow = millis();
  Led.setBrightness(32);
  Led.setPixelColor(0, ROT);
  Led.show();
  LastSave = millis();
  while (!digitalRead(ADJ_MESS)) {
    SollEntfernung = (byte)map(analogRead(A0), 0, 1023, 5, 100);
    if ((millis() - LastShow) > 100) {
      LastShow = millis();
      if (Abstand.ping_cm() > SollEntfernung) {
        Led.setPixelColor(1, MAG);
        Led.setPixelColor(2, MAG);
      }
      else {
        Led.setPixelColor(1, GRUEN);
        Led.setPixelColor(2, GRUEN);
      }
      Led.show();
    }
    if ((millis() - LastSave) > 5000) { // einmal pro 5 sec sichern
      Serial.print("Soll Entfernung = ");
      Serial.print(SollEntfernung);
      Serial.println("cm");
      digitalWrite(BUZZER, HIGH);
      EEPROM.write(2, SollEntfernung);
      Led.setPixelColor(0, GRUEN);
      Led.show();
      delay(100);
      digitalWrite(BUZZER, LOW);
      delay(200);
      Led.setPixelColor(0, ROT);
      Led.show();
      LastSave = millis();
    }
  }
}
