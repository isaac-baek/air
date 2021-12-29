/*
 *   MIT License
 *
 *   Copyright (c) 2021 Samsung Electronics Corporation
 *
 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"), to deal
 *   in the Software without restriction, including without limitation the rights
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *   copies of the Software, and to permit persons to whom the Software is
 *   furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all
 *   copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *   SOFTWARE.
 */

#include "src/lib/Protocol.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(Protocol, ValueCheck)
{
    uint32_t value32{0x00000000};
    EXPECT_EQ(to_dtype(pi::Type1::INPUT_TO_POLICY), value32);

    value32 = 0x00010012;
    EXPECT_EQ(to_dtype(pi::Type2::INITIALIZE_NODE_WITH_RANGE), value32);

    uint16_t value16{0x0001};
    EXPECT_EQ(to_dtype(pi::Type2_Upper::COLLECTION), value16);

    value16 = 0x0106;
    EXPECT_EQ(to_dtype(pi::Type2_Lower::SET_SAMPLING_RATE_ALL), value16);

    value32 = 5;
    EXPECT_EQ(to_dtype(pi::ChainHandler::STREAM), value32);

    const uint32_t max_value{pi::k_max_subject_size};
    EXPECT_GE(max_value, to_dtype(pi::InSubject::COUNT));
    EXPECT_GE(max_value, to_dtype(pi::PolicySubject::COUNT));
}
