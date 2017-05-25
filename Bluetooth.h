/*
 * File:   Bluetooth.h
 * Author: desarrollo
 *
 * Created on 26 de junio de 2014, 01:02 PM
 *
 * Funciones para habilitar y poder usar el bluetooth
 *
 */

#ifndef BLUETOOTH_H
#define	BLUETOOTH_H

#include <xc.h>         // Libreria del uC
#include "Retardos.h"
#include "UART1.h"

#define  OK           "\nOK\r\n"
#define  WORK_SLAVE   "\nWORK:SLAVER\r\n"
#define  INICIO       "\n+BTSTATE:0\r\n"
#define  READY        "\n+BTSTATE:1\r\n"
#define  INQUIRING    "\n+BTSTATE:2\r\n"
#define  CONECTING    "\n+BTSTATE:3\r\n"
#define  CONECTED     "\n+BTSTATE:4\r\n"
#define  CONECTEDOK   "\nCONNECT:OK\r\n"
#define BT_DISCONECT  "\nLINK LOSS\r\n"

void BT_Init(void);
void SendBlueToothCommand(const char *command,unsigned int total);
void CheckTX(const char *CheckC);
void clrBufferUSART(void);
void putcBluetoothString(char * a);
void putcBluetoothInt(int a);
#endif	/* BLUETOOTH_H */

