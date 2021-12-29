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

#include "node_data_test.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST_F(NodeDataTest, GetData)
{
    uint32_t idx {0};

    node_data = new node::NodeData {air::ProcessorType::PERFORMANCE, 32, 32};
    EXPECT_NE(nullptr, node_data->GetUserDataByHashIndex(idx, idx));
    EXPECT_NE(nullptr, node_data->GetAirData(idx, idx));
    EXPECT_NE(nullptr, node_data->GetAccData(idx, idx));

    idx = 1;
    EXPECT_NE(nullptr, node_data->GetUserDataByHashIndex(idx, idx));
    EXPECT_NE(nullptr, node_data->GetAirData(idx, idx));
    EXPECT_NE(nullptr, node_data->GetAccData(idx, idx));

    idx = 33;
    EXPECT_EQ(nullptr, node_data->GetUserDataByHashIndex(idx, idx));
    EXPECT_EQ(nullptr, node_data->GetAirData(idx, idx));
    EXPECT_EQ(nullptr, node_data->GetAccData(idx, idx));

    EXPECT_NE(nullptr, node_data->GetUserDataByNodeIndex(111, 0));
    EXPECT_NE(nullptr, node_data->GetUserDataByNodeIndex(222, 0));
    EXPECT_NE(nullptr, node_data->GetUserDataByNodeIndex(333, 0));
}

TEST_F(NodeDataTest, SwapBuffer)
{
    uint32_t idx {0};
    node_data = new node::NodeData {air::ProcessorType::PERFORMANCE, 32, 32};
    lib::Data* user_data = node_data->GetUserDataByHashIndex(idx, idx);
    lib::Data* air_data = node_data->GetAirData(idx, idx);

    EXPECT_EQ(1, user_data == node_data->GetUserDataByHashIndex(idx, idx));
    EXPECT_EQ(1, air_data == node_data->GetAirData(idx, idx));

    node_data->SwapBuffer(0);
    EXPECT_EQ(1, air_data == node_data->GetUserDataByHashIndex(idx, idx));
    EXPECT_EQ(1, user_data == node_data->GetAirData(idx, idx));

    node_data->SwapBuffer(33);
}
