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

#include "cobs.h"

class TestCobs : public ::testing::Test
{
protected:
        virtual void SetUp()
        {
        }

        virtual void TearDown()
        {
        }
};

TEST_F(TestCobs, cobs_encode)
{
        uint8_t rx_buf[256];
        struct cobs cobs;

        cobs_init(&cobs, rx_buf, sizeof(rx_buf));
        
        std::vector<uint8_t> testVector{0x01, 0x02, 0x03};
        cobs_encode(&cobs, testVector.data(), testVector.size());
}
