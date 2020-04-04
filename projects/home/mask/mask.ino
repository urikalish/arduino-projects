#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <dht.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4
#define dht_apin A0
#define mic_apin A1
#define mic_dpin 7
dht DHT;
int temperature = 0;
int humidity = 0;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.display();
  display.clearDisplay();
  pinMode(mic_dpin, INPUT);
}

void loop() {
  int val = analogRead(mic_apin);
  //int val = digitalRead(mic_dpin);
  Serial.println(val);
  DHT.read11(dht_apin);
  int t = max(round(DHT.temperature),0);
  int h = max(round(DHT.humidity),0);
  temperature = t;
  humidity = h;
  printClimate();
  delay(1500);
}

void printClimate() {
  display.clearDisplay();
  display.setTextColor(WHITE);        
  display.setCursor(0,0);             
  display.setTextSize(1);  
  display.println("Corona Face Mask v1.0");
  display.println("---------------------");
  display.println("");
  display.setTextSize(1);
  display.print("Est. Body Temp :: ");
  display.print(temperature + 3);
  display.print((char)247);
  display.println("");
  display.setTextSize(1);
  display.print("Mask Temp      :: ");
  display.print(temperature);
  display.print((char)247);
  display.println("");
  display.setTextSize(1);
  display.print("Mask Humidity  :: ");
  display.print(humidity);
  display.print("%");
  display.display();
}
