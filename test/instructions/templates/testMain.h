#ifndef TEST_MAIN_H
#define TEST_MAIN_H

#ifdef TEST_TEMPLATE_H
#ifdef SETUP_CONFIG
#ifdef TEARDOWN_CONFIG

#include "../../src/unity.h"
#include "../../src/unity_internals.h"

void setUp(void) { SETUP_CONFIG }

void tearDown(void) { TEARDOWN_CONFIG }

#ifdef IM_TEST
/** Test for immediate addressing */
void test_immediate(void) { IM_TEST }
#endif

#ifdef ZP_TEST
/** Test for zero page addressing */
void test_zero_page(void) { ZP_TEST }
#endif

#ifdef ZPX_TEST
/** Test for zero page,X addressing without wrapping */
void test_zero_page_x(void) { ZPX_TEST }
#endif

#ifdef ZPX_W_TEST
/** Test for zero page,X addressing with wrapping */
void test_zero_page_x_wrap(void) { ZPX_W_TEST }
#endif

#ifdef ZPY_TEST
/** Test for zero page,Y addressing without wrapping */
void test_zero_page_y(void) { ZPY_TEST }
#endif

#ifdef ZPY_W_TEST
/** Test for zero page,Y addressing with wrapping */
void test_zero_page_y_wrap(void) { ZPY_W_TEST }
#endif

#ifdef ABS_TEST
/** Test for absolute addressing */
void test_absolute(void) { ABS_TEST }
#endif

#ifdef ABSX_TEST
/** Test for absolute,X addressing */
void test_absolute_x(void) { ABSX_TEST }
#endif

#ifdef ABSY_TEST
/** Test for absolute,Y addressing */
void test_absolute_y(void) { ABSY_TEST }
#endif

#ifdef INDX_TEST
/** Test for indexed inderect addressing */
void test_indexed_inderect(void) { INDX_TEST }
#endif

#ifdef INDX_W_TEST
/** Test for indexed indirect addressing with wrap */
void test_indexed_indirect_wrap(void) { INDX_W_TEST }
#endif

#ifdef INDY_TEST
/** Test for indirect indexed addressing */
void test_indirect_indexed(void) { INDY_TEST }
#endif

#ifdef A_TEST
/** Test for special accumulator addressing */
void test_accumulator(void) { A_TEST }
#endif

int main(void) {
    initializeCPU(&cpu);  // Initialize CPU

    UNITY_BEGIN();

    #ifdef IM_TEST
    RUN_TEST(test_immediate);
    #endif

    #ifdef ZP_TEST
    RUN_TEST(test_zero_page);
    #endif

    #ifdef ZPX_TEST
    RUN_TEST(test_zero_page_x);
    #endif
    #ifdef ZPX_W_TEST
    RUN_TEST(test_zero_page_x_wrap);
    #endif

    #ifdef ZPY_TEST
    RUN_TEST(test_zero_page_y);
    #endif
    #ifdef ZPY_W_TEST
    RUN_TEST(test_zero_page_y_wrap);
    #endif

    #ifdef ABS_TEST
    RUN_TEST(test_absolute);
    #endif

    #ifdef ABSX_TEST
    RUN_TEST(test_absolute_x);
    #endif

    #ifdef ABSY_TEST
    RUN_TEST(test_absolute_y);
    #endif

    #ifdef INDX_TEST
    RUN_TEST(test_indexed_inderect);
    #endif
    #ifdef INDX_W_TEST
    RUN_TEST(test_indexed_indirect_wrap);
    #endif

    #ifdef INDY_TEST
    RUN_TEST(test_indirect_indexed);
    #endif

    #ifdef A_TEST
    RUN_TEST(test_accumulator);
    #endif
    
    freeCPU(&cpu);  // Free CPU

    return UNITY_END();
}

#endif
#endif
#endif

#endif  // TEST_MAIN_H