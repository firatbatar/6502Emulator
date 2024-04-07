#ifndef _TEST_H
#define _TEST_H

/**
 * LDA loads the value from memory into the accumulator
 * Zero and Negative flag are affected
 */

/** Each test will perform three LDA instructions
 * 1. LDA with (0000 0000) -> FIRST_DATA
 * 2. LDA with (1000 0000) -> SECOND_DATA
 * 3. LDA with (0100 0000) -> THIRD_DATA
 */
/** At the end of each instruction,
 * Accumulator starts as (0000 0001)
 * 1. Accumulator: 0000 0000, Zero Flag: 1, Negative Flag: 0 -> FIRST_INSTRUCTION_TEST
 * 2. Accumulator: 1000 0000, Zero Flag: 0, Negative Flag: 1 -> SECOND_INSTRUCTION_TEST
 * 3. Accumulator: 0100 0000, Zero Flag: 0, Negative Flag: 0 -> THIRD_INSTRUCTION_TEST
 */

#include "../../../include/cpu.h"
#include "../../../include/instructions.h"
#include "../../src/unity.h"
#include "../../src/unity_internals.h"

#define SETUP_CONFIG_C writeA(0x01);
#define TEARDOWN_CONFIG_C

#define INSTRUCTION_IM INS_LDA_IM
#define INSTRUCTION_ZP INS_LDA_ZP
#define INSTRUCTION_ZPX INS_LDA_ZPX
#define INSTRUCTION_ABS INS_LDA_ABS
#define INSTRUCTION_ABSX INS_LDA_ABSX
#define INSTRUCTION_ABSY INS_LDA_ABSY
#define INSTRUCTION_INDX INS_LDA_INDX
#define INSTRUCTION_INDY INS_LDA_INDY

#define FIRST_DATA 0x00
#define SECOND_DATA 0x80
#define THIRD_DATA 0x70

#define UNPACK_TESTS

#define FIRST_INSTRUCTION_TEST(addressing)                                                   \
    {                                                                                        \
        char msg1[100], msg2[100], msg3[100];                                                \
        sprintf(msg1, "A isn't right in first instruction for %s.", addressing);             \
        sprintf(msg2, "Zero flag isn't right in first instruction for %s.", addressing);     \
        sprintf(msg3, "Negative flag isn't right in first instruction for %s.", addressing); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readA(), msg1);                                 \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(ZM, readPS() & ZM, msg2);                             \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & NM, msg3);                           \
    }

#define SECOND_INSTRUCTION_TEST(addressing)                                                   \
    {                                                                                         \
        char msg1[100], msg2[100], msg3[100];                                                 \
        sprintf(msg1, "A isn't right in second instruction for %s.", addressing);             \
        sprintf(msg2, "Zero flag isn't right in second instruction for %s.", addressing);     \
        sprintf(msg3, "Negative flag isn't right in second instruction for %s.", addressing); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x80, readA(), msg1);                                  \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & ZM, msg2);                            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(NM, readPS() & NM, msg3);                              \
    }

#define THIRD_INSTRUCTION_TEST(addressing)                                                   \
    {                                                                                        \
        char msg1[100], msg2[100], msg3[100];                                                \
        sprintf(msg1, "A isn't right in third instruction for %s.", addressing);             \
        sprintf(msg2, "Zero flag isn't right in third instruction for %s.", addressing);     \
        sprintf(msg3, "Negative flag isn't right in third instruction for %s.", addressing); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x70, readA(), msg1);                                 \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & ZM, msg2);                           \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & NM, msg3);                           \
    }

#include "../templates/testTemplate.h"

#endif  // _TEST_H