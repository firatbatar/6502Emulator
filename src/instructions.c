#include "../include/instructions.h"

/* Instructions */
/** An inclusive OR is performed, bit by bit, on the accumulator contents using the contents of a byte of memory. */
void ORA(byte *addr, CPU_t *cpu) {
    cpu->A |= (*addr);

    setZeroFlag(cpu, cpu->A == 0);
    setNegativeFlag(cpu, cpu->A & 0x80);
}

/** A logical AND is performed, bit by bit, on the accumulator contents using the contents of a byte of memory. */
void AND(byte *addr, CPU_t *cpu) {
    cpu->A &= (*addr);

    setZeroFlag(cpu, cpu->A == 0);
    setNegativeFlag(cpu, cpu->A & 0x80);
}

/** An exclusive OR is performed, bit by bit, on the accumulator contents using the contents of a byte of memory. */
void EOR(byte *addr, CPU_t *cpu) {
    cpu->A ^= (*addr);

    setZeroFlag(cpu, cpu->A == 0);
    setNegativeFlag(cpu, cpu->A & 0x80);
}

/** This instruction adds the contents of a memory location to the accumulator together with the carry bit. If overflow occurs the carry bit is set, this
 * enables multiple byte addition to be performed. */
void ADC(byte *addr, CPU_t *cpu) {
    // TODO: No decimal mode

    word result = cpu->A + (*addr) + (cpu->PS & 0x01);
    byte oldA = cpu->A;  // Keep the old A for overflow
    cpu->A = result & 0xFF;

    setZeroFlag(cpu, cpu->A == 0);
    setNegativeFlag(cpu, cpu->A & 0x80);
    setCarryFlag(cpu, result & 0x0100);                                              // Set the carry flag if ninth bit is 1
    setOverflowFlag(cpu, ((~(oldA ^ (*addr))) & 0x80) && ((oldA ^ result) & 0x80));  // Set the overflow flag
                                                                                     // if same signed operands result in inverse sign
}

/** Stores the contents of the accumulator into memory. */
void STA(byte *addr, CPU_t *cpu) { writeByte(addr, cpu->A); }

/** Loads a byte of memory into the accumulator setting the zero and negative flags as appropriate. */
void LDA(byte *addr, CPU_t *cpu) {
    cpu->A = (*addr);

    setZeroFlag(cpu, cpu->A == 0);
    setNegativeFlag(cpu, cpu->A & 0x80);
}

/** This instruction compares the contents of the accumulator with another memory held value and sets the zero and carry flags as appropriate. */
void CMP(byte *addr, CPU_t *cpu) {
    byte result = cpu->A - (*addr);

    setZeroFlag(cpu, result == 0);
    setNegativeFlag(cpu, result & 0x80);
    setCarryFlag(cpu, cpu->A >= (*addr));  // Set the carry flag if the data <= accumulator
}

/** This instruction subtracts the contents of a memory location to the accumulator together with the not of the carry bit. If overflow occurs the carry bit is
 * clear, this enables multiple byte subtraction to be performed. */
void SBC(byte *addr, CPU_t *cpu) {
    // Subtraction is addition with data's one's complement
    byte complement = ~(*addr);  // One's complement of the data
    ADC(&complement, cpu);       // Add the one's complement to the accumulator
}

/** This operation shifts all the bits of the accumulator or memory contents one bit left. Bit 0 is set to 0 and bit 7 is placed in the carry flag. */
void ASL(byte *addr, CPU_t *cpu) {
    byte newCarry = (*addr) & 0x80;
    byte newVal = (*addr) << 1;

    writeByte(addr, newVal);

    setZeroFlag(cpu, newVal == 0);
    setNegativeFlag(cpu, newVal & 0x80);
    setCarryFlag(cpu, newCarry);
}

/** Move each of the bits in either A or M one place to the left. Bit 0 is filled with the current value of the carry flag whilst the old bit 7 becomes the new
 * carry flag value. */
void ROL(byte *addr, CPU_t *cpu) {
    byte newCarry = (*addr) & 0x80;
    byte newVal = ((*addr) << 1) | (cpu->PS & 0x01);

    writeByte(addr, newVal);
    setZeroFlag(cpu, newVal == 0);
    setNegativeFlag(cpu, newVal & 0x80);
    setCarryFlag(cpu, newCarry);
}

/** Each of the bits in A or M is shift one place to the right. The bit that was in bit 0 is shifted into the carry flag. Bit 7 is set to zero. */
void LSR(byte *addr, CPU_t *cpu) {
    byte newCarry = (*addr) & 0x01;
    byte newVal = (*addr) >> 1;

    writeByte(addr, newVal);
    setZeroFlag(cpu, newVal == 0);
    setNegativeFlag(cpu, newVal & 0x80);
    setCarryFlag(cpu, newCarry);
}

/** Move each of the bits in either A or M one place to the right. Bit 7 is filled with the current value of the carry flag whilst the old bit 0 becomes the new
 * carry flag value. */
void ROR(byte *addr, CPU_t *cpu) {
    byte newCarry = (*addr) & 0x01;
    byte newVal = ((*addr) >> 1) | ((cpu->PS & 0x01) << 7);

    writeByte(addr, newVal);
    setZeroFlag(cpu, newVal == 0);
    setNegativeFlag(cpu, newVal & 0x80);
    setCarryFlag(cpu, newCarry);
}

/** Stores the contents of the X register into memory. */
void STX(byte *addr, CPU_t *cpu) { writeByte(addr, cpu->X); }

/** Loads a byte of memory into the X register setting the zero and negative flags as appropriate. */
void LDX(byte *addr, CPU_t *cpu) {
    cpu->X = (*addr);

    setZeroFlag(cpu, cpu->X == 0);
    setNegativeFlag(cpu, cpu->X & 0x80);
}

/** Subtracts one from the value held at a specified memory location setting the zero and negative flags as appropriate. */
void DEC(byte *addr, CPU_t *cpu) {
    byte newVal = (*addr) - 1;

    writeByte(addr, newVal);
    setZeroFlag(cpu, newVal == 0);
    setNegativeFlag(cpu, newVal & 0x80);
}

/** Adds one to the value held at a specified memory location setting the zero and negative flags as appropriate. */
void INC(byte *addr, CPU_t *cpu) {
    byte newVal = (*addr) + 1;

    writeByte(addr, newVal);
    setZeroFlag(cpu, newVal == 0);
    setNegativeFlag(cpu, newVal & 0x80);
}

/** This instructions is used to test if one or more bits are set in a target memory location. The mask pattern in A is ANDed with the value in memory to set or
 * clear the zero flag, but the result is not kept. Bits 7 and 6 of the value from memory are copied into the N and V flags. */
void BIT(byte *addr, CPU_t *cpu) {
    byte result = cpu->A & (*addr);

    setZeroFlag(cpu, result == 0);         // Set the zero flag if the result is zero
    setNegativeFlag(cpu, (*addr) & 0x80);  // 7th bit of the memory
    setOverflowFlag(cpu, (*addr) & 0x40);  // 6th bit of the memory
}

/** Sets the program counter to the address specified by the operand. */
void JMP(byte *addr, CPU_t *cpu) { cpu->PC = (word)(addr - cpu->memory); }

/** Stores the contents of the Y register into memory. */
void STY(byte *addr, CPU_t *cpu) { writeByte(addr, cpu->Y); }

/** Loads a byte of memory into the Y register setting the zero and negative flags as appropriate. */
void LDY(byte *addr, CPU_t *cpu) {
    cpu->Y = (*addr);

    setZeroFlag(cpu, cpu->Y == 0);
    setNegativeFlag(cpu, cpu->Y & 0x80);
}

/** This instruction compares the contents of the Y register with another memory held value and sets the zero and carry flags as appropriate. */
void CPY(byte *addr, CPU_t *cpu) {
    byte result = cpu->Y - (*addr);

    setZeroFlag(cpu, result == 0);
    setNegativeFlag(cpu, result & 0x80);
    setCarryFlag(cpu, cpu->Y >= (*addr));  // Set the carry flag if the data <= Y
}

/** This instruction compares the contents of the X register with another memory held value and sets the zero and carry flags as appropriate. */
void CPX(byte *addr, CPU_t *cpu) {
    byte result = cpu->X - (*addr);

    setZeroFlag(cpu, result == 0);
    setNegativeFlag(cpu, result & 0x80);
    setCarryFlag(cpu, cpu->X >= (*addr));  // Set the carry flag if the data <= X
}