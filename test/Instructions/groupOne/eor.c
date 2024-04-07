#ifndef _TEST_GROUP_ONE_H
#define _TEST_GROUP_ONE_H

/**
 * EOR performs an exclusive or on the accumulator
 * Result is written in to the accumulator
 * Zero and Negative flag are affected
 */

/** Each test will perform three EOR instructions
 * Accumulator is set to (1111 1111) at the start
 * 1. EOR with (1111 1111) -> FIRST_DATA
 * 2. EOR with (0101 0101) -> SECOND_DATA
 * 3. EOR with (1010 1010) -> THIRD_DATA
 */
/** At the end of each instruction,
 * 1. Accumulator: 0000 0000, Zero Flag: 1, Negative Flag: 0 -> FIRST_INSTRUCTION_TEST
 * 2. Accumulator: 0101 0101, Zero Flag: 0, Negative Flag: 0 -> SECOND_INSTRUCTION_TEST
 * 3. Accumulator: 1111 1111, Zero Flag: 0, Negative Flag: 1 -> THIRD_INSTRUCTION_TEST
 */

#include "../../../include/cpu.h"
#include "../../../include/instructions.h"
#include "../../src/unity.h"
#include "../../src/unity_internals.h"

#define SETUP_CONFIG_C writeA(0xFF);
#define TEARDOWN_CONFIG_C

#define INSTRUCTION_IM INS_EOR_IM
#define INSTRUCTION_ZP INS_EOR_ZP
#define INSTRUCTION_ZPX INS_EOR_ZPX
#define INSTRUCTION_ABS INS_EOR_ABS
#define INSTRUCTION_ABSX INS_EOR_ABSX
#define INSTRUCTION_ABSY INS_EOR_ABSY
#define INSTRUCTION_INDX INS_EOR_INDX
#define INSTRUCTION_INDY INS_EOR_INDY

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
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readA(), msg1);                                 \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(ZM, readPS() & ZM, msg2);                             \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & NM, msg3);                           \
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
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0xFF, readA(), msg1);                                 \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & ZM, msg2);                           \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(NM, readPS() & NM, msg3);                             \
    }

#include "../templates/groupOneBase.h"

#endif  // _TEST_GROUP_ONE_H