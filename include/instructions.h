#ifndef _INSTRUCTIONS_H
#define _INSTRUCTIONS_H

// Define the opcodes for the instructions

/* Group 1*/
#define INS_ORA_IM 0x09
#define INS_ORA_ZP 0x05
#define INS_ORA_ZPX 0x15
#define INS_ORA_ABS 0x0D
#define INS_ORA_ABSX 0x1D
#define INS_ORA_ABSY 0x19
#define INS_ORA_INDX 0x01
#define INS_ORA_INDY 0x11

#define INS_AND_IM 0x29
#define INS_AND_ZP 0x25
#define INS_AND_ZPX 0x35
#define INS_AND_ABS 0x2D
#define INS_AND_ABSX 0x3D
#define INS_AND_ABSY 0x39
#define INS_AND_INDX 0x21
#define INS_AND_INDY 0x31

#define INS_EOR_IM 0x49
#define INS_EOR_ZP 0x45
#define INS_EOR_ZPX 0x55
#define INS_EOR_ABS 0x4D
#define INS_EOR_ABSX 0x5D
#define INS_EOR_ABSY 0x59
#define INS_EOR_INDX 0x41
#define INS_EOR_INDY 0x51

#define INS_ADC_IM 0x69
#define INS_ADC_ZP 0x65
#define INS_ADC_ZPX 0x75
#define INS_ADC_ABS 0x6D
#define INS_ADC_ABSX 0x7D
#define INS_ADC_ABSY 0x79
#define INS_ADC_INDX 0x61
#define INS_ADC_INDY 0x71

#define INS_STA_ZP 0x85
#define INS_STA_ZPX 0x95
#define INS_STA_ABS 0x8D
#define INS_STA_ABSX 0x9D
#define INS_STA_ABSY 0x99
#define INS_STA_INDX 0x81
#define INS_STA_INDY 0x91

#define INS_LDA_IM 0xA9
#define INS_LDA_ZP 0xA5
#define INS_LDA_ZPX 0xB5
#define INS_LDA_ABS 0xAD
#define INS_LDA_ABSX 0xBD
#define INS_LDA_ABSY 0xB9
#define INS_LDA_INDX 0xA1
#define INS_LDA_INDY 0xB1

#define INS_CMP_IM 0xC9
#define INS_CMP_ZP 0xC5
#define INS_CMP_ZPX 0xD5
#define INS_CMP_ABS 0xCD
#define INS_CMP_ABSX 0xDD
#define INS_CMP_ABSY 0xD9
#define INS_CMP_INDX 0xC1
#define INS_CMP_INDY 0xD1

#define INS_SBC_IM 0xE9
#define INS_SBC_ZP 0xE5
#define INS_SBC_ZPX 0xF5
#define INS_SBC_ABS 0xED
#define INS_SBC_ABSX 0xFD
#define INS_SBC_ABSY 0xF9
#define INS_SBC_INDX 0xE1
#define INS_SBC_INDY 0xF1

#endif