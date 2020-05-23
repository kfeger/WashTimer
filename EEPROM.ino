/*
   Hier werden die Werte im EEPROM geprüft
   und die Werte für die Entfernung abgelegt.
   Mit einem Poti kann die Schaltentfernung eingestellt werden.
   Adresse 0: 0x55, Adresse 1: 0xaa sind Prüfbytes
*/

void CheckEE(void) {
  uint16_t CheckValue = 0;
  CheckValue = (EEPROM.read(0) << 8) | EEPROM.read(1);
  if (CheckValue == 0x55aa) {
    Serial.println("EEPROM ok");
  }
  else {
    Serial.println("EEPROM NICHT ok, schreibe Default");
    EEPROM.write(0, 0x55);
    EEPROM.write(1, 0xaa);
    int EEData = 25;
    EEPROM.put(2, EEData);  // default 25cm, 255cm
  }
}

/*
   Hier wird der Sollwert der Entfernung zum Einschalten
   des WashTimer gesetzt und ins EEPROM gespeichert.
*/
void SetDistance(void) {
  int SollEntfernung;
  int Distance;
  int TempDistance;
  long LastSave, LastShow;
  LastShow = millis();
  Led.setBrightness(BRIGHT_LOW);
  Led.clear();
  Led.show();
  Led.show();
  LastSave = millis();
  while (!digitalRead(ADJ_MESS)) {
    if ((millis() - LastShow) > 100) {
      LastShow = millis();
      TempDistance = analogRead(A0);
      SollEntfernung = map(TempDistance, 0, 1023, MIN_DISTANCE, MAX_DISTANCE);
      Distance = Abstand.ping_cm();
      Serial.print(TempDistance);
      Serial.print("...");
      Serial.print(SollEntfernung);
      Serial.print("...");
      Serial.println(Distance);
      if ((Distance > SollEntfernung) || !Distance) {
        Led.setPixelColor(2, MAG);
        Led.setPixelColor(3, MAG);
      }
      else {
        Led.setPixelColor(2, GRUEN);
        Led.setPixelColor(3, GRUEN);
      }
      Led.show();
    }
    if ((millis() - LastSave) > 5000) { // einmal pro 5 sec sichern
      Serial.print("Soll Entfernung = ");
      Serial.print(SollEntfernung);
      Serial.println("cm");
      EEPROM.put(2, SollEntfernung);
      Led.setPixelColor(0, ROT);
      Led.setPixelColor(1, ROT);
      Led.show();
      Buzzer100();
      delay(200);
      Led.setPixelColor(0, 0);
      Led.setPixelColor(1, 0);
      Led.show();
      LastSave = millis();
    }
  }
}
