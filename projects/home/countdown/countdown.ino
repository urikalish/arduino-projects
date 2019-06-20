unsigned long startTime;
unsigned long millisToCount;
int pins6[6] = {2, 3, 4, 5, 6, 7};
int pins3[3] = {8, 9, 10};
int button1Pin = 11;
int button2Pin = 12;
int buzzerPin = 13;
int finalCountdown;
int p;
int n;

void setup() {
  Serial.begin(9600);
  Serial.println("start");
  millisToCount = 60;
  millisToCount *= 60;
  millisToCount *= 1000;
  millisToCount += 100;
  finalCountdown = -1;
  startBuzzer(440);
  for (p = 0; p < 6; p++) {
    pinMode(pins6[p], OUTPUT);
  }
  for (p = 0; p < 3; p++) {
    pinMode(pins3[p], OUTPUT);
  }
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  display3LedsNum(7);
  display6LedsNum(63);
  delay(1000);
  stopBuzzer();
  display3LedsNum(0);
  display6LedsNum(0);
  startTime = millis();
}

int getButtonsPressed() {
  int buttonsState = 0; 
  int button1State = digitalRead(button1Pin);
  int button2State = digitalRead(button2Pin);
  if (button1State == LOW && button2State == LOW) {
    buttonsState = 3;
  } else if (button1State == LOW) {
    buttonsState = 1;
  } else if (button2State == LOW) {
    buttonsState = 2;
  }
  return buttonsState;
}

long getMillisLeft() {
  unsigned long curTime = millis();
  unsigned long millisPassed = curTime - startTime;
  long millisLeft = millisToCount - millisPassed;
  return millisLeft;  
}

void changeTime(double secondsLeft, bool shouldAdd) {
  startTime = millis();
  unsigned long minutesLeft = secondsLeft / 60 + 1;
  int m5 = minutesLeft / 5; 
  if (shouldAdd) {
      m5++;     
  } else if (!shouldAdd) {
      m5--;  
  }
  if (m5 > 12) {
      m5 = 1;  
  } else if (m5 < 1) {
      m5 = 12;  
  }
  millisToCount = m5;
  millisToCount *= 5;
  millisToCount *= 60;
  millisToCount *= 1000;
  millisToCount += 100;
}

void loop() {
  unsigned long loopStartTime = millis();
  long millisLeft = getMillisLeft();
  if (millisLeft > 0) {
    double secondsLeft = millisLeft / 1000;
    int buttonsState = getButtonsPressed();
    if (buttonsState == 1) {
      changeTime(secondsLeft, false);
    } else if (buttonsState == 2) {
      changeTime(secondsLeft, true);
    }
    if (buttonsState != 0) {
      millisLeft = getMillisLeft();      
      secondsLeft = millisLeft / 1000;
      handleLeds(secondsLeft - 1);
      signalTime(secondsLeft);          
    } else {
      if ((finalCountdown == -1) && (secondsLeft <= 10)) {
        finalCountdown = 10;
      }
      if (finalCountdown == 0) {
        endCount();
      } else if (finalCountdown > -1) {
        finalCountdown--;
        warnEnding();
      } else if ((int)secondsLeft % 60 == 0) {
        handleLeds(secondsLeft - 1);
        signalTime(secondsLeft);
        //signal1Minute();
      } else {
        handleLeds(secondsLeft);
        tick(secondsLeft);
      }
    }
    endLoopDelay(loopStartTime);
  } else {
    endCount();    
  }
}

void endLoopDelay(unsigned long loopStartTime){
  unsigned long d = millis() - loopStartTime;
  d %= 1000;
  d = 1000 - d;
  if (d < 0) {
    d = -d;
  }
  if (d < 100){
    d += 1000;
  }
  delay(d);
}

void tick(double secondsLeft) {
  shortBuzzer(880, 1);  
}

//void signal1Minute() {
//  shortBuzzer(440, 100);
//}

void signalTime(double secondsLeft) {
  unsigned long minutesLeft = secondsLeft / 60;  
  int m10 = minutesLeft / 10;
  int m1 = minutesLeft - (m10 * 10);
  int i;
  for (i = 0; i < m10; i++) {
    shortBuzzer(880, 100);
    delay(100);
  }
  delay(100);
  for (i = 0; i < m1; i++) {
    shortBuzzer(440, 100);
    delay(100);
  }
}

void warnEnding() {
  display3LedsNum(7);
  display6LedsNum(63);
  shortBuzzer(880, 500);
  display3LedsNum(0);
  display6LedsNum(0);  
}

void endCount() {
  finalCountdown = 0;
  display3LedsNum(7);
  display6LedsNum(63);
  shortBuzzer(880, 2000);
  display3LedsNum(0);
  display6LedsNum(0);
  Serial.println("end");
  delay(3600000);  
}

void startBuzzer(double frequency) {
  tone(buzzerPin, frequency);
}

void stopBuzzer() {
  noTone(buzzerPin);
}

void shortBuzzer(double frequency, unsigned long duration) {
  startBuzzer(frequency);
  delay(duration);
  stopBuzzer();
}

void handleLeds(double secondsLeft) {
  handle3Leds(secondsLeft);
  handle6Leds(secondsLeft);
}

void handle3Leds(double secondsLeft) {
  unsigned long minutesLeft = secondsLeft / 60 + 1;
  if (minutesLeft > 40) {
    display3LedsNum(4);
  }
  else if (minutesLeft > 20) {
    display3LedsNum(2);
  }
  else if (minutesLeft > 0) {
    display3LedsNum(1);
  } else {
    display3LedsNum(0);
  }
  delay(100);
  display3LedsNum(0);
}

void handle6Leds(double secondsLeft) {
  unsigned long minutesLeft = secondsLeft / 60 + 1;
  display6LedsNum(minutesLeft);
}

void display3LedsNum(int num) {
  for (p = 0; p < 3; p++) {
    digitalWrite(pins3[p], LOW);
  }
  int rem = num;
  int fact[3] = {4, 2, 1};
  for (int i = 0; i < 3; i++) {
    if (rem / fact[i] > 0) {
      digitalWrite(pins3[2 - i], HIGH);
      rem -= fact[i];
    }
  }
}

void display6LedsNum(int num) {
  for (p = 0; p < 6; p++) {
    digitalWrite(pins6[p], LOW);
  }
  int rem = num;
  int fact[6] = {32, 16, 8, 4, 2, 1};
  for (int i = 0; i < 6; i++) {
    if (rem / fact[i] > 0) {
      digitalWrite(pins6[5 - i], HIGH);
      rem -= fact[i];
    }
  }
}
