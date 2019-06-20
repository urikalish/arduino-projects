#include "dht.h"

#define dht_apin A0

dht11 climateSensor;

void setup() {
  Serial.begin(9600);
}

void loop() {  
  climateSensor.read11(dht_apin);
  Serial.print("Temperature: ");
  Serial.print(climateSensor.temperature);
  lcd.print((char)223);
  Serial.print(", Humidity: ");
  Serial.print(climateSensor.humidity);
  Serial.println("%");
  delay(2000);
}
