#include "I2C_LCD.h"

// i2c_lcdクラスインスタンス
I2C_LCD lcd;

void setup() {
  lcd.begin();
  lcd.setContrast(25);
}

void loop() {
  lcd.setCursor(0, 0);
  int32_t num1 = 2345;
  lcd.printInt(num1);
  lcd.setCursor(6, 0);
  lcd.printStr("kP");
  lcd.setCursor(1, 1);
  float num2 = 10.25;
  lcd.printFloat(num2,5,1);
  delay(100);
}
