#ifndef __UART1_H
#define __UART1_H

#define FCY 32000000    // MHz  Necesaria para delays y UART
#include <xc.h>         // Libreria del uC
#include <plib/usart.h>      //     "    de UART
#include <stdio.h>      //     "    para itoa y esas cosas
#include <stdlib.h>     //     "     "      "      "
#include <string.h>

// <editor-fold defaultstate="collapsed" desc="Defines">
#define CLT putcTxU2(0x0c)                // Manda limpiar pantalla
#define LINE putcTxU2(13)                 // es un enter
#define SPACE putcTxU2(' ')               // da un espacio
#define SELECT putSTRINGU2("<---")      // imprime la flecha
#define CURSOR putcTxU2('>')              // imprime el cursor
#define BCKSP putcTxU2(0x08)              // Borra una letra
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="BaudRate Speed">
#define BAUDRATE    19200                                                       // Velocidad para UART
#define BRGHigh     1

#if BRGHigh
#define BRGVAL ((FCY/BAUDRATE)/4)-1                                             //Configurar baud rate como alta velocidad
#else
#define BRGVAL ((FCY/BAUDRATE)/16)-1                                            //Configurar baud rate como baja velocidad
#endif

#define BAUDRATE2    38400                                                      // Velocidad para UART
#define BRGHigh2     1

#if BRGHigh2
#define BRGVAL2 ((FCY/BAUDRATE2)/4)-1                                             //Configurar baud rate como alta velocidad
#else
#define BRGVAL2 ((FCY/BAUDRATE2)/16)-1                                            //Configurar baud rate como baja velocidad
#endif
// </editor-fold>
void UART1_Init(char bdr);
void putcTxU1(char character);
void putSTRINGU1(const char *dato,unsigned int total);
//void PRNTVARU1(unsigned int var);
//void PRNTsVARU1(int var);
//void putHEXU1(unsigned long data, char caracteres);
//void putlHEXU1(unsigned long dato, char caracteres);
//void putDEC5U1(unsigned int dato);
//void putDEC4U1(unsigned int dato);
//void putDEC3U1(unsigned int dato);
//void putDEC2U1(unsigned int dato);



#endif
