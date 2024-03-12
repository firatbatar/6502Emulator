#include "../../../include/cpu.h"
#include "../../../include/instructions.h"
#include "../../src/unity.h"
#include "../../src/unity_internals.h"

/**
 * ORA performs an inclusive or on the accumulator
 * Result is written in to the accumulator
 * Zero and Negative flag are affected
 */

/** Each test will perform three ORA instructions
 * 1. ORA with (0000 0000)
 * 2. ORA with (0101 0101)
 * 3. ORA with (1010 1010)
 */
/** At the end of each instruction, 
 * 1. Accumulator: 0000 0000, Zero Flag: 1, Negative Flag: 0
 * 2. Accumulator: 0101 0101, Zero Flag: 0, Negative Flag: 0
 * 3. Accumulator: 1111 1111, Zero Flag: 0, Negative Flag: 1
*/


void setUp(void) {
    resetMemory(0xFF);  // Set everything in memory to 0xFF

    // Set the program start to 0x0200
    writeMemory(0xFFFC, 0x00);
    writeMemory(0xFFFD, 0x02);

    resetCPU();  // Reset the registers
}

void tearDown(void) {}

/** Test for immediate addressing */
void test_immediate(void) {
    writeMemory(0x0200, INS_ORA_IM);
    writeMemory(0x0201, 0x00);
    execute();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readA(), "A isn't right in first instruction for IM.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(ZM, readPS() & ZM, "Zero flag isn't right in first instruction for IM.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & NM, "Negative flag isn't right in first instruction for IM.");

    writeMemory(0x0202, INS_ORA_IM);
    writeMemory(0x0203, 0x55);
    execute();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readA(), "A isn't right in second instruction for IM.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & ZM, "Zero flag isn't right in second instruction for IM.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & NM, "Negative flag isn't right in second instruction for IM.");

    writeMemory(0x0204, INS_ORA_IM);
    writeMemory(0x0205, 0xAA);
    execute();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0xFF, readA(), "A isn't right in third instruction for IM.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & ZM, "Zero flag isn't right in third instruction for IM.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(NM, readPS() & NM, "Negative flag isn't right in third instruction for IM.");
}

/** Test for zero page addressing */
void test_zero_page(void) {
    writeMemory(0x0200, INS_ORA_ZP);
    writeMemory(0x0201, 0x01);
    writeMemory(0x0001, 0x00);
    execute();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readA(), "A isn't right in first instruction for ZP.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(ZM, readPS() & ZM, "Zero flag isn't right in first instruction for ZP.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & NM, "Negative flag isn't right in first instruction for ZP.");

    writeMemory(0x0202, INS_ORA_ZP);
    writeMemory(0x0203, 0x02);
    writeMemory(0x0002, 0x55);
    execute();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readA(), "A isn't right in second instruction for ZP.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & ZM, "Zero flag isn't right in second instruction for ZP.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & NM, "Negative flag isn't right in second instruction for ZP.");

    writeMemory(0x0204, INS_ORA_ZP);
    writeMemory(0x0205, 0x03);
    writeMemory(0x0003, 0xAA);
    execute();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0xFF, readA(), "A isn't right in third instruction for ZP.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & ZM, "Zero flag isn't right in third instruction for ZP.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(NM, readPS() & NM, "Negative flag isn't right in third instruction for ZP.");
}

/** Test for zero page,X addressing without wrapping */
void test_zero_page_x(void) {
    writeX(0x05);  // Start with 0x05 in the X register

    writeMemory(0x0200, INS_ORA_ZPX);
    writeMemory(0x0201, 0x10);
    writeMemory(0x0015, 0x00);
    execute();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readA(), "A isn't right in first instruction for ZP,X.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(ZM, readPS() & ZM, "Zero flag isn't right in first instruction for ZP,X.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & NM, "Negative flag isn't right in first instruction for ZP,X.");

    writeMemory(0x0202, INS_ORA_ZPX);
    writeMemory(0x0203, 0x20);
    writeMemory(0x0025, 0x55);
    execute();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readA(), "A isn't right in second instruction for ZP,X.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & ZM, "Zero flag isn't right in second instruction for ZP,X.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & NM, "Negative flag isn't right in second instruction for ZP,X.");

    writeMemory(0x0204, INS_ORA_ZPX);
    writeMemory(0x0205, 0x30);
    writeMemory(0x0035, 0xAA);
    execute();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0xFF, readA(), "A isn't right in third instruction for ZP,X.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & ZM, "Zero flag isn't right in third instruction for ZP,X.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(NM, readPS() & NM, "Negative flag isn't right in third instruction for ZP,X.");
}

/** Test for zero page,X addressing with wrapping */
void test_zero_page_x_wrap(void) {
    writeX(0xFF);  // Start with 0xFF in the X register

    writeMemory(0x0200, INS_ORA_ZPX);
    writeMemory(0x0201, 0x20);
    writeMemory(0x001F, 0x00);
    execute();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readA(), "A isn't right in first instruction for ZP,X with wrapping.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(ZM, readPS() & ZM, "Zero flag isn't right in first instruction for ZP,X with wrapping.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & NM, "Negative flag isn't right in first instruction for ZP,X with wrapping.");

    writeMemory(0x0202, INS_ORA_ZPX);
    writeMemory(0x0203, 0x30);
    writeMemory(0x002F, 0x55);
    execute();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readA(), "A isn't right in second instruction for ZP,X with wrapping.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & ZM, "Zero flag isn't right in second instruction for ZP,X with wrapping.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & NM, "Negative flag isn't right in second instruction for ZP,X with wrapping.");

    writeMemory(0x0204, INS_ORA_ZPX);
    writeMemory(0x0205, 0x40);
    writeMemory(0x003F, 0xAA);
    execute();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0xFF, readA(), "A isn't right in third instruction for ZP,X with wrapping.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & ZM, "Zero flag isn't right in third instruction for ZP,X with wrapping.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(NM, readPS() & NM, "Negative flag isn't right in third instruction for ZP,X with wrapping.");
}

/** Test for absolute addressing */
void test_absolute(void) {
    writeMemory(0x0200, INS_ORA_ABS);
    writeMemory(0x0201, 0x00);
    writeMemory(0x0202, 0x04);
    writeMemory(0x0400, 0x00);
    execute();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readA(), "A isn't right in first instruction for ABS.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(ZM, readPS() & ZM, "Zero flag isn't right in first instruction for ABS.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & NM, "Negative flag isn't right in first instruction for ABS.");

    writeMemory(0x0203, INS_ORA_ABS);
    writeMemory(0x0204, 0x10);
    writeMemory(0x0205, 0x04);
    writeMemory(0x0410, 0x55);
    execute();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readA(), "A isn't right in second instruction for ABS.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & ZM, "Zero flag isn't right in second instruction for ABS.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & NM, "Negative flag isn't right in second instruction for ABS.");

    writeMemory(0x0206, INS_ORA_ABS);
    writeMemory(0x0207, 0x20);
    writeMemory(0x0208, 0x04);
    writeMemory(0x0420, 0xAA);
    execute();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0xFF, readA(), "A isn't right in third instruction for ABS.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & ZM, "Zero flag isn't right in third instruction for ABS.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(NM, readPS() & NM, "Negative flag isn't right in third instruction for ABS.");
}

/** Test for absolute,X addressing */
void test_absolute_x(void) {
    writeX(0x05);  // Start with 0x05 in the X register

    writeMemory(0x0200, INS_ORA_ABSX);
    writeMemory(0x0201, 0x00);
    writeMemory(0x0202, 0x04);
    writeMemory(0x0405, 0x00);
    execute();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readA(), "A isn't right in first instruction for ABS,X.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(ZM, readPS() & ZM, "Zero flag isn't right in first instruction for ABS,X.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & NM, "Negative flag isn't right in first instruction for ABS,X.");

    writeMemory(0x0203, INS_ORA_ABSX);
    writeMemory(0x0204, 0x10);
    writeMemory(0x0205, 0x04);
    writeMemory(0x0415, 0x55);
    execute();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readA(), "A isn't right in second instruction for ABS,X.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & ZM, "Zero flag isn't right in second instruction for ABS,X.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & NM, "Negative flag isn't right in second instruction for ABS,X.");

    writeMemory(0x0206, INS_ORA_ABSX);
    writeMemory(0x0207, 0x20);
    writeMemory(0x0208, 0x04);
    writeMemory(0x0425, 0xAA);
    execute();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0xFF, readA(), "A isn't right in third instruction for ABS,X.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & ZM, "Zero flag isn't right in third instruction for ABS,X.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(NM, readPS() & NM, "Negative flag isn't right in third instruction for ABS,X.");
}

/** Test for indexed inderect addressing */
void test_indexed_inderect(void) {
    writeX(0x05);  // Start with 0x05 in the X register

    writeMemory(0x0200, INS_ORA_INDX);
    writeMemory(0x0201, 0x10);
    writeMemory(0x0015, 0x00);
    writeMemory(0x0016, 0x04);
    writeMemory(0x0400, 0x00);
    execute();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readA(), "A isn't right in first instruction for INDX.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(ZM, readPS() & ZM, "Zero flag isn't right in first instruction for INDX.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & NM, "Negative flag isn't right in first instruction for INDX.");

    writeMemory(0x0202, INS_ORA_INDX);
    writeMemory(0x0203, 0x20);
    writeMemory(0x0025, 0x10);
    writeMemory(0x0026, 0x04);
    writeMemory(0x0410, 0x55);
    execute();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readA(), "A isn't right in second instruction for INDX.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & ZM, "Zero flag isn't right in second instruction for INDX.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & NM, "Negative flag isn't right in second instruction for INDX.");

    writeMemory(0x0204, INS_ORA_INDX);
    writeMemory(0x0205, 0x30);
    writeMemory(0x0035, 0x20);
    writeMemory(0x0036, 0x04);
    writeMemory(0x0420, 0xAA);
    execute();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0xFF, readA(), "A isn't right in third instruction for INDX.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & ZM, "Zero flag isn't right in third instruction for INDX.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(NM, readPS() & NM, "Negative flag isn't right in third instruction for INDX.");
}

/** Test for indexed indirect addressing with wrap */
void test_indexed_indirect_wrap(void) {
    writeX(0xFF);  // Start with 0xFF in the X register

    writeMemory(0x0200, INS_ORA_INDX);
    writeMemory(0x0201, 0x10);
    writeMemory(0x000F, 0x00);
    writeMemory(0x0010, 0x04);
    writeMemory(0x0400, 0x00);
    execute();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readA(), "A isn't right in first instruction for INDX with wrap.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(ZM, readPS() & ZM, "Zero flag isn't right in first instruction for INDX with wrap.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & NM, "Negative flag isn't right in first instruction for INDX with wrap.");

    writeMemory(0x0202, INS_ORA_INDX);
    writeMemory(0x0203, 0x20);
    writeMemory(0x001F, 0x10);
    writeMemory(0x0020, 0x04);
    writeMemory(0x0410, 0x55);
    execute();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readA(), "A isn't right in second instruction for INDX with wrap.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & ZM, "Zero flag isn't right in second instruction for INDX with wrap.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & NM, "Negative flag isn't right in second instruction for INDX with wrap.");

    writeMemory(0x0204, INS_ORA_INDX);
    writeMemory(0x0205, 0x30);
    writeMemory(0x002F, 0x20);
    writeMemory(0x0030, 0x04);
    writeMemory(0x0420, 0xAA);
    execute();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0xFF, readA(), "A isn't right in third instruction for INDX with wrap.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & ZM, "Zero flag isn't right in third instruction for INDX with wrap.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(NM, readPS() & NM, "Negative flag isn't right in third instruction for INDX with wrap.");
}

/** Test for indirect indexed addressing */
void test_indirect_indexed(void) {
    writeY(0x05);  // Start with 0x05 in the Y register

    writeMemory(0x0200, INS_ORA_INDY);
    writeMemory(0x0201, 0x10);
    writeMemory(0x0010, 0x00);
    writeMemory(0x0011, 0x04);
    writeMemory(0x0405, 0x00);
    execute();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readA(), "A isn't right in first instruction for INDY.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(ZM, readPS() & ZM, "Zero flag isn't right in first instruction for INDY.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & NM, "Negative flag isn't right in first instruction for INDY.");

    writeMemory(0x0202, INS_ORA_INDY);
    writeMemory(0x0203, 0x20);
    writeMemory(0x0020, 0x10);
    writeMemory(0x0021, 0x04);
    writeMemory(0x0415, 0x55);
    execute();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readA(), "A isn't right in second instruction for INDY.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & ZM, "Zero flag isn't right in second instruction for INDY.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & NM, "Negative flag isn't right in second instruction for INDY.");

    writeMemory(0x0204, INS_ORA_INDY);
    writeMemory(0x0205, 0x30);
    writeMemory(0x0030, 0x20);
    writeMemory(0x0031, 0x04);
    writeMemory(0x0425, 0xAA);
    execute();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0xFF, readA(), "A isn't right in third instruction for INDY.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x00, readPS() & ZM, "Zero flag isn't right in third instruction for INDY.");
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(NM, readPS() & NM, "Negative flag isn't right in third instruction for INDY.");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_immediate);
    RUN_TEST(test_zero_page);
    RUN_TEST(test_zero_page_x);
    RUN_TEST(test_zero_page_x_wrap);
    RUN_TEST(test_absolute);
    RUN_TEST(test_absolute_x);
    RUN_TEST(test_indexed_inderect);
    RUN_TEST(test_indirect_indexed);
    return UNITY_END();
}