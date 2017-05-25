/*
 * File:   LCDOrbital.c
 * Author: L
 *
 * Created on 23 de septiembre de 2014, 03:25 PM
 */


#include <xc.h>
#include<stdio.h>
#include<stdlib.h>
//#include"cc1101.h"
#include<plib/usart.h>
#include"GLK12232-25.h"


extern unsigned char dato[8];

void LCD_Init(){
    Open2USART(USART_TX_INT_OFF & USART_RX_INT_OFF & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX & USART_BRGH_HIGH, 207);
    putc2USART(0xFE);
    while (Busy2USART());
     putc2USART(0x99);
    while (Busy2USART());
     putc2USART(0xFF);
    while (Busy2USART());
    putc2USART(0xFE);
    while (Busy2USART());
     putc2USART(0x50);
    while (Busy2USART());
     putc2USART(0x71);
    while (Busy2USART());
    LCD_Limpiar();
 
}
void Draw_Line(int Px1,int Py1,int Px2,int Py2){

    putcDisplay(0xFE);
    putcDisplay(0x6C);
    putcDisplay(Px1);
    putcDisplay(Py1);
    putcDisplay(Px2);
    putcDisplay(Py2);


};
void Draw_Rectangle(int Px1,int Py1,int Px2,int Py2){

    putcDisplay(0xFE);
    putcDisplay(0x72);
    putcDisplay(0xFF);
    putcDisplay(Px1);
    putcDisplay(Py1);
    putcDisplay(Px2);
    putcDisplay(Py2);


};
void LCD_Pos_Cursor(unsigned char Columna, unsigned char Fila) {

    putcDisplay(0xFE);
    putcDisplay(0x47);
    putcDisplay(Columna);
    putcDisplay(Fila);
};
void LCD_Limpiar(void) {

    putcDisplay(0xFE);
    putcDisplay(0x58);

}
void Select_Font(unsigned char ID) {
    putcDisplay(0xFE);
    putcDisplay(0x31);
    putcDisplay(ID);

}
void LCD_Escribe(char *dato, int c) {
    int x;
    for (x = 0; x < c; x++) {
        putcDisplay(*dato++);
    }
}
void putcDisplay(unsigned char x) {

    putc2USART(x);
    while (Busy2USART());

}
void putcDisplayString(void) {
    char y[11];
    int i=0;
    for(i=3;i<=10;i++){//Se leagregó un Byte más
        puts2USART(itoa(y,dato[i],10));
        while (Busy2USART());
        putc2USART(' ');
        while (Busy2USART());
    }
}
void LCD_Coor_Cursor(int x, int y) {

    putcDisplay(0xFE);
    putcDisplay(0x79);
    putcDisplay(x);
    putcDisplay(y);
}



