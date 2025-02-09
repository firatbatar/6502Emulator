#ifndef TEST_H
#define TEST_H

/**
 * Compares the value in the accumulator with the value in memory
 * Does not change the accumulator
 * Carry, Zero and Negative flags are affected
 */

/** Each test will perform three CMP instructions
 * Accumulator will start as (0000 1111)
 * 1. CMP with (0000 1111) -> FIRST_DATA
 * 2. CMP with (0000 0000) -> SECOND_DATA
 * 3. CMP with (0111 1111) -> THIRD_DATA
 */
/** At the end of each instruction,
 * 1. Accumulator: 0x0F, Carry Flag: 1, Zero Flag: 1, Negative Flag: 0
 * 2. Accumulator: 0x0F, Carry Flag: 1, Zero Flag: 0, Negative Flag: 0
 * 3. Accumulator: 0x0F, Carry Flag: 0, Zero Flag: 0, Negative Flag: 1
 */

#include <cpu.h>
#include <initCPU.h>
#include <opcodes.h>
#include <unity.h>
#include <unity_internals.h>

#define SETUP_CONFIG_C writeA(&cpu, 0x0F);
#define TEARDOWN_CONFIG_C

#define INSTRUCTION_IM INS_CMP_IM
#define INSTRUCTION_ZP INS_CMP_ZP
#define INSTRUCTION_ZPX INS_CMP_ZPX
#define INSTRUCTION_ABS INS_CMP_ABS
#define INSTRUCTION_ABSX INS_CMP_ABSX
#define INSTRUCTION_ABSY INS_CMP_ABSY
#define INSTRUCTION_INDX INS_CMP_INDX
#define INSTRUCTION_INDY INS_CMP_INDY

#define FIRST_DATA 0x0F
#define SECOND_DATA 0x00
#define THIRD_DATA 0x7F

#define UNPACK_TESTS

#define FIRST_INSTRUCTION_TEST(addressing)                                               \
  {                                                                                      \
    char msg1[100], msg2[100], msg3[100], msg4[100];                                     \
                                                                                         \
    sprintf(msg1, "A isn't right in first instruction for %s.", addressing);             \
    sprintf(msg2, "Carry flag isn't right in first instruction for %s.", addressing);    \
    sprintf(msg3, "Zero flag isn't right in first instruction for %s.", addressing);     \
    sprintf(msg4, "Negative flag isn't right in first instruction for %s.", addressing); \
                                                                                         \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x0F, readA(&cpu), msg1);                             \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(CM, readPS(&cpu) & CM, msg2);                         \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(ZM, readPS(&cpu) & ZM, msg3);                         \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS(&cpu) & NM, msg4);                       \
  }

#define SECOND_INSTRUCTION_TEST(addressing)                                               \
  {                                                                                       \
    char msg1[100], msg2[100], msg3[100], msg4[100];                                      \
                                                                                          \
    sprintf(msg1, "A isn't right in second instruction for %s.", addressing);             \
    sprintf(msg2, "Carry flag isn't right in second instruction for %s.", addressing);    \
    sprintf(msg3, "Zero flag isn't right in second instruction for %s.", addressing);     \
    sprintf(msg4, "Negative flag isn't right in second instruction for %s.", addressing); \
                                                                                          \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x0F, readA(&cpu), msg1);                              \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(CM, readPS(&cpu) & CM, msg2);                          \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS(&cpu) & ZM, msg3);                        \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS(&cpu) & NM, msg4);                        \
  }

#define THIRD_INSTRUCTION_TEST(addressing)                                               \
  {                                                                                      \
    char msg1[100], msg2[100], msg3[100], msg4[100];                                     \
                                                                                         \
    sprintf(msg1, "A isn't right in third instruction for %s.", addressing);             \
    sprintf(msg2, "Carry flag isn't right in third instruction for %s.", addressing);    \
    sprintf(msg3, "Zero flag isn't right in third instruction for %s.", addressing);     \
    sprintf(msg4, "Negative flag isn't right in third instruction for %s.", addressing); \
                                                                                         \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x0F, readA(&cpu), msg1);                             \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS(&cpu) & CM, msg2);                       \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS(&cpu) & ZM, msg3);                       \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(NM, readPS(&cpu) & NM, msg4);                         \
  }

#include <testTemplate.h>

#endif  // TEST_H