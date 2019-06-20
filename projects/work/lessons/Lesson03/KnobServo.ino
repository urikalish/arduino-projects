#include <Servo.h>

#define KNOB_PIN  A0
#define LED_PIN    3
#define SERVO_PIN  4

Servo servo;

void setup() {
  pinMode(KNOB_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  servo.attach(SERVO_PIN);
  Serial.begin(9600);
  while(!Serial);
}

void loop() {
  int knobVal = analogRead(KNOB_PIN);
  Serial.println(knobVal);
  analogWrite(LED_PIN, map(knobVal, 0, 1023, 0, 255));
  servo.write(map(knobVal, 0, 1023, 10, 170));
  delay(50);
}
