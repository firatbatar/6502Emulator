#ifndef _CPU_H
#define _CPU_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// PS Flag Masks
#define CM 0x01  // Carry
#define ZM 0x02  // Zero
#define IM 0x04  // Interrupt Disable
#define DM 0x08  // Decimal Mode
#define BM 0x10  // Break Command
#define VM 0x40  // Overflow
#define NM 0x80  // Negative

typedef uint8_t byte;  // 8-bit standard byte
typedef uint16_t word;

const word readPC();  // Program Counter
const byte readSP();  // Stack Pointer
const byte readA();   // Accumulator
const byte readX();   // Index Register X
const byte readY();   // Index Register Y
const byte readPS();  // Processor Status
                      // From MSB to LSB:
                      // Negative(N) - Overflow(V) - Unused - Break Command(B) - Decimal Mode(D) - Interrupt Disable(I) - Zero(Z) - Carry(C)
void writePC(word v);
void writeSP(byte v);
void writeA(byte v);
void writeX(byte v);
void writeY(byte v);
void writePS(byte v);

void resetCPU();
void resetMemory(byte v);
void setMemory(byte newMem[]);
void readMemoryFromFile(char *fileName);
void initlizeCPU(byte mem[], char *fileName);

byte readMemory(word addr);
void writeMemory(word addr, byte data);
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