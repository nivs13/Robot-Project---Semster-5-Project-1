#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#define RDRF_MASK 0x20
#define RingMask 0x7F

#define BaudRate 9600
#define ClockRate 1550000
#define Divider (ClockRate/16/BaudRate)

interrupt VectorNumber_Vsci void SCIhandler( void );

void putcSCI( char cx );
void putsSCI( char *str );
char getcSCI( void );
 
void main(void) 
{
 char hello[14]= "Hello World!";

 SCISR1 = 0;
 
 SCIBD = Divider;      //configures Baud rate at set value
 
 SCICR1 = 0x00;          //First sci control register     set to 0x80 for loop select enable
 
 SCICR2 = 0;
 
 SCICR2 |= (SCICR2_RE_MASK | SCICR2_TE_MASK);
 
 SCICR2 |= RDRF_MASK;       //enables reciever full interrupts
 
	EnableInterrupts;
  
for(;;)
  putsSCI(hello);
}

void putcSCI( char cx ) {
  while (!(SCISR1 & SCISR1_TDRE_MASK));
  SCIDRL = cx;
}

void putsSCI( char *str ) {
  while( *str )
    putcSCI( *str++);
}

char getcSCI( void ) {
  while(!(SCISR1 & SCISR1_RDRF_MASK));
  return(SCIDRL);
}

// SCI interrupt handler
// Only caring about Receiver Full Interrupt Flag, to see if there's information that has been sent to us (bit 5)
// 
// SCI is interrupt #20
interrupt VectorNumber_Vsci void SCIhandler( void ){
    static char recievebuff[64];
    static char buffoff =0b00000000;

    if ((SCISR1 &= RDRF_MASK)>0){  //if the RDRF flag is set, Take RX info and save to ring buffer                   
        recievebuff[buffoff]= SCIDRL;
        buffoff++;
        buffoff &= RingMask; 
    }     
} // end of SCIhandler()