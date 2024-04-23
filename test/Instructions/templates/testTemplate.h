#ifndef TEST_TEMPLATE_H
#define TEST_TEMPLATE_H

#ifdef TEST_H
#ifdef SETUP_CONFIG_C
#ifdef TEARDOWN_CONFIG_C
#if defined(FIRST_DATA) && defined(SECOND_DATA) && defined(THIRD_DATA)

#include "../../../include/cpu.h"
#include "../../src/unity.h"
#include "../../src/unity_internals.h"

#ifdef UNPACK_TESTS
#include "unpackTests.h"
#endif

#define FAIL TEST_FAIL_MESSAGE("No test configured!");

#define SETUP_CONFIG                                        \
    resetMemory(0xFF); /*Set everything in memory to 0xFF*/ \
    /*Set the program start to 0x0200*/                     \
    writeMemory(0xFFFC, 0x00);                              \
    writeMemory(0xFFFD, 0x02);                              \
    resetCPU(); /*Reset the registers*/                     \
    SETUP_CONFIG_C

#define TEARDOWN_CONFIG TEARDOWN_CONFIG_C

#ifdef SAVE_STATE
#undef SAVE_STATE
#define SAVE_STATE_INIT byte oldA, oldX, oldY, oldPS;
// += 0 is used to avoid warnings
#define SAVE_STATE    \
    oldA = readA();   \
    oldA += 0;        \
    oldX = readX();   \
    oldX += 0;        \
    oldY = readY();   \
    oldY += 0;        \
    oldPS = readPS(); \
    oldPS += 0;
#else
#define SAVE_STATE_INIT
#define SAVE_STATE
#endif

#ifdef INSTRUCTION_IM
/** Test for immediate addressing */
#if defined(FIRST_TEST_IM) && defined(SECOND_TEST_IM) && defined(THIRD_TEST_IM)
#define IM_TEST                              \
    {                                        \
        SAVE_STATE_INIT                      \
                                             \
        writeMemory(0x0200, INSTRUCTION_IM); \
        writeMemory(0x0201, FIRST_DATA);     \
        SAVE_STATE                           \
        execute();                           \
        FIRST_TEST_IM;                       \
                                             \
        writeMemory(0x0202, INSTRUCTION_IM); \
        writeMemory(0x0203, SECOND_DATA);    \
        SAVE_STATE                           \
        execute();                           \
        SECOND_TEST_IM;                      \
                                             \
        writeMemory(0x0204, INSTRUCTION_IM); \
        writeMemory(0x0205, THIRD_DATA);     \
        SAVE_STATE                           \
        execute();                           \
        THIRD_TEST_IM;                       \
    }
#else
#define ZP_TEST FAIL
#endif
#endif

#ifdef INSTRUCTION_ZP
/** Test for zero page addressing */
#if defined(FIRST_TEST_ZP) && defined(SECOND_TEST_ZP) && defined(THIRD_TEST_ZP)
#define ZP_TEST                              \
    {                                        \
        SAVE_STATE_INIT                      \
                                             \
        writeMemory(0x0200, INSTRUCTION_ZP); \
        writeMemory(0x0201, 0x10);           \
        writeMemory(0x0010, FIRST_DATA);     \
        SAVE_STATE                           \
        execute();                           \
        FIRST_TEST_ZP;                       \
                                             \
        writeMemory(0x0202, INSTRUCTION_ZP); \
        writeMemory(0x0203, 0x20);           \
        writeMemory(0x0020, SECOND_DATA);    \
        SAVE_STATE                           \
        execute();                           \
        SECOND_TEST_ZP;                      \
                                             \
        writeMemory(0x0204, INSTRUCTION_ZP); \
        writeMemory(0x0205, 0x30);           \
        writeMemory(0x0030, THIRD_DATA);     \
        SAVE_STATE                           \
        execute();                           \
        THIRD_TEST_ZP;                       \
    }
#else
#define ZP_TEST FAIL
#endif
#endif

#ifdef INSTRUCTION_A
/** Test for special accumulator addressing mode */
#if defined(FIRST_TEST_A) && defined(SECOND_TEST_A) && defined(THIRD_TEST_A)
#define A_TEST                              \
    {                                       \
        SAVE_STATE_INIT                     \
                                            \
        writeMemory(0x0200, INSTRUCTION_A); \
        writeA(FIRST_DATA);                 \
        SAVE_STATE                          \
        execute();                          \
        FIRST_TEST_A;                       \
                                            \
        writeMemory(0x0201, INSTRUCTION_A); \
        writeA(SECOND_DATA);                \
        SAVE_STATE                          \
        execute();                          \
        SECOND_TEST_A;                      \
                                            \
        writeMemory(0x0202, INSTRUCTION_A); \
        writeA(THIRD_DATA);                 \
        SAVE_STATE                          \
        execute();                          \
        THIRD_TEST_A;                       \
    }
#else
#define A_TEST FAIL
#endif
#endif

#ifdef INSTRUCTION_ABS
/** Test for absolute addressing mode */
#if defined(FIRST_TEST_ABS) && defined(SECOND_TEST_ABS) && defined(THIRD_TEST_ABS)
#define ABS_TEST                              \
    {                                         \
        SAVE_STATE_INIT                       \
                                              \
        writeMemory(0x0200, INSTRUCTION_ABS); \
        writeMemory(0x0201, 0x00);            \
        writeMemory(0x0202, 0x04);            \
        writeMemory(0x0400, FIRST_DATA);      \
        SAVE_STATE                            \
        execute();                            \
        FIRST_TEST_ABS;                       \
                                              \
        writeMemory(0x0203, INSTRUCTION_ABS); \
        writeMemory(0x0204, 0x10);            \
        writeMemory(0x0205, 0x04);            \
        writeMemory(0x0410, SECOND_DATA);     \
        SAVE_STATE                            \
        execute();                            \
        SECOND_TEST_ABS;                      \
                                              \
        writeMemory(0x0206, INSTRUCTION_ABS); \
        writeMemory(0x0207, 0x20);            \
        writeMemory(0x0208, 0x04);            \
        writeMemory(0x0420, THIRD_DATA);      \
        SAVE_STATE                            \
        execute();                            \
        THIRD_TEST_ABS;                       \
    }
#else
#define ABS_TEST FAIL
#endif
#endif

#ifdef INSTRUCTION_ZPX
/** Test for zero page,X addressing without wrapping */
#if defined(FIRST_TEST_ZPX) && defined(SECOND_TEST_ZPX) && defined(THIRD_TEST_ZPX)
#define ZPX_TEST                                             \
    {                                                        \
        SAVE_STATE_INIT                                      \
                                                             \
        writeX(0x05); /* Start with 0x05 in the X register*/ \
                                                             \
        writeMemory(0x0200, INSTRUCTION_ZPX);                \
        writeMemory(0x0201, 0x10);                           \
        writeMemory(0x0015, FIRST_DATA);                     \
        SAVE_STATE                                           \
        execute();                                           \
        FIRST_TEST_ZPX;                                      \
                                                             \
        writeMemory(0x0202, INSTRUCTION_ZPX);                \
        writeMemory(0x0203, 0x20);                           \
        writeMemory(0x0025, SECOND_DATA);                    \
        SAVE_STATE                                           \
        execute();                                           \
        SECOND_TEST_ZPX;                                     \
                                                             \
        writeMemory(0x0204, INSTRUCTION_ZPX);                \
        writeMemory(0x0205, 0x30);                           \
        writeMemory(0x0035, THIRD_DATA);                     \
        SAVE_STATE                                           \
        execute();                                           \
        THIRD_TEST_ZPX;                                      \
    }
#else
#define ZPX_TEST FAIL
#endif

/** Test for zero page,X addressing with wrapping */
#if defined(FIRST_TEST_ZPXW) && defined(SECOND_TEST_ZPXW) && defined(THIRD_TEST_ZPXW)
#define ZPX_W_TEST                                          \
    {                                                       \
        SAVE_STATE_INIT                                     \
                                                            \
        writeX(0xFF); /*Start with 0xFF in the X register*/ \
                                                            \
        writeMemory(0x0200, INSTRUCTION_ZPX);               \
        writeMemory(0x0201, 0x20);                          \
        writeMemory(0x001F, FIRST_DATA);                    \
        SAVE_STATE                                          \
        execute();                                          \
        FIRST_TEST_ZPXW;                                    \
                                                            \
        writeMemory(0x0202, INSTRUCTION_ZPX);               \
        writeMemory(0x0203, 0x30);                          \
        writeMemory(0x002F, SECOND_DATA);                   \
        SAVE_STATE                                          \
        execute();                                          \
        SECOND_TEST_ZPXW;                                   \
                                                            \
        writeMemory(0x0204, INSTRUCTION_ZPX);               \
        writeMemory(0x0205, 0x40);                          \
        writeMemory(0x003F, THIRD_DATA);                    \
        SAVE_STATE                                          \
        execute();                                          \
        THIRD_TEST_ZPXW;                                    \
    }
#else
#define ZPX_W_TEST FAIL
#endif
#endif

#ifdef INSTRUCTION_ZPY
/** Test for zero page,Y addressing without wrapping */
#if defined(FIRST_TEST_ZPY) && defined(SECOND_TEST_ZPY) && defined(THIRD_TEST_ZPY)
#define ZPY_TEST                                             \
    {                                                        \
        SAVE_STATE_INIT                                      \
                                                             \
        writeY(0x05); /* Start with 0x05 in the X register*/ \
                                                             \
        writeMemory(0x0200, INSTRUCTION_ZPY);                \
        writeMemory(0x0201, 0x10);                           \
        writeMemory(0x0015, FIRST_DATA);                     \
        SAVE_STATE                                           \
        execute();                                           \
        FIRST_TEST_ZPY;                                      \
                                                             \
        writeMemory(0x0202, INSTRUCTION_ZPY);                \
        writeMemory(0x0203, 0x20);                           \
        writeMemory(0x0025, SECOND_DATA);                    \
        SAVE_STATE                                           \
        execute();                                           \
        SECOND_TEST_ZPY;                                     \
                                                             \
        writeMemory(0x0204, INSTRUCTION_ZPY);                \
        writeMemory(0x0205, 0x30);                           \
        writeMemory(0x0035, THIRD_DATA);                     \
        SAVE_STATE                                           \
        execute();                                           \
        THIRD_TEST_ZPY;                                      \
    }
#else
#define ZPY_TEST FAIL
#endif

/** Test for zero page,Y addressing with wrapping */
#if defined(FIRST_TEST_ZPYW) && defined(SECOND_TEST_ZPYW) && defined(THIRD_TEST_ZPYW)
#define ZPY_W_TEST                                          \
    {                                                       \
        SAVE_STATE_INIT                                     \
                                                            \
        writeY(0xFF); /*Start with 0xFF in the X register*/ \
                                                            \
        writeMemory(0x0200, INSTRUCTION_ZPY);               \
        writeMemory(0x0201, 0x20);                          \
        writeMemory(0x001F, FIRST_DATA);                    \
        SAVE_STATE                                          \
        execute();                                          \
        FIRST_TEST_ZPYW;                                    \
                                                            \
        writeMemory(0x0202, INSTRUCTION_ZPY);               \
        writeMemory(0x0203, 0x30);                          \
        writeMemory(0x002F, SECOND_DATA);                   \
        SAVE_STATE                                          \
        execute();                                          \
        SECOND_TEST_ZPYW;                                   \
                                                            \
        writeMemory(0x0204, INSTRUCTION_ZPY);               \
        writeMemory(0x0205, 0x40);                          \
        writeMemory(0x003F, THIRD_DATA);                    \
        SAVE_STATE                                          \
        execute();                                          \
        THIRD_TEST_ZPYW;                                    \
    }
#else
#define ZPY_W_TEST FAIL
#endif
#endif

#ifdef INSTRUCTION_ABSX
/** Test for absolute,X addressing */
#if defined(FIRST_TEST_ABSX) && defined(SECOND_TEST_ABSX) && defined(THIRD_TEST_ABSX)
#define ABSX_TEST                                           \
    {                                                       \
        SAVE_STATE_INIT                                     \
                                                            \
        writeX(0x05); /*Start with 0x05 in the X register*/ \
                                                            \
        writeMemory(0x0200, INSTRUCTION_ABSX);              \
        writeMemory(0x0201, 0x00);                          \
        writeMemory(0x0202, 0x04);                          \
        writeMemory(0x0405, FIRST_DATA);                    \
        SAVE_STATE                                          \
        execute();                                          \
        FIRST_TEST_ABSX;                                    \
                                                            \
        writeMemory(0x0203, INSTRUCTION_ABSX);              \
        writeMemory(0x0204, 0x10);                          \
        writeMemory(0x0205, 0x04);                          \
        writeMemory(0x0415, SECOND_DATA);                   \
        SAVE_STATE                                          \
        execute();                                          \
        SECOND_TEST_ABSX;                                   \
                                                            \
        writeMemory(0x0206, INSTRUCTION_ABSX);              \
        writeMemory(0x0207, 0x20);                          \
        writeMemory(0x0208, 0x04);                          \
        writeMemory(0x0425, THIRD_DATA);                    \
        SAVE_STATE                                          \
        execute();                                          \
        THIRD_TEST_ABSX;                                    \
    }
#else
#define ABSX_TEST FAIL
#endif
#endif

#ifdef INSTRUCTION_ABSY
/** Test for absolute,Y addressing */
#if defined(FIRST_TEST_ABSY) && defined(SECOND_TEST_ABSY) && defined(THIRD_TEST_ABSY)
#define ABSY_TEST                                           \
    {                                                       \
        SAVE_STATE_INIT                                     \
                                                            \
        writeY(0x05); /*Start with 0x05 in the Y register*/ \
                                                            \
        writeMemory(0x0200, INSTRUCTION_ABSY);              \
        writeMemory(0x0201, 0x00);                          \
        writeMemory(0x0202, 0x04);                          \
        writeMemory(0x0405, FIRST_DATA);                    \
        SAVE_STATE                                          \
        execute();                                          \
        FIRST_TEST_ABSY;                                    \
                                                            \
        writeMemory(0x0203, INSTRUCTION_ABSY);              \
        writeMemory(0x0204, 0x10);                          \
        writeMemory(0x0205, 0x04);                          \
        writeMemory(0x0415, SECOND_DATA);                   \
        SAVE_STATE                                          \
        execute();                                          \
        SECOND_TEST_ABSY;                                   \
                                                            \
        writeMemory(0x0206, INSTRUCTION_ABSY);              \
        writeMemory(0x0207, 0x20);                          \
        writeMemory(0x0208, 0x04);                          \
        writeMemory(0x0425, THIRD_DATA);                    \
        SAVE_STATE                                          \
        execute();                                          \
        THIRD_TEST_ABSY;                                    \
    }
#else
#define ABSY_TEST FAIL
#endif
#endif

#ifdef INSTRUCTION_INDX
/** Test for indexed inderect addressing */
#if defined(FIRST_TEST_INDX) && defined(SECOND_TEST_INDX) && defined(THIRD_TEST_INDX)
#define INDX_TEST                                           \
    {                                                       \
        SAVE_STATE_INIT                                     \
                                                            \
        writeX(0x05); /*Start with 0x05 in the X register*/ \
                                                            \
        writeMemory(0x0200, INSTRUCTION_INDX);              \
        writeMemory(0x0201, 0x10);                          \
        writeMemory(0x0015, 0x00);                          \
        writeMemory(0x0016, 0x04);                          \
        writeMemory(0x0400, FIRST_DATA);                    \
        SAVE_STATE                                          \
        execute();                                          \
        FIRST_TEST_INDX;                                    \
                                                            \
        writeMemory(0x0202, INSTRUCTION_INDX);              \
        writeMemory(0x0203, 0x20);                          \
        writeMemory(0x0025, 0x10);                          \
        writeMemory(0x0026, 0x04);                          \
        writeMemory(0x0410, SECOND_DATA);                   \
        SAVE_STATE                                          \
        execute();                                          \
        SECOND_TEST_INDX;                                   \
                                                            \
        writeMemory(0x0204, INSTRUCTION_INDX);              \
        writeMemory(0x0205, 0x30);                          \
        writeMemory(0x0035, 0x20);                          \
        writeMemory(0x0036, 0x04);                          \
        writeMemory(0x0420, THIRD_DATA);                    \
        SAVE_STATE                                          \
        execute();                                          \
        THIRD_TEST_INDX;                                    \
    }
#else
#define INDX_TEST FAIL
#endif

/** Test for indexed indirect addressing with wrap */
#if defined(FIRST_TEST_INDXW) && defined(SECOND_TEST_INDXW) && defined(THIRD_TEST_INDXW)
#define INDX_W_TEST                                         \
    {                                                       \
        SAVE_STATE_INIT                                     \
                                                            \
        writeX(0xFF); /*Start with 0xFF in the X register*/ \
                                                            \
        writeMemory(0x0200, INSTRUCTION_INDX);              \
        writeMemory(0x0201, 0x10);                          \
        writeMemory(0x000F, 0x00);                          \
        writeMemory(0x0010, 0x04);                          \
        writeMemory(0x0400, FIRST_DATA);                    \
        SAVE_STATE                                          \
        execute();                                          \
        FIRST_TEST_INDXW;                                   \
                                                            \
        writeMemory(0x0202, INSTRUCTION_INDX);              \
        writeMemory(0x0203, 0x20);                          \
        writeMemory(0x001F, 0x10);                          \
        writeMemory(0x0020, 0x04);                          \
        writeMemory(0x0410, SECOND_DATA);                   \
        SAVE_STATE                                          \
        execute();                                          \
        SECOND_TEST_INDXW;                                  \
                                                            \
        writeMemory(0x0204, INSTRUCTION_INDX);              \
        writeMemory(0x0205, 0x30);                          \
        writeMemory(0x002F, 0x20);                          \
        writeMemory(0x0030, 0x04);                          \
        writeMemory(0x0420, THIRD_DATA);                    \
        SAVE_STATE                                          \
        execute();                                          \
        THIRD_TEST_INDXW;                                   \
    }
#else
#define INDX_W_TEST FAIL
#endif
#endif

#ifdef INSTRUCTION_INDY
/** Test for indirect indexed addressing */
#if defined(FIRST_TEST_INDY) && defined(SECOND_TEST_INDY) && defined(THIRD_TEST_INDY)
#define INDY_TEST                                           \
    {                                                       \
        SAVE_STATE_INIT                                     \
                                                            \
        writeY(0x05); /*Start with 0x05 in the Y register*/ \
                                                            \
        writeMemory(0x0200, INSTRUCTION_INDY);              \
        writeMemory(0x0201, 0x10);                          \
        writeMemory(0x0010, 0x00);                          \
        writeMemory(0x0011, 0x04);                          \
        writeMemory(0x0405, FIRST_DATA);                    \
        SAVE_STATE                                          \
        execute();                                          \
        FIRST_TEST_INDY                                     \
                                                            \
        writeMemory(0x0202, INSTRUCTION_INDY);              \
        writeMemory(0x0203, 0x20);                          \
        writeMemory(0x0020, 0x10);                          \
        writeMemory(0x0021, 0x04);                          \
        writeMemory(0x0415, SECOND_DATA);                   \
        SAVE_STATE                                          \
        execute();                                          \
        SECOND_TEST_INDY                                    \
                                                            \
        writeMemory(0x0204, INSTRUCTION_INDY);              \
        writeMemory(0x0205, 0x30);                          \
        writeMemory(0x0030, 0x20);                          \
        writeMemory(0x0031, 0x04);                          \
        writeMemory(0x0425, THIRD_DATA);                    \
        SAVE_STATE                                          \
        execute();                                          \
        THIRD_TEST_INDY                                     \
    }
#else
#define INDY_TEST FAIL
#endif
#endif

#endif
#endif
#endif
#endif

#include "testMain.h"

#endif  // TEST_TEMPLATE_H