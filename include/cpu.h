#ifndef _CPU_H
#define _CPU_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef uint8_t byte;  // 8-bit standard byte
typedef uint16_t word;

// Registers
extern word PC;  // Program Counter
extern byte SP;  // Stack Pointer
extern byte A;   // Accumulator
extern byte X;   // Index Register X
extern byte Y;   // Index Register Y
extern byte PS;  // Processor Status
                 // From MSB to LSB:
                 // Negative(N) - Overflow(V) - Unused - Break Command(B) - Decimal Mode(D) - Interrupt Disable(I) - Zero(Z) - Carry(C)

// Flags
#define C (PS & 0x01)
#define Z (PS & 0x02)
#define I (PS & 0x04)
#define D (PS & 0x08)
#define B (PS & 0x10)
#define V (PS & 0x40)
#define N (PS & 0x80)


// The Memory
extern byte memory[0x10000];

void resetCPU();
void resetMemory();
void setMemory(byte newMem[]);
void initlizeCPU(byte mem[]);

byte readMemory(word addr);
byte readByte(byte *addr);
void writeByte(byte *addr, byte data);
word readWord(word addr);
void setNegativeFlag(bool value);
void setOverflowFlag(bool value);
void setZeroFlag(bool value);
void setCarryFlag(bool value);

bool validateOpcode(byte aaa, byte bbb, byte validAddrModes[]);

byte *decodeG1Address(byte bbb);
byte *decodeG2Address(byte bbb);

void executeG1(byte aaa, byte *addr);
void executeG2(byte aaa, byte *addr);

void execute();

void ORA(byte *addr);
void AND(byte *addr);
void EOR(byte *addr);
void ADC(byte *addr);
void STA(byte *addr);
void LDA(byte *addr);
void CMP(byte *addr);
void SBC(byte *addr);

// void ASL(byte *addr);
// void ROL(byte *addr);
// void LSR(byte *addr);
// void ROR(byte *addr);
// void STX(byte *addr);
// void LDX(byte *addr);
// void DEC(byte *addr);
// void INC(byte *addr);

#endif