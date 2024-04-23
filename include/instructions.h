#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "cpu.h"

void ORA(byte *addr, byte *accumalatorAddr);
void AND(byte *addr, byte *accumalatorAddr);
void EOR(byte *addr, byte *accumalatorAddr);
void ADC(byte *addr, byte *accumalatorAddr, byte *psAddr);
void STA(byte *addr, byte *accumalatorAddr);
void LDA(byte *addr, byte *accumalatorAddr);
void CMP(byte *addr, byte *accumalatorAddr);
void SBC(byte *addr, byte *accumalatorAddr, byte *psAddr);

void ASL(byte *addr);
void ROL(byte *addr, byte *psAddr);
void LSR(byte *addr);
void ROR(byte *addr, byte *psAddr);
void STX(byte *addr, byte *xAddr);
void LDX(byte *addr, byte *xAddr);
void DEC(byte *addr);
void INC(byte *addr);

void BIT(byte *addr, byte *accumalatorAddr);
void JMP(byte *addr, word *pcAddr, byte *memory);
void STY(byte *addr, byte *yAddr);
void LDY(byte *addr, byte *yAddr);
void CPY(byte *addr, byte *yAddr);
void CPX(byte *addr, byte *xAddr);

#endif  // INSTRUCTIONS_H