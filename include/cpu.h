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
    byte PS;       // Processor Status:
                   // Negative(N) - Overflow(V) - Unused -
                   // Break Command(B) - Decimal Mode(D) - Interrupt Disable(I) - Zero(Z) - Carry(C)
    byte *memory;  // RAM
} CPU_t;

/** Initialize CPU.
 * Initialize all registers to 0, except SP to 0xFF and PC to reset vector.
 * Initialize memory to 0.
 * @param cpu CPU_t struct to initialize.
 */
void initializeCPU(CPU_t *cpu);

/** Free CPU.
 * Free the memory allocated for the CPU.
 * @param cpu CPU_t struct to free.
 */
void freeCPU(CPU_t *cpu);

/** Reset CPU internal state.
 * Set PC to reset vector.
 * Set SP to 0xFF (0x1FF).
 * Reset A, X, Y registers to 0.
 * @param cpu CPU_t struct to reset.
 */
void resetCPU(CPU_t *cpu);

/** Clear all memory to 0.
 * @param cpu CPU_t struct to reset memory.
 */
void resetMemory(CPU_t *cpu, byte v);

/** Set memory to the given CPU.
 * @param cpu CPU_t struct to set memory.
 * @param newMem[] New memory to set.
 */
void setMemory(CPU_t *cpu, byte newMem[]);

/** Read memory from file.
 * @param cpu CPU_t struct to read memory.
 * @param fileName File name to read memory from.
 */
void readMemoryFromFile(CPU_t *cpu, char *fileName);

/* Getters */

/** Read PC.
 * @param cpu CPU_t struct to read PC from.
 */
const word readPC(CPU_t *cpu);

/** Read SP.
 * @param cpu CPU_t struct to read SP from.
 */
const byte readSP(CPU_t *cpu);

/** Read A.
 * @param cpu CPU_t struct to read A from.
 */
const byte readA(CPU_t *cpu);

/** Read X.
 * @param cpu CPU_t struct to read X from.
 */
const byte readX(CPU_t *cpu);

/** Read Y.
 * @param cpu CPU_t struct to read Y from.
 */
const byte readY(CPU_t *cpu);

/** Read PS.
 * @param cpu CPU_t struct to read PS from.
 */
const byte readPS(CPU_t *cpu);

/* Settters */

/** Write PC
 * @param cpu CPU_t struct to write PC to
 * @param v Value to write to PC
 */
void writePC(CPU_t *cpu, word v);

/** Write SP
 * @param cpu CPU_t struct to write SP to
 * @param v Value to write to SP
 */
void writeSP(CPU_t *cpu, byte v);

/** Write A. Does not affect flags
 * @param cpu CPU_t struct to write A to
 * @param v Value to write to A
 */
void writeA(CPU_t *cpu, byte v);

/** Write X. Does not affect flags.
 * @param cpu CPU_t struct to write X to
 * @param v Value to write to X
 */
void writeX(CPU_t *cpu, byte v);

/** Write Y. Does not affect flags.
 * @param cpu CPU_t struct to write Y to
 * @param v Value to write to Y
 */
void writeY(CPU_t *cpu, byte v);

/** Write PS.
 * @param cpu CPU_t struct to write PS to.
 * @param v Value to write to PS.
 */
void writePS(CPU_t *cpu, byte v);

/** Read one byte from the memory.
 * @param cpu CPU_t struct to read memory from.
 * @param addr Address to read from.
 */
byte readMemory(CPU_t *cpu, word addr);

/** Write one byte to given memory index.
 * @param cpu CPU_t struct to write memory to.
 * @param addr Address to write to.
 */
void writeMemory(CPU_t *cpu, word addr, byte data);

/** Read one byte from the given address.
 * @param addr Address to read from.
 */
byte readByte(byte *addr);

/** Write one byte to the given address.
 * @param addr Address to write to.
 * @param data Data to write.
 */
void writeByte(byte *addr, byte data);

/** Read two consecutive bytes (16-bit full address) from the memory.
 * @param cpu CPU_t struct to read memory from.
 * @param addr Address to read from.
 */
word readWord(CPU_t *cpu, word addr);

/** Set/Reset negative flag.
 * @param cpu CPU_t struct to set negative flag.
 * @param value Value to set.
 */
void setNegativeFlag(CPU_t *cpu, bool value);

/** Set/Reset overflow flag.
 * @param cpu CPU_t struct to set overflow flag.
 * @param value Value to set.
 */
void setOverflowFlag(CPU_t *cpu, bool value);

/** Set/Reset zero flag.
 * @param cpu CPU_t struct to set zero flag.
 * @param value Value to set.
 */
void setZeroFlag(CPU_t *cpu, bool value);

/** Set/Reset carry flag.
 * @param cpu CPU_t struct to set carry flag.
 * @param value Value to set.
 */
void setCarryFlag(CPU_t *cpu, bool value);

/* Fetch - Decode - Execute */

/** Validate opcode.
 * @param aaa
 * @param bbb
 * @param validAddrModes
 */
bool validateOpcode(byte aaa, byte bbb, byte validAddrModes[]);

/** Decode Group 1 Address Mode.
 * @param bbb
 * @param cpu
 */
byte *decodeG1AddressMode(byte bbb, CPU_t *cpu);

/** Decode Group 2 and Group 3 Address Mode.
 * @param bbb
 * @param aaa
 */
byte *decodeG23AddressMode(byte bbb, byte aaa, CPU_t *cpu);

/** Execute Group 1 Instruction.
 * @param aaa
 * @param addr
 * @param cpu
 */
void decodeG1Instruction(byte aaa, byte *addr, CPU_t *cpu);

/** Execute Group 2 Instruction.
 * @param aaa
 * @param addr
 * @param cpu
 */
void decodeG2Instruction(byte aaa, byte *addr, CPU_t *cpu);

/** Execute Group 3 Instruction.
 * @param aaa
 * @param addr
 * @param cpu
 */
void decodeG3Instruction(byte aaa, byte *addr, CPU_t *cpu);

/** Fetch, Decode, and Execute single instruction.
 * @param cpu CPU_t struct to execute.
 */
void execute(CPU_t *cpu);

#endif  // CPU_H