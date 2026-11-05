#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Configuration OLED (128x64 I2C)
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Configuration RFID RC522
#define SS_PIN 10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();       // Init SPI bus
  rfid.PCD_Init();   // Init MFRC522

  // Init OLED Display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C ou 0x3D
    Serial.println(F("OLED activation failed!"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(15, 20);
  display.println(F("Scan RFID Tag..."));
  display.display();
}

void loop() {
  // Verifier si une nouvelle carte est présente
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Kharej el UID te3 el carte
  String content = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    content.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(rfid.uid.uidByte[i], HEX));
  }
  content.toUpperCase();

  // Affichage 3la OLED
  display.clearDisplay();
  
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("--- CARD DETECTED ---"));
  
  display.setTextSize(1);
  display.setCursor(0, 25);
  display.println(F("UID:"));
  
  display.setTextSize(1);
  display.setCursor(0, 40);
  display.println(content);
  
  display.display();

  // Reset tag detection
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  delay(2000); // Intedhar 2 sec bch tarja3 tqra men jadid

  // Rajja3 l-ecran l'etat de départ
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(15, 20);
  display.println(F("Scan RFID Tag..."));
  display.display();
}