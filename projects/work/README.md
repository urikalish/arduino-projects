# Links
* [Arduino site](https://www.arduino.cc/)
* [Fritzing site](http://fritzing.org/home/)

# Troubleshooting
* Port error in Windows Device Manager - Install driver from [WinDriver directory](https://github.com/urikalish/arduino-projects/tree/master/windriver).
* Strange compilation error on Verify - Close and reopen the IDE.
* Upload error - Validate correct board and port in the IDE Tools menu.

# Lessons

## Lesson #1 - LED Speaker - 10/02/19
* Introduction to [Arduino](https://www.arduino.cc/)
* Electricity - voltage, resistance, current - [Ohm's law](https://en.wikipedia.org/wiki/Ohm%27s_law)
* Batteries, wires, breadboards
* Resistors
* LEDs
* Speakers
* Arduino pins
* setup()
* loop()
* pinMode(pinNumber, INPUT|OUTPUT)
* delay(milliseconds)
* val = digitalRead(pinNumber) // HIGH|LOW
* digitalWrite(pinNumber, HIGH|LOW)
* tone(speakerPinNumber, frequency, \[durationMilliseconds\])
* noTone(pinNumber)
* Workshop - Led Speaker - [Circuit](https://raw.githubusercontent.com/urikalish/arduino-projects/master/projects/work/lessons/lesson01/LedSpeaker.png) | [Code](https://raw.githubusercontent.com/urikalish/arduino-projects/master/projects/work/lessons/lesson01/LedSpeaker.ino)

## Lesson #2 - Radar Music - 24/02/19
* Radar sensor
* IDE serial monitor and serial plotter
* Serial.begin(9600)
* Serial.print(msg) and Serial.println(msg)
* newVal = constrain(val, minVal, maxVal)
* newVal = map(val, srcMin, srcMax, dstMin, dstMax)
* delayMicroseconds(microseconds)
* Workshop - Radar Music - [Circuit](https://raw.githubusercontent.com/urikalish/arduino-projects/master/projects/work/lessons/lesson02/RadarMusic.png) | [Code](https://raw.githubusercontent.com/urikalish/arduino-projects/master/projects/work/lessons/lesson02/RadarMusic.ino)

## Lesson #3 - Knob Servo - 10/03/19
* Potentiometers
* Servos
* Analog input pins (for UNO - A0, A1, A2, A3, A4, A5)
* Digital PWM pins as "analog" output pins (for UNO - ~3, ~5, ~6, ~9, ~10, ~11)
* val = analogRead(analogPinNumber) // 0-1023
* analogWrite(pwmPinNumber, val) // 0-255
* servo.attach(servoPinNumber)
* servo.write(angle) // 0-180
* Workshop - Knob Servo - [Circuit](https://raw.githubusercontent.com/urikalish/arduino-projects/master/projects/work/lessons/lesson03/KnobServo.png) | [Code](https://raw.githubusercontent.com/urikalish/arduino-projects/master/projects/work/lessons/lesson03/KnobServo.ino)

## Lesson #4 - Button Pullup - 24/03/19
* Serial resistors
* Parralel resistors
* Buttons
* Floating pins
* pinMode(pinNUmber, INPUT_PULLUP)
* Interrups
* attachInterrupt(digitalPinToInterrupt(interruptPin), isrFunc, CHANGE|RISING|FALLING|LOW|HIGH);
* Volatile variable
* Workshop - Button No Pullup - [Circuit](https://raw.githubusercontent.com/urikalish/arduino-projects/master/projects/work/lessons/lesson04/ButtonNoPullup.png) | [Code](https://raw.githubusercontent.com/urikalish/arduino-projects/master/projects/work/lessons/lesson04/ButtonNoPullup.ino)
* Workshop - Button with Pullup - [Circuit](https://raw.githubusercontent.com/urikalish/arduino-projects/master/projects/work/lessons/lesson04/ButtonPullup.png) | [Code](https://raw.githubusercontent.com/urikalish/arduino-projects/master/projects/work/lessons/lesson04/ButtonPullup.ino)
* Workshop - Button with Pullup and Interrupt - [Code](https://raw.githubusercontent.com/urikalish/arduino-projects/master/projects/work/lessons/lesson04/ButtonPullupInterrupt.ino)

## Lesson #5 - Climate Sensor - 07/04/19
* Power options
* Relay - connecting to 230v circuits
* Installing external libraries
* Workshop - Climate Sensor - [Circuit](https://raw.githubusercontent.com/urikalish/arduino-projects/master/projects/work/lessons/lesson05/ClimateSensor.png) | [Code](https://raw.githubusercontent.com/urikalish/arduino-projects/master/projects/work/lessons/lesson05/ClimateSensor.ino)
