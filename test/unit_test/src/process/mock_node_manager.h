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

#include "src/data_structure/NodeManager.h"

#include <gmock/gmock.h>

namespace node
{

class MockNodeManager : public NodeManager
{
public:
    using NodeManager::NodeManager;
    MOCK_METHOD(NodeDataArray*, GetNodeDataArray, (uint32_t tid), (override));
    MOCK_METHOD(void, SetNodeDataArrayName, (uint32_t tid), (override));
    MOCK_METHOD(void, CreateNodeDataArray, (uint32_t tid), (override));
    MOCK_METHOD(void, DeleteNodeDataArray, (NodeDataArray* node_data_array), (override));
    MOCK_METHOD(bool, CanDeleteNodeDataArray, (NodeDataArray* node_data_array), (override));
    MOCK_METHOD(lib::AccLatencyData*, GetAccLatData, (uint32_t nid, uint32_t hash_index, uint32_t filter_index), (override));
};

} // namespace node
