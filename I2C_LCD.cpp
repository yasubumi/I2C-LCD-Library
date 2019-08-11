#include "I2C_LCD.h"

I2C_LCD::I2C_LCD(){
}

void I2C_LCD::begin(){
    Wire.begin();

    contrast = DEFAULT_CONTRAST;
    lcd_cmd(0b00111000); // function set
    lcd_cmd(0b00111001); // function set
    lcd_cmd(0b00000100); // EntryModeSet
    lcd_cmd(0b00010100); // interval osc
    lcd_cmd(0b01110000 | (contrast & 0xF)); // contrast Low
    lcd_cmd(0b01011100 | ((contrast >> 4) & 0x3)); // contast High/icon/power
    lcd_cmd(0b01101100); // follower control
    delay(200);
    lcd_cmd(0b00111000); // function set
    lcd_cmd(0b00001100); // Display On
    lcd_cmd(0b00000001); // Clear Display
    delay(2);
}

// ----- public -----
// カーソル位置セット
void I2C_LCD::setCursor(byte x, byte y){
  lcd_cmd(0x80 | (y * 0x40 + x));
}

// 文字の表示
void I2C_LCD::printStr(const char *s){
  Wire.beginTransmission(LCD_I2CADDR);
  while (*s) {
    if (*(s + 1)) {
      lcd_contdata(*s);
    } else {
      lcd_lastdata(*s);
    }
    s++;
  }
  Wire.endTransmission();
}

// intの表示
void I2C_LCD::printInt(int num){
   char str[10]; 
   sprintf(str,"%d",num);
   printStr(str);    
}

// floatの表示
void I2C_LCD::printFloat(float num, signed char width, unsigned char prec){
   char str[10];
   dtostrf(num, width, prec, str);
   printStr(str);
}

// コントラストセット
void I2C_LCD::setContrast(byte c){
  lcd_cmd(0x39);
  lcd_cmd(0b01110000 | (c & 0x0f)); // contrast Low
  lcd_cmd(0b01011100 | ( (c >> 4) & 0x03) ); // contrast High/icon/power
  lcd_cmd(0x38);
}

// ----- private -----
void I2C_LCD::lcd_cmd(byte x){
  Wire.beginTransmission(LCD_I2CADDR);
  Wire.write(0b00000000); // CO = 0,RS = 0
  Wire.write(x);
  Wire.endTransmission();
}

void I2C_LCD::lcd_contdata(byte x){
  Wire.write(0b11000000); // CO = 1, RS = 1
  Wire.write(x);
}
void I2C_LCD::lcd_lastdata(byte x){
  Wire.write(0b01000000); // CO = 0, RS = 1
  Wire.write(x);
}
