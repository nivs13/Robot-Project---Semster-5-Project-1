/********************************************************************************************************* 

Niv Segal
April 6, 2017
DC_motor

This code runs the operations of a DC motor

*********************************************************************************************************/



#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "macros.h"


void DC_motor_init(void);



#define EIGHT_BIT_MODE 0x00
#define PWM_RESET 0x00
#define PWM_ECLK 0x00
#define PRESCALE_0 0x00
#define SA_DIVIDE_2 0x01
#define PERIOD_22KHZ_LEFT_ALINGED 182U
#define PWM_DTY_10 18U
#define PWM_DTY_60 108U
#define PWM_DTY_75 135U
#define PERIOD_22KHZ_CENTER_ALINGED 182U
#define SB_DIVIDE_128 0x60
#define PERIOD_300HZ_LEFT_ALINGED 208U
#define RTI_PERIOD 0x49                                                   // Sets RTI period to 5.12mS (Look up tabel in slides)



void main(void) {
  /* put your own code here */
  
  CLR_BITS(PEAR,PEAR_NECLK_MASK);                                                     // Turns on E-clock on PE4
  DC_motor_init();



	EnableInterrupts;


  for(;;) {
   // _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}







void DC_motor_init(void) {
  
  
  //Initilize PWM ports 4 & 5
  PWMCTL = EIGHT_BIT_MODE;                                                              // 8-bit mode 
  PWMPRCLK = PWM_ECLK;                                                                  // Counts E-clock directly
  PWMSCLA = SA_DIVIDE_2;                                                                // Set the SA divisor to devide the clock by 2 (Refer to table 8.4 in textbook)
  PWMCLK |= (PWMCLK_PCLK4_MASK | PWMCLK_PCLK5_MASK);                                    // Select clock SA as the clock source for PWM port 4 & 5 
  PWMPOL |= (PWMPOL_PPOL4_MASK | PWMPOL_PPOL5_MASK);                                    // Sets both PWM port 4 & 5 to output high at the start of a period (Positave Polarity), by setting the bits
  PWMCAE &= LOW(PWMCAE_CAE0_MASK);                                                      // Select left - aligned mode for PWM port 4
  PWMCAE &= LOW(PWMCAE_CAE1_MASK);                                                      // Select left - aligned mode for PWM port 5
  PWMPER4 = PERIOD_22KHZ_LEFT_ALINGED;                                                  // Sets period value to 22KHz
  PWMPER5 = PERIOD_22KHZ_LEFT_ALINGED;
  PWMDTY4 = PWM_DTY_75;                                                                 // Duty cycle (75% of the PWM frequency for PWM channel 4)
  PWMDTY5 = PWM_DTY_75;                                                                 // Duty cycle (75% of the PWM frequency for PWM channel 5)
  PWMCNT4 = PWM_RESET;                                                                  // Reset PWM4 & PWM5 counter
  PWMCNT5 = PWM_RESET;
  
  
  SET_BITS(DDRB, (DDRB_BIT0_MASK|DDRB_BIT1_MASK|DDRB_BIT2_MASK|DDRB_BIT3_MASK));         // configures PORTB 0,1,2,3 to outputs
  
  SET_BITS(PORTB,(PORTB_BIT1_MASK|PORTB_BIT3_MASK));                                     // writes a 1 to bits 0 and 3
  CLR_BITS(PORTB,(PORTB_BIT0_MASK|PORTB_BIT2_MASK));                                     // writes a 0 to bits 1 and 2
  
  
  
  PWME |= (PWME_PWME4_MASK|PWME_PWME5_MASK);                                            // Enable the PWM0 and PWM1 ports
  
  
}
  