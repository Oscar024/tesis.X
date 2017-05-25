/* 
 * File:   lcd.h
 * Author: oscar
 *
 * Created on May 18, 2016, 3:17 PM
 */
#include <xc.h>

#ifndef LCD_H
#define	LCD_H

//LCD Functions Developed by electroSome

#define _XTAL_FREQ 4000000

#define RS PORTEbits.RE0
#define RW1 PORTEbits.RE1
#define EN PORTEbits.RE2
#define D4 PORTDbits.RD4
#define D5 PORTDbits.RD5
#define D6 PORTDbits.RD6
#define D7 PORTDbits.RD7

void Lcd_Port(char a);
void Lcd_Cmd(char a);
void Lcd_Clear(void);
void Lcd_Set_Cursor(char a, char b);
void Lcd_Init();
void Lcd_Write_Char(char a);
void Lcd_Write_String(char *a);
void Lcd_Shift_Right();
void Lcd_Shift_Left();
void Lcd_Write_Float(float f);
void Lcd_Write_Integer(int a);




#endif	/* LCD_H */

