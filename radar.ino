#include <Servo.h>

//Radar
const int trigPin = 9;
const int echoPin = 10;
const int minAngle = 0;
const int maxAngle = 180;
const int angleStep = 10;
const int mapPingCount = 30;

int minDistances[360];
int maxDistances[360];
int accDistances[360];

//Servo
Servo servo;
const int servoPin = 8;
int angle = 90;
boolean isUp = true;

void setup() {
  Serial.begin(9600);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);  
  servo.attach(servoPin);
  moveServo(90);
  delay(3000);
  for (int ang = minAngle; ang <= maxAngle; ang+=angleStep) {
    mapAngle(ang);
  }
}

void loop() {
  radarPing();
  delay(1000);
  //handleServo();
  delay(1000);
}

void mapAngle(int ang) {
  moveServo(ang);
  delay(1000);
  int arr[mapPingCount];
  int minVal = 10000;
  int maxVal = 0;
  int dst;
  for (int i = 0; i < mapPingCount; i++) {
    dst = radarPing();
    arr[i] = dst;
    delay(100); 
  }
  sortArr(arr);
  minDistances[ang] = arr[3]; 
  maxDistances[ang] = arr[mapPingCount-4];
  accDistances[ang] = arr[mapPingCount-4] - arr[3];
  Serial.print("ANG:");
  Serial.print(ang);
  Serial.print(", ACC:");
  Serial.print(accDistances[ang]);
  Serial.print(", DST:");  
  Serial.print(minDistances[ang]);
  Serial.print("-");
  Serial.println(maxDistances[ang]);
}

void sortArr(int arr[]) {
  boolean switched;
  do {
    switched = false;
    for (int i = 0; i < mapPingCount-1; i++) {
      if (arr[i] > arr[i+1]) {
        switched = true;
        int temp = arr[i];
        arr[i] = arr[i+1];
        arr[i+1] = temp;        
      }
    }
  } while (switched);
}

int radarPing() {
  long duration;
  int distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;  
  Serial.print(distance);
  Serial.println("cm");
  return distance; 
}

void handleServo() {
  if (isUp) {
    if (angle < maxAngle) {
      angle+=angleStep;
    } else {
      isUp = false;
    }  
  } else {
    if (angle > minAngle) {
      angle-=angleStep;
    } else {
      isUp = true;
    }      
  }
  moveServo(angle);
}

void moveServo(int ang) {
  servo.write(ang);  
}
