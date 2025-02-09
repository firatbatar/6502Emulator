#ifndef TEST_H
#define TEST_H

/**
 * LDX loads the value from memory into the X register
 * Zero and Negative flag are affected
 */

/** Each test will perform three LDX instructions
 * 1. LDX with (0000 0000) -> FIRST_DATA
 * 2. LDX with (1000 0000) -> SECOND_DATA
 * 3. LDX with (0100 0000) -> THIRD_DATA
 */
/** At the end of each instruction,
 * X starts as (0000 0001)
 * 1. X Register: 0000 0000, Zero Flag: 1, Negative Flag: 0 -> FIRST_INSTRUCTION_TEST
 * 2. X Register: 1000 0000, Zero Flag: 0, Negative Flag: 1 -> SECOND_INSTRUCTION_TEST
 * 3. X Register: 0100 0000, Zero Flag: 0, Negative Flag: 0 -> THIRD_INSTRUCTION_TEST
 */

#include <cpu.h>
#include <initCPU.h>
#include <opcodes.h>
#include <unity.h>
#include <unity_internals.h>

#define SETUP_CONFIG_C writeX(&cpu, 0x01);
#define TEARDOWN_CONFIG_C

#define INSTRUCTION_IM INS_LDX_IM
#define INSTRUCTION_ZP INS_LDX_ZP
#define INSTRUCTION_ZPY INS_LDX_ZPY
#define INSTRUCTION_ABS INS_LDX_ABS
#define INSTRUCTION_ABSY INS_LDX_ABSY

#define FIRST_DATA 0x00
#define SECOND_DATA 0x80
#define THIRD_DATA 0x70

#define UNPACK_TESTS

#define FIRST_INSTRUCTION_TEST(addressing)                                               \
  {                                                                                      \
    char msg1[100], msg2[100], msg3[100];                                                \
    sprintf(msg1, "X isn't right in first instruction for %s.", addressing);             \
    sprintf(msg2, "Zero flag isn't right in first instruction for %s.", addressing);     \
    sprintf(msg3, "Negative flag isn't right in first instruction for %s.", addressing); \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readX(&cpu), msg1);                             \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(ZM, readPS(&cpu) & ZM, msg2);                         \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS(&cpu) & NM, msg3);                       \
  }

#define SECOND_INSTRUCTION_TEST(addressing)                                               \
  {                                                                                       \
    char msg1[100], msg2[100], msg3[100];                                                 \
    sprintf(msg1, "X isn't right in second instruction for %s.", addressing);             \
    sprintf(msg2, "Zero flag isn't right in second instruction for %s.", addressing);     \
    sprintf(msg3, "Negative flag isn't right in second instruction for %s.", addressing); \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x80, readX(&cpu), msg1);                              \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS(&cpu) & ZM, msg2);                        \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(NM, readPS(&cpu) & NM, msg3);                          \
  }

#define THIRD_INSTRUCTION_TEST(addressing)                                               \
  {                                                                                      \
    char msg1[100], msg2[100], msg3[100];                                                \
    sprintf(msg1, "X isn't right in third instruction for %s.", addressing);             \
    sprintf(msg2, "Zero flag isn't right in third instruction for %s.", addressing);     \
    sprintf(msg3, "Negative flag isn't right in third instruction for %s.", addressing); \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x70, readX(&cpu), msg1);                             \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS(&cpu) & ZM, msg2);                       \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS(&cpu) & NM, msg3);                       \
  }

#include <testTemplate.h>

#endif  // TEST_H