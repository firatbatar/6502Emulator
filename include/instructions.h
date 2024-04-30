#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "cpu.h"

void ORA(byte *addr, CPU_t *cpu);
void AND(byte *addr, CPU_t *cpu);
void EOR(byte *addr, CPU_t *cpu);
void ADC(byte *addr, CPU_t *cpu);
void STA(byte *addr, CPU_t *cpu);
void LDA(byte *addr, CPU_t *cpu);
void CMP(byte *addr, CPU_t *cpu);
void SBC(byte *addr, CPU_t *cpu);

void ASL(byte *addr, CPU_t *cpu);
void ROL(byte *addr, CPU_t *cpu);
void LSR(byte *addr, CPU_t *cpu);
void ROR(byte *addr, CPU_t *cpu);
void STX(byte *addr, CPU_t *cpu);
void LDX(byte *addr, CPU_t *cpu);
void DEC(byte *addr, CPU_t *cpu);
void INC(byte *addr, CPU_t *cpu);

void BIT(byte *addr, CPU_t *cpu);
void JMP(byte *addr, CPU_t *cpu);
void STY(byte *addr, CPU_t *cpu);
void LDY(byte *addr, CPU_t *cpu);
void CPY(byte *addr, CPU_t *cpu);
void CPX(byte *addr, CPU_t *cpu);

#endif  // INSTRUCTIONS_H