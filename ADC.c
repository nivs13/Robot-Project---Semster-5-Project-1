#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "Bitwise-Operations.h"

#define ATD_IP_CHNL     0

#define ATDCL2          0xE0 // Normal ATD operation, CCF flag clear when result register accessed, conversion halted during wait mode.
#define ATDCL3          0x0A // 1 conversion, Finishes conversion and then freezes.
#define ATDCL4          0xA1 // 8 bit mode, maximum ATD clock frequency (2MHz)
#define ATDCL5          (0x20 | (0x01 << ATD_IP_CHNL)) // signed conversion, scan on, channel 1

void getATD(void);

void main(void){

    SET_BITS(ATDCTL2, ATDCL2);
    SET_BITS(ATDCTL3, ATDCL3);
    SET_BITS(ATDCTL4, ATDCL4);

    for(;;) {
        getATD();
    }
}

void getATD(void){
    static int result;

    ATDCTL5 = ATDCL5;
    while (!(ATDSTAT0 & ATDSTAT0_SCF_MASK));
    result =  ATDDR0H;
}