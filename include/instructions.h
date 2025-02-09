#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "cpu.h"

/** Glossary
 * A - Accumulator
 * X - X Register
 * Y - Y Register
 * M - Memory
 * PS - Processor Status
 * N - Negative
 * V - Overflow
 * B - Break Command
 * D - Decimal Mode
 * I - Interrupt Disable
 * Z - Zero
 * C - Carry
 * PC - Program Counter
 * SP - Stack Pointer
 */

/** A bitwise OR on A using the contents of M.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read A from.
 */
void ORA(byte *addr, CPU_t *cpu);

/** A bitwise AND on A using the contents of M.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read A from.
 */
void AND(byte *addr, CPU_t *cpu);

/** A bitwise exclusive OR is performed on A using the contents of M.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read A from.
 */
void EOR(byte *addr, CPU_t *cpu);

/** Adds the contents of M to A together with C.
 * If overflow occurs the C is set, this enables multiple byte addition to be performed.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read A and PS from.
 */
void ADC(byte *addr, CPU_t *cpu);

/** Stores the contents of A into M.
 * @param addr Address to write to.
 * @param cpu CPU_t struct to read A from.
 */
void STA(byte *addr, CPU_t *cpu);

/** Loads a byte of M into A setting Z and N as appropriate.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read/write A PS from/to.
 */
void LDA(byte *addr, CPU_t *cpu);

/** Compares the contents of A with another M held value.
 * Sets the Z, N, and C as appropriate.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read/write A and PS from/to.
 */
void CMP(byte *addr, CPU_t *cpu);

/** Subtracts the contents of M from A together with the compliment of C.
 * If overflow occurs C is reset, this enables multiple byte subtraction to be performed.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read/write A and PS from/to.
 */
void SBC(byte *addr, CPU_t *cpu);

/** Shifts the bits of A or M one bit left.
 * Bit 0 is set to zero and bit 7 is placed into C.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read/write A and PS from/to.
 */
void ASL(byte *addr, CPU_t *cpu);

/** Rotates the bits of A or M one place to the left.
 * Bit 0 is filled with the current value of the C whilst the old bit 7 becomes the new C.
 * Set Z if result is zero, otherwise reset. N is equal to bit 7 of the result.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read/write A and PS from/to.
 */
void ROL(byte *addr, CPU_t *cpu);

/** Shifts the bits of the A or M one bit right.
 * The bit that was in bit 0 is shifted into C. Bit 7 is set to zero.
 * Set Z if result is zero, otherwise reset. N is always reset.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read/write A and PS from/to.
 */
void LSR(byte *addr, CPU_t *cpu);

/** Rotates the bits of A or M one place to the right.
 * Bit 7 is filled with the current value of the C whilst the old bit 0 becomes the new C.
 * Set Z if result is zero, otherwise reset. N is equal to bit 7 of the result.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read/write A and PS from/to.
 */
void ROR(byte *addr, CPU_t *cpu);

/** Stores the contents of the X register into M.
 * @param addr Address to write to.
 * @param cpu CPU_t struct to read X from.
 */
void STX(byte *addr, CPU_t *cpu);

/** Loads a byte of memory M into the X register setting the Z and N as appropriate.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read/write X and PS from/to.
 */
void LDX(byte *addr, CPU_t *cpu);

/** Subtracts one from the value held at M, setting the Z and N as appropriate.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read/write memory from/to.
 */
void DEC(byte *addr, CPU_t *cpu);

/** Adds one to the value held at M, setting the Z and N as appropriate.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read/write memory from/to.
 */
void INC(byte *addr, CPU_t *cpu);

/** Test if one or more bits are set in a target M.
 * The mask pattern in A is ANDed with M to set or reset the Z, but the result is not kept.
 * Bits 7 and 6 of the value from memory are copied into N and V flags.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read A and PS from.
 */
void BIT(byte *addr, CPU_t *cpu);

/** Sets PC to the address specified by the operand.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to write PC to.
 */
void JMP(byte *addr, CPU_t *cpu);

/** Stores the contents of the Y register into M.
 * @param addr Address to write to.
 * @param cpu CPU_t struct to read Y from.
 */
void STY(byte *addr, CPU_t *cpu);

/** Loads a byte of M into the Y register setting Z and N as appropriate.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read/write Y and PS from/to.
 */
void LDY(byte *addr, CPU_t *cpu);

/** Compares the contents of the Y register with another M held value.
 * Sets Z, N, and C as appropriate.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read/write Y and PS from/to.
 */
void CPY(byte *addr, CPU_t *cpu);

/** Compares the contents of the X register with another M held value.
 * Sets the Z, N, and C as appropriate.
 * @param addr Address to read from.
 * @param cpu CPU_t struct to read/write X and PS from/to.
 */
void CPX(byte *addr, CPU_t *cpu);

/** Bracnh on Result Plus
 * If N is clear, the program counter is advanced by the relative displacement.
 * @param cpu CPU_t struct to read/write PS and PC from/to.
 */
void BPL(CPU_t *cpu);

/** Branch on Result Minus
 * If N is set, the program counter is advanced by the relative displacement.
 * @param cpu CPU_t struct to read/write PS and PC from/to.
 */
void BMI(CPU_t *cpu);

/** Branch on Overflow Clear
 * If V is clear, the program counter is advanced by the relative displacement.
 * @param cpu CPU_t struct to read/write PS and PC from/to.
 */
void BVC(CPU_t *cpu);

/** Branch on Overflow Set
 * If V is set, the program counter is advanced by the relative displacement.
 * @param cpu CPU_t struct to read/write PS and PC from/to.
 */
void BVS(CPU_t *cpu);

/** Branch on Carry Clear
 * If C is clear, the program counter is advanced by the relative displacement.
 * @param cpu CPU_t struct to read/write PS and PC from/to.
 */
void BCC(CPU_t *cpu);

/** Branch on Carry Set
 * If C is set, the program counter is advanced by the relative displacement.
 * @param cpu CPU_t struct to read/write PS and PC from/to.
 */
void BCS(CPU_t *cpu);

/** Branch on Result Not Zero
 * If Z is set, the program counter is advanced by the relative displacement.
 * @param cpu CPU_t struct to read/write PS and PC from/to.
 */
void BNE(CPU_t *cpu);

/** Branch on Result Zero
 * If Z is clear, the program counter is advanced by the relative displacement.
 * @param cpu CPU_t struct to read/write PS and PC from/to.
 */
void BEQ(CPU_t *cpu);

#endif  // INSTRUCTIONS_H