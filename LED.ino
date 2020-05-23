void rainbow(int wait) {
  long LastBeep;
  long firstPixelHue;
  LastBeep = millis();
  // Thanks to Adafruit!
  for (firstPixelHue = 0; firstPixelHue < 65536; firstPixelHue += 256) {
    for (int i = 0; i < Led.numPixels(); i++) { // For each pixel in strip...
      int pixelHue = firstPixelHue + (65536L / Led.numPixels());
      Led.setPixelColor(i,Led.ColorHSV(pixelHue)); // Led.gamma32(Led.ColorHSV(pixelHue)));
    }
    Led.show(); // Update strip with new contents
    int Position = map(firstPixelHue, 0, 65536L, ServoEnde, ServoBeginn);  //langsamer Rücklauf
    //Serial.println(firstPixelHue);
    if((millis() - LastBeep) >= 500) {
      LastBeep = millis();
      if(digitalRead(SOUND_OFF))
        digitalWrite(BUZZER, !digitalRead(BUZZER));
      else
        digitalWrite(BUZZER, LOW);
    }
    Zeiger.write(Position);
    delay(wait);  // Pause for a moment
  }
  digitalWrite(BUZZER, LOW);
}

void SetStrand(unsigned long LedColor, int Hell) {
  Led.setBrightness(Hell);
  for (int i = 0; i < Led.numPixels(); i++) { // For each pixel in strip...
    Led.setPixelColor(i, LedColor);
  }
  Led.show();
}
