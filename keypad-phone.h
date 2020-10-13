/*
 * keypad_phone.h
 *
 * Created: 10/10/2020 05:15:13 ص
 *  Author: omar.M.ezzeldeen
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "GPIO.h"
#include <util/delay.h>
#define F_CPU 1000000UL
#define keypadport D
#define bin1 0
#define bin2 1
#define bin3 2
#define binA 3
#define binB 4
#define binC 5
#define binD 6
void keypad_init();
char keypad_read();
unsigned char scan();

#endif /* KEYPAD_H_ */