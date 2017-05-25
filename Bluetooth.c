
#include"Bluetooth.h"
#include"UART1.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Funciones_Db.h"
#include "lcd.h"
extern char          SBUSART;
unsigned char         comando[20];
extern unsigned char  cad;
extern unsigned char  BluetoothDato[20];
//extern unsigned char  dato[8];
extern unsigned char  TramaTablet[20];

void BT_Init() {
    
    UART1_Init(51); //9600 frecuencia de 8MHZ


    Pause_seg(1);
    char nameBT[18] = {
      "AT+NAME=robot\r\n\0"
    }; //Pausa de 1 seg. necesaria
    //Lo pone visible

    SendBlueToothCommand("AT+ROLE=0\r\n", 11); //Esa onda como esclavo

    Pause_seg(1);


    SendBlueToothCommand((const char * ) nameBT, sizeof(nameBT)); //El nombre
    Pause_seg(2);

    SendBlueToothCommand("AT+PSWD=0000\r\n", 14); //Password
    Pause_seg(2);



    SendBlueToothCommand("AT+INQ\r\n", 8); //MODO VISIBLE                                                                //Espera 2 seg.
    Pause_seg(2);

    SendBlueToothCommand("AT+INQ\r\n", 8); //Modo visible                                                               //Espera 2 seg.
    Pause_seg(2);
    return;
}

void SendBlueToothCommand(const char * command, unsigned int total) {
    putSTRINGU1(command, total);
    return;
}

void CheckTX(const char * CheckC) {
    
    strcpy(comando, CheckC);
    clrBufferUSART();
    SBUSART = 0;
    while (SBUSART == 0) {
      if (strcmp(comando, BluetoothDato) == 0) {
        SBUSART = 1;
        cad = 0;
      } else if (strcmp(comando, BluetoothDato) != 0)
        SBUSART = 0;
    }
    return;
}

void clrBufferUSART(void) {
    int i;
    for (i = 0; i < 20; i++) {
      BluetoothDato[i] = 0;
      cad = 0;
    }
    return;

}
//void putcBluetoothString(int NumBytes, unsigned char dato[]) {
//    //Manda los datos a la Tablet con el tamaño de la trama
//    int i;
//    UART1_Init(51);
//    for (i = 0; i < NumBytes; i++) { //Trama a enviar
//      putcUSART(dato[i]);
//      while (BusyUSART());
//    }
//    CloseUSART();
//    return;
//}


void putcBluetoothString(char * a) {
    //Manda los datos a la Tablet con el tamaño de la trama
    int i;
    UART1_Init(51);
   
    for (i = 0; a[i] != '\0'; i++){
        putcUSART(a[i]);
        while (BusyUSART());
    }    
    CloseUSART();
    return;
}
void putcBluetoothInt(int a) {
    //Manda los datos a la Tablet con el tamaño de la trama
    int i;
    unsigned char s[20];
    UART1_Init(51);

    sprintf(s,"%d",a);   
    for (i = 0; s[i] != '\0'; i++){
        putcUSART(s[i]);
        while (BusyUSART());
    }    
    CloseUSART();
    return;
}


