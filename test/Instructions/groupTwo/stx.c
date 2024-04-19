#ifndef _TEST_H
#define _TEST_H

#include "../../../include/cpu.h"
#include "../../../include/opcodes.h"
#include "../../src/unity.h"
#include "../../src/unity_internals.h"

#define SETUP_CONFIG_C writeX(0x55);
#define TEARDOWN_CONFIG_C

#define INSTRUCTION_ZP INS_STX_ZP
#define INSTRUCTION_ZPY INS_STX_ZPY
#define INSTRUCTION_ABS INS_STX_ABS

#define FIRST_DATA 0xFF
#define SECOND_DATA 0xFF
#define THIRD_DATA 0xFF

#define SAVE_STATE

#define FIRST_TEST_ZP                                                                          \
    {                                                                                          \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readMemory(0x0010), "Memory isn't right in ZP."); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldX, readX(), "X has been changed in ZP.");            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldPS, readPS(), "PS has been changed in ZP.");         \
    }
#define SECOND_TEST_ZP
#define THIRD_TEST_ZP

#define FIRST_TEST_ZPY                                                                          \
    {                                                                                           \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readMemory(0x0015), "Memory isn't right in ZPY."); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldX, readX(), "X has been changed in ZPY.");            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldPS, readPS(), "PS has been changed in ZPY.");         \
    }
#define SECOND_TEST_ZPY
#define THIRD_TEST_ZPY

#define FIRST_TEST_ZPYW                                                                                    \
    {                                                                                                      \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readMemory(0x001F), "Memory isn't right in ZPY with wrapp."); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldX, readX(), "X has been changed in ZPY with wrap.");             \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldPS, readPS(), "PS has been changed in ZPY with wrap.");          \
    }
#define SECOND_TEST_ZPYW
#define THIRD_TEST_ZPYW

#define FIRST_TEST_ABS                                                                          \
    {                                                                                           \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readMemory(0x0400), "Memory isn't right in ABS."); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldX, readX(), "X has been changed in ABS.");            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldPS, readPS(), "PS has been changed in ABS.");         \
    }
#define SECOND_TEST_ABS
#define THIRD_TEST_ABS

#include "../templates/testTemplate.h"

#endif  // _TEST_H