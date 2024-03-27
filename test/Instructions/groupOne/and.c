#ifndef _TEST_GROUP_ONE_H
#define _TEST_GROUP_ONE_H

/**
 * AND performs an inclusive and on the accumulator
 * Result is written into the accumulator
 * Zero and Negative flag are affected
 */

/** Each test will perform three AND instructions
 * Accumulator wil start as (1111 1111)
 * 1. AND with (1111 1111)
 * 2. AND with (0101 0101)
 * 3. AND with (1010 1010)
 */
/** At the end of each instruction,
 * 1. Accumulator: 1111 1111, Zero Flag: 0, Negative Flag: 1
 * 2. Accumulator: 0101 0101, Zero Flag: 0, Negative Flag: 0
 * 3. Accumulator: 0000 0000, Zero Flag: 1, Negative Flag: 0
 */

#include "../../../include/cpu.h"
#include "../../../include/instructions.h"
#include "../../src/unity.h"
#include "../../src/unity_internals.h"

#define SETUP_CONFIG_C writeA(0xFF);
#define TEARDOWN_CONFIG_C

#define INSTRUCTION_IM INS_AND_IM
#define INSTRUCTION_ZP INS_AND_ZP
#define INSTRUCTION_ZPX INS_AND_ZPX
#define INSTRUCTION_ABS INS_AND_ABS
#define INSTRUCTION_ABSX INS_AND_ABSX
#define INSTRUCTION_ABSY INS_AND_ABSY
#define INSTRUCTION_INDX INS_AND_INDX
#define INSTRUCTION_INDY INS_AND_INDY

#define FIRST_DATA 0xFF
#define SECOND_DATA 0x55
#define THIRD_DATA 0xAA

#define FIRST_INSTRUCTION_TEST(addressing)                                                   \
    {                                                                                        \
        char msg1[100], msg2[100], msg3[100];                                                \
                                                                                             \
        sprintf(msg1, "A isn't right in first instruction for %s.", addressing);             \
        sprintf(msg2, "Zero flag isn't right in first instruction for %s.", addressing);     \
        sprintf(msg3, "Negative flag isn't right in first instruction for %s.", addressing); \
                                                                                             \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0xFF, readA(), msg1);                                 \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & ZM, msg2);                           \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(NM, readPS() & NM, msg3);                             \
    }

#define SECOND_INSTRUCTION_TEST(addressing)                                                   \
    {                                                                                         \
        char msg1[100], msg2[100], msg3[100];                                                 \
                                                                                              \
        sprintf(msg1, "A isn't right in second instruction for %s.", addressing);             \
        sprintf(msg2, "Zero flag isn't right in second instruction for %s.", addressing);     \
        sprintf(msg3, "Negative flag isn't right in second instruction for %s.", addressing); \
                                                                                              \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readA(), msg1);                                  \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & ZM, msg2);                            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & NM, msg3);                            \
    }

#define THIRD_INSTRUCTION_TEST(addressing)                                                   \
    {                                                                                        \
        char msg1[100], msg2[100], msg3[100];                                                \
                                                                                             \
        sprintf(msg1, "A isn't right in third instruction for %s.", addressing);             \
        sprintf(msg2, "Zero flag isn't right in third instruction for %s.", addressing);     \
        sprintf(msg3, "Negative flag isn't right in third instruction for %s.", addressing); \
                                                                                             \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readA(), msg1);                                 \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(ZM, readPS() & ZM, msg2);                             \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & NM, msg3);                           \
    }

#include "../templates/groupOneBase_1.h"

#endif  // _TEST_GROUP_ONE_H