#include "Wire.h"
#include "LCD.h"
#include "LiquidCrystal_I2C.h"
#include "IRLremote.h"

// --- PINS ---
// LCD SDA --> A4
// LCD SLA --> A5
// IR reciever --> 2
// Speaker -> 4

#define IRRECV_PIN 2
#define SPEAKER_PIN 4

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7);
CNec IRLremote;
String arduinoMsg = "";
boolean sendMsg = false;
const long IR_KEY_PLAY = 0x43;
const long IR_KEY_PREV = 0x44;

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  if (!IRLremote.begin(IRRECV_PIN)) {
    Serial.println("Invalid IR sensor pin!");  
  }    
  delay(1000);  
}

void loop() {
  getMsgFromComputer();
  sendMsgToComputer();  
  delay(100);
}

void getMsgFromComputer() {
  String computerMsg = "";
  String s = readSerial();
  while (s != "") {
    computerMsg += s;
    s = readSerial();  
  }
  if (computerMsg != "") {
    print2LCD("Computer>Arduino", String(computerMsg));
    for (int i = 0; i < computerMsg.length(); i++) {
      beep2();
      delay(100);    
    }
  }  
}

void sendMsgToComputer() {
  readIR();
  if (sendMsg) {    
    print2LCD("Arduino>Computer", String(arduinoMsg));
    for (int i = 0; i < arduinoMsg.length(); i++) {
      beep2();
      delay(100);    
    }
    Serial.println(String(arduinoMsg));    
    arduinoMsg = "";
  }  
}

void print2LCD(String line1, String line2) {
  lcd.clear();
  lcd.home();
  lcd.setCursor(0,0);  
  lcd.print(line1);
  lcd.setCursor(0,1);
  lcd.print(line2);
}

void beep1() {
  tone(SPEAKER_PIN, 880, 50);
}

void beep2() {
  tone(SPEAKER_PIN, 1760, 50);
}

void readIR() {
  sendMsg = false;
  const long btnNumbers[10] = {0x16, 0xC, 0x18, 0x5E, 0x8, 0x1C, 0x5A, 0x42, 0x52, 0x4A};
  if (IRLremote.available()) {
    auto data = IRLremote.read();
    //Serial.println(data.command, HEX);
    if (IR_KEY_PREV == data.command) {
      beep1();
      arduinoMsg = "";    
    } else if ((IR_KEY_PLAY == data.command) && (arduinoMsg.length() > 0)) {
      //beep1();
      sendMsg = true;  
    } else {
      for (int i = 0; i < 10; i++) {
        if (btnNumbers[i] == data.command) {
          beep1();
          arduinoMsg += String(i);
        }       
      }
    }
  }
}

String readSerial() {
  if (Serial.available() > 0) {
    char receivedChar = Serial.read();
    return String(receivedChar);
  }
  return "";  
}
