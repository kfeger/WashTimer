/*
   Inspiriert von hier: https://www.hackster.io/331510/wash-a-lot-bot-a-diy-hand-washing-timer-2df500
   Auch hier für simple Aduinos (Uno, Nano, Pro...)
   30s-Timer fürs Händewaschen.
   Pindefinitionen
   Pin 2  Servo
   Pin 3  US-Entf.-Messer Echo
   Pin 4  US-Entf.-Messer Trigger
   Pin 5  4 x NeoPixel
   Pin 6  Umschaltung Einstellung(0), Betrieb(1)
   Pin 7  Umschaltung der Servo-Richtung bei unterschiedlichen Stellrichtungen
   Pin 8  Ton abschalten (der Buzzer-Pin wird bei "off" auf Pin 99 gesetzt)
   Pin 10 Buzzer
   Pin A0 Poti Schaltentfernung
*/
#include <EEPROM.h>
#include <NewPing.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

#define SERVO 2
#define ECHO_PIN 3
#define TRIGGER_PIN 4
#define NEO_PIN 5
#define ADJ_MESS 6
#define SERVO_DIR 7
#define SOUND_OFF 8
#define BUZZER 10
#define POTI A0

void CheckEE(void);
void SetDistance(void);
void State0(void);
void State1(void);

#define DISTANCE 25 // default Entfernung
#define MAX_DISTANCE 100
#define MIN_DISTANCE 10
#define WASHTIME 30000  // 30s Händewasche

Servo Zeiger;
NewPing Abstand(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Adafruit_NeoPixel Led(4, NEO_PIN, NEO_GRB + NEO_KHZ800);  // Anz., Pin, Funktion
#define ROT   0xff0000
#define GRUEN 0x00ff00
#define GELB  0xff8800
#define BLAU  0xff
#define MAG   0xff00ff

#define BRIGHT_HIGH 128
#define BRIGHT_LOW 50


long LastPing = 0;
int Entfernung, NahZaehler, EntfernungGrenze;
bool StartZeiger = false, ServoDir = false;
int ServoBeginn = 0, ServoEnde = 180;

void Buzzer100(void) {
  if (digitalRead(SOUND_OFF)) {
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);
  }
  else {
    delay(100);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(ADJ_MESS, INPUT_PULLUP);
  pinMode(SERVO_DIR, INPUT_PULLUP);
  pinMode(SOUND_OFF, INPUT_PULLUP);
  pinMode(NEO_PIN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  // Richtungsauswahl je nach verbautem Servo
  if (digitalRead(SERVO_DIR)) {
    ServoBeginn = 175;
    ServoEnde = 5;
  }
  else {
    ServoBeginn = 5;
    ServoEnde = 175;
  }
  
  Led.begin();
  Led.show();
  Led.setBrightness(BRIGHT_LOW);
  Zeiger.attach(SERVO);
  delay(100);
  Zeiger.write(ServoBeginn);
  delay(1000);
  Zeiger.detach();
  CheckEE();  //Müll im EEPROM? Dann init.
  EntfernungGrenze = (int)EEPROM.read(2);
  Serial.println(EntfernungGrenze);
  LastPing = millis();
  randomSeed(millis());

}

void loop() {
  if (!digitalRead(6)) {
    SetDistance();
  }
  else {
    State0();
    State1();
  }
}
