#ifndef _CPU_H
#define _CPU_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t byte;  // 8-bit standard byte
typedef uint16_t word;

// Registers
word const readPC();  // Program Counter
byte const readSP();  // Stack Pointer
byte const readA();   // Accumulator
byte const readX();   // Index Register X
byte const readY();   // Index Register Y
byte const readPS();  // Processor Status
                      // From MSB to LSB:
                      // Negative(N) - Overflow(V) - Unused - Break Command(B) - Decimal Mode(D) - Interrupt Disable(I) - Zero(Z) - Carry(C)

void resetCPU();
void resetMemory();
void setMemory(byte newMem[]);
void readMemoryFromFile(char *fileName);
void initlizeCPU(byte mem[], char *fileName);

byte readMemory(word addr);
byte readByte(byte *addr);
void writeByte(byte *addr, byte data);
word readWord(word addr);
void setNegativeFlag(bool value);
void setOverflowFlag(bool value);
void setZeroFlag(bool value);
void setCarryFlag(bool value);

bool validateOpcode(byte aaa, byte bbb, byte validAddrModes[]);

byte *decodeG1AddressMode(byte bbb);
byte *decodeG23AddressMode(byte bbb, byte aaa);

void decodeG1Instruction(byte aaa, byte *addr);
void decodeG2Instruction(byte aaa, byte *addr);
void decodeG3Instruction(byte aaa, byte *addr);

void execute();

void ORA(byte *addr);
void AND(byte *addr);
void EOR(byte *addr);
void ADC(byte *addr);
void STA(byte *addr);
void LDA(byte *addr);
void CMP(byte *addr);
void SBC(byte *addr);

void ASL(byte *addr);
void ROL(byte *addr);
void LSR(byte *addr);
void ROR(byte *addr);
void STX(byte *addr);
void LDX(byte *addr);
void DEC(byte *addr);
void INC(byte *addr);

void BIT(byte *addr);
void JMP(byte *addr);
void STY(byte *addr);
void LDY(byte *addr);
void CPY(byte *addr);
void CPX(byte *addr);

#endif