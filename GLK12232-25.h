/* 
 * File:   LCDOrbital.h
 * Author: L
 *
 * Created on 23 de septiembre de 2014, 03:24 PM
 */

#ifndef LCDORBITAL_H
#define	LCDORBITAL_H

void LCD_Init();
void Draw_Line(int Px1,int Py1,int Px2,int Py2);
void Draw_Rectangle(int Px1,int Py1,int Px2,int Py2);
void LCD_Pos_Cursor(unsigned char Columna, unsigned char Fila);
void putcDisplayString(void);
void LCD_Limpiar(void);
void Select_Font(unsigned char ID);
void LCD_Escribe(char *dato, int c);
void putcDisplay(unsigned char x);
void LCD_Coor_Cursor(int x, int y);
void LCD_Coor_Cursor(int x, int y);
//void LCD_Escribe_dato(char dato);


#endif	/* LCDORBITAL_H */

