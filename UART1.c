#include"UART1.h"
#include <plib/usart.h>
// <editor-fold defaultstate="collapsed" desc="UART1">

void UART1_Init(char bdr)
{
 
    OpenUSART(USART_TX_INT_OFF & USART_RX_INT_ON & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX & USART_BRGH_HIGH,bdr);

}

void putcTxU1(char character)
{
    putcUSART(character);
    while (BusyUSART());
}

void putSTRINGU1(const char *dato,unsigned int total){
        unsigned char cont,last;

    for(cont=0,last=0;cont<total;cont++){
         if(dato[cont]!='\0') last=cont;
     }

    for (cont=0;cont<=last;cont++){
        putcTxU1(*dato++);
    }
}
