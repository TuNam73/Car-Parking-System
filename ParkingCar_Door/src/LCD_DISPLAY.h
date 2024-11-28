#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H
#include <Wire.h> 
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); 

static unsigned long previous_time_lcd = 0;
static unsigned int lcd_state = 0;

namespace LCD_display {
    void LCD_display() {
        if (millis() - previous_time_lcd >= 3000){
            previous_time_lcd = millis();
            lcd.clear();
            if (lcd_state == 0) {
                lcd.setCursor(1, 0);
                lcd.print("Welcome to....");
                lcd.setCursor(1, 1);
                lcd.print("My Parking Car");
                lcd_state = 1;
            }
            else if (lcd_state == 1) {
                lcd.setCursor(4, 0);
                lcd.print("Author:");
                lcd.setCursor(1, 1);
                lcd.print("Tu Van Hoai Nam");
                lcd_state = 0;
            }
        }
    }
}

#endif