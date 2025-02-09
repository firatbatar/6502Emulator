#ifndef TEST_TEMPLATE_H
#define TEST_TEMPLATE_H

#ifndef TEST_H
#define TEST_H

/**
 * Tests if the Overflow flag is clear.
 * Only the PC should be affected.
 */

/** There is one test which will perform 3 BVC instructions
 * 1. BPL 0x0F (with Overflow flag set)
 * 2. BPL 0x0F (with Overflow flag clear)
 * 3. BPL 0xFE (with Overflow flag clear)
 */

/** At the end of each instruction,
 * 1. PC will be 0x0202
 * 2. PC will be 0x0213
 * 3. PC will be 0x0213
 */

#include <cpu.h>
#include <initCPU.h>
#include <opcodes.h>
#include <unity.h>
#include <unity_internals.h>

#define SETUP_CONFIG                    \
  resetMemory(&cpu, 0xFF);              \
  /* Set the program start to 0x0200 */ \
  writeMemory(&cpu, 0xFFFC, 0x00);      \
  writeMemory(&cpu, 0xFFFD, 0x02);      \
  resetCPU(&cpu);

#define TEARDOWN_CONFIG

#define REL_TEST                                                                 \
  {                                                                              \
    writePS(&cpu, VM);                                                           \
    writeMemory(&cpu, 0x0200, INS_BVC_REL);                                      \
    writeMemory(&cpu, 0x0201, 0x0F);                                             \
    execute(&cpu);                                                               \
                                                                                 \
    TEST_ASSERT_EQUAL_HEX16_MESSAGE(0x0202, readPC(&cpu),                        \
                                    "PC is not set right for the first test.");  \
                                                                                 \
    writePS(&cpu, 0x00);                                                         \
    writeMemory(&cpu, 0x0202, INS_BVC_REL);                                      \
    writeMemory(&cpu, 0x0203, 0x0F);                                             \
    execute(&cpu);                                                               \
                                                                                 \
    TEST_ASSERT_EQUAL_HEX16_MESSAGE(0x0213, readPC(&cpu),                        \
                                    "PC is not set right for the second test."); \
                                                                                 \
    writePS(&cpu, 0x00);                                                         \
    writeMemory(&cpu, 0x0213, INS_BVC_REL);                                      \
    writeMemory(&cpu, 0x0214, 0xFE);                                             \
    execute(&cpu);                                                               \
                                                                                 \
    TEST_ASSERT_EQUAL_HEX16_MESSAGE(0x0213, readPC(&cpu),                        \
                                    "PC is not set right for the third test.");  \
  }

#include <testMain.h>

#endif  // TEST_H
#endif  // TEST_TEMPLATE_H