#ifndef TEST_H
#define TEST_H

/**
 * Compares the value in the X register with the value in memory
 * Does not change the X register
 * Carry, Zero and Negative flags are affected
 */

/** Each test will perform three CPX instructions
 * X register will start as (0000 1111)
 * 1. CPX with (0000 1111) -> FIRST_DATA
 * 2. CPX with (0000 0000) -> SECOND_DATA
 * 3. CPX with (0111 1111) -> THIRD_DATA
 */
/** At the end of each instruction,
 * 1. X register: 0x0F, Carry Flag: 1, Zero Flag: 1, Negative Flag: 0
 * 2. X register: 0x0F, Carry Flag: 1, Zero Flag: 0, Negative Flag: 0
 * 3. X register: 0x0F, Carry Flag: 0, Zero Flag: 0, Negative Flag: 1
 */

#include <cpu.h>
#include <initCPU.h>
#include <opcodes.h>
#include <unity.h>
#include <unity_internals.h>

#define SETUP_CONFIG_C writeX(&cpu, 0x0F);
#define TEARDOWN_CONFIG_C

#define INSTRUCTION_IM INS_CPX_IM
#define INSTRUCTION_ZP INS_CPX_ZP
#define INSTRUCTION_ABS INS_CPX_ABS

#define FIRST_DATA 0x0F
#define SECOND_DATA 0x00
#define THIRD_DATA 0x7F

#define UNPACK_TESTS

#define FIRST_INSTRUCTION_TEST(addressing)                                               \
  {                                                                                      \
    char msg1[100], msg2[100], msg3[100], msg4[100];                                     \
                                                                                         \
    sprintf(msg1, "X isn't right in first instruction for %s.", addressing);             \
    sprintf(msg2, "Carry flag isn't right in first instruction for %s.", addressing);    \
    sprintf(msg3, "Zero flag isn't right in first instruction for %s.", addressing);     \
    sprintf(msg4, "Negative flag isn't right in first instruction for %s.", addressing); \
                                                                                         \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x0F, readX(&cpu), msg1);                             \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(CM, readPS(&cpu) & CM, msg2);                         \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(ZM, readPS(&cpu) & ZM, msg3);                         \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS(&cpu) & NM, msg4);                       \
  }

#define SECOND_INSTRUCTION_TEST(addressing)                                               \
  {                                                                                       \
    char msg1[100], msg2[100], msg3[100], msg4[100];                                      \
                                                                                          \
    sprintf(msg1, "X isn't right in second instruction for %s.", addressing);             \
    sprintf(msg2, "Carry flag isn't right in second instruction for %s.", addressing);    \
    sprintf(msg3, "Zero flag isn't right in second instruction for %s.", addressing);     \
    sprintf(msg4, "Negative flag isn't right in second instruction for %s.", addressing); \
                                                                                          \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x0F, readX(&cpu), msg1);                              \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(CM, readPS(&cpu) & CM, msg2);                          \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS(&cpu) & ZM, msg3);                        \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS(&cpu) & NM, msg4);                        \
  }

#define THIRD_INSTRUCTION_TEST(addressing)                                               \
  {                                                                                      \
    char msg1[100], msg2[100], msg3[100], msg4[100];                                     \
                                                                                         \
    sprintf(msg1, "X isn't right in third instruction for %s.", addressing);             \
    sprintf(msg2, "Carry flag isn't right in third instruction for %s.", addressing);    \
    sprintf(msg3, "Zero flag isn't right in third instruction for %s.", addressing);     \
    sprintf(msg4, "Negative flag isn't right in third instruction for %s.", addressing); \
                                                                                         \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x0F, readX(&cpu), msg1);                             \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS(&cpu) & CM, msg2);                       \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS(&cpu) & ZM, msg3);                       \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(NM, readPS(&cpu) & NM, msg4);                         \
  }

#include <testTemplate.h>

#endif  // TEST_H