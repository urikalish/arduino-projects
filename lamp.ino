// Speaker to pin 4
// IR reciever to pin 2

#include "IRLremote.h"
#define IRRECV_PIN 2
#define SPEAKER_PIN 4
#define R_PIN 9
#define G_PIN 10
#define B_PIN 11

CNec IRLremote;
int colors[3] = {255, 255, 255};
int myStatus;
boolean myToggle;

void setup() {  
  while (!Serial);
  Serial.begin(9600);
  Serial.println("setup");

  pinMode(SPEAKER_PIN, OUTPUT);
  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
  
  // Start reading the remote. PinInterrupt or PinChangeInterrupt* will automatically be selected
  if (!IRLremote.begin(IRRECV_PIN)) {
    Serial.println("Invalid IR sensor pin!");  
  }

  randomSeed(analogRead(A0));
    
  myStatus = 2;
  myToggle = true;
}

void goBeep(int number) {
  if (number == 0) {
    tone(SPEAKER_PIN, 880, 500);  
  } else {
    for (int i = 0; i < number; i++) {
      tone(SPEAKER_PIN, 880, 50);
      delay(200);
    }
  }
}

void goLed(int r, int g, int b) {
  analogWrite(R_PIN, r);
  analogWrite(G_PIN, g);
  analogWrite(B_PIN, b);  
}

void readIR() {
  if (IRLremote.available()) {
    auto data = IRLremote.read();
    Serial.println(data.command, HEX);
    const long btnNumbers[10] = {0x16, 0xC, 0x18, 0x5E, 0x8, 0x1C, 0x5A, 0x42, 0x52, 0x4A};
    for (int i = 0; i < 10; i++) {
      if (btnNumbers[i] == data.command) {
        goBeep(i); 
        myStatus = i;        
      }
    }
  }  
}

void turnOff() {
  goLed(0, 0, 0);
  delay(1000);  
}

void whiteLight() {
  goLed(255, 255, 255);
  delay(1000);  
}

void policeLight() {
  if (myToggle) {
    goLed(255, 0, 0);  
  } else {
    goLed(0, 0, 255);
  }
  myToggle = !myToggle;
  delay(200);
}

void colorChange() {
  goLed(colors[0], colors[1], colors[2]);
  int r = 0;
  int g = 0;
  int b = 0;
  int rnd = random(3);
  if (rnd == 0) {
    r = 128 + random(128);
    if (random(2) == 0) {
      g = random(256);
    } else {
      b = random(256);
    }
  } else if (rnd == 1) {
    g = 128 + random(128);
    if (random(2) == 0) {
      r = random(256);
    } else {
      b = random(256);
    }
  } else {
    b = 128 + random(128);
    if (random(2) == 0) {
      r = random(256);
    } else {
      g = random(256);
    }
  }
  const int steps = 255;    
  for (int i = 0; i <= steps; i++) {
    readIR();
    if (myStatus == 2) {
      goLed(colors[0] + i*(r-colors[0])/steps, colors[1] + i*(g-colors[1])/steps, colors[2] + i*(b-colors[2])/steps);
      delay(100);
    }
  }
  colors[0] = r;
  colors[1] = g;
  colors[2] = b;
  goLed(colors[0], colors[1], colors[2]);
}

void loop() {
  readIR();
  int d = 1000;
  if (myStatus == 0) {
    turnOff();
  } else if (myStatus == 1) {
    whiteLight();
  } else if (myStatus == 2) {
    colorChange();
  } else if (myStatus == 3) {
    policeLight(); 
  }
}
