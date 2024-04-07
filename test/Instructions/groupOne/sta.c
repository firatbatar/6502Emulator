#ifndef _TEST_H
#define _TEST_H

#include "../../../include/cpu.h"
#include "../../../include/instructions.h"
#include "../../src/unity.h"
#include "../../src/unity_internals.h"

#define SETUP_CONFIG_C writeA(0x55);
#define TEARDOWN_CONFIG_C

#define INSTRUCTION_ZP INS_STA_ZP
#define INSTRUCTION_ZPX INS_STA_ZPX
#define INSTRUCTION_ABS INS_STA_ABS
#define INSTRUCTION_ABSX INS_STA_ABSX
#define INSTRUCTION_ABSY INS_STA_ABSY
#define INSTRUCTION_INDX INS_STA_INDX
#define INSTRUCTION_INDY INS_STA_INDY

#define FIRST_DATA 0xFF
#define SECOND_DATA 0xFF
#define THIRD_DATA 0xFF

#define SAVE_STATE

#define FIRST_TEST_ZP                                                                          \
    {                                                                                          \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readMemory(0x0010), "Memory isn't right in ZP."); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldA, readA(), "A has been changed in ZP.");            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldPS, readPS(), "PS has been changed in ZP.");         \
    }
#define SECOND_TEST_ZP
#define THIRD_TEST_ZP

#define FIRST_TEST_ZPX                                                                          \
    {                                                                                           \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readMemory(0x0015), "Memory isn't right in ZPX."); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldA, readA(), "A has been changed in ZPX.");            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldPS, readPS(), "PS has been changed in ZPX.");         \
    }
#define SECOND_TEST_ZPX
#define THIRD_TEST_ZPX

#define FIRST_TEST_ZPXW                                                                                    \
    {                                                                                                      \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readMemory(0x001F), "Memory isn't right in ZPX with wrapp."); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldA, readA(), "A has been changed in ZPX with wrap.");             \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldPS, readPS(), "PS has been changed in ZPX with wrap.");          \
    }
#define SECOND_TEST_ZPXW
#define THIRD_TEST_ZPXW

#define FIRST_TEST_ABS                                                                          \
    {                                                                                           \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readMemory(0x0400), "Memory isn't right in ABS."); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldA, readA(), "A has been changed in ABS.");            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldPS, readPS(), "PS has been changed in ABS.");         \
    }
#define SECOND_TEST_ABS
#define THIRD_TEST_ABS

#define FIRST_TEST_ABSX                                                                          \
    {                                                                                            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readMemory(0x0405), "Memory isn't right in ABSX."); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldA, readA(), "A has been changed in ABSX.");            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldPS, readPS(), "PS has been changed in ABSX.");         \
    }
#define SECOND_TEST_ABSX
#define THIRD_TEST_ABSX

#define FIRST_TEST_ABSY                                                                          \
    {                                                                                            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readMemory(0x0405), "Memory isn't right in ABSY."); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldA, readA(), "A has been changed in ABSY.");            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldPS, readPS(), "PS has been changed in ABSY.");         \
    }
#define SECOND_TEST_ABSY
#define THIRD_TEST_ABSY

#define FIRST_TEST_INDX                                                                          \
    {                                                                                            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readMemory(0x0400), "Memory isn't right in INDX."); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldA, readA(), "A has been changed in INDX.");            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldPS, readPS(), "PS has been changed in INDX.");         \
    }
#define SECOND_TEST_INDX
#define THIRD_TEST_INDX

#define FIRST_TEST_INDXW                                                                                   \
    {                                                                                                      \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readMemory(0x0400), "Memory isn't right in INDX with wrap."); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldA, readA(), "A has been changed in INDX with wrap.");            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldPS, readPS(), "PS has been changed in INDX with wrap.");         \
    }
#define SECOND_TEST_INDXW
#define THIRD_TEST_INDXW

#define FIRST_TEST_INDY                                                                          \
    {                                                                                            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x55, readMemory(0x0405), "Memory isn't right in INDY."); \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldA, readA(), "A has been changed in INDY.");            \
        TEST_ASSERT_EQUAL_HEX8_MESSAGE(oldPS, readPS(), "PS has been changed in INDY.");         \
    }
#define SECOND_TEST_INDY
#define THIRD_TEST_INDY

#include "../templates/testTemplate.h"

#endif  // _TEST_H