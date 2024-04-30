#ifndef CPU_H
#define CPU_H

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

/* CPU Structure */
typedef struct __CPU_t {
    word PC;       // Program Counter
    byte SP;       // Stack Pointer
    byte A;        // Accumulator
    byte X;        // Index Register X
    byte Y;        // Index Register Y
    byte PS;       // Processor Status
                   // From MSB to LSB:
                   // Negative(N) - Overflow(V) - Unused - Break Command(B) - Decimal Mode(D) - Interrupt Disable(I) - Zero(Z) - Carry(C)
    byte *memory;  // RAM
} CPU_t;

void initializeCPU(CPU_t *cpu);
void freeCPU(CPU_t *cpu);
void resetCPU(CPU_t *cpu);
void resetMemory(CPU_t *cpu, byte v);
void setMemory(CPU_t *cpu, byte newMem[]);
void readMemoryFromFile(CPU_t *cpu, char *fileName);

const word readPC(CPU_t *cpu);
const byte readSP(CPU_t *cpu);
const byte readA(CPU_t *cpu);
const byte readX(CPU_t *cpu);
const byte readY(CPU_t *cpu);
const byte readPS(CPU_t *cpu);

void writePC(CPU_t *cpu, word v);
void writeSP(CPU_t *cpu, byte v);
void writeA(CPU_t *cpu, byte v);
void writeX(CPU_t *cpu, byte v);
void writeY(CPU_t *cpu, byte v);
void writePS(CPU_t *cpu, byte v);

byte readMemory(CPU_t *cpu, word addr);
void writeMemory(CPU_t *cpu, word addr, byte data);
byte readByte(byte *addr);
void writeByte(byte *addr, byte data);
word readWord(CPU_t *cpu, word addr);

void setNegativeFlag(CPU_t *cpu, bool value);
void setOverflowFlag(CPU_t *cpu, bool value);
void setZeroFlag(CPU_t *cpu, bool value);
void setCarryFlag(CPU_t *cpu, bool value);

/* Fetch - Decode - Execute */
bool validateOpcode(byte aaa, byte bbb, byte validAddrModes[]);

byte *decodeG1AddressMode(byte bbb, CPU_t *cpu);
byte *decodeG23AddressMode(byte bbb, byte aaa, CPU_t *cpu);

void decodeG1Instruction(byte aaa, byte *addr, CPU_t *cpu);
void decodeG2Instruction(byte aaa, byte *addr, CPU_t *cpu);
void decodeG3Instruction(byte aaa, byte *addr, CPU_t *cpu);

void execute(CPU_t *cpu);
#endif