/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * File:   CC1101V2.h                                                          *
 * Autor: Ing. Jorge Luis Gutiérrez Palomino                                   *
 * Fecha: 13 de noviembre de 2012.                                             *
 *                                                                             *
 * Modificado por : Ing.Luis Fernando Santos Navarro                           *
 *                  Ing.Oscar Rigoberto Carvajal Ortiz                         *
 * Fecha: 24 de Septiembre de 2014.                                            *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef CC1101_H
#define	CC1101_H

#define PIC18
//#define PIC16


#if defined PIC18
//Pines para la comunicación del radio
#define SDI		PORTCbits.RC4                                           //MISO
#define SDO		PORTCbits.RC5                                           //MOSI
#define SCKR		PORTCbits.RC3                                           //Clock
#define CS_CC1101	PORTDbits.RD7                                           //Chip Select
#define GDO0_TX         PORTDbits.RD0                                           //GDO0 Transmision
#define GDO2_RX         PORTDbits.RD1                                           //GDO2 Recepción
#endif

#if defined  (PIC16)
#define SDI			PORTCbits.RC7                                   //MISO
#define SDO			PORTCbits.RC4                                   //MOSI
#define SCK			PORTCbits.RC6                                   //Clock
#define CS_CC1101		PORTCbits.RC2                                   //Chip Select
#define GDO2_RX                 PORTCbits.RC5                                   //GDO2 Recepción
#define GDO0_TX                 PORTCbits.RC0                                   //GDO0 Transmision
#endif

                                           //direccione del Drive-by

         //Configuraciones cc1101


         //CANAL

#define Channel         0x05                                                    // Canal de transmicion

        /****control de paquetes del registro PKTCRL1 *****/

// #define Conf_PKTCTRL1  0x09                                                    // Flush automatico al RF FIFO cuando CRC no es correcto,Addres check-no broadcast,
#define Conf_PKTCTRL1  0X0D                                                   // Anexado de 2 bytes al payload del paquete ( RSSI Y Valores de LWI, asi como el CRC OK ), Flush automatico al RF FIFO cuando CRC no es correcto,Addres check-no broadcast,

        /****control de paquetes del registro PKTCRL0 *****/

 #define Conf_PKTCTRL0   0x44                                                   // Tamano de paquete fijo( segun el tamano PKT_LEN_MAX asignado), Cálculo de CRC en TX y RX de comprobación CRC en habilitado, El modo normal, use FIFO para RX y TX , Turn data whitening on / off
//#define Conf_PKTCTRL0  0X45                                                   // Tamano variable del paquete configurado por el primer byte despues del SYNC WORD, Cálculo de CRC en TX y RX de comprobación CRC en habilitado, El modo normal, use FIFO para RX y TX , Turn data whitening on / off
//#define Conf_PKTCTRL0  0x32                                                   // Cálculo de CRC en TX y RX de comprobación CRC Deshabilitado,Tamano de paquete fijo( segun el tamano PKT_LEN_MAX asignado), El modo normal, use FIFO para RX y TX , Turn data whitening on / off

        /**** Tamano del paquete *****/

#define PKT_LEN_MAX      0x09                                                   // Tamaño máximo del paquete( utilizar solo si se configuro  en PKTCTRL)

       /****  Configuracion del registro modem MDMCFG2 *****/

#define Conf_MDMCFG2     0x13                                                   // Formato de modulacion de la senal de radio GFSK, Disabel machester encoding, 30/32 sync word bits detected, Enable digital DC blocking filter before demodulator
//#define Conf_MDMCFG2    0x03                                                  // Formato de modulacion de la senal de radio 2-FSK, Disabel machester encoding, 30/32 sync word bits detected, Enable digital DC blocking filter before demodulator
//#define Conf_MDMCFG2    0x33                                                  // Formato de modulacion de la senal de radio ASK/OOK, Disabel machester encoding, 30/32 sync word bits detected, Enable digital DC blocking filter before demodulator
//#define Conf_MDMCFG2    0x43                                                  // Formato de modulacion de la senal de radio 4-ASK, Disabel machester encoding, 30/32 sync word bits detected, Enable digital DC blocking filter before demodulator

        /**** Configuracion del registro modem MDMCFG1 *****/

#define Conf_MDMCFG1     0xA2                                                   //Enable Forward Error Correction (FEC) with interleaving for packet payload, 4 preamble bytes(Ver datasheet las variantes), 2 bit channel spacing
//#define Conf_MDMCFG1    0x22                                                  //2 bit exponent of channel spacing. Sets the minimum number of preamble bytes to be transmitted,4 preamble bytes(Ver datasheet las variantes)

#define MCSM1            0b00000011                                             //Next state after  TX     (bits[1:0]):      IDLE 00 ,FSTXON 01 ,TX 10 ,RX 11
                                                                                //Next state after  RX     (bits[3:2]):      IDLE 00 ,FSTXON 01 ,TX 10 ,RX 11
                                                                                //Clear channel indication (bits[5:4]):      Always 00 ,if RSSI below threshold 01 ,Unless currently receivin a packet 10 ,If RSSI below threshold unless currentlyreceiving a packet11





        // Nombre de los strobes //

#define   SRES       0x30                                                       // Strobe que realiza el reset del radio
#define   SFSTXON    0x31                                                       //Strobe para habilitar el sintonizador de frecuencia
#define   SXOFF      0x32                                                       //Strobe para apagar el cristal del oscilador
#define   SCAL       0x33                                                       //Strobe para calibrar el sintonizador de frecuencia y apagarlo
#define   SRX        0x34                                                       //Strobe para habilitar la recepción SRX
#define   STX        0x35                                                       //Strobe para habilitar la transmisión STX
#define   SIDLE      0x36                                                       //Strobe para habilitar modo de espera SIDLE
#define   SWOR       0x38                                                       //Strobe para que habilita el modo Wake On Radio
#define   SPDW       0x39                                                       //Strobe para habilitar el power down mode
#define   SFRX       0x3A                                                       //Strobe que realiza un Flush en RX FIFO
#define   SFTX       0x3B                                                       //Strobe que realiza un Flush en TX FIFO
#define   SWORRST    0x3C                                                       //Strobe que realiza un reset al reloj de tiempo real
#define   SNOP       0x3D                                                       //Strobe para leer el estado del radio
#define   RSSI       0xF4                                                       //para obtener el RSSI
#define   TXFIFO     0x7F                                                       //Strobe que escribe el paquete configurado en la TX FIFO
#define   RXFIFO     0xFF                                                       //Strobe que accesa al RX FIFO


        //Estados del radio CC1101 //

#define IDLE			0
#define RX			16
#define TX			32
#define FSTXON			48
#define CALIBRATE		64
#define SETTLING		80
#define RXFIFO_OVERFLOW		96
#define TXFIFO_UNDERFLOW	112

void SPI1_CC1101_Init(unsigned char Frec_Mhz);
void CC1101_Init(unsigned char adress);                                         //Funcion para inicializar el CC1101
void CC1101_Packet(char Address);                                               //Funcion para armar paquete de la RX FIFO
void Write_CC1101(unsigned char Strobe);                                        //Funcion para mandar un STROBE al CC1101
void CC1101_ConfRx(void);                                                       //Funcion para Configurara el CC1101 en modo recepcion ( RX )
void CC1101_VerifRx(void);                                                      //Funcion para verificar que se este en estado RX
void CC1101_Reinicia(unsigned char adress);                                     //Funcion que reinicia el CC1101
void CC1101_SRES(void);                                                         //Funcion que se utiliza para reiniciar el CC1101
void Canal(unsigned char channel);                                              //Funcion para establecer el canal del CC1101
unsigned char CC1101_Detect(void);                                              //Funcion para detectar al CC1101
unsigned char CC1101_Restore(unsigned char status_act);                         //Funcion para restaurar al CC1101
unsigned char Read_CC1101(unsigned char Strobe);                                //Funcion para Leer la respuesta de un STROBE al CC1101
void rssi_output_power(unsigned char mode);

                                                

#endif	/* CC1101V2_H */

