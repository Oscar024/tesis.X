#include"Retardos.h"
#include <xc.h>
#include"Funciones_Db.h"
void Pause_us(unsigned int x){
    unsigned int i=0;
    for(i=0;i<=x;i++){
        __delay_us(1);
    }
}

void Pause_ms(unsigned int x){
    unsigned int i=0;
    for(i=0;i<=x;i++){
        __delay_ms(1);
    }
}

void Pause_seg(unsigned char x){
    unsigned char i=0;
    for(i=0;i<=x;i++){
        Pause_ms(250);Pause_ms(250);
        Pause_ms(250);Pause_ms(250);
    }
}
