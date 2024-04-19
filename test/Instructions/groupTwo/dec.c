#ifndef _TEST_H
#define _TEST_H

/**
 * Decrements the memory content by 1
 * The zero flag and the negative flag are set accordingly
 */

/** Each test will perform three DEC instructions
 * 1. DEC (0000 0001) -> FIRST_DATA
 * 2. DEC (0000 0000) -> SECOND_DATA
 * 3. DEC (0101 0101) -> THIRD_DATA
 */
/** At the end of each instruction,
 * 2. Content: 0000 0000, Zero Flag: 1, Negative Flag: 0
 * 1. Content: 1111 1111, Zero Flag: 0, Negative Flag: 1
 * 3. Content: 0101 0100, Zero Flag: 0, Negative Flag: 0
 */

#include "../../../include/cpu.h"
#include "../../../include/opcodes.h"
#include "../../src/unity.h"
#include "../../src/unity_internals.h"

#define INSTRUCTION_ZP INS_DEC_ZP
#define INSTRUCTION_ABS INS_DEC_ABS
#define INSTRUCTION_ZPX INS_DEC_ZPX
#define INSTRUCTION_ABSX INS_DEC_ABSX

#define SETUP_CONFIG_C
#define TEARDOWN_CONFIG_C

#define FIRST_DATA 0x01
#define SECOND_DATA 0x00
#define THIRD_DATA 0x55

#define TEST(number, addressing, address, val, z, n)                                              \
    {                                                                                             \
        char msg1[100], msg2[100], msg3[100];                                                     \
        sprintf(msg1, "Memory isn't right in %s instruction for %s.", number, addressing);        \
        sprintf(msg2, "Zero flag isn't right in %s instruction for %s.", number, addressing);     \
        sprintf(msg3, "Negative flag isn't right in %s instruction for %s.", number, addressing); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(val, readMemory(address), msg1);                           \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(z, readPS() & ZM, msg2);                                   \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(n, readPS() & NM, msg3);                                   \
    }

#define FIRST_TEST_ZP TEST("first", "ZP", 0x0010, 0x00, ZM, 0x00)
#define SECOND_TEST_ZP TEST("second", "ZP", 0x0020, 0xFF, 0x00, NM)
#define THIRD_TEST_ZP TEST("third", "ZP", 0x0030, 0x54, 0x00, 0x00)

#define FIRST_TEST_ABS TEST("first", "ABS", 0x0400, 0x00, ZM, 0x00)
#define SECOND_TEST_ABS TEST("second", "ABS", 0x0410, 0xFF, 0x00, NM)
#define THIRD_TEST_ABS TEST("third", "ABS", 0x0420, 0x54, 0x00, 0x00)

#define FIRST_TEST_ZPX TEST("first", "ZPX", 0x0015, 0x00, ZM, 0x00)
#define SECOND_TEST_ZPX TEST("second", "ZPX", 0x0025, 0xFF, 0x00, NM)
#define THIRD_TEST_ZPX TEST("third", "ZPX", 0x0035, 0x54, 0x00, 0x00)

#define FIRST_TEST_ZPXW TEST("first", "ZPX with wrapping", 0x001F, 0x00, ZM, 0x00)
#define SECOND_TEST_ZPXW TEST("second", "ZPX with wrapping", 0x002F, 0xFF, 0x00, NM)
#define THIRD_TEST_ZPXW TEST("third", "ZPX with wrapping", 0x003F, 0x54, 0x00, 0x00)

#define FIRST_TEST_ABSX TEST("first", "ABSX", 0x0405, 0x00, ZM, 0x00)
#define SECOND_TEST_ABSX TEST("second", "ABSX", 0x0415, 0xFF, 0x00, NM)
#define THIRD_TEST_ABSX TEST("third", "ABSX", 0x0425, 0x54, 0x00, 0x00)

#include "../templates/testTemplate.h"

#endif  // _TEST_H