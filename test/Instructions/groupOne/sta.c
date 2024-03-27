#ifndef _TEST_H
#define _TEST_H

#include "../../../include/cpu.h"
#include "../../../include/instructions.h"
#include "../../src/unity.h"
#include "../../src/unity_internals.h"

#define SETUP_CONFIG                                        \
    resetMemory(0xFF); /*Set everything in memory to 0xFF*/ \
    /*Set the program start to 0x0200*/                     \
    writeMemory(0xFFFC, 0x00);                              \
    writeMemory(0xFFFD, 0x02);                              \
    resetCPU(); /*Reset the registers*/                     \
    writeA(0x55);

#define TEARDOWN_CONFIG

#define ZP_TEST                                                                                \
    {                                                                                          \
        writeMemory(0x0200, INS_STA_ZP);                                                       \
        writeMemory(0x0201, 0x01);                                                             \
        byte oldA = readA();                                                                   \
        byte oldPS = readPS();                                                                 \
        execute();                                                                             \
                                                                                               \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readMemory(0x0001), "Memory isn't right in ZP."); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldA, readA(), "A has been changed in ZP.");            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldPS, readPS(), "PS has been changed in ZP.");         \
    }

#define ZPX_TEST                                                                                \
    {                                                                                           \
        writeX(0x05); /* Start with 0x05 in the X register*/                                    \
                                                                                                \
        writeMemory(0x0200, INS_STA_ZPX);                                                       \
        writeMemory(0x0201, 0x10);                                                              \
        byte oldA = readA();                                                                    \
        byte oldPS = readPS();                                                                  \
        execute();                                                                              \
                                                                                                \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readMemory(0x0015), "Memory isn't right in ZPX."); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldA, readA(), "A has been changed in ZPX.");            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldPS, readPS(), "PS has been changed in ZPX.");         \
    }

#define ZPX_W_TEST                                                                                         \
    {                                                                                                      \
        writeX(0xFF); /*Start with 0xFF in the X register*/                                                \
                                                                                                           \
        writeMemory(0x0200, INS_STA_ZPX);                                                                  \
        writeMemory(0x0201, 0x20);                                                                         \
        byte oldA = readA();                                                                               \
        byte oldPS = readPS();                                                                             \
        execute();                                                                                         \
                                                                                                           \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readMemory(0x001F), "Memory isn't right in ZPX with wrapp."); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldA, readA(), "A has been changed in ZPX with wrap.");             \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldPS, readPS(), "PS has been changed in ZPX with wrap.");          \
    }

#define ABS_TEST                                                                                \
    {                                                                                           \
        writeMemory(0x0200, INS_STA_ABS);                                                       \
        writeMemory(0x0201, 0x00);                                                              \
        writeMemory(0x0202, 0x04);                                                              \
        byte oldA = readA();                                                                    \
        byte oldPS = readPS();                                                                  \
        execute();                                                                              \
                                                                                                \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readMemory(0x0400), "Memory isn't right in ABS."); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldA, readA(), "A has been changed in ABS.");            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldPS, readPS(), "PS has been changed in ABS.");         \
    }

#define ABSX_TEST                                                                                \
    {                                                                                            \
        writeX(0x05); /*Start with 0x05 in the X register*/                                      \
                                                                                                 \
        writeMemory(0x0200, INS_STA_ABSX);                                                       \
        writeMemory(0x0201, 0x00);                                                               \
        writeMemory(0x0202, 0x04);                                                               \
        byte oldA = readA();                                                                     \
        byte oldPS = readPS();                                                                   \
        execute();                                                                               \
                                                                                                 \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readMemory(0x0405), "Memory isn't right in ABSX."); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldA, readA(), "A has been changed in ABSX.");            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldPS, readPS(), "PS has been changed in ABSX.");         \
    }

#define INDX_TEST                                                                                \
    {                                                                                            \
        writeX(0x05); /*Start with 0x05 in the X register*/                                      \
                                                                                                 \
        writeMemory(0x0200, INS_STA_INDX);                                                       \
        writeMemory(0x0201, 0x10);                                                               \
        writeMemory(0x0015, 0x00);                                                               \
        writeMemory(0x0016, 0x04);                                                               \
        byte oldA = readA();                                                                     \
        byte oldPS = readPS();                                                                   \
        execute();                                                                               \
                                                                                                 \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readMemory(0x0400), "Memory isn't right in INDX."); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldA, readA(), "A has been changed in INDX.");            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldPS, readPS(), "PS has been changed in INDX.");         \
    }

#define INDX_W_TEST                                                                                        \
    {                                                                                                      \
        writeX(0xFF); /*Start with 0xFF in the X register*/                                                \
                                                                                                           \
        writeMemory(0x0200, INS_STA_INDX);                                                                 \
        writeMemory(0x0201, 0x10);                                                                         \
        writeMemory(0x000F, 0x00);                                                                         \
        writeMemory(0x0010, 0x04);                                                                         \
        byte oldA = readA();                                                                               \
        byte oldPS = readPS();                                                                             \
        execute();                                                                                         \
                                                                                                           \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readMemory(0x0400), "Memory isn't right in INDX with wrap."); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldA, readA(), "A has been changed in INDX with wrap.");            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldPS, readPS(), "PS has been changed in INDX with wrap.");         \
    }

#define INDY_TEST                                                                                \
    {                                                                                            \
        writeY(0x05); /*Start with 0x05 in the Y register*/                                      \
                                                                                                 \
        writeMemory(0x0200, INS_STA_INDY);                                                       \
        writeMemory(0x0201, 0x10);                                                               \
        writeMemory(0x0010, 0x00);                                                               \
        writeMemory(0x0011, 0x04);                                                               \
        byte oldA = readA();                                                                     \
        byte oldPS = readPS();                                                                   \
        execute();                                                                               \
                                                                                                 \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readMemory(0x0405), "Memory isn't right in INDY."); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldA, readA(), "A has been changed in INDY.");            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldPS, readPS(), "PS has been changed in INDY.");         \
    }

#include "../templates/testBase.h"

#endif  // _TEST_H