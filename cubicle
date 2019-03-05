#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define TRIG_PIN  4
#define ECHO_PIN  5
#define LED_PIN   7
#define RELAY_PIN 8

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     4

#define MAX_RADAR_RANGE_CM  2200
#define DISTANCE_THRESHOLD_CM 50
#define FAR_DELAY_MILLIS   10000

#define SECS_PER_MIN  (60UL)
#define SECS_PER_HOUR (3600UL)
#define SECS_PER_DAY  (SECS_PER_HOUR * 24L)
#define numberOfSeconds(_time_) (_time_ % SECS_PER_MIN)  
#define numberOfMinutes(_time_) ((_time_ / SECS_PER_MIN) % SECS_PER_MIN) 
#define numberOfHours(_time_) (( _time_% SECS_PER_DAY) / SECS_PER_HOUR)
#define elapsedDays(_time_) ( _time_ / SECS_PER_DAY)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
boolean detectTarget;
boolean isFar;
boolean isRelayOn;
unsigned long lastDetectTime;
unsigned long nearStartTime;
unsigned long farStartTime;

String line1 = "Cubicle Radar  v1.0.0";
String line2 = "--- by Uri Kalish ---";

void setup() {
  Serial.begin(9600);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  lastDetectTime = millis();  
  nearStartTime = millis();
  farStartTime = millis();
  detectTarget = true;
  isRelayOn = true;
  isFar = false;
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.display();
  display.clearDisplay();
}

void loop() {
  int distance = radarPing();   
  if (distance <= DISTANCE_THRESHOLD_CM) {
    detectTarget = true;
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
    lastDetectTime = millis();
    if (isFar) {
      isFar = false;
      nearStartTime = millis();
    }
  } else {
    detectTarget = false;
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(LED_PIN, LOW);
    if (!isFar && ((millis() - lastDetectTime) > FAR_DELAY_MILLIS)) {
      isFar = true;
      farStartTime = millis();
    }
  }
  if (isFar) {
    isRelayOn = false;
    digitalWrite(RELAY_PIN, LOW);
  } else {
    isRelayOn = true;
    digitalWrite(RELAY_PIN, HIGH);
  }
  goDisplay(distance);
  delay(1000);
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
  distance = duration*0.0343/2;
  //Serial.println(distance);   
  return distance; 
}

void printDigits(byte digits){
 display.print(":");
 if (digits < 10) {
   display.print("0");
 }
 display.print(digits, DEC);  
}

void printTime(unsigned long totalSeconds) {
  display.print(elapsedDays(totalSeconds), DEC);  
  printDigits(numberOfHours(totalSeconds));  
  printDigits(numberOfMinutes(totalSeconds));
  printDigits(numberOfSeconds(totalSeconds));  
}

void goDisplay(int distance) {
  display.clearDisplay();
  display.setTextColor(WHITE);        
  display.setCursor(0,0);             
  display.setTextSize(1);
  
  display.println(line1);

  display.println(line2);

  unsigned long curTime = millis();

  display.print("RNG : ");
  String rngTrg = "";
  if (distance <= MAX_RADAR_RANGE_CM) {
    String distanceStr = String(distance);
    display.print(distanceStr);
    display.println("cm");
  } else {
    display.println("---");
  }
  
  display.print("TRG : ");
  if (detectTarget) {
    display.println("NEAR"); 
  } else {
    display.println("FAR"); 
  }

  display.print("N/F : ");
  if (!isFar) {
    display.print("N ");
    printTime((curTime - nearStartTime) / 1000.0);
    display.println();
  } else {
    display.print("F ");  
    printTime((curTime - farStartTime) / 1000.0);
    display.println();
  }

  display.print("RLY : ");
  if (isRelayOn) {
    display.println("ON");  
  } else {
    display.println("OFF");
  }

  display.println("---------------------");
  
  display.print("TOT : T ");
  printTime(curTime / 1000.0);
  display.println(); 
     
  display.display();
}
