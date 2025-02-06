#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "cpu.h"

/** A bitwise OR on the accumulator using the contents of a byte of memory.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read A from.
*/
void ORA(byte *addr, CPU_t *cpu);

/** A bitwise AND on the accumulator using the contents of a byte of memory.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read A from.
*/
void AND(byte *addr, CPU_t *cpu);

/** A bitwise exclusive OR is performed on the accumulator using the contents of a byte of memory.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read A from. 
*/
void EOR(byte *addr, CPU_t *cpu);

/** Adds the contents of a memory location to the accumulator together with the carry bit. 
 * If overflow occurs the carry bit is set, this enables multiple byte addition to be performed.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read A and PS from.
*/
void ADC(byte *addr, CPU_t *cpu);

/** Stores the contents of the accumulator into memory.
 * @param addr Address to write to.
 * @param cpu CPU_t struct to read A from.
*/
void STA(byte *addr, CPU_t *cpu);

/** Loads a byte of memory into the accumulator setting the zero and negative flags as appropriate.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read/write A PS from/to.
*/
void LDA(byte *addr, CPU_t *cpu);

/** Compares the contents of the accumulator with another memory held value and sets the zero, negative, and carry flags as appropriate.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read/write A and PS from/to.
*/
void CMP(byte *addr, CPU_t *cpu);

/** Subtracts the contents of a memory location to the accumulator together with the compliment of the carry bit.
 * If overflow occurs the carry bit is reset, this enables multiple byte subtraction to be performed.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read/write A and PS from/to.
*/
void SBC(byte *addr, CPU_t *cpu);

/** Shifts the bits of the accumulator or memory one bit left.
 * Bit 0 is set to zero and bit 7 is placed in the carry flag.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read/write A and PS from/to.
*/
void ASL(byte *addr, CPU_t *cpu);

/** Rotates the bits of the accumulator or memory one place to the left.
 * Bit 0 is filled with the current value of the carry flag whilst the old bit 7 becomes the new carry flag value.
 * Set zero flag if result is zero, otherwise reset. Negative flag is equal to bit 7 of the result.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read/write A and PS from/to.
*/
void ROL(byte *addr, CPU_t *cpu);

/** Shifts the bits of the accumulator or memory one bit right. 
 * The bit that was in bit 0 is shifted into the carry flag. Bit 7 is set to zero.
 * Set zero flag if result is zero, otherwise reset. Negative flag is always reset.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read/write A and PS from/to. 
*/
void LSR(byte *addr, CPU_t *cpu);

/** Rotates the bits of the accumulator or memory one place to the right.
 * Bit 7 is filled with the current value of the carry flag whilst the old bit 0 becomes the new carry flag value.
 * Set zero flag if result is zero, otherwise reset. Negative flag is equal to bit 7 of the result.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read/write A and PS from/to.
*/
void ROR(byte *addr, CPU_t *cpu);

/** Stores the contents of the X register into memory.
 * @param addr Address to write to.
 * @param cpu CPU_t struct to read X from.
*/
void STX(byte *addr, CPU_t *cpu);

/** Loads a byte of memory into the X register setting the zero and negative flags as appropriate.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read/write X and PS from/to.
*/
void LDX(byte *addr, CPU_t *cpu);

/** Subtracts one from the value held at a specified memory location setting the zero and negative flags as appropriate.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read/write memory from/to.
*/
void DEC(byte *addr, CPU_t *cpu);

/** Adds one to the value held at a specified memory location setting the zero and negative flags as appropriate.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read/write memory from/to.
*/
void INC(byte *addr, CPU_t *cpu);

/** Test if one or more bits are set in a target memory location.
 * The mask pattern in A is ANDed with the value in memory to set or reset the zero flag, but the result is not kept.
 * Bits 7 and 6 of the value from memory are copied into the negative and overflow flags.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read A and PS from.
*/
void BIT(byte *addr, CPU_t *cpu);

/** Sets the program counter to the address specified by the operand.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to write PC to.
*/
void JMP(byte *addr, CPU_t *cpu);

/** Stores the contents of the Y register into memory.
 * @param addr Address to write to.
 * @param cpu CPU_t struct to read Y from.
*/
void STY(byte *addr, CPU_t *cpu);

/** Loads a byte of memory into the Y register setting the zero and negative flags as appropriate.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read/write Y and PS from/to.
*/
void LDY(byte *addr, CPU_t *cpu);

/** Compares the contents of the Y register with another memory held value and sets the zero, negative, and carry flags as appropriate.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read/write Y and PS from/to.
*/
void CPY(byte *addr, CPU_t *cpu);

/** Compares the contents of the X register with another memory held value and sets the zero, negative, and carry flags as appropriate.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read/write X and PS from/to.
*/
void CPX(byte *addr, CPU_t *cpu);

#endif  // INSTRUCTIONS_H