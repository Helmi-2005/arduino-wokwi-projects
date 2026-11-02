#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27 ,16 ,2);
int red=11;
int yellow=12;
int green=13;
void setup() {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  lcd.init();
  lcd.backlight();

}
void phase(int ledPin, const char* name, int seconds){
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
  digitalWrite(ledPin, HIGH);
  for (int s=seconds ;s > 0 ;s--){
    lcd.clear();
    lcd.print(name);
    lcd.setCursor(0,1);
    lcd.print("mzel==> ");
    lcd.print(s);
    lcd.print("s");
    delay(1000);
  }
}
void loop() {
phase(red,"ROUGE",45);
phase(yellow,"ORANGE",15);
phase(green,"VERT",30);

}
