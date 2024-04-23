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

#include "../../../include/cpu.h"
#include "../../../include/opcodes.h"
#include "../../src/unity.h"
#include "../../src/unity_internals.h"

#define SETUP_CONFIG                                        \
    resetMemory(0xFF); /*Set everything in memory to 0xFF*/ \
    /*Set the program start to 0x0200*/                     \
    writeMemory(0xFFFC, 0x00);                              \
    writeMemory(0xFFFD, 0x02);                              \
    resetCPU(); /*Reset the registers*/                     \
    writeX(0x55);

#define TEARDOWN_CONFIG

#define ABS_TEST                                                                               \
    /* Both absolute and indirect addressing will be here since indirect is special for JMP */ \
    {                                                                                          \
        writeMemory(0x0200, INS_JMP_ABS);                                                      \
        writeMemory(0x0201, 0x20);                                                             \
        writeMemory(0x0202, 0x10);                                                             \
        execute();                                                                             \
                                                                                               \
        TEST_ASSERT_EQUAL_HEX16_MESSAGE(0x1020, readPC(), "PC is not set right for ABS.");     \
                                                                                               \
        writeMemory(0x1020, INS_JMPABS_ABS);                                                   \
        writeMemory(0x1021, 0x20);                                                             \
        writeMemory(0x1022, 0x20);                                                             \
        writeMemory(0x2020, 0xDD);                                                             \
        writeMemory(0x2021, 0xCC);                                                             \
        execute();                                                                             \
                                                                                               \
        TEST_ASSERT_EQUAL_HEX16_MESSAGE(0xCCDD, readPC(), "PC is not set right for ABS.");     \
    }

#include "../templates/testMain.h"

#endif  // TEST_H
#endif  // TEST_TEMPLATE_H