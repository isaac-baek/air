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

#ifndef AIR_MSG_H
#define AIR_MSG_H

#include <cstdint>

namespace lib
{
struct MsgEntry
{
    uint32_t type1 {0};
    uint32_t type2 {0};
    uint32_t value1 {0};
    uint32_t value2 {0};
    int pid {0};
    int cmd_type {0};
    int cmd_order {0};
};

enum class MsgType : int64_t
{
    FILE = 1,
    CLI,
    NULLMsgType
};

enum class AirStatus : uint32_t
{
    RUN,
    DONE,
    ABNORMAL_DONE,
    IDLE
};

struct FileMsg
{
    int64_t type {(int64_t)MsgType::FILE};
    char name[50] {
        0,
    };
    uint32_t air_pid {0};
    AirStatus status {AirStatus::IDLE};
    char time_stamp[30] {
        0,
    };
};

enum class CmdType : uint32_t
{
    SetStreamingInterval = 1,
    RunNode,
    InitNode,
    GetConfig,
    NullCliCmd
};

struct CliMsg
{
    uint32_t msg_id {0};
    CmdType cmd {CmdType::NullCliCmd};
    char node_list[256] {
        0,
    };
    uint32_t value {0};
    uint32_t air_pid {0};
};

} // namespace lib

#endif // AIR_MSG_H
