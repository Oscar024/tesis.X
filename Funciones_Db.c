
#include <xc.h>
#include <plib/spi.h>
#include<stdio.h>
#include<stdlib.h>
#include"Bluetooth.h"
#include<string.h>
#include"Funciones_Db.h"
#include "lcd.h"
#include "pwm.h"
#include "cny70.h"


char FinComandB;
char FinComandT;
char                  CheckSum              = 0;
int                   TamanhoTrama          = 0;
unsigned char     num_med_low           = 0;
unsigned char     num_med_medium        = 0;
unsigned char     num_med_hi            = 0;
int                   Med_msb               = 0;
int                   Med_lsb               = 0;
//unsigned char         dato[14];
unsigned char         packet                = 0;
unsigned char         contador              = 0;
unsigned char         contador2             = 0;
unsigned char         TramaTablet[20];
extern unsigned char  BluetoothDato[20];
extern unsigned char  cad;
extern unsigned char  cleanBfer,Timer1;
char array[20];
unsigned char j=0;





//Estados del Bluetooth Bee
void EstadoBluetooth(void) {

    if (strcmp(BluetoothDato, READY) == 0) {
      Pause_seg(4);

      BT_Init();

      CheckTX(CONECTING);

      CheckTX(CONECTEDOK);
      CheckTX(CONECTED);
      Pause_seg(7);
      cad = 0;
      clrBufferUSART();
    }
    UART1_Init(51);
    return;

}


//******************************************************************************
//Función Que inicializa el Drive By
void Inicializa_Driveby(void) {
    TRISA = TRISB = TRISC = TRISD = 0;
    INTCON = 0b11000000;
    //        PIE1bits.RCIE=1;
    //Inicialización del MCU
    int i = 0;
    __delay_ms(40);
    OSCCONbits.IRCF = 0b111; // Oscilador Interno a 8 Mhz
//            OSCTUNEbits.PLLEN = 1; // PLL Activado (8 Mhz x 4 = 32 Mhz)_
//            __delay_ms(40);
    //        ODCON2bits.U2OD = 1; // Activa Open Drain en USART2
    //        TRISGbits.TRISG1 = 0; // USART2 TX
    TRISA = 0;
    PORTA = 0;
    TRISCbits.TRISC7 = 1;
    TRISCbits.TRISC6 = 0;
    for (i = 1; i <= 50; i++)
      __delay_ms(20);
    PORTE = 0;
    PORTB = 0;
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1;
    TRISBbits.TRISB3 = 1;
    TRISBbits.TRISB4 = 1;
    Lcd_Clear();
    Lcd_Set_Cursor(2, 1);
    Lcd_Write_String("INICIO");
    //        CheckTX(INICIO);
    BT_Init();
    Lcd_Clear();
    Lcd_Set_Cursor(1, 1);
    Lcd_Write_String("BT INICIALIZADO");

    Pause_seg(7);
    cad = 0;
    clrBufferUSART();
    return;
}



void Comando_Tablet() {
   
  int sensed=0;
  switch (BluetoothDato[1]) {
    case 1:
      Lcd_Clear();
      Lcd_Set_Cursor(1, 1);      
      Lcd_Write_String("1");      
      break;
    case 2:
      Lcd_Clear();
      Lcd_Set_Cursor(1, 1);      
      Lcd_Write_String("2");    
      break;

    case 3:
      Lcd_Clear();
      Lcd_Set_Cursor(1, 1);
      
      Lcd_Write_String("3");
      break;
    case 4:
//      Lcd_Clear();
//      Lcd_Set_Cursor(1, 1);
//      Lcd_Write_String("4");
      sensed = getCNY70Value();
      Lcd_Clear();
      Lcd_Set_Cursor(1,1);
      Lcd_Write_Integer(sensed);
      putcBluetoothInt(sensed);
      putcBluetoothString("\n");      
      break;
    case 5:
      Lcd_Clear();
      Lcd_Set_Cursor(1, 1);
      Lcd_Write_Integer(BluetoothDato[3]);
       Lcd_Set_Cursor(2, 1);
      Lcd_Write_Integer(BluetoothDato[4]);
      PWM_init1(0xff);
      PWM_init2(0xff);
      PWM_DutyCycle1(BluetoothDato[3]);
      PWM_DutyCycle2(BluetoothDato[4]);
      break;  
    default:
      Lcd_Clear();
      Lcd_Set_Cursor(1, 1);      
      Lcd_Write_String("Default");
      break;
  }
  clrBufferUSART();
  return;

}


