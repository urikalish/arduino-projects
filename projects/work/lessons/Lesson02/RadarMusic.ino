#define SPEAKER_PIN 7
#define TRIG_PIN 8
#define ECHO_PIN 9
#define MIN_DIST_CM 10
#define MAX_DIST_CM 50
#define MIN_FREQ_HZ 261
#define MAX_FREQ_HZ 523

void setup() {
  pinMode(SPEAKER_PIN, OUTPUT);  
  pinMode(TRIG_PIN, OUTPUT);  
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
  while(!Serial);
}

void loop() {
  int distance = radarPing();
  Serial.println(distance);
  distance = constrain(distance, MIN_DIST_CM, MAX_DIST_CM);
  Serial.println(distance);
  int playTone = map(distance, MIN_DIST_CM, MAX_DIST_CM, MIN_FREQ_HZ, MAX_FREQ_HZ);
  Serial.println(playTone);
  tone(SPEAKER_PIN, playTone);
  Serial.println();
  delay(300);
  noTone(SPEAKER_PIN); 
  delay(100);
}

int radarPing() {
  long duration;
  int distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration*0.034/2;  
  return distance; 
}
