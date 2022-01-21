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

#ifndef AIR_CHAIN_MANAGER_H
#define AIR_CHAIN_MANAGER_H

#include <cstdint>

#include "src/lib/Design.h"
#include "src/lib/Protocol.h"
#include "src/meta/GlobalMeta.h"
#include "src/thread/Thread.h"

namespace chain
{
class TaskChain
{
public:
    void
    SetPeriod(uint32_t new_period)
    {
        period = new_period;
        deadline = period;
    }
    uint32_t
    GetPeriod(void)
    {
        return period;
    }
    uint32_t
    GetDeadline(void)
    {
        return deadline;
    }
    virtual void RunChain(lib_design::AbstractCoRHandler** cor_handler,
        meta::GlobalMeta* g_meta, int32_t option = 0) = 0;
    bool IsRun(meta::GlobalMeta* g_meta, uint32_t delayed_time);

protected:
    explicit TaskChain(uint32_t new_period): period(new_period)
    {
        deadline = period;
    }

private:
    void _ResetTime(void);
    int32_t _SpendTime(uint32_t time);

    uint32_t period {0};  // 10 millisecond resolution
    int32_t deadline {0}; // 10 millisecond resolution
};

class SwitchGearTask : public TaskChain
{
public:
    SwitchGearTask(void): TaskChain(50)
    {
    }
    virtual void RunChain(lib_design::AbstractCoRHandler** cor_handler,
        meta::GlobalMeta* g_meta, int32_t option = 0);
};

class PreprocessTask : public TaskChain
{
public:
    PreprocessTask(void): TaskChain(100)
    {
    }
    virtual void RunChain(lib_design::AbstractCoRHandler** cor_handler,
        meta::GlobalMeta* g_meta, int32_t option = 0);
};

class CLITask : public TaskChain
{
public:
    CLITask(void): TaskChain(100)
    {
    }
    virtual void RunChain(lib_design::AbstractCoRHandler** cor_handler,
        meta::GlobalMeta* g_meta, int32_t option = 0);
};

class AnalysisTask : public TaskChain
{
public:
    AnalysisTask(void): TaskChain(1000)
    {
    }
    virtual void RunChain(lib_design::AbstractCoRHandler** cor_handler,
        meta::GlobalMeta* g_meta, int32_t option = 0);
};

class ChainManager : public thread::OneTimeThread
{
public:
    ChainManager(void)
    {
    }
    virtual ~ChainManager(void)
    {
    }
    explicit ChainManager(meta::GlobalMeta* new_global_meta)
    : global_meta(new_global_meta)
    {
    }
    void Init(void);
    void RunChain(uint32_t delayed_time);
    void
    AttachChain(lib_design::AbstractCoRHandler* new_cor_handler, uint32_t index)
    {
        cor_handler[index] = new_cor_handler;
    }
    virtual void RunThread(uint32_t run_skip_count);
    SwitchGearTask*
    GetSwitchGearTask(void)
    {
        return &switch_gear_task;
    }
    PreprocessTask*
    GetPreprocessTask(void)
    {
        return &preprocess_task;
    }
    CLITask*
    GetCLITask(void)
    {
        return &cli_task;
    }
    AnalysisTask*
    GetAnalysisTask(void)
    {
        return &analysis_task;
    }

private:
    lib_design::AbstractCoRHandler* cor_handler[to_dtype(pi::ChainHandler::COUNT)] {
        nullptr,
    };
    SwitchGearTask switch_gear_task {};
    PreprocessTask preprocess_task {};
    CLITask cli_task {};
    AnalysisTask analysis_task {};
    meta::GlobalMeta* global_meta {nullptr};
};

} // namespace chain

#endif // AIR_CHAIN_MANAGER_H
