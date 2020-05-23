/*
   Status 0, Ruhezustand
   es wird alle 100ms die Nähe zu einem Objekt gemessen
*/

void State0(void) {
  if ((millis() - LastPing) >= 100) { // alle 100ms Entfernung messen
     EEPROM.get(2, EntfernungGrenze);
    Entfernung = Abstand.ping_cm();
    if ((Entfernung) && (Entfernung < EntfernungGrenze)) {  // größer Null und näher als EntfernungGrenze
      NahZaehler++;
      if (NahZaehler > 15) {
        StartZeiger = true;
        SetStrand(GRUEN, BRIGHT_HIGH);
      }
      else {
        StartZeiger = false;
        SetStrand(GELB, BRIGHT_LOW);
      }
    }
    else {
      NahZaehler = 0;
      SetStrand(ROT, BRIGHT_LOW/4);
    }
    LastPing = millis();
  }
}
