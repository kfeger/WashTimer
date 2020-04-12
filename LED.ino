void rainbow(int wait) {
  long LastBeep;
  LastBeep = millis();
#define MULTIPLIER 2
  // Thanks to Adafruit!
  for (long firstPixelHue = 0; firstPixelHue < MULTIPLIER * 65536; firstPixelHue += 256) {
    for (int i = 0; i < Led.numPixels(); i++) { // For each pixel in strip...
      int pixelHue = firstPixelHue + (1 * 65536L / Led.numPixels());
      Led.setPixelColor(i, Led.gamma32(Led.ColorHSV(pixelHue)));
    }
    Led.show(); // Update strip with new contents
    int Position = map(firstPixelHue, 0, MULTIPLIER * 65536L, 180, 0);
    if((millis() - LastBeep) >= 500) {
      LastBeep = millis();
      digitalWrite(BUZZER, !digitalRead(BUZZER));
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
