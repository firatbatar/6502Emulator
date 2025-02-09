#ifndef TEST_H
#define TEST_H

/**
 * Adds the value of memory and carry flag the accumulator
 * Result is writtion into the accumulator.
 * Carry, Overflow, Zero and Negative flags are affected
 */

/** Each test will perform three ADC instructions
 * Accumulator is set to 0x00 and carry flag is set to 1
 * 1. ADC with (0111 1110) -> FIRST_DATA
 * 2. ADC with (0000 0001) -> SECOND_DATA
 * 3. ADC with (1000 0000) -> THIRD_DATA
 */
/** At the end of each instruction,
 * 1. Accumulator: 0111 1111, Carry Flag: 0, Overflow Flag: 0, Zero Flag: 0, Negative Flag: 0 ->
 * FIRST_INSTRUCTION_TEST
 * 2. Accumulator: 1000 0000, Carry Flag: 0, Overflow Flag: 1, Zero Flag: 0, Negative Flag: 1 ->
 * SECOND_INSTRUCTION_TEST
 * 3. Accumulator: 0000 0000, Carry Flag: 1, Overflow Flag: 1, Zero Flag: 1, Negative Flag: 0 ->
 * THIRD_INSTRUCTION_TEST
 */

#include <cpu.h>
#include <initCPU.h>
#include <opcodes.h>
#include <unity.h>
#include <unity_internals.h>

#define SETUP_CONFIG_C writePS(&cpu, readPS(&cpu) | CM);
#define TEARDOWN_CONFIG_C

#define INSTRUCTION_IM INS_ADC_IM
#define INSTRUCTION_ZP INS_ADC_ZP
#define INSTRUCTION_ZPX INS_ADC_ZPX
#define INSTRUCTION_ABS INS_ADC_ABS
#define INSTRUCTION_ABSX INS_ADC_ABSX
#define INSTRUCTION_ABSY INS_ADC_ABSY
#define INSTRUCTION_INDX INS_ADC_INDX
#define INSTRUCTION_INDY INS_ADC_INDY

#define FIRST_DATA 0x7E
#define SECOND_DATA 0x01
#define THIRD_DATA 0x80

#define UNPACK_TESTS

#define FIRST_INSTRUCTION_TEST(addressing)                                               \
  {                                                                                      \
    char msg1[100], msg2[100], msg3[100], msg4[100], msg5[100];                          \
    sprintf(msg1, "A isn't right in first instruction for %s.", addressing);             \
    sprintf(msg2, "Carry flag isn't right in first instruction for %s.", addressing);    \
    sprintf(msg3, "Overflow flag isn't right in first instruction for %s.", addressing); \
    sprintf(msg4, "Zero flag isn't right in first instruction for %s.", addressing);     \
    sprintf(msg5, "Negative flag isn't right in first instruction for %s.", addressing); \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x7F, readA(&cpu), msg1);                             \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS(&cpu) & CM, msg2);                       \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS(&cpu) & VM, msg3);                       \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS(&cpu) & ZM, msg4);                       \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS(&cpu) & NM, msg5);                       \
  }

#define SECOND_INSTRUCTION_TEST(addressing)                                               \
  {                                                                                       \
    char msg1[100], msg2[100], msg3[100], msg4[100], msg5[100];                           \
    sprintf(msg1, "A isn't right in second instruction for %s.", addressing);             \
    sprintf(msg2, "Carry flag isn't right in second instruction for %s.", addressing);    \
    sprintf(msg3, "Overflow flag isn't right in second instruction for %s.", addressing); \
    sprintf(msg4, "Zero flag isn't right in second instruction for %s.", addressing);     \
    sprintf(msg5, "Negative flag isn't right in second instruction for %s.", addressing); \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x80, readA(&cpu), msg1);                              \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS(&cpu) & CM, msg2);                        \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(VM, readPS(&cpu) & VM, msg3);                          \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS(&cpu) & ZM, msg4);                        \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(NM, readPS(&cpu) & NM, msg5);                          \
  }

#define THIRD_INSTRUCTION_TEST(addressing)                                               \
  {                                                                                      \
    char msg1[100], msg2[100], msg3[100], msg4[100], msg5[100];                          \
    sprintf(msg1, "A isn't right in third instruction for %s.", addressing);             \
    sprintf(msg2, "Carry flag isn't right in third instruction for %s.", addressing);    \
    sprintf(msg3, "Overflow flag isn't right in third instruction for %s.", addressing); \
    sprintf(msg4, "Zero flag isn't right in third instruction for %s.", addressing);     \
    sprintf(msg5, "Negative flag isn't right in third instruction for %s.", addressing); \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readA(&cpu), msg1);                             \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(CM, readPS(&cpu) & CM, msg2);                         \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(VM, readPS(&cpu) & VM, msg3);                         \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(ZM, readPS(&cpu) & ZM, msg4);                         \
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS(&cpu) & NM, msg5);                       \
  }

#include <testTemplate.h>

#endif  // TEST_H