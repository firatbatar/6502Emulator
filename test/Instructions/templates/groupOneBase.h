#ifndef _TEST_H
#define _TEST_H

#ifdef _TEST_GROUP_ONE_H
#ifdef SETUP_CONFIG_C
#ifdef TEARDOWN_CONFIG_C
#ifdef FIRST_DATA
#ifdef SECOND_DATA
#ifdef THIRD_DATA
#ifdef FIRST_INSTRUCTION_TEST
#ifdef SECOND_INSTRUCTION_TEST
#ifdef THIRD_INSTRUCTION_TEST

#include "../../../include/cpu.h"

#define SETUP_CONFIG                                        \
    resetMemory(0xFF); /*Set everything in memory to 0xFF*/ \
    /*Set the program start to 0x0200*/                     \
    writeMemory(0xFFFC, 0x00);                              \
    writeMemory(0xFFFD, 0x02);                              \
    resetCPU(); /*Reset the registers*/                     \
    SETUP_CONFIG_C

#define TEARDOWN_CONFIG TEARDOWN_CONFIG_C

#ifdef INSTRUCTION_IM
/** Test for immediate addressing */
#define IM_TEST                              \
    {                                        \
        writeMemory(0x0200, INSTRUCTION_IM); \
        writeMemory(0x0201, FIRST_DATA);     \
        execute();                           \
        FIRST_INSTRUCTION_TEST("IM");        \
                                             \
        writeMemory(0x0202, INSTRUCTION_IM); \
        writeMemory(0x0203, SECOND_DATA);    \
        execute();                           \
        SECOND_INSTRUCTION_TEST("IM");       \
                                             \
        writeMemory(0x0204, INSTRUCTION_IM); \
        writeMemory(0x0205, THIRD_DATA);     \
        execute();                           \
        THIRD_INSTRUCTION_TEST("IM");        \
    }
#endif

#ifdef INSTRUCTION_ZP
/** Test for zero page addressing */
#define ZP_TEST                              \
    {                                        \
        writeMemory(0x0200, INSTRUCTION_ZP); \
        writeMemory(0x0201, 0x01);           \
        writeMemory(0x0001, FIRST_DATA);     \
        execute();                           \
        FIRST_INSTRUCTION_TEST("ZP");        \
                                             \
        writeMemory(0x0202, INSTRUCTION_ZP); \
        writeMemory(0x0203, 0x02);           \
        writeMemory(0x0002, SECOND_DATA);    \
        execute();                           \
        SECOND_INSTRUCTION_TEST("ZP");       \
                                             \
        writeMemory(0x0204, INSTRUCTION_ZP); \
        writeMemory(0x0205, 0x03);           \
        writeMemory(0x0003, THIRD_DATA);     \
        execute();                           \
        THIRD_INSTRUCTION_TEST("ZP");        \
    }
#endif

#ifdef INSTRUCTION_ZPX
/** Test for zero page,X addressing without wrapping */
#define ZPX_TEST                                             \
    {                                                        \
        writeX(0x05); /* Start with 0x05 in the X register*/ \
                                                             \
        writeMemory(0x0200, INSTRUCTION_ZPX);                \
        writeMemory(0x0201, 0x10);                           \
        writeMemory(0x0015, FIRST_DATA);                     \
        execute();                                           \
        FIRST_INSTRUCTION_TEST("ZP,X");                      \
                                                             \
        writeMemory(0x0202, INSTRUCTION_ZPX);                \
        writeMemory(0x0203, 0x20);                           \
        writeMemory(0x0025, SECOND_DATA);                    \
        execute();                                           \
        SECOND_INSTRUCTION_TEST("ZP,X");                     \
                                                             \
        writeMemory(0x0204, INSTRUCTION_ZPX);                \
        writeMemory(0x0205, 0x30);                           \
        writeMemory(0x0035, THIRD_DATA);                     \
        execute();                                           \
        THIRD_INSTRUCTION_TEST("ZP,X");                      \
    }
/** Test for zero page,X addressing with wrapping */
#define ZPX_W_TEST                                          \
    {                                                       \
        writeX(0xFF); /*Start with 0xFF in the X register*/ \
                                                            \
        writeMemory(0x0200, INSTRUCTION_ZPX);               \
        writeMemory(0x0201, 0x20);                          \
        writeMemory(0x001F, FIRST_DATA);                    \
        execute();                                          \
        FIRST_INSTRUCTION_TEST("ZP,X with wrapping");       \
                                                            \
        writeMemory(0x0202, INSTRUCTION_ZPX);               \
        writeMemory(0x0203, 0x30);                          \
        writeMemory(0x002F, SECOND_DATA);                   \
        execute();                                          \
        SECOND_INSTRUCTION_TEST("ZP,X with wrapping");      \
                                                            \
        writeMemory(0x0204, INSTRUCTION_ZPX);               \
        writeMemory(0x0205, 0x40);                          \
        writeMemory(0x003F, THIRD_DATA);                    \
        execute();                                          \
        THIRD_INSTRUCTION_TEST("ZP,X with wrapping");       \
    }
#endif

#ifdef INSTRUCTION_ZPY
/** Test for zero page,Y addressing without wrapping */
#define ZPY_TEST                                             \
    {                                                        \
        writeY(0x05); /* Start with 0x05 in the Y register*/ \
                                                             \
        writeMemory(0x0200, INSTRUCTION_ZPY);                \
        writeMemory(0x0201, 0x10);                           \
        writeMemory(0x0015, FIRST_DATA);                     \
        execute();                                           \
        FIRST_INSTRUCTION_TEST("ZP,Y");                      \
                                                             \
        writeMemory(0x0202, INSTRUCTION_ZPY);                \
        writeMemory(0x0203, 0x20);                           \
        writeMemory(0x0025, SECOND_DATA);                    \
        execute();                                           \
        SECOND_INSTRUCTION_TEST("ZP,Y");                     \
                                                             \
        writeMemory(0x0204, INSTRUCTION_ZPY);                \
        writeMemory(0x0205, 0x30);                           \
        writeMemory(0x0035, THIRD_DATA);                     \
        execute();                                           \
        THIRD_INSTRUCTION_TEST("ZP,Y");                      \
    }
/** Test for zero page,X addressing with wrapping */
#define ZPY_W_TEST                                          \
    {                                                       \
        writeY(0xFF); /*Start with 0xFF in the Y register*/ \
                                                            \
        writeMemory(0x0200, INSTRUCTION_ZPY);               \
        writeMemory(0x0201, 0x20);                          \
        writeMemory(0x001F, FIRST_DATA);                    \
        execute();                                          \
        FIRST_INSTRUCTION_TEST("ZP,Y with wrapping");       \
                                                            \
        writeMemory(0x0202, INSTRUCTION_ZPY);               \
        writeMemory(0x0203, 0x30);                          \
        writeMemory(0x002F, SECOND_DATA);                   \
        execute();                                          \
        SECOND_INSTRUCTION_TEST("ZP,Y with wrapping");      \
                                                            \
        writeMemory(0x0204, INSTRUCTION_ZPY);               \
        writeMemory(0x0205, 0x40);                          \
        writeMemory(0x003F, THIRD_DATA);                    \
        execute();                                          \
        THIRD_INSTRUCTION_TEST("ZP,Y with wrapping");       \
    }
#endif

#ifdef INSTRUCTION_ABS
/** Test for absolute addressing */
#define ABS_TEST                              \
    {                                         \
        writeMemory(0x0200, INSTRUCTION_ABS); \
        writeMemory(0x0201, 0x00);            \
        writeMemory(0x0202, 0x04);            \
        writeMemory(0x0400, FIRST_DATA);      \
        execute();                            \
        FIRST_INSTRUCTION_TEST("ABS");        \
                                              \
        writeMemory(0x0203, INSTRUCTION_ABS); \
        writeMemory(0x0204, 0x10);            \
        writeMemory(0x0205, 0x04);            \
        writeMemory(0x0410, SECOND_DATA);     \
        execute();                            \
        SECOND_INSTRUCTION_TEST("ABS");       \
                                              \
        writeMemory(0x0206, INSTRUCTION_ABS); \
        writeMemory(0x0207, 0x20);            \
        writeMemory(0x0208, 0x04);            \
        writeMemory(0x0420, THIRD_DATA);      \
        execute();                            \
        THIRD_INSTRUCTION_TEST("ABS");        \
    }
#endif

#ifdef INSTRUCTION_ABSX
/** Test for absolute,X addressing */
#define ABSX_TEST                                           \
    {                                                       \
        writeX(0x05); /*Start with 0x05 in the X register*/ \
                                                            \
        writeMemory(0x0200, INSTRUCTION_ABSX);              \
        writeMemory(0x0201, 0x00);                          \
        writeMemory(0x0202, 0x04);                          \
        writeMemory(0x0405, FIRST_DATA);                    \
        execute();                                          \
        FIRST_INSTRUCTION_TEST("ABS,X");                    \
                                                            \
        writeMemory(0x0203, INSTRUCTION_ABSX);              \
        writeMemory(0x0204, 0x10);                          \
        writeMemory(0x0205, 0x04);                          \
        writeMemory(0x0415, SECOND_DATA);                   \
        execute();                                          \
        SECOND_INSTRUCTION_TEST("ABS,X");                   \
                                                            \
        writeMemory(0x0206, INSTRUCTION_ABSX);              \
        writeMemory(0x0207, 0x20);                          \
        writeMemory(0x0208, 0x04);                          \
        writeMemory(0x0425, THIRD_DATA);                    \
        execute();                                          \
        THIRD_INSTRUCTION_TEST("ABS,X");                    \
    }
#endif

#ifdef INSTRUCTION_ABSY
/** Test for absolute,Y addressing */
#define ABSY_TEST                                           \
    {                                                       \
        writeY(0x05); /*Start with 0x05 in the Y register*/ \
                                                            \
        writeMemory(0x0200, INSTRUCTION_ABSY);              \
        writeMemory(0x0201, 0x00);                          \
        writeMemory(0x0202, 0x04);                          \
        writeMemory(0x0405, FIRST_DATA);                    \
        execute();                                          \
        FIRST_INSTRUCTION_TEST("ABS,Y");                    \
                                                            \
        writeMemory(0x0203, INSTRUCTION_ABSY);              \
        writeMemory(0x0204, 0x10);                          \
        writeMemory(0x0205, 0x04);                          \
        writeMemory(0x0415, SECOND_DATA);                   \
        execute();                                          \
        SECOND_INSTRUCTION_TEST("ABS,Y");                   \
                                                            \
        writeMemory(0x0206, INSTRUCTION_ABSY);              \
        writeMemory(0x0207, 0x20);                          \
        writeMemory(0x0208, 0x04);                          \
        writeMemory(0x0425, THIRD_DATA);                    \
        execute();                                          \
        THIRD_INSTRUCTION_TEST("ABS,Y");                    \
    }
#endif

#ifdef INSTRUCTION_INDX
/** Test for indexed inderect addressing */                 \
#define INDX_TEST                                           \
    {                                                       \
        writeX(0x05); /*Start with 0x05 in the X register*/ \
                                                            \
        writeMemory(0x0200, INSTRUCTION_INDX);              \
        writeMemory(0x0201, 0x10);                          \
        writeMemory(0x0015, 0x00);                          \
        writeMemory(0x0016, 0x04);                          \
        writeMemory(0x0400, FIRST_DATA);                    \
        execute();                                          \
        FIRST_INSTRUCTION_TEST("INDX");                     \
                                                            \
        writeMemory(0x0202, INSTRUCTION_INDX);              \
        writeMemory(0x0203, 0x20);                          \
        writeMemory(0x0025, 0x10);                          \
        writeMemory(0x0026, 0x04);                          \
        writeMemory(0x0410, SECOND_DATA);                   \
        execute();                                          \
        SECOND_INSTRUCTION_TEST("INDX");                    \
                                                            \
        writeMemory(0x0204, INSTRUCTION_INDX);              \
        writeMemory(0x0205, 0x30);                          \
        writeMemory(0x0035, 0x20);                          \
        writeMemory(0x0036, 0x04);                          \
        writeMemory(0x0420, THIRD_DATA);                    \
        execute();                                          \
        THIRD_INSTRUCTION_TEST("INDX");                     \
    }
/** Test for indexed indirect addressing with wrap */
#define INDX_W_TEST                                         \
    {                                                       \
        writeX(0xFF); /*Start with 0xFF in the X register*/ \
                                                            \
        writeMemory(0x0200, INSTRUCTION_INDX);              \
        writeMemory(0x0201, 0x10);                          \
        writeMemory(0x000F, 0x00);                          \
        writeMemory(0x0010, 0x04);                          \
        writeMemory(0x0400, FIRST_DATA);                    \
        execute();                                          \
        FIRST_INSTRUCTION_TEST("INDX with wrap");           \
                                                            \
        writeMemory(0x0202, INSTRUCTION_INDX);              \
        writeMemory(0x0203, 0x20);                          \
        writeMemory(0x001F, 0x10);                          \
        writeMemory(0x0020, 0x04);                          \
        writeMemory(0x0410, SECOND_DATA);                   \
        execute();                                          \
        SECOND_INSTRUCTION_TEST("INDX with wrap");          \
                                                            \
        writeMemory(0x0204, INSTRUCTION_INDX);              \
        writeMemory(0x0205, 0x30);                          \
        writeMemory(0x002F, 0x20);                          \
        writeMemory(0x0030, 0x04);                          \
        writeMemory(0x0420, THIRD_DATA);                    \
        execute();                                          \
        THIRD_INSTRUCTION_TEST("INDX with wrap");           \
    }
#endif

#ifdef INSTRUCTION_INDY
/** Test for indirect indexed addressing */
#define INDY_TEST                                           \
    {                                                       \
        writeY(0x05); /*Start with 0x05 in the Y register*/ \
                                                            \
        writeMemory(0x0200, INSTRUCTION_INDY);              \
        writeMemory(0x0201, 0x10);                          \
        writeMemory(0x0010, 0x00);                          \
        writeMemory(0x0011, 0x04);                          \
        writeMemory(0x0405, FIRST_DATA);                    \
        execute();                                          \
        FIRST_INSTRUCTION_TEST("INDY");                     \
                                                            \
        writeMemory(0x0202, INSTRUCTION_INDY);              \
        writeMemory(0x0203, 0x20);                          \
        writeMemory(0x0020, 0x10);                          \
        writeMemory(0x0021, 0x04);                          \
        writeMemory(0x0415, SECOND_DATA);                   \
        execute();                                          \
        SECOND_INSTRUCTION_TEST("INDY");                    \
                                                            \
        writeMemory(0x0204, INSTRUCTION_INDY);              \
        writeMemory(0x0205, 0x30);                          \
        writeMemory(0x0030, 0x20);                          \
        writeMemory(0x0031, 0x04);                          \
        writeMemory(0x0425, THIRD_DATA);                    \
        execute();                                          \
        THIRD_INSTRUCTION_TEST("INDY");                     \
    }
#endif

#include "testBase.h"

#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#endif  // _TEST_H