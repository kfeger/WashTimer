/*
 * Inspiriert von hier: https://www.hackster.io/331510/wash-a-lot-bot-a-diy-hand-washing-timer-2df500
 * Auch hier für simple Aduinos (Uno, Nano, Pro...)
 * 30s-Timer fürs Händewaschen.
 * Pindefinitionen
 * Pin 2  Servo
 * Pin 3, 4 US-Entf.-Messer Echo Trigger
 * Pin 5  4 x NeoPixel
 * Pin 6  Umschaltung Einstellung(0), Betrieb(1)
 * Pin 10 Buzzer
 * Pin A0 Poti Schaltentfernung
 */
 #include <EEPROM.h>
#include <NewPing.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

#define SERVO 2
#define TRIGGER_PIN 4
#define ECHO_PIN 3
#define NEO_PIN 5
#define ADJ_MESS 6
#define BUZZER 10
#define POTI A0

void CheckEE(void);
void SetDistance(void);
void State0(void);
void State1(void);

Servo Zeiger;
#define MAX_DISTANCE 200
NewPing Abstand(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Adafruit_NeoPixel Led(4, NEO_PIN, NEO_GRB + NEO_KHZ800);  // Anz., Pin, Funktion
#define ROT   0xff0000
#define GRUEN 0x00ff00
#define GELB  0xff8800
#define BLAU  0xff
#define MAG   0xff00ff

#define DISTANCE 25 // default Entfernung
#define WASHTIME 30000  // 30s Händewasche

long LastPing = 0;
int Entfernung, NahZaehler, EntfernungGrenze;
bool StartZeiger = false;

void setup() {
  Serial.begin(115200);
  pinMode(ADJ_MESS, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  Led.begin();
  Led.show();
  Led.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  Zeiger.attach(SERVO);
  Zeiger.write(0);
  delay(1000);
  CheckEE();  //Müll im EEPROM? Dann init.
  EntfernungGrenze = (int)EEPROM.read(2);
  Serial.println(EntfernungGrenze);
  LastPing = millis();

}

void loop() {
  if (!digitalRead(6))
    SetDistance();
  else {
    State0();
    State1();
  }
}
