// LCD SDA --> A4
// LCD SLA --> A5
// DHT11 S --> A0 

#include "Wire.h"
#include "LCD.h"
#include "LiquidCrystal_I2C.h"
#include "dht.h"
t 
#define dht_apin A0
dht DHT;
int temperature = 0;
int humidity = 0;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7);

void setup() {
  Serial.begin(9600);
  Serial.println("setup");
  lcd.begin(16,2);
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  printClimate();
}

void loop() {  
  DHT.read11(dht_apin);
  int t = max(round(DHT.temperature),0);
  int h = max(round(DHT.humidity),0);
  if (t == temperature && h == humidity) {
    printClimate();
    delay(30000);  
  } else {
    temperature = t;
    humidity = h;
    printClimate();
    delay(3000);
  }
}

void printClimate() {
  lcd.clear();
  lcd.home();  
  lcd.print("Temperature");
  if (temperature > 0) {
    lcd.setCursor(13,0);
    lcd.print(temperature);  
    lcd.setCursor(15,0);
    lcd.print((char)223);
  }
  lcd.setCursor(0,1);
  lcd.print("Humidity");
  if (humidity > 0) {
    lcd.setCursor(13,1);
    lcd.print(humidity);
    lcd.setCursor(15,1);
    lcd.print("%");
  }
}
