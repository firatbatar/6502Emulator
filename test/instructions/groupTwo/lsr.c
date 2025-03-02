#ifndef TEST_H
#define TEST_H

/**
 * Shifts the content to 1 bit to the right
 * The leftmost bit is always 0, the rightmost bit is stored in the carry flag
 * Negative flag is always reset, Zero flag is set accordingly
 */

/** Each test will perform two LSR instructions
 * 1. LSR (0000 0001) -> FIRST_DATA
 * 2. LSR (1000 0000) -> SECOND_DATA
 */
/** At the end of each instruction,
 * 1. Content: 0000 0000, Carry Flag: 1, Zero Flag: 1, Negative Flag: 0
 * 2. Content: 0100 0000, Carry Flag: 0, Zero Flag: 0, Negative Flag: 0
 */

#include <cpu.h>
#include <initCPU.h>
#include <opcodes.h>
#include <unity.h>
#include <unity_internals.h>

#define INSTRUCTION_ZP INS_LSR_ZP
#define INSTRUCTION_A INS_LSR_A
#define INSTRUCTION_ABS INS_LSR_ABS
#define INSTRUCTION_ZPX INS_LSR_ZPX
#define INSTRUCTION_ABSX INS_LSR_ABSX

#define SETUP_CONFIG_C writePS(&cpu, readPS(&cpu) | ZM);
#define TEARDOWN_CONFIG_C

#define FIRST_DATA 0x01
#define SECOND_DATA 0x80
#define THIRD_DATA 0xFF

#define TEST(number, addressing, address, val, c, z)                                          \
  {                                                                                           \
    char msg1[100], msg2[100], msg3[100], msg4[100];                                          \
    sprintf(msg1, "Memory isn't right in %s instruction for %s.", number, addressing);        \
    sprintf(msg2, "Carry flag isn't right in %s instruction for %s.", number, addressing);    \
    sprintf(msg3, "Zero flag isn't right in %s instruction for %s.", number, addressing);     \
    sprintf(msg4, "Negative flag isn't right in %s instruction for %s.", number, addressing); \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(val, readMemory(&cpu, address), msg1);                     \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(c, readPS(&cpu) & CM, msg2);                               \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(z, readPS(&cpu) & ZM, msg3);                               \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS(&cpu) & NM, msg4);                            \
  }

#define TEST_A(number, val, c, z)                                                                  \
  {                                                                                                \
    char msg1[100], msg2[100], msg3[100], msg4[100];                                               \
    sprintf(msg1, "A isn't right in %s instruction for Accumulator addressing.", number);          \
    sprintf(msg2, "Carry flag isn't right in %s instruction for Accumulator addressing.", number); \
    sprintf(msg3, "Zero flag isn't right in %s instruction for Accumulator addressing.", number);  \
    sprintf(msg4, "Negative flag isn't right in %s instruction for Accumulator addressing.",       \
            number);                                                                               \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(val, readA(&cpu), msg1);                                        \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(c, readPS(&cpu) & CM, msg2);                                    \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(z, readPS(&cpu) & ZM, msg3);                                    \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS(&cpu) & NM, msg4);                                 \
  }

#define FIRST_TEST_ZP TEST("first", "ZP", 0x0010, 0x00, CM, ZM)
#define SECOND_TEST_ZP TEST("second", "ZP", 0x0020, 0x40, 0x00, 0x00)
#define THIRD_TEST_ZP

#define FIRST_TEST_A TEST_A("first", 0x00, CM, ZM)
#define SECOND_TEST_A TEST_A("second", 0x40, 0x00, 0x00)
#define THIRD_TEST_A

#define FIRST_TEST_ABS TEST("first", "ABS", 0x0400, 0x00, CM, ZM)
#define SECOND_TEST_ABS TEST("second", "ABS", 0x0410, 0x40, 0x00, 0x00)
#define THIRD_TEST_ABS

#define FIRST_TEST_ZPX TEST("first", "ZPX", 0x0015, 0x00, CM, ZM)
#define SECOND_TEST_ZPX TEST("second", "ZPX", 0x0025, 0x40, 0x00, 0x00)
#define THIRD_TEST_ZPX

#define FIRST_TEST_ZPXW TEST("first", "ZPX with wrapping", 0x001F, 0x00, CM, ZM)
#define SECOND_TEST_ZPXW TEST("second", "ZPX with wrapping", 0x002F, 0x40, 0x00, 0x00)
#define THIRD_TEST_ZPXW

#define FIRST_TEST_ABSX TEST("first", "ABSX", 0x0405, 0x00, CM, ZM)
#define SECOND_TEST_ABSX TEST("second", "ABSX", 0x0415, 0x40, 0x00, 0x00)
#define THIRD_TEST_ABSX

#include <testTemplate.h>

#endif  // TEST_H