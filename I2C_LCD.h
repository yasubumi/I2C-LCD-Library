#ifndef I2C_LCD_H
#define I2C_LCD_H

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include "Wire.h"

#define LCD_I2CADDR 0x3E
#define DEFAULT_CONTRAST 20 // contrast(0~63)

class I2C_LCD{
public:
    I2C_LCD();
    void begin();
    void setCursor(byte x, byte y);
    void printStr(const char *s);
    void printInt(int num);
    void printFloat(float num, signed char width, unsigned char prec);
    void setContrast(byte c);

private:
    byte contrast;
    void lcd_cmd(byte x);
    void lcd_contdata(byte x);
    void lcd_lastdata(byte x);
};

#endif // I2C_LCD_H
