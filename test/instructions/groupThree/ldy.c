#ifndef TEST_H
#define TEST_H

/**
 * LDX loads the value from memory into the Y register
 * Zero and Negative flag are affected
 */

/** Each test will perform three LDY instructions
 * 1. LDY with (0000 0000) -> FIRST_DATA
 * 2. LDY with (1000 0000) -> SECOND_DATA
 * 3. LDY with (0100 0000) -> THIRD_DATA
 */
/** At the end of each instruction,
 * Y starts as (0000 0001)
 * 1. Y Register: 0000 0000, Zero Flag: 1, Negative Flag: 0 -> FIRST_INSTRUCTION_TEST
 * 2. Y Register: 1000 0000, Zero Flag: 0, Negative Flag: 1 -> SECOND_INSTRUCTION_TEST
 * 3. Y Register: 0100 0000, Zero Flag: 0, Negative Flag: 0 -> THIRD_INSTRUCTION_TEST
 */

#include "../../../include/cpu.h"
#include "../../../include/opcodes.h"
#include "../../src/unity.h"
#include "../../src/unity_internals.h"
#include "../templates/initCPU.h"

#define SETUP_CONFIG_C writeY(&cpu, 0x01);
#define TEARDOWN_CONFIG_C

#define INSTRUCTION_IM INS_LDY_IM
#define INSTRUCTION_ZP INS_LDY_ZP
#define INSTRUCTION_ZPX INS_LDY_ZPX
#define INSTRUCTION_ABS INS_LDY_ABS
#define INSTRUCTION_ABSX INS_LDY_ABSX

#define FIRST_DATA 0x00
#define SECOND_DATA 0x80
#define THIRD_DATA 0x70

#define UNPACK_TESTS

#define FIRST_INSTRUCTION_TEST(addressing)                                                   \
    {                                                                                        \
        char msg1[100], msg2[100], msg3[100];                                                \
        sprintf(msg1, "Y isn't right in first instruction for %s.", addressing);             \
        sprintf(msg2, "Zero flag isn't right in first instruction for %s.", addressing);     \
        sprintf(msg3, "Negative flag isn't right in first instruction for %s.", addressing); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readY(&cpu), msg1);                             \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(ZM, readPS(&cpu) & ZM, msg2);                         \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS(&cpu) & NM, msg3);                       \
    }

#define SECOND_INSTRUCTION_TEST(addressing)                                                   \
    {                                                                                         \
        char msg1[100], msg2[100], msg3[100];                                                 \
        sprintf(msg1, "Y isn't right in second instruction for %s.", addressing);             \
        sprintf(msg2, "Zero flag isn't right in second instruction for %s.", addressing);     \
        sprintf(msg3, "Negative flag isn't right in second instruction for %s.", addressing); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x80, readY(&cpu), msg1);                              \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS(&cpu) & ZM, msg2);                        \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(NM, readPS(&cpu) & NM, msg3);                          \
    }

#define THIRD_INSTRUCTION_TEST(addressing)                                                   \
    {                                                                                        \
        char msg1[100], msg2[100], msg3[100];                                                \
        sprintf(msg1, "Y isn't right in third instruction for %s.", addressing);             \
        sprintf(msg2, "Zero flag isn't right in third instruction for %s.", addressing);     \
        sprintf(msg3, "Negative flag isn't right in third instruction for %s.", addressing); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x70, readY(&cpu), msg1);                             \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS(&cpu) & ZM, msg2);                       \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS(&cpu) & NM, msg3);                       \
    }

#include "../templates/testTemplate.h"

#endif  // TEST_H