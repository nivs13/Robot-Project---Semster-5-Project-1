/***********************************************************************************

Niv Segal
Stepper Motor Code
April 5, 2017


This code is designed to operate the Stepper motor for the HCS12 microcontroller
board.

- The speed of the motor can be slowed down by increasing the integer value of 
  stepper_speeed
- The step type and direction of the motor can be changed by changing the step_type
  variable between -2,-1,1,2 with 1 being half step and 2 being full step, while 
  negtiave being clock-wise and positave means counter clock-wise


***********************************************************************************/

#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "macros.h"


//prototypes

void stepper_init(void);



#define MOTOR_A                  0x80
#define MOTOR_AC                 0xA0
#define MOTOR_C                  0x20
#define MOTOR_BC                 0x60
#define MOTOR_B                  0x40
#define MOTOR_BD                 0x50
#define MOTOR_D                  0x10
#define MOTOR_AD                 0x90

#define REVERSE                  (-1)
#define STEPPER_MASK             0x07
#define PORT_T_WRITE_MASK        0xF0
#define RTI_PERIOD               0x49                                                   // Sets RTI period to 5.12mS or 200Hz (Look up tabel in slides)
#define LIMIT_SWITCH_MASK        0xC0

unsigned char stepper_speed;
unsigned char rti_count;
unsigned char stepper_array[] = {MOTOR_A,MOTOR_AC,MOTOR_C,MOTOR_BC,MOTOR_B,MOTOR_BD,MOTOR_D,MOTOR_AD};        // array with the different outputs required for the stepper motor.
unsigned char state;                                                                                          // array index
char step_type;                                                                                               // full step or halfstep, forwards or backwards
char limit_switch;



void main(void) {
  /* put your own code here */
  
  //Initialization of stepper motor
  
  stepper_init();
  
  
  
  /*state = 0;
  step_type = -1; 
  
  
  SET_BITS(DDRP,DDRP_DDRP3_MASK);                                                                        // enables the stepper motor
  SET_BITS(PTP,PTP_PTP3_MASK);
  
  SET_BITS(DDRT, (DDRT_DDRT7_MASK|DDRT_DDRT6_MASK|DDRT_DDRT5_MASK|DDRT_DDRT4_MASK));                       // configures Port T 4,5,6,7 to be outputs
  
  FORCE_BITS(PTT,PORT_T_WRITE_MASK,stepper_array[state]);                                                                             // loads the first value of stepper_array into the Port T
  
  */
  
  RTICTL = RTI_PERIOD;                                                      // Set RTI period 
  COPCTL |= COPCTL_RSBCK_MASK;                                              // Freeze RTI during BDM active
  CRGFLG = CRGFLG_RTIF_MASK;                                                // Clear any possibly pending RTI interrupts
  CRGINT |= CRGINT_RTIE_MASK;                                               // Enable RTI interrupt

  

	EnableInterrupts;
	
	
	


  for(;;) {
   // _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}


interrupt VectorNumber_Vrti void RTIhandler (void) {
	
	
    CRGFLG = CRGFLG_RTIF_MASK;                                                // Clear any possibly pending RTI interrupts

   limit_switch = (PTAD & LIMIT_SWITCH_MASK);                                 // equates the value of PAD6 and PAD7 to limit_switch
   
   
   if(limit_switch != 0) {                                                     // checks if either of the limit switches has been pressed
    step_type = (step_type * REVERSE);
   }
   
    
	 if (rti_count < stepper_speed) {                                           // counter that devides the speed of the motor.
	  rti_count++;       
	 }
	 else{
	  
	  state += step_type;                                                       //mod 7
	  state &= STEPPER_MASK;
	  
	  FORCE_BITS(PTT,PORT_T_WRITE_MASK,stepper_array[state]);
	  
	  rti_count = 1; 
	 }
	}



void stepper_init(void) {
  
  rti_count = 1;
  stepper_speed = 4;
  state = 0;
  step_type = -1;
  limit_switch = 0; 
  
  CLR_BITS(DDRAD,(DDRAD_DDRAD6_MASK|DDRAD_DDRAD7_MASK));                                                   // configures PAD6 & PAD7 to be inputs
  SET_BITS(ATDDIEN,(ATDDIEN_IEN6_MASK|ATDDIEN_IEN7_MASK));                                                 // Must be set for PAD registers to read digital. Read Datasheet for more
  
  SET_BITS(DDRP,DDRP_DDRP3_MASK);                                                                          // enables the stepper motor by enabeling PP3 to an output
  SET_BITS(PTP,PTP_PTP3_MASK);                                                                             // sets PP3 to a high
  
  SET_BITS(DDRT, (DDRT_DDRT7_MASK|DDRT_DDRT6_MASK|DDRT_DDRT5_MASK|DDRT_DDRT4_MASK));                       // configures Port T 4,5,6,7 to be outputs
  
  FORCE_BITS(PTT,PORT_T_WRITE_MASK,stepper_array[state]);                                                                             // loads the first value of stepper_array into the Port T
}