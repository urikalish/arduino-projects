/* Blink a LED and play a sound
*
*  Physical Circuit:
*
*  Arduino PIN 4 --> 220 ohm Resistor 1st leg
*  220 ohm Resistor 2nd leg  --> LED positive (long) leg
*  LED negative (short) leg --> Arduino GND
*
*  Arduino PIN 8 --> Passive Speaker positive (long) leg
*  Passive Speaker negative (short) leg --> Arduino GND
*/

#define LED_PIN 4
#define SPEAKER_PIN 8

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH); //turn the LED on (HIGH is the voltage level)
  tone(SPEAKER_PIN, 440);      //play the note "La" (440Hz) via the speaker
  delay(1000);                 //wait for a second
  
  digitalWrite(LED_PIN, LOW);  //turn the LED off by making the voltage LOW
  noTone(SPEAKER_PIN);         //stop the speaker
  delay(1000);                 //wait for a second (before loop starts again)
}
