#include "../include/cpu.h"
#include "../include/instructions.h"
#include "../include/opcodes.h"

/* CPU Structure */

/** Initialize CPU
 * Initialize all registers to 0, except SP to 0xFF and PC to reset vector
 * Initialize memory to 0
 */
void initializeCPU(CPU_t *cpu) {
    cpu->PC = 0;
    cpu->SP = 0;
    cpu->A = 0;
    cpu->X = 0;
    cpu->Y = 0;
    cpu->PS = 0;
    cpu->memory = (byte *)malloc(0x10000 * sizeof(byte));

    resetCPU(cpu);
    resetMemory(cpu, 0);
}

/** Free CPU */
void freeCPU(CPU_t *cpu) { free(cpu->memory); }

/** Set PC to reset vector
 * Set SP to 0xFF (0x1FF)
 * Reset A, X, Y registers to 0
 */
void resetCPU(CPU_t *cpu) {
    // Set the program counter to the reset vector
    // 6502 CPU starts at 0xFFFC and 0xFFFD
    // and it's a little endian system
    cpu->PC = (cpu->memory[0xFFFD] << 8) | cpu->memory[0xFFFC];

    // Set the stack pointer to 0x01FF (0xFF)
    cpu->SP = 0xFF;

    // Set the registers to 0
    cpu->A = 0;
    cpu->X = 0;
    cpu->Y = 0;
}

/** Clear all memory to 0 */
void resetMemory(CPU_t *cpu, byte v) {
    // Set all the memory to 0
    for (int i = 0; i < 0x10000; i++) cpu->memory[i] = v;
}

/** Set memory to the given */
void setMemory(CPU_t *cpu, byte newMem[]) {
    for (int i = 0; i < 0x10000; i++) cpu->memory[i] = newMem[i];
}

void readMemoryFromFile(CPU_t *cpu, char *fileName) {
    FILE *file = fopen(fileName, "r");

    if (file == NULL) {
        fprintf(stderr, "Can't open file!");
        exit(1);
    }

    char m;
    word idx = 0;
    while (!feof(file) && idx <= 0xFFFF) {
        m = fgetc(file);
        cpu->memory[idx] = (int8_t)m;
        idx++;
    }
    fclose(file);

    printf("Loaded memory from file \"%s\"\n", fileName);
}

const word readPC(CPU_t *cpu) { return cpu->PC; }
const byte readSP(CPU_t *cpu) { return cpu->SP; }
const byte readA(CPU_t *cpu) { return cpu->A; }
const byte readX(CPU_t *cpu) { return cpu->X; }
const byte readY(CPU_t *cpu) { return cpu->Y; }
const byte readPS(CPU_t *cpu) { return cpu->PS; }

/* Setters */

void writePC(CPU_t *cpu, word v) { cpu->PC = v; }
void writeSP(CPU_t *cpu, byte v) { cpu->SP = v; }
void writeA(CPU_t *cpu, byte v) { cpu->A = v; }
void writeX(CPU_t *cpu, byte v) { cpu->X = v; }
void writeY(CPU_t *cpu, byte v) { cpu->Y = v; }
void writePS(CPU_t *cpu, byte v) { cpu->PS = v; }

/** Read one byte from the memory */
byte readMemory(CPU_t *cpu, word addr) { return cpu->memory[addr]; }

/** Write one byte to given memory index */
void writeMemory(CPU_t *cpu, word addr, byte data) { cpu->memory[addr] = data; }

/** Read one byte from the given address */
byte readByte(byte *addr) { return *addr; }

/** Write one byte to the given address */
void writeByte(byte *addr, byte data) { *addr = data; }

/** Read two consecutive bytes (16-bit full address) from the memory */
word readWord(CPU_t *cpu, word addr) { return (cpu->memory[addr + 1] << 8) | cpu->memory[addr]; }

/** Set/Reset negative flag */
void setNegativeFlag(CPU_t *cpu, bool value) {
    if (value)
        cpu->PS |= 0x80;
    else
        cpu->PS &= 0x7F;
}

/** Set/Reset overflow flag */
void setOverflowFlag(CPU_t *cpu, bool value) {
    if (value)
        cpu->PS |= 0x40;
    else
        cpu->PS &= 0xBF;
}

/** Set/Reset zero flag */
void setZeroFlag(CPU_t *cpu, bool value) {
    if (value)
        cpu->PS |= 0x02;
    else
        cpu->PS &= 0xFD;
}

/** Set/Reset carry flag */
void setCarryFlag(CPU_t *cpu, bool value) {
    if (value)
        cpu->PS |= 0x01;
    else
        cpu->PS &= 0xFE;
}

/* Fetch - Decode - Execute */

/** There are 8 possible addressing modes but not all instructions are able to use all */
// Valid addressing modes for G1
byte validAddrModesG1[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0xFF, 0xFF, 0xFF};
// Valid addressing modes for G2
byte validAddrModesG2[] = {0xAE, 0xAE, 0xAE, 0xAE, 0x2A, 0xAB, 0xAA, 0xAA};
// Valid addressing modes for G3
byte validAddrModesG3[] = {0x00, 0x0A, 0x08, 0x08, 0x2A, 0xAB, 0x0B, 0x0B};

/** Validators */
bool validateOpcode(byte aaa, byte bbb, byte validAddrModes[]) { return validAddrModes[aaa] & (1 << bbb); }

/** Decode Group 1 Address Mode */
byte *decodeG1AddressMode(byte bbb, CPU_t *cpu) {
    word addr;
    switch (bbb) {
        case 0:  // (Indirect, X)
            addr = readMemory(cpu, cpu->PC) + cpu->X;
            addr &= 0xFF;  // The address calculation wraps around
            addr = readWord(cpu, addr);
            cpu->PC++;
            break;
        case 1:  // Zero Page
            addr = readMemory(cpu, cpu->PC);
            cpu->PC++;
            break;
        case 2:  // Immediate
            addr = cpu->PC;
            cpu->PC++;
            break;
        case 3:  // Absolute
            addr = readWord(cpu, cpu->PC);
            cpu->PC += 2;
            break;
        case 4:  // (Indirect), Y
            addr = readMemory(cpu, cpu->PC);
            addr = readWord(cpu, addr);
            addr += cpu->Y;
            cpu->PC++;
            break;
        case 5:  // Zero Page, X
            addr = (readMemory(cpu, cpu->PC) + cpu->X);
            addr &= 0xFF;  // The address calculation wraps around
            cpu->PC++;
            break;
        case 6:  // Absolute, Y
            addr = readWord(cpu, cpu->PC) + cpu->Y;
            cpu->PC += 2;
            break;
        case 7:  // Absolute, X
            addr = readWord(cpu, cpu->PC) + cpu->X;
            cpu->PC += 2;
            break;
        default:
            fprintf(stderr, "Invalid bbb value: %d\n", bbb);
            exit(1);
    }

    return cpu->memory + addr;
}

/** Decode Group 2 and Group 3 Address Mode */
byte *decodeG23AddressMode(byte bbb, byte aaa, CPU_t *cpu) {
    word addr;
    switch (bbb) {
        case 0:  // Immediate
            addr = cpu->PC;
            cpu->PC++;
            break;
        case 1:  // Zero Page
            addr = readMemory(cpu, cpu->PC);
            cpu->PC++;
            break;
        case 2:  // Accumulator
            return &cpu->A;
            break;
        case 3:  // Absolute
            addr = readWord(cpu, cpu->PC);
            cpu->PC += 2;
            break;
        case 5:  // Zero Page, X / Zero Page, Y
            addr = readMemory(cpu, cpu->PC);
            // On STX and LDX ZP,X becomes ZP,Y (only in G2)
            addr += (aaa == 4 || aaa == 5) ? cpu->Y : cpu->X;
            addr &= 0xFF;  // The address calculation wraps around
            cpu->PC++;
            break;
        case 7:  // Absolute, X / Absolute Y
            addr = readWord(cpu, cpu->PC);
            // On LDX ABS,X becomes ABS,Y
            // Only in G2
            addr += (aaa == 5) ? cpu->Y : cpu->X;
            cpu->PC += 2;
            break;
        default:
            fprintf(stderr, "Invalid bbb value: %d\n", bbb);
            exit(1);
    }

    return cpu->memory + addr;
}

/** Execute Group 1 Instructions */
void decodeG1Instruction(byte aaa, byte *addr, CPU_t *cpu) {
    switch (aaa) {
        case 0:  // ORA
            ORA(addr, cpu);
            break;
        case 1:  // AND
            AND(addr, cpu);
            break;
        case 2:  // EOR
            EOR(addr, cpu);
            break;
        case 3:  // ADC
            ADC(addr, cpu);
            break;
        case 4:  // STA
            STA(addr, cpu);
            break;
        case 5:  // LDA
            LDA(addr, cpu);
            break;
        case 6:  // CMP
            CMP(addr, cpu);
            break;
        case 7:  // SBC
            SBC(addr, cpu);
            break;
        default:
            fprintf(stderr, "Invalid aaa value: %d\n", aaa);
            exit(1);
    }
}

/** Execute Group 2 Instructions */
void decodeG2Instruction(byte aaa, byte *addr, CPU_t *cpu) {
    switch (aaa) {
        case 0:  // ASL
            ASL(addr, cpu);
            break;
        case 1:  // ROL
            ROL(addr, cpu);
            break;
        case 2:  // LSR
            LSR(addr, cpu);
            break;
        case 3:  // ROR
            ROR(addr, cpu);
            break;
        case 4:  // STX
            STX(addr, cpu);
            break;
        case 5:  // LDX
            LDX(addr, cpu);
            break;
        case 6:  // DEC
            DEC(addr, cpu);
            break;
        case 7:  // INC
            INC(addr, cpu);
            break;
        default:
            fprintf(stderr, "Invalid aaa value: %d\n", aaa);
            exit(1);
    }
}

/** Execute Group 3 Instructions */
void decodeG3Instruction(byte aaa, byte *addr, CPU_t *cpu) {
    switch (aaa) {
        case 1:  // BIT
            BIT(addr, cpu);
            break;
        case 2:  // JMP
            JMP(addr, cpu);
            break;
        case 3:  // JMP()
            addr = cpu->memory + ((*(addr + 1) << 8) | (*addr));
            JMP(addr, cpu);
            break;
        case 4:  // STY
            STY(addr, cpu);
            break;
        case 5:  // LDY
            LDY(addr, cpu);
            break;
        case 6:  // CPY
            CPY(addr, cpu);
            break;
        case 7:  // CPX
            CPX(addr, cpu);
            break;
        default:
            fprintf(stderr, "Invalid aaa value: %d\n", aaa);
            exit(1);
    }
}

/** Fetch, Decode, and Execute single instruction */
void execute(CPU_t *cpu) {
    // Fetch
    byte opcode = cpu->memory[cpu->PC];
    cpu->PC++;  // Increment the program counter

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

                addr = decodeG1AddressMode(bbb, cpu);  // Decode the addressing mode
                decodeG1Instruction(aaa, addr, cpu);   // Execute the instruction
                break;
            case 2:  // Group 2 instructions
                // Validate addressing mode exists for the instruction (NOP)
                if (!validateOpcode(aaa, bbb, validAddrModesG2)) {
                    fprintf(stderr, "Invalid opcode!\n");
                    exit(1);
                }

                addr = decodeG23AddressMode(bbb, aaa, cpu);  // Decode the addressing mode
                decodeG2Instruction(aaa, addr, cpu);         // Execute the instruction
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

                    addr = decodeG23AddressMode(bbb, -1, cpu);  // Decode the addressing mode
                                                                // Pass -1 for second parameter to avoid X-Y change needed for G2
                    decodeG3Instruction(aaa, addr, cpu);        // Execute the instruction
                }
                break;
            default:
                fprintf(stderr, "Invalid cc value: %d\n", cc);
                exit(1);
        }
    }
}