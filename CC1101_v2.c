#include <xc.h>
#include <plib/spi.h>
#include"CC1101_v2.h"

//#include "cc1101.h"

#define _XTAL_FREQ 8000000

unsigned int count;
unsigned char RFBuff[8];
unsigned char chip_status;

extern unsigned char dato[8];                                  
extern unsigned char Bandera_Error_Recepcion;


//Función que configura los parámetros iniciales del radio CC1101
#if defined PIC18
void SPI1_CC1101_Init(unsigned char Frec_Mhz){

    
      if(Frec_Mhz>112)
      OpenSPI1(SPI_FOSC_64, MODE_00, SMPMID); //Configuración del modulo SPI
      else if(Frec_Mhz<=112&&Frec_Mhz>24)
      OpenSPI1(SPI_FOSC_16, MODE_00, SMPMID); //Configuración del modulo SPI
      else if(Frec_Mhz<=24)
      OpenSPI1(SPI_FOSC_4, MODE_00, SMPMID); //Configuración del modulo SPI
}

void CC1101_Init(unsigned char adress){


    CS_CC1101=0;

    WriteSPI1(0x00);                                                             //ESCRIBE EN GDO2 (GDO2 Output Pin Configuration)
    WriteSPI1(0x07);                                                             //Enciende cuando el paquete ha sido recibido con CRC Ok. Se apaga cuando el primer byte es leido de la RX FIFO

    WriteSPI1(0x02);                                                             //ESCRIBE EN GD00 (GDO0 Output Pin Configuration)
    WriteSPI1(0x06);                                                             //Enciende cuando el sync word ha sido enviado y se apaga en el final del paquete.

    WriteSPI1(0x03);                                                             //ESCRIBE EN FIFO_THR (RX FIFO and TX FIFO Thresholds)
    WriteSPI1(0x07);                                                             //33 bytes en TX FIFO y 32 bytes en RX FIFO

    WriteSPI1(0x04);                                                             //ESCRIBE EN SYNC1 (Sync Word, High Byte)
    WriteSPI1(0xD3);                                                             //8 MSB of 16-bit sync word

    WriteSPI1(0x05);                                                             //ESCRIBE EN SYNC0 (Sync Word, Low Byte)
    WriteSPI1(0x91);                                                             //8 LSB of 16-bit sy nc word

    WriteSPI1(0x06);                                                             //ESCRIBE EN PKTLEN (Packet Length)
    WriteSPI1(PKT_LEN_MAX);

    WriteSPI1(0x07);                                                             //ESCRIBE EN PKTCTRL1 (Packet Automation Control)
    WriteSPI1(Conf_PKTCTRL1);

    WriteSPI1(0x08);                                                             //ESCRIBE EN PKTCTRL0 (Packet Automation Control)
    WriteSPI1(Conf_PKTCTRL0);

    WriteSPI1(0x09);                                                             //ESCRIBE ADDR (Device Address)
    WriteSPI1(adress);                                                          //Address used for packet filtration. Optional broadcast addresses are 0(0x00) and 255 (0xFF).

    WriteSPI1(0x0A);                                                             //ESCRIBE CHANNR (Channel Number)
    WriteSPI1(Channel);                                                          //The 8-bit unsigned channel number, which is multiplied by the channel spacing setting and added to the base frequency.

    WriteSPI1(0x0B);                                                             //ESCRIBE FSCTRL1 (Frequency Synthesizer Control)
    WriteSPI1(0x06);

    WriteSPI1(0x0C);                                                             //ESCRIBE FSCTRL0 (Frequency Synthesizer Control)
    WriteSPI1(0x00);

    WriteSPI1(0x0D);                                                             //ESCRIBE FREQ2 (Frequency Control Word, High Byte)
    WriteSPI1(0x21);

    WriteSPI1(0x0E);                                                             //ESCRIBE FREQ1 (Frequency Control Word, Middle Byte)
    WriteSPI1(0x62);

    WriteSPI1(0x0F);                                                             //ESCRIBE FREQ0 (Frequency Control Word, Low Byte)
    WriteSPI1(0x76);

    WriteSPI1(0x10);                                                             //ESCRIBE MDMCFG4 (Modem Configuration)
    WriteSPI1(0xF5);                                                             //Data rate = 1.2 KBaudios                0XF8 = 9.6 Kbaudios

    WriteSPI1(0x11);                                                             //ESCRIBE MDMCFG3 (Modem Configuration)
    WriteSPI1(0x83);

    WriteSPI1(0x12);                                                             //ESCRIBE MDMCFG2 (Modem Configuration)
    WriteSPI1(Conf_MDMCFG2);

    WriteSPI1(0x13);                                                             //ESCRIBE MDMCFG1 (Modem Configuration)
    WriteSPI1(Conf_MDMCFG1);

    WriteSPI1(0x14);                                                             //ESCRIBE MDMCFG0 (Modem Configuration)
    WriteSPI1(0xF8);

    WriteSPI1(0x15);                                                             //ESCRIBE DEVIATN (Modem Deviation Setting)
    WriteSPI1(0x15);

    WriteSPI1(0x16);                                                             //ESCRIBE MCSM2 (Main Radio Control State Machine Configuration)
    WriteSPI1(0x07);                                                             //Sirve para la configuracion del TMR de RX y sus condiciones

    WriteSPI1(0x17);                                                             //ESCRIBE MCSM1 (Main Radio Control State Machine Configuration)
    WriteSPI1(MCSM1);                                                             //Clear channel indication Always. Next state after finishing packet reception IDLE. Next state after finishing packet transmission IDLE

    WriteSPI1(0x18);                                                             //ESCRIBE MCSM0 (Main Radio Control State Machine Configuration)
    WriteSPI1(0x18);                                                             //When to perform automatic calibration, Every 4th time when going from RX or TX to IDLE automatically. Timeout after XOSC start Approx. 2.3 ? 2.4 µs. Enables the pin radio control option. Force the XOSC to stay on in the SLEEP state.

    WriteSPI1(0x19);                                                             //ESCRIBE FOCCFG (Frequency Offset Compensation Configuration)
    WriteSPI1(0x16);                                                             //Saturation point (max compensated offset) ±BWCHAN/4. Freq. compensation loop gain after sync word K/2. Freq. compensation loop gain before sync word 3K

    WriteSPI1(0x21);                                                             //ESCRIBE FREND1 (Front End RX Configuration)
    WriteSPI1(0x56);                                                             //Adjusts front-end LNA PTAT current output. Adjusts front-end PTAT outputs. Adjusts current in RX LO buffer (LO input to mixer). Adjusts current in mixer

    WriteSPI1(0x22);                                                             //ESCRIBE FREND0 (Front End RX Configuration)
    WriteSPI1(0x10);                                                             //Adjusts current TX LO buffer (input to PA). The value to use in this field is given by the SmartRF Studio software. Selects PA power setting. This value is an index to the PATABLE, which can be programmed with up to 8 different PA settings. In OOK/ASK mode, this selects the PATABLE index to use when transmitting a ?1?. PATABLE index zero is used in OOK/ASK when transmitting a ?0?. The PATABLE settings from index ?0? to the PA_POWER value are used for ASK TX shaping, and for power ramp-up/ramp-down at the start/end of transmission in all TX modulation formats

    WriteSPI1(0x23);                                                             //ESCRIBE FSCAL3 (Frequency Synthesizer Calibration)
    WriteSPI1(0xE9);

    WriteSPI1(0x24);                                                             //ESCRIBE FSCAL2 (Frequency Synthesizer Calibration)
    WriteSPI1(0x2A);

    WriteSPI1(0x25);                                                             //ESCRIBE FSCAL1 (Frequency Synthesizer Calibration)
    WriteSPI1(0x00);

    WriteSPI1(0x26);                                                             //ESCRIBE FSCAL0 (Frequency Synthesizer Calibration)
    WriteSPI1(0x1F);

    WriteSPI1(0x27);                                                             //ESCRIBE RCCTRL1 (RC Oscillator Configuration)
    WriteSPI1(0x41);

    WriteSPI1(0x28);                                                             //ESCRIBE RCCTRL0 (RC Oscillator Configuration)
    WriteSPI1(0x00);

    WriteSPI1(0x1A);                                                             //ESCRIBE BSCFG (Bit Synchronization Configuration)
    WriteSPI1(0x6C);                                                             //±0 (No data rate offset compensation performed). Clock recovery loop proportional gain after sync word KP. The clock recovery feedback loop integral gain to be used after a sync word is detected KI /2. Clock recovery loop proportional gain before sync word 3KP. Clock recovery loop integral gain before sync word 2KI

    WriteSPI1(0x1B);                                                             //ESCRIBE AGCCTRL2 (AGC Control)
    WriteSPI1(0x03);                                                             //Target amplitude from channel filter 33 dB. Maximum possible LNA + LNA 2 gain. All gain settings can be used

    WriteSPI1(0x1C);                                                             //ESCRIBE AGCCTRL1 (AGC Control)
    WriteSPI1(0x40);                                                             //Carrier sense absolute threshold At MAGN_TARGET setting. Carrier sense relative threshold, Relative carrier sense threshold disabled. Selects between two different strategies for LNA and LNA 2 gain adjustment. When 1, the LNA gain is decreased first. When 0, the LNA 2 gain is decreased to minimum before decreasing LNA gain.

    WriteSPI1(0x1D);                                                             //ESCRIBE AGCCTRL0 (AGC Control)
    WriteSPI1(0x91);                                                             //Channel filter samples 16. OOK/ASK decision boundary 8 dB. Control when the AGC gain should be frozen, Normal operation, Always adjust gain when required. Channel filter samples 8. Sets the level of hysteresis on the magnitude deviation (internal AGC signal that determine gain changes), Medium hysteresis, medium asymmetric dead zone, medium gain

    WriteSPI1(0x3E);                                                             //ESCRIBE PATABLE selecting PA power control settings.
    WriteSPI1(0xC0);

    CS_CC1101=1;
}
void CC1101_Packet(unsigned char Address){
    int i=1;


    RFBuff[0] = Address;                                                        //Dirección
    for(i=1;i<=8;i++){                                                          //Se le agregó un dato mas
        RFBuff[i+1]= dato[i];};



}

void Write_CC1101(unsigned char Strobe){
    unsigned char chip_status,cnt_rx=0;
    char R=0;
    int i=1;
    switch(Strobe){
        case TXFIFO:

                 CS_CC1101=0;
                 WriteSPI1(TXFIFO);                                             //Acceso en burst a TX FIFO
                 WriteSPI1(RFBuff[0]);                                          //Escribe el paquete en la TX FIFO
                 for(i=1;i<=PKT_LEN_MAX;i++)                                    //Escribe Dirección y Datos en la TX FIFO
                 WriteSPI1(RFBuff[i+1]);
                 break;
        case SRES :

                 SCKR=1;
                 SDO=0;                                                         //Secuencia para un correcto Reset al radio CC1101
                 CS_CC1101=0;
                 CS_CC1101=1;
                 __delay_us(40);
                 CS_CC1101=0;
                 while(SDI);
                 WriteSPI1(Strobe);
                 chip_status=ReadSPI1();
                 while(SDI);
                 CS_CC1101=1;
                 do{__delay_us(100);
                 chip_status=Read_CC1101(SNOP);
                 }while(chip_status!=IDLE);
                 break;



        case SFSTXON:
        case SRX:
        case SIDLE:

                 do{
                 CS_CC1101=0;
                 WriteSPI1(Strobe);
                 __delay_us(800);
                 chip_status=ReadSPI1();
                 CS_CC1101=1;

                 chip_status&=0b11110000;
                 if(Strobe==SRX){
                         if(chip_status!=RX)
                            R=1;
                         cnt_rx++;
                         if (cnt_rx >= 50)
                          break;
                 }
                 else if(Strobe==IDLE){
                         if(chip_status!=IDLE)
                            R=1;}
                  else if(Strobe==SFSTXON){
                         if(chip_status!=FSTXON)
                            R=1;}
                 else R=0;
                 }while(R);
                 break;

        case STX:
               do{
                 CS_CC1101=0;
                 WriteSPI1(Strobe);
                __delay_us(800);
                 __delay_us(800);
                 __delay_us(800);
                 chip_status=ReadSPI1();
                 CS_CC1101=1;
                 chip_status&=0b11110000;
                 }while(chip_status!=TX);
                 break;

        case SXOFF:
        case SCAL:
        case SWOR:
        case SPDW:
        case SFRX:
        case SFTX:
        case SWORRST:

                 CS_CC1101=0;
                 WriteSPI1(Strobe);
                 chip_status=ReadSPI1();
                 CS_CC1101=1;
                 break;

         default:break;
                            };// fin de switch




}

void CC1101_ConfRx(void){

         Write_CC1101(SFRX);
         Write_CC1101(SIDLE);
         Write_CC1101(SFRX);
         Write_CC1101(SRX);


}

void CC1101_Reinicia(unsigned char adress){
    CC1101_SRES();                                                              //Realiza un reset al radio CC1101
    CC1101_Init(adress);                                                              //Carga configuración del radio CC1101
    Write_CC1101(SIDLE);                                                         //Radio en Idle
    Write_CC1101(SFRX);                                                         //Limpia RX FIFO
    Write_CC1101(SRX);                                                               //Configura al radio CC1101 para la recepción
}

void CC1101_VerifRx(void){
    unsigned char status_cc1101;

    status_cc1101 = Read_CC1101(SNOP);                                              //Lee el estado actual del radio
    if(status_cc1101 != RX)                                                     //Verifica si el radio aun se encuentra en RX
    {
         Write_CC1101(SFRX);
         Write_CC1101(SIDLE);
         Write_CC1101(SFRX);
         Write_CC1101(SRX);
    }
}

void CC1101_SRES(void){
    SCKR=1;
    SDO=0;                                                                      //Secuencia para un correcto Reset al radio CC1101
    CS_CC1101=0;
    CS_CC1101=1;
    __delay_us(40);
    CS_CC1101=0;
    while(SDI);
    WriteSPI1(SRES);                                                             //Escribe comando SRES
    chip_status=ReadSPI1();                                                      //Lee el estado del radio CC1101
    while(SDI);
    CS_CC1101=1;
    do
    {
        __delay_us(100);
        chip_status=Read_CC1101(SNOP);
    }while(chip_status!=IDLE);
}

void Canal(unsigned char channel){

 	CS=0;
 	WriteSPI1(0x0A);     			//ESCRIBE CHANNR
 	WriteSPI1(channel);
 	CS=1;
}

unsigned char Read_CC1101(unsigned char Strobe){
    unsigned char STATUSorRSSI;

    switch(Strobe){

        case RXFIFO:
        case RSSI :
                  CS_CC1101=0;
                  WriteSPI1(Strobe);                                            //Acceso a burst RX FIFO
                  STATUSorRSSI=ReadSPI1();                                      //Obtenemos la cantidad de paquetes
                  CS_CC1101=1; break;

        case SNOP :
                  CS_CC1101=0;
                  WriteSPI1(Strobe);                                            //Comando SNOP para accesar al estado del radio CC1101
                  STATUSorRSSI=ReadSPI1();
                  CS_CC1101=1;
                  STATUSorRSSI&=0b11110000; break;

        default:break;

    }

    return STATUSorRSSI;

}

void rssi_output_power(unsigned char mode){

    CS_CC1101=0;

    if(mode==0)
    {
        WriteSPI1(0x3E);                                                             //ESCRIBE PATABLE selecting PA power control settings.
        WriteSPI1(0x17);                                                             //Low power
     }
    else{
        WriteSPI1(0x3E);                                                             //ESCRIBE PATABLE selecting PA power control setting
        WriteSPI1(0xC0);                                                             //Máxima potencia
    }
    
    CS_CC1101=1;

    return;
}


#endif

#if defined PIC16

void CC1101_Init(){
    CS_CC1101=0;

    WriteSPI(0x00);                                                             //ESCRIBE EN GDO2 (GDO2 Output Pin Configuration)
    WriteSPI(0x07);                                                             //Enciende cuando el paquete ha sido recibido con CRC Ok. Se apaga cuando el primer byte es leido de la RX FIFO

    WriteSPI(0x02);                                                             //ESCRIBE EN GD00 (GDO0 Output Pin Configuration)
    WriteSPI(0x06);                                                             //Enciende cuando el sync word ha sido enviado y se apaga en el final del paquete.

    WriteSPI(0x03);                                                             //ESCRIBE EN FIFO_THR (RX FIFO and TX FIFO Thresholds)
    WriteSPI(0x07);                                                             //33 bytes en TX FIFO y 32 bytes en RX FIFO

    WriteSPI(0x04);                                                             //ESCRIBE EN SYNC1 (Sync Word, High Byte)
    WriteSPI(0xD3);                                                             //8 MSB of 16-bit sync word

    WriteSPI(0x05);                                                             //ESCRIBE EN SYNC0 (Sync Word, Low Byte)
    WriteSPI(0x91);                                                             //8 LSB of 16-bit sy nc word

    WriteSPI(0x06);                                                             //ESCRIBE EN PKTLEN (Packet Length)
    WriteSPI(PKT_LEN_MAX);

    WriteSPI(0x07);                                                             //ESCRIBE EN PKTCTRL1 (Packet Automation Control)
    WriteSPI(Conf_PKTCTRL1);

    WriteSPI(0x08);                                                             //ESCRIBE EN PKTCTRL0 (Packet Automation Control)
    WriteSPI(Conf_PKTCTRL0);

    WriteSPI(0x09);                                                             //ESCRIBE ADDR (Device Address)
    WriteSPI(Drive_by);                                                         //Address used for packet filtration. Optional broadcast addresses are 0(0x00) and 255 (0xFF).

    WriteSPI(0x0A);                                                             //ESCRIBE CHANNR (Channel Number)
    WriteSPI(Channel);                                                          //The 8-bit unsigned channel number, which is multiplied by the channel spacing setting and added to the base frequency.

    WriteSPI(0x0B);                                                             //ESCRIBE FSCTRL1 (Frequency Synthesizer Control)
    WriteSPI(0x06);

    WriteSPI(0x0C);                                                             //ESCRIBE FSCTRL0 (Frequency Synthesizer Control)
    WriteSPI(0x00);

    WriteSPI(0x0D);                                                             //ESCRIBE FREQ2 (Frequency Control Word, High Byte)
    WriteSPI(0x21);

    WriteSPI(0x0E);                                                             //ESCRIBE FREQ1 (Frequency Control Word, Middle Byte)
    WriteSPI(0x62);

    WriteSPI(0x0F);                                                             //ESCRIBE FREQ0 (Frequency Control Word, Low Byte)
    WriteSPI(0x76);

    WriteSPI(0x10);                                                             //ESCRIBE MDMCFG4 (Modem Configuration)
    WriteSPI(0xF5);                                                             //Data rate = 1.2 KBaudios                0XF8 = 9.6 Kbaudios

    WriteSPI(0x11);                                                             //ESCRIBE MDMCFG3 (Modem Configuration)
    WriteSPI(0x83);

    WriteSPI(0x12);                                                             //ESCRIBE MDMCFG2 (Modem Configuration)
    WriteSPI(Conf_MDMCFG2);

    WriteSPI(0x13);                                                             //ESCRIBE MDMCFG1 (Modem Configuration)
    WriteSPI(Conf_MDMCFG1);

    WriteSPI(0x14);                                                             //ESCRIBE MDMCFG0 (Modem Configuration)
    WriteSPI(0xF8);

    WriteSPI(0x15);                                                             //ESCRIBE DEVIATN (Modem Deviation Setting)
    WriteSPI(0x15);

    WriteSPI(0x16);                                                             //ESCRIBE MCSM2 (Main Radio Control State Machine Configuration)
    WriteSPI(0x07);                                                             //Sirve para la configuracion del TMR de RX y sus condiciones

    WriteSPI(0x17);                                                             //ESCRIBE MCSM1 (Main Radio Control State Machine Configuration)
    WriteSPI(0x00);                                                             //Clear channel indication Always. Next state after finishing packet reception IDLE. Next state after finishing packet transmission IDLE

    WriteSPI(0x18);                                                             //ESCRIBE MCSM0 (Main Radio Control State Machine Configuration)
    WriteSPI(0x18);                                                             //When to perform automatic calibration, Every 4th time when going from RX or TX to IDLE automatically. Timeout after XOSC start Approx. 2.3 ? 2.4 µs. Enables the pin radio control option. Force the XOSC to stay on in the SLEEP state.

    WriteSPI(0x19);                                                             //ESCRIBE FOCCFG (Frequency Offset Compensation Configuration)
    WriteSPI(0x16);                                                             //Saturation point (max compensated offset) ±BWCHAN/4. Freq. compensation loop gain after sync word K/2. Freq. compensation loop gain before sync word 3K

    WriteSPI(0x21);                                                             //ESCRIBE FREND1 (Front End RX Configuration)
    WriteSPI(0x56);                                                             //Adjusts front-end LNA PTAT current output. Adjusts front-end PTAT outputs. Adjusts current in RX LO buffer (LO input to mixer). Adjusts current in mixer

    WriteSPI(0x22);                                                             //ESCRIBE FREND0 (Front End RX Configuration)
    WriteSPI(0x10);                                                             //Adjusts current TX LO buffer (input to PA). The value to use in this field is given by the SmartRF Studio software. Selects PA power setting. This value is an index to the PATABLE, which can be programmed with up to 8 different PA settings. In OOK/ASK mode, this selects the PATABLE index to use when transmitting a ?1?. PATABLE index zero is used in OOK/ASK when transmitting a ?0?. The PATABLE settings from index ?0? to the PA_POWER value are used for ASK TX shaping, and for power ramp-up/ramp-down at the start/end of transmission in all TX modulation formats

    WriteSPI(0x23);                                                             //ESCRIBE FSCAL3 (Frequency Synthesizer Calibration)
    WriteSPI(0xE9);

    WriteSPI(0x24);                                                             //ESCRIBE FSCAL2 (Frequency Synthesizer Calibration)
    WriteSPI(0x2A);

    WriteSPI(0x25);                                                             //ESCRIBE FSCAL1 (Frequency Synthesizer Calibration)
    WriteSPI(0x00);

    WriteSPI(0x26);                                                             //ESCRIBE FSCAL0 (Frequency Synthesizer Calibration)
    WriteSPI(0x1F);

    WriteSPI(0x27);                                                             //ESCRIBE RCCTRL1 (RC Oscillator Configuration)
    WriteSPI(0x41);

    WriteSPI(0x28);                                                             //ESCRIBE RCCTRL0 (RC Oscillator Configuration)
    WriteSPI(0x00);

    WriteSPI(0x1A);                                                             //ESCRIBE BSCFG (Bit Synchronization Configuration)
    WriteSPI(0x6C);                                                             //±0 (No data rate offset compensation performed). Clock recovery loop proportional gain after sync word KP. The clock recovery feedback loop integral gain to be used after a sync word is detected KI /2. Clock recovery loop proportional gain before sync word 3KP. Clock recovery loop integral gain before sync word 2KI

    WriteSPI(0x1B);                                                             //ESCRIBE AGCCTRL2 (AGC Control)
    WriteSPI(0x03);                                                             //Target amplitude from channel filter 33 dB. Maximum possible LNA + LNA 2 gain. All gain settings can be used

    WriteSPI(0x1C);                                                             //ESCRIBE AGCCTRL1 (AGC Control)
    WriteSPI(0x40);                                                             //Carrier sense absolute threshold At MAGN_TARGET setting. Carrier sense relative threshold, Relative carrier sense threshold disabled. Selects between two different strategies for LNA and LNA 2 gain adjustment. When 1, the LNA gain is decreased first. When 0, the LNA 2 gain is decreased to minimum before decreasing LNA gain.

    WriteSPI(0x1D);                                                             //ESCRIBE AGCCTRL0 (AGC Control)
    WriteSPI(0x91);                                                             //Channel filter samples 16. OOK/ASK decision boundary 8 dB. Control when the AGC gain should be frozen, Normal operation, Always adjust gain when required. Channel filter samples 8. Sets the level of hysteresis on the magnitude deviation (internal AGC signal that determine gain changes), Medium hysteresis, medium asymmetric dead zone, medium gain

    WriteSPI(0x3E);                                                             //ESCRIBE PATABLE
    WriteSPI(0xC0);

    CS_CC1101=1;

}


void CC1101_Packet(unsigned char Address){
    int i=1;
                                                                                //Tamaño del paquete
    RFBuff[0] = Address;                                                        //Dirección

    for(i=1;i<=7;i++){                                                          //Datos
        RFBuff[i+1]= dato[i];};



}

void Write_CC1101(unsigned char Strobe){
    unsigned char chip_status;
    char R=0;
    int i=1;
    switch(Strobe){
        case TXFIFO:

                 CS_CC1101=0;
                 WriteSPI(TXFIFO);                                             //Acceso en burst a TX FIFO
                 //paq=RFBuff[0];
                 WriteSPI(RFBuff[0]);                                          //Escribe el paquete en la TX FIFO
                 for(i=1;i<=PKT_LEN_MAX;i++)                                    //Escribe Dirección y Datos en la TX FIFO
                 WriteSPI(RFBuff[i+1]);
        case SRES :                              
            
                 SCKR=1;
                 SDO=0;                                                         //Secuencia para un correcto Reset al radio CC1101
                 CS_CC1101=0;
                 CS_CC1101=1;
                 __delay_us(40);
                 CS_CC1101=0;
                 while(SDI);
                 WriteSPI(Strobe);                    
                 chip_status=ReadSPI();                
                 while(SDI);
                 CS_CC1101=1;
                 do{__delay_us(100);
                 chip_status=Read_CC1101(SNOP);
                 }while(chip_status!=IDLE);
                 break; 
    
        
        
        case SFSTXON:                            
        case SRX:
        case STX:
        case SIDLE:

                 do{
                 CS_CC1101=0;
                 WriteSPI(Strobe);             
                 __delay_us(800);
                 chip_status=ReadSPI(); 
                 CS_CC1101=1;
                 chip_status&=0b11110000;
                 if(chip_status==RX||chip_status==FSTXON||chip_status==TX)
                     R=1;
                 else if(Strobe==IDLE){
                         if(chip_status!=IDLE)
                            R=1;}
                 else R=0;
                 }while(R);
                 break;
        
        
        
        case SXOFF:                              
        case SCAL:
        case SWOR:
        case SPDW:
        case SFRX:
        case SFTX:
        case SWORRST:

                 CS_CC1101=0;                          
                 WriteSPI(Strobe);                    
                 chip_status=ReadSPI();
                 CS_CC1101=1;
                 break;
        
         default:break;
                            };// fin de switch
    
    


}

void CC1101_ConfRx(void){

         Write_CC1101(SFRX);
         Write_CC1101(SIDLE);
         Write_CC1101(SFRX);
         Write_CC1101(SRX);


}

void CC1101_Reinicia(void){
    CC1101_SRES();                                                              //Realiza un reset al radio CC1101
    CC1101_Init();                                                              //Carga configuración del radio CC1101
    Write_CC1101(SIDLE);                                                         //Radio en Idle
    Write_CC1101(SFRX);                                                         //Limpia RX FIFO
    Write_CC1101(SRX);                                                               //Configura al radio CC1101 para la recepción
}

void CC1101_VerifRx(void){
    unsigned char status_cc1101;

    status_cc1101 = Read_CC1101(SNOP);                                              //Lee el estado actual del radio
    if(status_cc1101 != RX)                                                     //Verifica si el radio aun se encuentra en RX
    {
         Write_CC1101(SFRX);
         Write_CC1101(SIDLE);
         Write_CC1101(SFRX);
         Write_CC1101(SRX);
    }
}

void CC1101_SRES(void){
    SCKR=1;
    SDO=0;                                                                      //Secuencia para un correcto Reset al radio CC1101
    CS_CC1101=0;
    CS_CC1101=1;
    __delay_us(40);
    CS_CC1101=0;
    while(SDI);
    WriteSPI(SRES);                                                             //Escribe comando SRES
    chip_status=ReadSPI();                                                      //Lee el estado del radio CC1101
    while(SDI);
    CS_CC1101=1;
    do
    {
        __delay_us(100);
        chip_status=Read_CC1101(SNOP);
    }while(chip_status!=IDLE);
}

void Canal(unsigned char channel){

 	CS=0;
 	WriteSPI(0x0A);     			//ESCRIBE CHANNR
 	WriteSPI(channel);
 	CS=1;
}

unsigned char Read_CC1101(unsigned char Strobe){
    unsigned char STATUSorRSSI;

    switch(Strobe){

        case RFFIFO:
        case RSSI :
                  CS_CC1101=0;
                  WriteSPI(Strobe);                                            //Acceso a burst RX FIFO
                  STATUSorRSSI=ReadSPI();                                      //Obtenemos la cantidad de paquetes
                  CS_CC1101=1; break;

        case SNOP : 
                  CS_CC1101=0;
                  WriteSPI(Strobe);                                            //Comando SNOP para accesar al estado del radio CC1101
                  STATUSorRSSI=ReadSPI();
                  CS_CC1101=1;
                  STATUSorRSSI&=0b11110000; break;

        default:break;
                       }
    
    return STATUSorRSSI;

}

#endif