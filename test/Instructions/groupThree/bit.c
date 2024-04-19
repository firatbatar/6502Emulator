#ifndef _TEST_H
#define _TEST_H

/**
 * Tests if one or more bits are set in a target memory using the mask pattern in A
 * Zero flag is set if the result is zero
 * Negative flag is set if bit 7 is set in the memory
 * Overflow flag is set if bit 6 is set in the memory
 */

/** Each test will perform three BIT instructions
 * Accumulator will hold (0000 1010) always
 * 1. BIT (0000 0000) -> FIRST_DATA
 * 2. BIT (1100 0101) -> SECOND_DATA
 * 3. BIT (0000 1010) -> THIRD_DATA
 */
/** At the end of each instruction,
 * 1. Content: Zero Flag: 1, Overflow Flag: 0, Negative Flag: 0
 * 2. Content: Zero Flag: 1, Overflow Flag: 1, Negative Flag: 1
 * 3. Content: Zero Flag: 0, Overflow Flag: 0, Negative Flag: 0
 */

#include "../../../include/cpu.h"
#include "../../../include/opcodes.h"
#include "../../src/unity.h"
#include "../../src/unity_internals.h"

#define INSTRUCTION_ZP INS_BIT_ZP
#define INSTRUCTION_ABS INS_BIT_ABS

#define SETUP_CONFIG_C writeA(0x0A);
#define TEARDOWN_CONFIG_C

#define FIRST_DATA 0x00
#define SECOND_DATA 0xC5
#define THIRD_DATA 0x0A

#define TEST(number, addressing, address, val, v, z, n)                                           \
    {                                                                                             \
        char msg1[100], msg2[100], msg3[100], msg4[100], msg5[100];                               \
        sprintf(msg1, "Memory has been changed in %s instruction for %s.", number, addressing);   \
        sprintf(msg2, "A has been changed in %s instruction for %s.", number, addressing);        \
        sprintf(msg3, "Overflow flag isn't right in %s instruction for %s.", number, addressing); \
        sprintf(msg4, "Zero flag isn't right in %s instruction for %s.", number, addressing);     \
        sprintf(msg5, "Negative flag isn't right in %s instruction for %s.", number, addressing); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(val, readMemory(address), msg1);                           \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x0A, readA(), msg2);                                      \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(v, readPS() & VM, msg3);                                   \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(z, readPS() & ZM, msg4);                                   \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(n, readPS() & NM, msg5);                                   \
    }

#define FIRST_TEST_ZP TEST("first", "ZP", 0x0010, FIRST_DATA, 0x00, ZM, 0x00)
#define SECOND_TEST_ZP TEST("second", "ZP", 0x0020, SECOND_DATA, VM, ZM, NM)
#define THIRD_TEST_ZP TEST("third", "ZP", 0x0030, THIRD_DATA, 0x00, 0x00, 0x00)

#define FIRST_TEST_ABS TEST("first", "ABS", 0x0400, FIRST_DATA, 0x00, ZM, 0x00)
#define SECOND_TEST_ABS TEST("second", "ABS", 0x0410, SECOND_DATA, VM, ZM, NM)
#define THIRD_TEST_ABS TEST("third", "ABS", 0x0420, THIRD_DATA, 0x00, 0x00, 0x00)

#include "../templates/testTemplate.h"

#endif  // _TEST_H