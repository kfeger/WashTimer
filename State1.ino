/*
   State1() lässt den Zeiger laufen, wenn der
   Trigger einmal ausgelöst wurde.
*/

void State1(void) {
  int ZeigerPosition;
  if (StartZeiger) {
    Zeiger.attach(SERVO);
    Zeiger.write(ServoBeginn);  // Servo auf Null
    Buzzer100();
    LastPing = millis();
    while ((millis() - LastPing) < WASHTIME) {
      ZeigerPosition = map((millis() - LastPing), 0, WASHTIME, ServoBeginn, ServoEnde);
      Zeiger.write(ZeigerPosition);
      delay(10);
    }
    StartZeiger = false;
    Led.setBrightness(BRIGHT_HIGH);
    rainbow(30);
    Led.setBrightness(BRIGHT_LOW);
    Zeiger.write(ServoBeginn);
    delay(50); 
    Zeiger.detach();
  }
}
