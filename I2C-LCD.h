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

class i2c_lcd{
public:
    i2c_lcd();
    void begin();
    void setCursor(byte x, byte y);
    void printStr(const char *s);
    void printInt(int32_t num);
    void printFloat(float num);
    void setContrast(byte c);

private:
    byte contrast;
    void lcd_cmd(byte x);
    void lcd_contdata(byte x);
    void lcd_lastdata(byte x);
};

#endif // I2C_LCD_H
