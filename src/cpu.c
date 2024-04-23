#include "../include/cpu.h"
#include "../include/opcodes.h"
#include "../include/instructions.h"

/* Initilaztions */

// Define and initilize the registers
word PC = 0;
byte SP = 0;
byte A = 0;
byte X = 0;
byte Y = 0;
byte PS = 0;

// PS Flags
#define C (PS & 0x01)  // Carry
#define Z (PS & 0x02)  // Zero
#define I (PS & 0x04)  // Interrupt Disable
#define D (PS & 0x08)  // Decimal Mode
#define B (PS & 0x10)  // Break Command
#define V (PS & 0x40)  // Overflow
#define N (PS & 0x80)  // Negative

// Initilize the memory - From 0x0000 to 0xFFFF, 0x10000 bytes
byte memory[0x10000];

/* There are 8 possible addressing modes
but not all instructions are able to use all */
// Valid addressing modes for G1
byte validAddrModesG1[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0xFF, 0xFF, 0xFF};
// Valid addressing modes for G2
byte validAddrModesG2[] = {0xAE, 0xAE, 0xAE, 0xAE, 0x2A, 0xAB, 0xAA, 0xAA};
// Valid addressing modes for G3
byte validAddrModesG3[] = {0x00, 0x0A, 0x08, 0x08, 0x2A, 0xAB, 0x0B, 0x0B};

/* Getters */

const word readPC() { return PC; }
const byte readSP() { return SP; }
const byte readA() { return A; }
const byte readX() { return X; }
const byte readY() { return Y; }
const byte readPS() { return PS; }

/* Setters */

void writePC(word v) { PC = v; }
void writeSP(byte v) { SP = v; }
void writeA(byte v) { A = v; }
void writeX(byte v) { X = v; }
void writeY(byte v) { Y = v; }
void writePS(byte v) { PS = v; }

/* General Purpose Functionalities */

/** Set PC to reset vector
 * Set SP to 0xFF (0x1FF)
 * Reset A, X, Y registers to 0
 */
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

/** Clear all memory to 0 */
void resetMemory(byte v) {
    // Set all the memory to 0
    for (int i = 0; i < 0x10000; i++) {
        memory[i] = v;
    }
}

/** Set memory to the given */
void setMemory(byte newMem[]) {
    for (int i = 0; i < 0x10000; i++) {
        memory[i] = newMem[i];
    }
}

void readMemoryFromFile(char *fileName) {
    FILE *file = fopen(fileName, "r");

    if (file == NULL) {
        fprintf(stderr, "Can't open file!");
        exit(1);
    }

    char m;
    word idx = 0;
    while (!feof(file) && idx <= 0xFFFF) {
        m = fgetc(file);
        memory[idx] = (int8_t)m;
        idx++;
    }

    printf("Loaded memory from file \"%s\"\n", fileName);

    fclose(file);
}

/** Clear the memory
 * Set/Load memory
 * Reset the CPU
 */
void initlizeCPU(byte mem[], char *fileName) {
    resetMemory(0);
    // printf("Cleared existing memory.\n");

    if (fileName == NULL) {
        setMemory(mem);
        // printf("Set given memory.\n");
    }
    else {
        readMemoryFromFile(fileName);
        // printf("Load given memory.\n");
    }

    resetCPU();
    // printf("Reset registers. CPU is ready to run.\n");
}

/** Read one byte from the memory */
byte readMemory(word addr) { return memory[addr]; }

/** Write one byte to given memory index */
void writeMemory(word addr, byte data) { memory[addr] = data; }

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
byte *decodeG1AddressMode(byte bbb) {
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

/** Decode Group 2 and Group 3 Address Mode */
byte *decodeG23AddressMode(byte bbb, byte aaa) {
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
        case 5:  // Zero Page, X / Zero Page, Y
            addr = readMemory(PC);
            // On STX and LDX ZP,X becomes ZP,Y (only in G2)
            addr += (aaa == 4 || aaa == 5) ? Y : X;
            addr &= 0xFF;  // The address calculation wraps around
            PC++;
            break;
        case 7:  // Absolute, X / Absolute Y
            addr = readWord(PC);
            // On LDX ABS,X becomes ABS,Y
            // Only in G2
            addr += (aaa == 5) ? Y : X;
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
void decodeG1Instruction(byte aaa, byte *addr) {
    switch (aaa) {
        case 0:  // ORA
            ORA(addr, &A);
            break;
        case 1:  // AND
            AND(addr, &A);
            break;
        case 2:  // EOR
            EOR(addr, &A);
            break;
        case 3:  // ADC
            ADC(addr, &A, &PS);
            break;
        case 4:  // STA
            STA(addr, &A);
            break;
        case 5:  // LDA
            LDA(addr, &A);
            break;
        case 6:  // CMP
            CMP(addr, &A);
            break;
        case 7:  // SBC
            SBC(addr, &A, &PS);
            break;
        default:
            fprintf(stderr, "Invalid aaa value: %d\n", aaa);
            exit(1);
    }
}

/** Execute Group 2 Instructions */
void decodeG2Instruction(byte aaa, byte *addr) {
    switch (aaa) {
        case 0:  // ASL
            ASL(addr);
            break;
        case 1:  // ROL
            ROL(addr, &PS);
            break;
        case 2:  // LSR
            LSR(addr);
            break;
        case 3:  // ROR
            ROR(addr, &PS);
            break;
        case 4:  // STX
            STX(addr, &X);
            break;
        case 5:  // LDX
            LDX(addr, &X);
            break;
        case 6:  // DEC
            DEC(addr);
            break;
        case 7:  // INC
            INC(addr);
            break;
        default:
            fprintf(stderr, "Invalid aaa value: %d\n", aaa);
            exit(1);
    }
}

/** Execute Group 3 Instructions */
void decodeG3Instruction(byte aaa, byte *addr) {
    switch (aaa) {
        case 1:  // BIT
            BIT(addr, &A);
            break;
        case 2:  // JMP
            JMP(addr, &PC, memory);
            break;
        case 3:  // JMP()
            addr = memory + ((*(addr + 1) << 8) | (*addr));
            JMP(addr, &PC, memory);
            break;
        case 4:  // STY
            STY(addr, &Y);
            break;
        case 5:  // LDY
            LDY(addr, &Y);
            break;
        case 6:  // CPY
            CPY(addr, &Y);
            break;
        case 7:  // CPX
            CPX(addr, &X);
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

                addr = decodeG1AddressMode(bbb);  // Decode the addressing mode
                decodeG1Instruction(aaa, addr);   // Execute the instruction
                break;
            case 2:  // Group 2 instructions
                // Validate addressing mode exists for the instruction (NOP)
                if (!validateOpcode(aaa, bbb, validAddrModesG2)) {
                    fprintf(stderr, "Invalid opcode!\n");
                    exit(1);
                }

                addr = decodeG23AddressMode(bbb, aaa);  // Decode the addressing mode
                decodeG2Instruction(aaa, addr);         // Execute the instruction
                break;
            case 0:  // Group 3, branch, and inturrupt/subroutine instructions
                if (bbb == 4) {
                    // Branch
                }
                else if (bbb == 0 && (aaa == 0 || aaa == 1 || aaa == 2 || aaa == 3)) {
                    // Inturrupt/subroutine
                    // 0x00, 0x20, 0x40, 0x60
                }
                else {
                    // Validate addressing mode for G3
                    if (!validateOpcode(aaa, bbb, validAddrModesG3)) {
                        fprintf(stderr, "Invalid opcode!\n");
                        exit(1);
                    }

                    addr = decodeG23AddressMode(bbb, -1);  // Decode the addressing mode
                                                           // Pass -1 for second parameter to avoid X-Y change needed for G2
                    decodeG3Instruction(aaa, addr);        // Execute the instruction
                }
                break;
            default:
                fprintf(stderr, "Invalid cc value: %d\n", cc);
                exit(1);
        }
    }
}