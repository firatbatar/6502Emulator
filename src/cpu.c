#include "../include/cpu.h"
#include "../include/instructions.h"

/* Initilaztions */

// Define and initilize the registers
word PC = 0;
byte SP = 0;
byte A = 0;
byte X = 0;
byte Y = 0;
byte PS = 0;

// Initilize the memory - From 0x0000 to 0xFFFF, 0x10000 bytes
byte memory[0x10000];

/* There are 8 possible addressing modes
but not all instructions are able to use all */
// Valid addressing modes for G1
byte validAddrModesG1[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0xFF, 0xFF, 0xFF};

void resetCPU() {
    // Set the program counter to the reset vector
    // 6502 CPU starts at 0xFFFC and 0xFFFD
    // and it's a little endian system
    PC = (memory[0xFFFD] << 8) | memory[0xFFFC];

    // Set the stack pointer to 0x01FF (0xFF)
    SP = 0xFF;

    // Set the registers to 0
    A = 0;
    X = 0;
    Y = 0;
}

void resetMemory() {
    // Set all the memory to 0
    for (int i = 0; i < 0x10000; i++) {
        memory[i] = 0;
    }
}

void setMemory(byte newMem[]) {
    for (int i = 0; i < 0x10000; i++) {
        memory[i] = newMem[i];
    }
}

void initlizeCPU(byte mem[]) {
    resetMemory();
    printf("Cleared existing memory.\n");
    setMemory(mem);
    printf("Set given memory.\n");
    resetCPU();
    printf("Reset registers. CPU is ready to run.\n");
}

/* General Purpose Functionalities */

/** Read one byte from the memory */
byte readMemory(word addr) { return memory[addr]; }

/** Read one byte from the given address */
byte readByte(byte *addr) { return *addr; }

/** Write one byte to the given address */
void writeByte(byte *addr, byte data) { *addr = data; }

/** Read two consecutive bytes (16-bit full address) from the memory */
word readWord(word addr) { return (memory[addr + 1] << 8) | memory[addr]; }

/** Set/Reset negative flag */
void setNegativeFlag(bool value) {
    if (value)
        PS |= 0x80;
    else
        PS &= 0x7F;
}

/** Set/Reset overflow flag */
void setOverflowFlag(bool value) {
    if (value)
        PS |= 0x40;
    else
        PS &= 0xBF;
}

/** Set/Reset zero flag */
void setZeroFlag(bool value) {
    if (value)
        PS |= 0x02;
    else
        PS &= 0xFD;
}

/** Set/Reset carry flag */
void setCarryFlag(bool value) {
    if (value)
        PS |= 0x01;
    else
        PS &= 0xFE;
}

/* Decoders */

/** Validators */
bool validateOpcode(byte aaa, byte bbb, byte validAddrModes[]) { return validAddrModes[aaa] & (1 << bbb); }

/** Decode Group 1 Address Mode */
byte *decodeG1Address(byte bbb) {
    word addr;
    switch (bbb) {
        case 0:  // (Indirect, X)
            addr = readMemory(PC) + X;
            addr &= 0xFF;  // The address calculation wraps around
            addr = readWord(addr);
            PC++;
            break;
        case 1:  // Zero Page
            addr = readMemory(PC);
            PC++;
            break;
        case 2:  // Immediate
            addr = PC;
            PC++;
            break;
        case 3:  // Absolute
            addr = readWord(PC);
            PC += 2;
            break;
        case 4:  // (Indirect), Y
            addr = readMemory(PC);
            addr = readWord(addr);
            addr += Y;
            PC++;
            break;
        case 5:  // Zero Page, X
            addr = (readMemory(PC) + X);
            addr &= 0xFF;  // The address calculation wraps around
            PC++;
            break;
        case 6:  // Absolute, Y
            addr = readWord(PC) + Y;
            PC += 2;
            break;
        case 7:  // Absolute, X
            addr = readWord(PC) + X;
            PC += 2;
            break;
        default:
            fprintf(stderr, "Invalid bbb value: %d\n", bbb);
            exit(1);
    }

    return memory + addr;
}

/** Decode Group 2 Address Mode */
byte *decodeG2Address(byte bbb) {
    word addr;
    switch (bbb) {
        case 0:  // Immediate
            addr = PC;
            PC++;
            break;
        case 1:  // Zero Page
            addr = readMemory(PC);
            PC++;
            break;
        case 2:  // Accumulator
            return &A;
            break;
        case 3:  // Absolute
            addr = readWord(PC);
            PC += 2;
            break;
        case 4:  // Zero Page, X
            addr = (readMemory(PC) + X);
            addr &= 0xFF;  // The address calculation wraps around
            PC++;
            break;
        case 5:  // Absolute, X
            addr = readWord(PC) + X;
            PC += 2;
            break;
        default:
            fprintf(stderr, "Invalid bbb value: %d\n", bbb);
            exit(1);
    }

    return memory + addr;
}

/* Executers */

/** Execute Group 1 Instructions */
void executeG1(byte aaa, byte *addr) {
    // TODO: Some of the instruction doesn't have all addressing types
    switch (aaa) {
        case 0:  // ORA
            ORA(addr);
            break;
        case 1:  // AND
            AND(addr);
            break;
        case 2:  // EOR
            EOR(addr);
            break;
        case 3:  // ADC
            ADC(addr);
            break;
        case 4:  // STA
            STA(addr);
            break;
        case 5:  // LDA
            LDA(addr);
            break;
        case 6:  // CMP
            CMP(addr);
            break;
        case 7:  // SBC
            SBC(addr);
            break;
        default:
            fprintf(stderr, "Invalid aaa value: %d\n", aaa);
            exit(1);
    }
}

/** Execute Group 2 Instructions */
void executeG2(byte aaa, byte *addr) {
    // TODO: Some of the instruction doesn't have all addressing types
    switch (aaa) {
        case 0:  // ASL
            // ASL(addr);
            break;
        case 1:  // ROL
            // ROL(addr);
            break;
        case 2:  // LSR
            // LSR(addr);
            break;
        case 3:  // ROR
            // ROR(addr);
            break;
        case 4:  // STX
            // STX(addr);
            break;
        case 5:  // LDX
            // LDX(addr);
            break;
        case 6:  // DEC
            // DEC(addr);
            break;
        case 7:  // INC
            // INC(addr);
            break;
        default:
            fprintf(stderr, "Invalid aaa value: %d\n", aaa);
            exit(1);
    }
}

/** Fetch, Decode, and Execute single instruction */
void execute() {
    // Fetch
    byte opcode = memory[PC];
    PC++;  // Increment the program counter

    // Decode
    byte lowNibble = opcode & 0x0F;
    byte highNibble = (opcode) >> 4;

    if (lowNibble == 8) {
        //
    }
    else if (lowNibble == 0xA && highNibble >= 8) {
        //
    }
    else {
        // Three main groups of instructions
        // Bit patterns of the form aaabbbcc.
        // The aaa and cc bits determine the opcode,
        // and the bbb bits determine the addressing mode.

        byte aaa = opcode >> 5;
        byte bbb = (opcode & 0x1C) >> 2;
        byte cc = opcode & 0x03;

        byte *addr;
        switch (cc) {
            case 1:  // Group 1 instructions
                // Validate addressing mode exists for the instruction (NOP)
                if (!validateOpcode(aaa, bbb, validAddrModesG1)) {
                    fprintf(stderr, "Invalid opcode!\n");
                    exit(1);
                }

                addr = decodeG1Address(bbb);  // Decode the addressing mode

                executeG1(aaa, addr);  // Execute the instruction
                break;
            case 2:  // Group 2 instructions
                // Decode the addressing mode
                // addr = decodeG2Address(bbb);
                // Execute the instruction
                // executeG2(aaa, addr);
                break;
            default:
                fprintf(stderr, "Invalid cc value: %d\n", cc);
                exit(1);
        }
    }
}

/* Instructions */
/** An inclusive OR is performed, bit by bit, on the accumulator contents using the contents of a byte of memory. */
void ORA(byte *addr) {
    A |= (*addr);

    setZeroFlag(A == 0);
    setNegativeFlag(A & 0x80);
}

/** A logical AND is performed, bit by bit, on the accumulator contents using the contents of a byte of memory. */
void AND(byte *addr) {
    A &= (*addr);

    setZeroFlag(A == 0);
    setNegativeFlag(A & 0x80);
}

/** An exclusive OR is performed, bit by bit, on the accumulator contents using the contents of a byte of memory. */
void EOR(byte *addr) {
    A ^= (*addr);

    setZeroFlag(A == 0);
    setNegativeFlag(A & 0x80);
}

/** This instruction adds the contents of a memory location to the accumulator together with the carry bit. If overflow occurs the carry bit is set, this
 * enables multiple byte addition to be performed. */
void ADC(byte *addr) {
    // TODO: No decimal mode

    word result = A + (*addr) + C;
    byte oldA = A;  // Keep the old A for overflow
    A = result & 0xFF;

    setZeroFlag(A == 0);
    setNegativeFlag(A & 0x80);
    setCarryFlag(result & 0x0100);                                              // Set the carry flag if ninth bit is 1
    setOverflowFlag(((~(oldA ^ (*addr))) & 0x80) && ((oldA ^ result) & 0x80));  // Set the overflow flag
                                                                                // if same signed operands result in inverse sign
}

/** Stores the contents of the accumulator into memory. */
void STA(byte *addr) { writeByte(addr, A); }

/** Loads a byte of memory into the accumulator setting the zero and negative flags as appropriate. */
void LDA(byte *addr) {
    A = (*addr);

    setZeroFlag(A == 0);
    setNegativeFlag(A & 0x80);
}

/** This instruction compares the contents of the accumulator with another memory held value and sets the zero and carry flags as appropriate. */
void CMP(byte *addr) {
    byte result = A - (*addr);

    setZeroFlag(A == 0);
    setNegativeFlag(A & 0x80);
    setCarryFlag(result >= 0);  // Set the carry flag if the data >= accumulator
}

/** This instruction subtracts the contents of a memory location to the accumulator together with the not of the carry bit. If overflow occurs the carry bit is
 * clear, this enables multiple byte subtraction to be performed. */
void SBC(byte *addr) {
    byte result = A - (*addr) - ~C;
    byte oldA = A;
    A = result;

    setZeroFlag(A == 0);
    setNegativeFlag(A & 0x80);
    setCarryFlag(result >= 0);
    setOverflowFlag(((oldA ^ (*addr)) & 0x80) && (((*addr) ^ result) & 0x80));  // Set the overflow flag
                                                                                // if inverse signed operands result
                                                                                // in same sign as the second operand
}