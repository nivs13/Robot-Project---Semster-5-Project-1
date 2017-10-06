#define SCF ATDSTAT0_SCF_MASK

#define ATD_IP_CHNL     0

#define ATDCL2          0xE0 // Normal ATD operation, CCF flag clear when result register accessed, conversion halted during wait mode.
#define ATDCL3          0x0A // 1 conversion, Finishes conversion and then freezes.
#define ATDCL4          0xA1 // 8 bit mode, maximum ATD clock frequency (2MHz) 
#define ATDCL5          (0x60 | (0x01 << ATD_IP_CHNL)) // signed conversion, scan on, channel 1