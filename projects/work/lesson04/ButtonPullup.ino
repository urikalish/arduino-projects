#define BTN_PIN 3
#define LED_PIN 4

void setup() {
  Serial.begin(9600);
  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  byte val = digitalRead(BTN_PIN);
  Serial.println(val);
  if (val == LOW) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);  
  }
  delay(100);
}
