/*
 * LCD.h
 *
 * Created: 3/21/2020 11:02:44 PM
 *  Author: BS
 */ 


#ifndef LCD_H_
#define LCD_H_
#include <util/delay.h>
#define F_CPU 8000000UL
#include "GPIO.h"
#define data B
#define command B
#define lcdport B
#define E 1
#define RS 0
#define mode 4
#define datanibble 1 // if you want to use the lower bits of port put 0
void lcd_init();
void lcd_command(char com);
void lcd_data(char c);
void lcd_print(char* str);

#endif /* LCD_H_ */