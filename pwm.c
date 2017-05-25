/*
 * File:   pwm.c
 * Author: OSCAR
 *
 * Created on 29 de octubre de 2016, 10:49 AM
 */


#include <xc.h>
#include <plib/timers.h>
#include <plib/pwm.h>
#include "pwm.h"


int i = 0;
int countup = 1; //our flag to set up/down dutycycle
int DutyCycle = 0;
unsigned char Timer2Config; //PWM clock source


//void PWM_init(unsigned long pwm_freq)
//{
//    unsigned char pwm_value=0;
//    unsigned long Tpwm=0;
//    Tpwm=1/pwm_freq;
//    Timer2Config = T2_PS_1_16; //prescale 16
//    OpenTimer2(Timer2Config);
//    pwm_value= (char)((Tpwm /(4* _XTAL_FREQ* PRESCALER))-1);
////    pwm_value = (char)(((pwm_freq ) + 1) * 4 * _XTAL_FREQ * PRESCALER);             
//    OpenPWM1(pwm_value); //Open pwm at pwm frequency Hz
//    return;
//}

void PWM_init1(unsigned char period)
{
    Timer2Config = T2_PS_1_16; //prescale 16
//    OpenTimer2(Timer2Config); 
    
 
  T2CON = (0xfb & Timer2Config);  // Set all configuration values, but
                            // don't start timer yet 								

  TMR2 = 0;                 // Clear Timer2
  PIR1bits.TMR2IF = 0;

  
    PIE1bits.TMR2IE = 0;

    T2CONbits.TMR2ON = 1; // Turn on Timer2

    
    
    OpenPWM1(period); //Open pwm at pwm frequency Hz.
//    CloseTimer2();
    return;
}
void PWM_DutyCycle1(unsigned char percentageDuty )
{ 
   
    unsigned int DC=0, DutyCycle=0;
  
    DC=(unsigned int)(percentageDuty *10.23);
//    DutyCycle = (DC* _XTAL_FREQ);
//    SetDCPWM1(DutyCycle);
    SetDCPWM1(DC);
    return;
}
//void PWM_init2(unsigned char period)
//{
//    Timer2Config = T2_PS_1_16; //prescale 16
//    OpenTimer2(Timer2Config);             
//    OpenPWM2(period); //Open pwm at pwm frequency Hz
//    return;
//}
//void PWM_DutyCycle2(unsigned char percentageDuty )
//{ 
//   
//    unsigned int DC=0, DutyCycle=0;
//  
//    DC=(unsigned int)(percentageDuty *10.23);
////    DutyCycle = (DC* _XTAL_FREQ);
////    SetDCPWM1(DutyCycle);
//    SetDCPWM2(DC);
//    return;
//}