#ifndef TEST_H
#define TEST_H

/**
 * Rotates the content to 1 bit to the left
 * The first bit is set to the carry flag
 * The carry flag is set to the last bit of the content
 * The zero flag and the negative flag are set accordingly
 */

/** Each test will perform three ROL instructions
 * 1. ROL (1000 0000) -> FIRST_DATA
 * 2. ROL (0000 0000) -> SECOND_DATA
 * 3. ROL (0100 0000) -> THIRD_DATA
 */
/** At the end of each instruction,
 * 1. Content: 0000 0000, Carry Flag: 1, Zero Flag: 1, Negative Flag: 0
 * 2. Content: 0000 0001, Carry Flag: 0, Zero Flag: 0, Negative Flag: 0
 * 3. Content: 1000 0000, Carry Flag: 0, Zero Flag: 0, Negative Flag: 1
 */

#include "../../../include/cpu.h"
#include "../../../include/opcodes.h"
#include "../../src/unity.h"
#include "../../src/unity_internals.h"
#include "../templates/initCPU.h"

#define INSTRUCTION_ZP INS_ROL_ZP
#define INSTRUCTION_A INS_ROL_A
#define INSTRUCTION_ABS INS_ROL_ABS
#define INSTRUCTION_ZPX INS_ROL_ZPX
#define INSTRUCTION_ABSX INS_ROL_ABSX

#define SETUP_CONFIG_C
#define TEARDOWN_CONFIG_C

#define FIRST_DATA 0x80
#define SECOND_DATA 0x00
#define THIRD_DATA 0x40

#define TEST(number, addressing, address, val, c, z, n)                                           \
    {                                                                                             \
        char msg1[100], msg2[100], msg3[100], msg4[100];                                          \
        sprintf(msg1, "Memory isn't right in %s instruction for %s.", number, addressing);        \
        sprintf(msg2, "Carry flag isn't right in %s instruction for %s.", number, addressing);    \
        sprintf(msg3, "Zero flag isn't right in %s instruction for %s.", number, addressing);     \
        sprintf(msg4, "Negative flag isn't right in %s instruction for %s.", number, addressing); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(val, readMemory(&cpu, address), msg1);                     \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(c, readPS(&cpu) & CM, msg2);                               \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(z, readPS(&cpu) & ZM, msg3);                               \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(n, readPS(&cpu) & NM, msg4);                               \
    }

#define TEST_A(number, val, c, z, n)                                                                      \
    {                                                                                                     \
        char msg1[100], msg2[100], msg3[100], msg4[100];                                                  \
        sprintf(msg1, "A isn't right in %s instruction for Accumulator addressing.", number);             \
        sprintf(msg2, "Carry flag isn't right in %s instruction for Accumulator addressing.", number);    \
        sprintf(msg3, "Zero flag isn't right in %s instruction for Accumulator addressing.", number);     \
        sprintf(msg4, "Negative flag isn't right in %s instruction for Accumulator addressing.", number); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(val, readA(&cpu), msg1);                                           \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(c, readPS(&cpu) & CM, msg2);                                       \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(z, readPS(&cpu) & ZM, msg3);                                       \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(n, readPS(&cpu) & NM, msg4);                                       \
    }

#define FIRST_TEST_ZP TEST("first", "ZP", 0x0010, 0x00, CM, ZM, 0x00)
#define SECOND_TEST_ZP TEST("second", "ZP", 0x0020, 0x01, 0x00, 0x00, 0x00)
#define THIRD_TEST_ZP TEST("third", "ZP", 0x0030, 0x80, 0x00, 0x00, NM)

#define FIRST_TEST_A TEST_A("first", 0x00, CM, ZM, 0x00)
#define SECOND_TEST_A TEST_A("second", 0x01, 0x00, 0x00, 0x00)
#define THIRD_TEST_A TEST_A("third", 0x80, 0x00, 0x00, NM)

#define FIRST_TEST_ABS TEST("first", "ABS", 0x0400, 0x00, CM, ZM, 0x00)
#define SECOND_TEST_ABS TEST("second", "ABS", 0x0410, 0x01, 0x00, 0x00, 0x00)
#define THIRD_TEST_ABS TEST("third", "ABS", 0x0420, 0x80, 0x00, 0x00, NM)

#define FIRST_TEST_ZPX TEST("first", "ZPX", 0x0015, 0x00, CM, ZM, 0x00)
#define SECOND_TEST_ZPX TEST("second", "ZPX", 0x0025, 0x01, 0x00, 0x00, 0x00)
#define THIRD_TEST_ZPX TEST("third", "ZPX", 0x0035, 0x80, 0x00, 0x00, NM)

#define FIRST_TEST_ZPXW TEST("first", "ZPX with wrapping", 0x001F, 0x00, CM, ZM, 0x00)
#define SECOND_TEST_ZPXW TEST("second", "ZPX with wrapping", 0x002F, 0x01, 0x00, 0x00, 0x00)
#define THIRD_TEST_ZPXW TEST("third", "ZPX with wrapping", 0x003F, 0x80, 0x00, 0x00, NM)

#define FIRST_TEST_ABSX TEST("first", "ABSX", 0x0405, 0x00, CM, ZM, 0x00)
#define SECOND_TEST_ABSX TEST("second", "ABSX", 0x0415, 0x01, 0x00, 0x00, 0x00)
#define THIRD_TEST_ABSX TEST("third", "ABSX", 0x0425, 0x80, 0x00, 0x00, NM)

#include "../templates/testTemplate.h"

#endif  // TEST_H