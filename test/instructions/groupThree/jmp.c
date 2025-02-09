#ifndef TEST_TEMPLATE_H
#define TEST_TEMPLATE_H

#ifndef TEST_H
#define TEST_H

/** Sets the program counter to the address specified by the operand.
 */

/** Test will perform 2 instructions
 * 1. JMP 0x1020
 * 2. JMP (0x2020)
 */
/** At the end of each instruction,
 * 1. PC will be 0x1020
 * 2. PC will be 0xCCDD
 */

#include <cpu.h>
#include <initCPU.h>
#include <opcodes.h>
#include <unity.h>
#include <unity_internals.h>

#define SETUP_CONFIG                                            \
  resetMemory(&cpu, 0xFF); /*Set everything in memory to 0xFF*/ \
  /*Set the program start to 0x0200*/                           \
  writeMemory(&cpu, 0xFFFC, 0x00);                              \
  writeMemory(&cpu, 0xFFFD, 0x02);                              \
  resetCPU(&cpu); /*Reset the registers*/                       \
  writeX(&cpu, 0x55);

#define TEARDOWN_CONFIG

#define ABS_TEST                                                                             \
  /* Both absolute and indirect addressing will be here since indirect is special for JMP */ \
  {                                                                                          \
    writeMemory(&cpu, 0x0200, INS_JMP_ABS);                                                  \
    writeMemory(&cpu, 0x0201, 0x20);                                                         \
    writeMemory(&cpu, 0x0202, 0x10);                                                         \
    execute(&cpu);                                                                           \
                                                                                             \
    TEST_ASSERT_EQUAL_HEX16_MESSAGE(0x1020, readPC(&cpu), "PC is not set right for ABS.");   \
                                                                                             \
    writeMemory(&cpu, 0x1020, INS_JMPABS_ABS);                                               \
    writeMemory(&cpu, 0x1021, 0x20);                                                         \
    writeMemory(&cpu, 0x1022, 0x20);                                                         \
    writeMemory(&cpu, 0x2020, 0xDD);                                                         \
    writeMemory(&cpu, 0x2021, 0xCC);                                                         \
    execute(&cpu);                                                                           \
                                                                                             \
    TEST_ASSERT_EQUAL_HEX16_MESSAGE(0xCCDD, readPC(&cpu), "PC is not set right for ABS.");   \
  }

#include <testMain.h>

#endif  // TEST_H
#endif  // TEST_TEMPLATE_H