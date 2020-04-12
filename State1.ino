/*
   State1() lässt den Zeiger laufen, wenn der
   Trigger einmal ausgelöst wurde.
*/

void State1(void) {
  int ZeigerPosition;
  if (StartZeiger) {
    Zeiger.write(0);  // Servo auf Null
    digitalWrite(BUZZER, HIGH);
    delay(100);   // Stellzeit abwarten
    digitalWrite(BUZZER, LOW);
    LastPing = millis();
    while ((millis() - LastPing) < WASHTIME) {
      ZeigerPosition = map((millis() - LastPing), 0, WASHTIME, 0, 180);
      Zeiger.write(ZeigerPosition);
      delay(10);
    }
    StartZeiger = false;
    Led.setBrightness(128);
    rainbow(10);
    Led.setBrightness(50);
    Zeiger.write(0);
    delay(50);
  }
}
