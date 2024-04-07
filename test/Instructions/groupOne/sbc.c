#ifndef _TEST_H
#define _TEST_H

/**
 * Subtracts the contents of a memory location to the accumulator
 * Result is written into the accumulator
 * Carry, Overflow, Zero and Negative flags are affected
 */

/** Each test will perform three SBC instructions
 * Accumulator is set to 0x7F and carry flag is set to 1
 * 1. SBC with (0111 1111) -> FIRST_DATA
 * 2. SBC with (1111 0001) -> SECOND_DATA
 * 3. SBC with (1000 0000) -> THIRD_DATA
 */
/** At the end of each instruction,
 * 1. Accumulator: 0x00, Carry Flag: 1, Overflow Flag: 0, Zero Flag: 1, Negative Flag: 0 -> FIRST_INSTRUCTION_TEST
 * 2. Accumulator: 0x0F, Carry Flag: 0, Overflow Flag: 0, Zero Flag: 0, Negative Flag: 0 -> SECOND_INSTRUCTION_TEST
 * 3 Accumulator: 0x8E, Carry Flag: 0, Overflow Flag: 1, Zero Flag: 0, Negative Flag: 1 -> THIRD_INSTRUCTION_TEST
 */

#include "../../../include/cpu.h"
#include "../../../include/instructions.h"
#include "../../src/unity.h"
#include "../../src/unity_internals.h"

#define SETUP_CONFIG_C      \
    writePS(readPS() | CM); \
    writeA(0x7F);
#define TEARDOWN_CONFIG_C

#define INSTRUCTION_IM INS_SBC_IM
#define INSTRUCTION_ZP INS_SBC_ZP
#define INSTRUCTION_ZPX INS_SBC_ZPX
#define INSTRUCTION_ABS INS_SBC_ABS
#define INSTRUCTION_ABSX INS_SBC_ABSX
#define INSTRUCTION_ABSY INS_SBC_ABSY
#define INSTRUCTION_INDX INS_SBC_INDX
#define INSTRUCTION_INDY INS_SBC_INDY

#define FIRST_DATA 0x7F
#define SECOND_DATA 0xF1
#define THIRD_DATA 0x80

#define UNPACK_TESTS

#define FIRST_INSTRUCTION_TEST(addressing)                                                   \
    {                                                                                        \
        char msg1[100], msg2[100], msg3[100], msg4[100], msg5[100];                          \
        sprintf(msg1, "A isn't right in first instruction for %s.", addressing);             \
        sprintf(msg2, "Carry flag isn't right in first instruction for %s.", addressing);    \
        sprintf(msg3, "Overflow flag isn't right in first instruction for %s.", addressing); \
        sprintf(msg4, "Zero flag isn't right in first instruction for %s.", addressing);     \
        sprintf(msg5, "Negative flag isn't right in first instruction for %s.", addressing); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readA(), msg1);                                 \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(CM, readPS() & CM, msg2);                             \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & VM, msg3);                           \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(ZM, readPS() & ZM, msg4);                             \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & NM, msg5);                           \
    }

#define SECOND_INSTRUCTION_TEST(addressing)                                                   \
    {                                                                                         \
        char msg1[100], msg2[100], msg3[100], msg4[100], msg5[100];                           \
        sprintf(msg1, "A isn't right in second instruction for %s.", addressing);             \
        sprintf(msg2, "Carry flag isn't right in second instruction for %s.", addressing);    \
        sprintf(msg3, "Overflow flag isn't right in second instruction for %s.", addressing); \
        sprintf(msg4, "Zero flag isn't right in second instruction for %s.", addressing);     \
        sprintf(msg5, "Negative flag isn't right in second instruction for %s.", addressing); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x0F, readA(), msg1);                                  \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & CM, msg2);                            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & VM, msg3);                            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & ZM, msg4);                            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & NM, msg5);                            \
    }

#define THIRD_INSTRUCTION_TEST(addressing)                                                   \
    {                                                                                        \
        char msg1[100], msg2[100], msg3[100], msg4[100], msg5[100];                          \
        sprintf(msg1, "A isn't right in third instruction for %s.", addressing);             \
        sprintf(msg2, "Carry flag isn't right in third instruction for %s.", addressing);    \
        sprintf(msg3, "Overflow flag isn't right in third instruction for %s.", addressing); \
        sprintf(msg4, "Zero flag isn't right in third instruction for %s.", addressing);     \
        sprintf(msg5, "Negative flag isn't right in third instruction for %s.", addressing); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x8E, readA(), msg1);                                 \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & CM, msg2);                           \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(VM, readPS() & VM, msg3);                             \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & ZM, msg4);                           \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(NM, readPS() & NM, msg5);                             \
    }

#include "../templates/testTemplate.h"

#endif  // _TEST_H