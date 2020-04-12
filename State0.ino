/*
   Status 0, Ruhezustand
   es wird alle 100ms die Nähe zu einem Objekt gemessen
*/

void State0(void) {
  if ((millis() - LastPing) >= 100) { // alle 100ms Entfernung messen
    EntfernungGrenze = (int)EEPROM.read(2);
    Entfernung = Abstand.ping_cm();
    if ((Entfernung) && (Entfernung < EntfernungGrenze)) {  // größer Null und näher als EntfernungGrenze
      NahZaehler++;
      if (NahZaehler > 15) {
        StartZeiger = true;
        SetStrand(GRUEN, 100);
      }
      else {
        StartZeiger = false;
        SetStrand(GELB, 50);
      }
    }
    else {
      NahZaehler = 0;
      SetStrand(ROT, 5);
    }
    LastPing = millis();
  }
}
