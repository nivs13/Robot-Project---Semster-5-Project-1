#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

//interrupt VectorNumber_Vtimch2 void ISR_usDelay(void);
  
unsigned int dutycycle = 500;  

void main(void) {  
  DDRT = 0xFF;
  PTT = 0x06;  
  /*TSCR2 	= 0x03;           //pre-scaler of 8
  TSCR1 	= 0xB0;      
  TCTL2   = 0x20;           //drive low  08               
  
                                      //tc2 stuff was here

  TIE     |= 0x04;
 	
	TIOS    |= TIOS_IOS2_MASK;	//was IOS3
	
  TC2 	  = TCNT + dutycycle;	//arbitrary time to enter ISR to start the program ...... tc3   
	EnableInterrupts;
	
  for(;;); 
}

interrupt VectorNumber_Vtimch2 void ISR_usDelay(void){
    if(TCTL2 == 0x20){
    TC2 += (20000 - dutycycle);    //tc3
    TCTL2 = 0x30; //was C0
    } 
    
    else if(TCTL2 == 0x30){
    TC2 += dutycycle;		
    TCTL2 = 0x20; //was 80           //tc3
    }  */
}
