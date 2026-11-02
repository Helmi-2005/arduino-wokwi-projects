#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);

  // Start the DS18B20 sensor
  sensors.begin();

  // initialize OLED display with I2C address 0x3C
  if (!oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("failed to start SSD1306 OLED"));
    while (1);
  }
  delay(2000);
  oled.clearDisplay();
}

void loop() {
  // Request temperature from the sensor
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);

  oled.clearDisplay();

  // title
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0, 0);
  oled.println("DS18B20 Temp Monitor");

  // temperature value
  oled.setTextSize(2);
  oled.setCursor(15, 25);

  if (tempC == DEVICE_DISCONNECTED_C) {
    oled.print("Error!");
  } else {
    oled.print(tempC);
    oled.print(" ");
    oled.cp437(true);
    oled.write(167);
    oled.print("C");
  }

  oled.display();
  delay(2000);
}