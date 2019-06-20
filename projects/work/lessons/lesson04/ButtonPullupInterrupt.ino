#define BTN_PIN 3
#define LED_PIN 4

boolean ledState = false;
volatile boolean shouldChangeState = false;

void setup() {
  //Serial.begin(9600);
  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(BTN_PIN), onBtnChange, FALLING);
}

void loop() {
  if (shouldChangeState) {
    ledState = !ledState;
    shouldChangeState = false;     
  }
  if (ledState) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);  
  }
  delay(1000);
}

void onBtnChange() {
  shouldChangeState = true;
}

