#ifndef _TEST_H
#define _TEST_H

#ifdef _TEST_GROUP_TWO_H
#ifdef SETUP_CONFIG_C
#ifdef TEARDOWN_CONFIG_C
#if defined(FIRST_DATA) && defined(SECOND_DATA) && defined(THIRD_DATA)

#include "../../../include/cpu.h"
#include "../../src/unity.h"
#include "../../src/unity_internals.h"

#define FAIL TEST_FAIL_MESSAGE("No test configured!");

#define SETUP_CONFIG                                        \
    resetMemory(0xFF); /*Set everything in memory to 0xFF*/ \
    /*Set the program start to 0x0200*/                     \
    writeMemory(0xFFFC, 0x00);                              \
    writeMemory(0xFFFD, 0x02);                              \
    resetCPU(); /*Reset the registers*/                     \
    SETUP_CONFIG_C

#define TEARDOWN_CONFIG TEARDOWN_CONFIG_C

#ifdef INSTRUCTION_ZP
/** Test for zero page addressing */
#if defined(FIRST_TEST_ZP) && defined(SECOND_TEST_ZP) && defined(THIRD_TEST_ZP)
#define ZP_TEST                              \
    {                                        \
        writeMemory(0x0200, INSTRUCTION_ZP); \
        writeMemory(0x0201, 0x10);           \
        writeMemory(0x0010, FIRST_DATA);     \
        execute();                           \
        FIRST_TEST_ZP;                       \
                                             \
        writeMemory(0x0202, INSTRUCTION_ZP); \
        writeMemory(0x0203, 0x20);           \
        writeMemory(0x0020, SECOND_DATA);    \
        execute();                           \
        SECOND_TEST_ZP;                      \
                                             \
        writeMemory(0x0204, INSTRUCTION_ZP); \
        writeMemory(0x0205, 0x30);           \
        writeMemory(0x0030, THIRD_DATA);     \
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
        writeMemory(0x0200, INSTRUCTION_A); \
        writeA(FIRST_DATA);                 \
        execute();                          \
        FIRST_TEST_A;                       \
                                            \
        writeMemory(0x0201, INSTRUCTION_A); \
        writeA(SECOND_DATA);                \
        execute();                          \
        SECOND_TEST_A;                      \
                                            \
        writeMemory(0x0202, INSTRUCTION_A); \
        writeA(THIRD_DATA);                 \
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
        writeMemory(0x0200, INSTRUCTION_ABS); \
        writeMemory(0x0201, 0x00);            \
        writeMemory(0x0202, 0x04);            \
        writeMemory(0x0400, FIRST_DATA);      \
        execute();                            \
        FIRST_TEST_ABS;                       \
                                              \
        writeMemory(0x0203, INSTRUCTION_ABS); \
        writeMemory(0x0204, 0x10);            \
        writeMemory(0x0205, 0x04);            \
        writeMemory(0x0410, SECOND_DATA);     \
        execute();                            \
        SECOND_TEST_ABS;                      \
                                              \
        writeMemory(0x0206, INSTRUCTION_ABS); \
        writeMemory(0x0207, 0x20);            \
        writeMemory(0x0208, 0x04);            \
        writeMemory(0x0420, THIRD_DATA);      \
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
        writeX(0x05); /* Start with 0x05 in the X register*/ \
                                                             \
        writeMemory(0x0200, INSTRUCTION_ZPX);                \
        writeMemory(0x0201, 0x10);                           \
        writeMemory(0x0015, FIRST_DATA);                     \
        execute();                                           \
        FIRST_TEST_ZPX;                                      \
                                                             \
        writeMemory(0x0202, INSTRUCTION_ZPX);                \
        writeMemory(0x0203, 0x20);                           \
        writeMemory(0x0025, SECOND_DATA);                    \
        execute();                                           \
        SECOND_TEST_ZPX;                                     \
                                                             \
        writeMemory(0x0204, INSTRUCTION_ZPX);                \
        writeMemory(0x0205, 0x30);                           \
        writeMemory(0x0035, THIRD_DATA);                     \
        execute();                                           \
        THIRD_TEST_ZPX;                                      \
    }
#else
#define ZPX_TEST FAIL
#endif

#if defined(FIRST_TEST_ZPXW) && defined(SECOND_TEST_ZPXW) && defined(THIRD_TEST_ZPXW)
/** Test for zero page,X addressing with wrapping */
#define ZPX_W_TEST                                          \
    {                                                       \
        writeX(0xFF); /*Start with 0xFF in the X register*/ \
                                                            \
        writeMemory(0x0200, INSTRUCTION_ZPX);               \
        writeMemory(0x0201, 0x20);                          \
        writeMemory(0x001F, FIRST_DATA);                    \
        execute();                                          \
        FIRST_TEST_ZPXW;                                    \
                                                            \
        writeMemory(0x0202, INSTRUCTION_ZPX);               \
        writeMemory(0x0203, 0x30);                          \
        writeMemory(0x002F, SECOND_DATA);                   \
        execute();                                          \
        SECOND_TEST_ZPXW;                                   \
                                                            \
        writeMemory(0x0204, INSTRUCTION_ZPX);               \
        writeMemory(0x0205, 0x40);                          \
        writeMemory(0x003F, THIRD_DATA);                    \
        execute();                                          \
        THIRD_TEST_ZPXW;                                    \
    }
#else
#define ZPX_W_TEST FAIL
#endif
#endif

#ifdef INSTRUCTION_ABSX
/** Test for absolute,X addressing */
#if defined(FIRST_TEST_ABSX) && defined(SECOND_TEST_ABSX) && defined(THIRD_TEST_ABSX)
#define ABSX_TEST                                           \
    {                                                       \
        writeX(0x05); /*Start with 0x05 in the X register*/ \
                                                            \
        writeMemory(0x0200, INSTRUCTION_ABSX);              \
        writeMemory(0x0201, 0x00);                          \
        writeMemory(0x0202, 0x04);                          \
        writeMemory(0x0405, FIRST_DATA);                    \
        execute();                                          \
        FIRST_TEST_ABSX;                                    \
                                                            \
        writeMemory(0x0203, INSTRUCTION_ABSX);              \
        writeMemory(0x0204, 0x10);                          \
        writeMemory(0x0205, 0x04);                          \
        writeMemory(0x0415, SECOND_DATA);                   \
        execute();                                          \
        SECOND_TEST_ABSX;                                   \
                                                            \
        writeMemory(0x0206, INSTRUCTION_ABSX);              \
        writeMemory(0x0207, 0x20);                          \
        writeMemory(0x0208, 0x04);                          \
        writeMemory(0x0425, THIRD_DATA);                    \
        execute();                                          \
        THIRD_TEST_ABSX;                                    \
    }
#else
#define ABSX_TEST FAIL
#endif
#endif

#endif
#endif
#endif
#endif

#include "testBase.h"

#endif  // _TEST_H