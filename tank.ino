#include <Servo.h>

//Motor
const byte RSP_PIN = 5;
const byte RFW_PIN = 4;
const byte RBW_PIN = 2;
const byte LSP_PIN = 6;
const byte LFW_PIN = 7;
const byte LBW_PIN = 8;
int mySpeed = 0;

//Servo
const byte SERVO_PIN = 11;
int headAngle = 90;
Servo myServo;

//Radar
const byte TRIG_PIN = 9;
const byte ECHO_PIN = 10;
int myDistance = 0;

void setup() {
  Serial.begin(9600);
  pinMode(RSP_PIN, OUTPUT);
  pinMode(RFW_PIN, OUTPUT);
  pinMode(RBW_PIN, OUTPUT);
  pinMode(LSP_PIN, OUTPUT);
  pinMode(LFW_PIN, OUTPUT);
  pinMode(LBW_PIN, OUTPUT);
  myServo.attach(SERVO_PIN);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT); 
  stopTank();  
  rotateServo(headAngle);
  delay(5000);
}

void stopTank() {
  digitalWrite(RSP_PIN, 0);
  digitalWrite(RFW_PIN, LOW);
  digitalWrite(RBW_PIN, LOW);
  digitalWrite(LSP_PIN, 0);
  digitalWrite(LFW_PIN, LOW);
  digitalWrite(LBW_PIN, LOW);  
}

void moveForward(int speed) {
  stopTank();
  digitalWrite(RFW_PIN, HIGH);
  digitalWrite(LFW_PIN, HIGH);
  analogWrite(RSP_PIN, speed);
  analogWrite(LSP_PIN, speed);  
}

void moveBackward(int speed) {
  stopTank();
  digitalWrite(RBW_PIN, HIGH);
  digitalWrite(LBW_PIN, HIGH);
  analogWrite(RSP_PIN, speed);
  analogWrite(LSP_PIN, speed);  
}

void turnRight(int speed) {
  stopTank();  
  digitalWrite(LFW_PIN, HIGH);
  digitalWrite(RBW_PIN, HIGH);
  analogWrite(RSP_PIN, speed);
  analogWrite(LSP_PIN, speed);  
}

void turnLeft(int speed) {
  stopTank();
  digitalWrite(RFW_PIN, HIGH);
  digitalWrite(LBW_PIN, HIGH);  
  analogWrite(RSP_PIN, speed);
  analogWrite(LSP_PIN, speed);  
}

void turn() {
  Serial.println("turn");
  int lDistance = 0;
  int rDistance = 0;
  delay(1000);
  rotateServo(5);
  delay(2000);
  lDistance = radarPing();
  delay(100);
  rotateServo(175);
  delay(2000);
  rDistance = radarPing();
  delay(100);
  if (lDistance > rDistance) {
    turnLeft(255);       
  } else {
    turnRight(255); 
  }
  int time = random(500, 1000);
  delay(time);
  stopTank();
  rotateServo(90);  
  delay(2000);
}

void rotateServo(int ang) {
  headAngle = ang;
  myServo.write(headAngle);
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
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}

void loop() {
  myDistance = radarPing();
  if (myDistance > 50) {
    mySpeed = min(mySpeed + 5, 255);
    moveForward(mySpeed);
    rotateServo(90);
  } else {
    stopTank();
    mySpeed = 0;
    turn();      
  }
  delay(100);
}
