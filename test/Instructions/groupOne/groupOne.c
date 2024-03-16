#ifdef _TEST_GROUP_ONE_H
#ifdef SETUP_CONFIG
#ifdef TEARDOWN_CONFIG
#ifdef FIRST_DATA
#ifdef SECOND_DATA
#ifdef THIRD_DATA
#ifdef FIRST_INSTRUCTION_TEST
#ifdef SECOND_INSTRUCTION_TEST
#ifdef THIRD_INSTRUCTION_TEST

#include "../../../include/cpu.h"
#include "../../../include/instructions.h"
#include "../../src/unity.h"
#include "../../src/unity_internals.h"

void setUp(void) {
    resetMemory(0xFF);  // Set everything in memory to 0xFF

    // Set the program start to 0x0200
    writeMemory(0xFFFC, 0x00);
    writeMemory(0xFFFD, 0x02);

    resetCPU();  // Reset the registers

    SETUP_CONFIG
}

void tearDown(void) { TEARDOWN_CONFIG }

#ifdef INSTRUCTION_IM
/** Test for immediate addressing */
void test_immediate(void) {
    writeMemory(0x0200, INSTRUCTION_IM);
    writeMemory(0x0201, FIRST_DATA);
    execute();
    FIRST_INSTRUCTION_TEST("IM");

    writeMemory(0x0202, INSTRUCTION_IM);
    writeMemory(0x0203, SECOND_DATA);
    execute();
    SECOND_INSTRUCTION_TEST("IM");

    writeMemory(0x0204, INSTRUCTION_IM);
    writeMemory(0x0205, THIRD_DATA);
    execute();
    THIRD_INSTRUCTION_TEST("IM");
}
#endif

#ifdef INSTRUCTION_ZP
/** Test for zero page addressing */
void test_zero_page(void) {
    writeMemory(0x0200, INSTRUCTION_ZP);
    writeMemory(0x0201, 0x01);
    writeMemory(0x0001, FIRST_DATA);
    execute();
    FIRST_INSTRUCTION_TEST("ZP");

    writeMemory(0x0202, INSTRUCTION_ZP);
    writeMemory(0x0203, 0x02);
    writeMemory(0x0002, SECOND_DATA);
    execute();
    SECOND_INSTRUCTION_TEST("ZP");

    writeMemory(0x0204, INSTRUCTION_ZP);
    writeMemory(0x0205, 0x03);
    writeMemory(0x0003, THIRD_DATA);
    execute();
    THIRD_INSTRUCTION_TEST("ZP");
}
#endif

#ifdef INSTRUCTION_ZPX
/** Test for zero page,X addressing without wrapping */
void test_zero_page_x(void) {
    writeX(0x05);  // Start with 0x05 in the X register

    writeMemory(0x0200, INSTRUCTION_ZPX);
    writeMemory(0x0201, 0x10);
    writeMemory(0x0015, FIRST_DATA);
    execute();
    FIRST_INSTRUCTION_TEST("ZP,X");

    writeMemory(0x0202, INSTRUCTION_ZPX);
    writeMemory(0x0203, 0x20);
    writeMemory(0x0025, SECOND_DATA);
    execute();
    SECOND_INSTRUCTION_TEST("ZP,X");

    writeMemory(0x0204, INSTRUCTION_ZPX);
    writeMemory(0x0205, 0x30);
    writeMemory(0x0035, THIRD_DATA);
    execute();
    THIRD_INSTRUCTION_TEST("ZP,X");
}
#endif

#ifdef INSTRUCTION_ZPX
/** Test for zero page,X addressing with wrapping */
void test_zero_page_x_wrap(void) {
    writeX(0xFF);  // Start with 0xFF in the X register

    writeMemory(0x0200, INSTRUCTION_ZPX);
    writeMemory(0x0201, 0x20);
    writeMemory(0x001F, FIRST_DATA);
    execute();
    FIRST_INSTRUCTION_TEST("ZP,X with wrapping");

    writeMemory(0x0202, INSTRUCTION_ZPX);
    writeMemory(0x0203, 0x30);
    writeMemory(0x002F, SECOND_DATA);
    execute();
    SECOND_INSTRUCTION_TEST("ZP,X with wrapping");

    writeMemory(0x0204, INSTRUCTION_ZPX);
    writeMemory(0x0205, 0x40);
    writeMemory(0x003F, THIRD_DATA);
    execute();
    THIRD_INSTRUCTION_TEST("ZP,X with wrapping");
}
#endif

#ifdef INSTRUCTION_ABS
/** Test for absolute addressing */
void test_absolute(void) {
    writeMemory(0x0200, INSTRUCTION_ABS);
    writeMemory(0x0201, 0x00);
    writeMemory(0x0202, 0x04);
    writeMemory(0x0400, FIRST_DATA);
    execute();
    FIRST_INSTRUCTION_TEST("ABS");

    writeMemory(0x0203, INSTRUCTION_ABS);
    writeMemory(0x0204, 0x10);
    writeMemory(0x0205, 0x04);
    writeMemory(0x0410, SECOND_DATA);
    execute();
    SECOND_INSTRUCTION_TEST("ABS");

    writeMemory(0x0206, INSTRUCTION_ABS);
    writeMemory(0x0207, 0x20);
    writeMemory(0x0208, 0x04);
    writeMemory(0x0420, THIRD_DATA);
    execute();
    THIRD_INSTRUCTION_TEST("ABS");
}
#endif

#ifdef INSTRUCTION_ABSX
/** Test for absolute,X addressing */
void test_absolute_x(void) {
    writeX(0x05);  // Start with 0x05 in the X register

    writeMemory(0x0200, INSTRUCTION_ABSX);
    writeMemory(0x0201, 0x00);
    writeMemory(0x0202, 0x04);
    writeMemory(0x0405, FIRST_DATA);
    execute();
    FIRST_INSTRUCTION_TEST("ABS,X");

    writeMemory(0x0203, INSTRUCTION_ABSX);
    writeMemory(0x0204, 0x10);
    writeMemory(0x0205, 0x04);
    writeMemory(0x0415, SECOND_DATA);
    execute();
    SECOND_INSTRUCTION_TEST("ABS,X");

    writeMemory(0x0206, INSTRUCTION_ABSX);
    writeMemory(0x0207, 0x20);
    writeMemory(0x0208, 0x04);
    writeMemory(0x0425, THIRD_DATA);
    execute();
    THIRD_INSTRUCTION_TEST("ABS,X");
}
#endif

#ifdef INSTRUCTION_INDX
/** Test for indexed inderect addressing */
void test_indexed_inderect(void) {
    writeX(0x05);  // Start with 0x05 in the X register

    writeMemory(0x0200, INSTRUCTION_INDX);
    writeMemory(0x0201, 0x10);
    writeMemory(0x0015, 0x00);
    writeMemory(0x0016, 0x04);
    writeMemory(0x0400, FIRST_DATA);
    execute();
    FIRST_INSTRUCTION_TEST("INDX");

    writeMemory(0x0202, INSTRUCTION_INDX);
    writeMemory(0x0203, 0x20);
    writeMemory(0x0025, 0x10);
    writeMemory(0x0026, 0x04);
    writeMemory(0x0410, SECOND_DATA);
    execute();
    SECOND_INSTRUCTION_TEST("INDX");

    writeMemory(0x0204, INSTRUCTION_INDX);
    writeMemory(0x0205, 0x30);
    writeMemory(0x0035, 0x20);
    writeMemory(0x0036, 0x04);
    writeMemory(0x0420, THIRD_DATA);
    execute();
    THIRD_INSTRUCTION_TEST("INDX");
}
#endif

#ifdef INSTRUCTION_INDX
/** Test for indexed indirect addressing with wrap */
void test_indexed_indirect_wrap(void) {
    writeX(0xFF);  // Start with 0xFF in the X register

    writeMemory(0x0200, INSTRUCTION_INDX);
    writeMemory(0x0201, 0x10);
    writeMemory(0x000F, 0x00);
    writeMemory(0x0010, 0x04);
    writeMemory(0x0400, FIRST_DATA);
    execute();
    FIRST_INSTRUCTION_TEST("INDX with wrap");

    writeMemory(0x0202, INSTRUCTION_INDX);
    writeMemory(0x0203, 0x20);
    writeMemory(0x001F, 0x10);
    writeMemory(0x0020, 0x04);
    writeMemory(0x0410, SECOND_DATA);
    execute();
    SECOND_INSTRUCTION_TEST("INDX with wrap");

    writeMemory(0x0204, INSTRUCTION_INDX);
    writeMemory(0x0205, 0x30);
    writeMemory(0x002F, 0x20);
    writeMemory(0x0030, 0x04);
    writeMemory(0x0420, THIRD_DATA);
    execute();
    THIRD_INSTRUCTION_TEST("INDX with wrap");
}
#endif

#ifdef INSTRUCTION_INDY
/** Test for indirect indexed addressing */
void test_indirect_indexed(void) {
    writeY(0x05);  // Start with 0x05 in the Y register

    writeMemory(0x0200, INSTRUCTION_INDY);
    writeMemory(0x0201, 0x10);
    writeMemory(0x0010, 0x00);
    writeMemory(0x0011, 0x04);
    writeMemory(0x0405, FIRST_DATA);
    execute();
    FIRST_INSTRUCTION_TEST("INDY");

    writeMemory(0x0202, INSTRUCTION_INDY);
    writeMemory(0x0203, 0x20);
    writeMemory(0x0020, 0x10);
    writeMemory(0x0021, 0x04);
    writeMemory(0x0415, SECOND_DATA);
    execute();
    SECOND_INSTRUCTION_TEST("INDY");

    writeMemory(0x0204, INSTRUCTION_INDY);
    writeMemory(0x0205, 0x30);
    writeMemory(0x0030, 0x20);
    writeMemory(0x0031, 0x04);
    writeMemory(0x0425, THIRD_DATA);
    execute();
    THIRD_INSTRUCTION_TEST("INDY");
}
#endif

int main(void) {
    UNITY_BEGIN();
    #ifdef INSTRUCTION_IM
    RUN_TEST(test_immediate);
    #endif
    #ifdef INSTRUCTION_ZP
    RUN_TEST(test_zero_page);
    #endif
    #ifdef INSTRUCTION_ZPX
    RUN_TEST(test_zero_page_x);
    RUN_TEST(test_zero_page_x_wrap);
    #endif
    #ifdef INSTRUCTION_ABS
    RUN_TEST(test_absolute);
    #endif
    #ifdef INSTRUCTION_ABSX
    RUN_TEST(test_absolute_x);
    #endif
    #ifdef INSTRUCTION_INDX
    RUN_TEST(test_indexed_inderect);
    RUN_TEST(test_indexed_indirect_wrap);
    #endif
    #ifdef INSTRUCTION_INDY
    RUN_TEST(test_indirect_indexed);
    #endif
    
    return UNITY_END();
}

#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif