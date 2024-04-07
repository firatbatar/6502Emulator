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
    writeX(0x55);

#define TEARDOWN_CONFIG

#define ZP_TEST                                                                                \
    {                                                                                          \
        writeMemory(0x0200, INS_STX_ZP);                                                       \
        writeMemory(0x0201, 0x01);                                                             \
        byte oldX = readX();                                                                   \
        byte oldPS = readPS();                                                                 \
        execute();                                                                             \
                                                                                               \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readMemory(0x0001), "Memory isn't right in ZP."); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldX, readX(), "X has been changed in ZP.");            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldPS, readPS(), "PS has been changed in ZP.");         \
    }

#define ZPY_TEST                                                                                \
    {                                                                                           \
        writeY(0x05); /* Start with 0x05 in the Y register*/                                    \
                                                                                                \
        writeMemory(0x0200, INS_STX_ZPY);                                                       \
        writeMemory(0x0201, 0x10);                                                              \
        byte oldX = readX();                                                                    \
        byte oldPS = readPS();                                                                  \
        execute();                                                                              \
                                                                                                \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readMemory(0x0015), "Memory isn't right in ZPY."); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldX, readX(), "X has been changed in ZPY.");            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldPS, readPS(), "PS has been changed in ZPY.");         \
    }

#define ZPY_W_TEST                                                                                         \
    {                                                                                                      \
        writeY(0xFF); /*Start with 0xFF in the Y register*/                                                \
                                                                                                           \
        writeMemory(0x0200, INS_STX_ZPY);                                                                  \
        writeMemory(0x0201, 0x20);                                                                         \
        byte oldX = readX();                                                                               \
        byte oldPS = readPS();                                                                             \
        execute();                                                                                         \
                                                                                                           \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readMemory(0x001F), "Memory isn't right in ZPY with wrapp."); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldX, readX(), "X has been changed in ZPY with wrap.");             \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldPS, readPS(), "PS has been changed in ZPY with wrap.");          \
    }

#define ABS_TEST                                                                                \
    {                                                                                           \
        writeMemory(0x0200, INS_STX_ABS);                                                       \
        writeMemory(0x0201, 0x00);                                                              \
        writeMemory(0x0202, 0x04);                                                              \
        byte oldX = readX();                                                                    \
        byte oldPS = readPS();                                                                  \
        execute();                                                                              \
                                                                                                \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readMemory(0x0400), "Memory isn't right in ABS."); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldX, readX(), "X has been changed in ABS.");            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldPS, readPS(), "PS has been changed in ABS.");         \
    }

#include "../templates/testBase.h"

#endif  // _TEST_H