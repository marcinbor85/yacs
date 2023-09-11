/*
The MIT License (MIT)

Copyright (c) 2023 Marcin Borowicz <marcinbor85@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "crc.h"

class TestCrc : public ::testing::Test
{
protected:
        virtual void SetUp()
        {
        }

        virtual void TearDown()
        {
        }
};

TEST_F(TestCrc, crc_calc_ccitt_array)
{
        struct testCase {
                std::vector<uint8_t> testVector;
                uint16_t initValue;
                uint16_t expectedValue;
        };

        std::vector<testCase> testCases{
                {{0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39}, 0xFFFF, 0x29B1},
                {{0x29, 0xB1}, 0x29B1, 0x0000},
                {{}, 0x55AA, 0x55AA},
        };

        for (auto test : testCases) {
                EXPECT_EQ(test.expectedValue, crc_calc_ccitt_array(test.testVector.data(), test.testVector.size(), test.initValue));
        }
}

TEST_F(TestCrc, crc_calc_ccitt)
{
        struct testCase {
                uint8_t testByte;
                uint16_t initValue;
                uint16_t expectedValue;
        };

        std::vector<testCase> testCases{
                {0x00, 0xFFFF, 0xE1F0},
                {0xFF, 0xFFFF, 0xFF00},

                {0x31, 0xFFFF, 0xC782},
                {0x32, 0xC782, 0x3DBA},
                {0x33, 0x3DBA, 0x5BCE},
                {0x34, 0x5BCE, 0x5349},
                {0x35, 0x5349, 0x4560},
                {0x36, 0x4560, 0x2EF4},
                {0x37, 0x2EF4, 0x7718},
                {0x38, 0x7718, 0xA12B},
                {0x39, 0xA12B, 0x29B1},

                {0x29, 0x29B1, 0xB100},
                {0xB1, 0xB100, 0x0000},
        };

        for (auto test : testCases) {
                EXPECT_EQ(test.expectedValue, crc_calc_ccitt(test.testByte, test.initValue));
        }
}
