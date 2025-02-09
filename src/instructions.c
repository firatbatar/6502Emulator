#include <instructions.h>

void ORA(byte *addr, CPU_t *cpu) {
  cpu->A |= (*addr);

  setZeroFlag(cpu, cpu->A == 0);
  setNegativeFlag(cpu, cpu->A & 0x80);
}

void AND(byte *addr, CPU_t *cpu) {
  cpu->A &= (*addr);

  setZeroFlag(cpu, cpu->A == 0);
  setNegativeFlag(cpu, cpu->A & 0x80);
}

void EOR(byte *addr, CPU_t *cpu) {
  cpu->A ^= (*addr);

  setZeroFlag(cpu, cpu->A == 0);
  setNegativeFlag(cpu, cpu->A & 0x80);
}

void ADC(byte *addr, CPU_t *cpu) {
  // TODO: No decimal mode

  word result = cpu->A + (*addr) + (cpu->PS & CM);
  byte oldA = cpu->A;  // Keep the old A for overflow
  cpu->A = result & 0xFF;

  setZeroFlag(cpu, cpu->A == 0);
  setNegativeFlag(cpu, cpu->A & 0x80);
  setCarryFlag(cpu, result & 0x0100);  // Set the carry flag if ninth bit is 1
  // Set the overflow flag if same signed operands result in inverse sign
  setOverflowFlag(cpu, ((oldA & (*addr)) | (~(oldA ^ (*addr)) & result)) & 0x80);
}

void STA(byte *addr, CPU_t *cpu) { writeByte(addr, cpu->A); }

void LDA(byte *addr, CPU_t *cpu) {
  cpu->A = (*addr);

  setZeroFlag(cpu, cpu->A == 0);
  setNegativeFlag(cpu, cpu->A & 0x80);
}

void CMP(byte *addr, CPU_t *cpu) {
  byte result = cpu->A - (*addr);

  setZeroFlag(cpu, result == 0);
  setNegativeFlag(cpu, result & 0x80);
  setCarryFlag(cpu, cpu->A >= (*addr));  // Set the carry flag if the data <= accumulator
}

void SBC(byte *addr, CPU_t *cpu) {
  // Subtraction is addition with data's one's complement
  byte complement = ~(*addr);  // One's complement of the data
  ADC(&complement, cpu);       // Add the one's complement to the accumulator
}

void ASL(byte *addr, CPU_t *cpu) {
  byte newCarry = (*addr) & 0x80;
  byte newVal = (*addr) << 1;

  writeByte(addr, newVal);

  setZeroFlag(cpu, newVal == 0);
  setNegativeFlag(cpu, newVal & 0x80);
  setCarryFlag(cpu, newCarry);
}

void ROL(byte *addr, CPU_t *cpu) {
  byte newCarry = (*addr) & 0x80;
  byte newVal = ((*addr) << 1) | (cpu->PS & CM);

  writeByte(addr, newVal);
  setZeroFlag(cpu, newVal == 0);
  setNegativeFlag(cpu, newVal & 0x80);
  setCarryFlag(cpu, newCarry);
}

void LSR(byte *addr, CPU_t *cpu) {
  byte newCarry = (*addr) & 0x01;
  byte newVal = (*addr) >> 1;

  writeByte(addr, newVal);
  setZeroFlag(cpu, newVal == 0);
  setNegativeFlag(cpu, newVal & 0x80);
  setCarryFlag(cpu, newCarry);
}

void ROR(byte *addr, CPU_t *cpu) {
  byte newCarry = (*addr) & 0x01;
  byte newVal = ((*addr) >> 1) | ((cpu->PS & CM) << 7);

  writeByte(addr, newVal);
  setZeroFlag(cpu, newVal == 0);
  setNegativeFlag(cpu, newVal & 0x80);
  setCarryFlag(cpu, newCarry);
}

void STX(byte *addr, CPU_t *cpu) { writeByte(addr, cpu->X); }

void LDX(byte *addr, CPU_t *cpu) {
  cpu->X = (*addr);

  setZeroFlag(cpu, cpu->X == 0);
  setNegativeFlag(cpu, cpu->X & 0x80);
}

void DEC(byte *addr, CPU_t *cpu) {
  byte newVal = (*addr) - 1;

  writeByte(addr, newVal);
  setZeroFlag(cpu, newVal == 0);
  setNegativeFlag(cpu, newVal & 0x80);
}

void INC(byte *addr, CPU_t *cpu) {
  byte newVal = (*addr) + 1;

  writeByte(addr, newVal);
  setZeroFlag(cpu, newVal == 0);
  setNegativeFlag(cpu, newVal & 0x80);
}

void BIT(byte *addr, CPU_t *cpu) {
  byte result = cpu->A & (*addr);

  setZeroFlag(cpu, result == 0);         // Set the zero flag if the result is zero
  setNegativeFlag(cpu, (*addr) & 0x80);  // 7th bit of the memory
  setOverflowFlag(cpu, (*addr) & 0x40);  // 6th bit of the memory
}

void JMP(byte *addr, CPU_t *cpu) { cpu->PC = (word)(addr - cpu->memory); }

void STY(byte *addr, CPU_t *cpu) { writeByte(addr, cpu->Y); }

void LDY(byte *addr, CPU_t *cpu) {
  cpu->Y = (*addr);

  setZeroFlag(cpu, cpu->Y == 0);
  setNegativeFlag(cpu, cpu->Y & 0x80);
}

void CPY(byte *addr, CPU_t *cpu) {
  byte result = cpu->Y - (*addr);

  setZeroFlag(cpu, result == 0);
  setNegativeFlag(cpu, result & 0x80);
  setCarryFlag(cpu, cpu->Y >= (*addr));  // Set the carry flag if the data <= Y
}

void CPX(byte *addr, CPU_t *cpu) {
  byte result = cpu->X - (*addr);

  setZeroFlag(cpu, result == 0);
  setNegativeFlag(cpu, result & 0x80);
  setCarryFlag(cpu, cpu->X >= (*addr));  // Set the carry flag if the data <= X
}

void BPL(CPU_t *cpu) {
  if (!(cpu->PS & NM)) {
    byte offset = cpu->memory[cpu->PC];
    if (offset & 0x80) {
      offset = ~offset + 1;
      cpu->PC -= offset;
    }
    else {
      cpu->PC += offset;
    }
  }
  cpu->PC++;
}

void BMI(CPU_t *cpu) {
  if (cpu->PS & NM) {
    byte offset = cpu->memory[cpu->PC];
    if (offset & 0x80) {
      offset = ~offset + 1;
      cpu->PC -= offset;
    }
    else {
      cpu->PC += offset;
    }
  }
  cpu->PC++;
}

void BVC(CPU_t *cpu) {
  if (!(cpu->PS & VM)) {
    byte offset = cpu->memory[cpu->PC];
    if (offset & 0x80) {
      offset = ~offset + 1;
      cpu->PC -= offset;
    }
    else {
      cpu->PC += offset;
    }
  }
  cpu->PC++;
}

void BVS(CPU_t *cpu) {
  if (cpu->PS & VM) {
    byte offset = cpu->memory[cpu->PC];
    if (offset & 0x80) {
      offset = ~offset + 1;
      cpu->PC -= offset;
    }
    else {
      cpu->PC += offset;
    }
  }
  cpu->PC++;
}

void BCC(CPU_t *cpu) {
  if (!(cpu->PS & CM)) {
    byte offset = cpu->memory[cpu->PC];
    if (offset & 0x80) {
      offset = ~offset + 1;
      cpu->PC -= offset;
    }
    else {
      cpu->PC += offset;
    }
  }
  cpu->PC++;
}

void BCS(CPU_t *cpu) {
  if (cpu->PS & CM) {
    byte offset = cpu->memory[cpu->PC];
    if (offset & 0x80) {
      offset = ~offset + 1;
      cpu->PC -= offset;
    }
    else {
      cpu->PC += offset;
    }
  }
  cpu->PC++;
}

void BNE(CPU_t *cpu) {
  if (!(cpu->PS & ZM)) {
    byte offset = cpu->memory[cpu->PC];
    if (offset & 0x80) {
      offset = ~offset + 1;
      cpu->PC -= offset;
    }
    else {
      cpu->PC += offset;
    }
  }
  cpu->PC++;
}

void BEQ(CPU_t *cpu) {
  if (cpu->PS & ZM) {
    byte offset = cpu->memory[cpu->PC];
    if (offset & 0x80) {
      offset = ~offset + 1;
      cpu->PC -= offset;
    }
    else {
      cpu->PC += offset;
    }
  }
  cpu->PC++;
}