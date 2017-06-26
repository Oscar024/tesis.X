/*
 * File:   funciones.h
 * Author: L
 *
 * Created on 11 de septiembre de 2014, 07:15 PM
 */

#ifndef FUNCIONES_H
#define	FUNCIONES_H
#define _XTAL_FREQ 8000000


        // DIRECCIONES //

#define DIR_MAE                 0
#define DIR_ESC                 1
#define DIR_TEL                 2                                               //direccion del esclavo
#define Drive_by                4
#define TABLET                  5					                // Número del medidor

#define SOlIBATON               1
#define SOLIBATOFF              2
#define SOLIPORC                3
#define PINGBT                  4
#define ACK                     5
#define NAME                    41
#define SOLIPORC_LOW_POWER      7

#define NUM_SOLICITUD           2
#define BT_DISCONN PORTCbits.RC0
#define CHRG_EN    PORTBbits.RB5

//Sensores CNY70
#define SENSOR_NL PORTAbits.RA0
#define SENSOR_N PORTAbits.RA1
#define SENSOR_Z PORTAbits.RA2
#define SENSOR_P PORTAbits.RA3
#define SENSOR_PL PORTAbits.RA4

void PantallaPrin(void);
void PONGBT(void);
void clrBufferDato(void);
void ConecBatteria(int Off_On_BAt);
void EstadoBluetooth(void);
void Comando_Tablet(void);
void Inicializa_Driveby(void);
void Mandar_Tablet(void);
char Tecla(void);
void Teclado(void);
void DelayCommands();
void BT_ModoVisible(void);
int sensar(void);
#endif	/* FUNCIONES_H */

