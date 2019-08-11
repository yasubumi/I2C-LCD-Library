#include <Wire.h>

#define vddPin 16    // ArduinoA2
#define gndPin 17    // ArduinoA3
#define sdaPin 18    // ArduinoA4
#define sclPin 19    // ArduinoA5
#define I2Cadr 0x3e  // 固定
byte contrast = 35;  // コントラスト(0～63)


void setup() {
  Serial.begin(9600);
  pinMode(gndPin, OUTPUT);
  digitalWrite(gndPin, LOW);
  pinMode(vddPin, OUTPUT);
  digitalWrite(vddPin, HIGH);
  delay(500);
  Wire.begin();
  init_dev();
  lcd_setContrast(20);
}

void loop() {
  lcd_setCursor(0, 0);
  int num1 = 1000723;
  lcd_printInt(num1);
  lcd_setCursor(1, 1);
  float num2 = 10.25;
  lcd_printFloat(num2);
  delay(100);
}

void init_dev(){
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

void lcd_cmd(byte x) {
  Wire.beginTransmission(I2Cadr);
  Wire.write(0b00000000); // CO = 0,RS = 0
  Wire.write(x);
  Wire.endTransmission();
}

void lcd_contdata(byte x) {
  Wire.write(0b11000000); // CO = 1, RS = 1
  Wire.write(x);
}

void lcd_lastdata(byte x) {
  Wire.write(0b01000000); // CO = 0, RS = 1
  Wire.write(x);
}

// 文字の表示
void lcd_printStr(const char *s) {
  Wire.beginTransmission(I2Cadr);
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

// 表示位置の指定
void lcd_setCursor(byte x, byte y) {
  lcd_cmd(0x80 | (y * 0x40 + x));
}

void lcd_printInt(int num)
 {
   char str[10]; 
   sprintf(str,"%d",num);
   lcd_printStr(str);    
 }

void lcd_printFloat(float num)
 {
   char str[10];
   dtostrf(num, 5, 1, str);
   lcd_printStr(str);
 }

void lcd_setContrast(byte c) {
  lcd_cmd(0x39);
  lcd_cmd(0b01110000 | (c & 0x0f)); // contrast Low
  lcd_cmd(0b01011100 | ( (c >> 4) & 0x03) ); // contrast High/icon/power
  lcd_cmd(0x38);
}
