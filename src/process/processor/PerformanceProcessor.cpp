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

#include "src/process/processor/PerformanceProcessor.h"

#include <string>

#include "src/config/ConfigInterface.h"
#include "src/lib/json/Json.h"

void
process::PerformanceProcessor::_ProcessData(lib::Data* air_data,
    lib::AccData* acc_data)
{
    lib::PerformanceData* perf_data = static_cast<lib::PerformanceData*>(air_data);
    lib::AccPerformanceData* acc_perf_data = static_cast<lib::AccPerformanceData*>(acc_data);

    if (time > 0.0)
    {
        perf_data->iops = (double)perf_data->iops / time;
        perf_data->bandwidth = (double)perf_data->bandwidth / time;

        double common_divisor = acc_perf_data->time_spent + time;

        acc_perf_data->iops_avg =
            ((double)acc_perf_data->iops_avg / common_divisor *
                acc_perf_data->time_spent) +
            ((double)perf_data->iops / common_divisor * time);

        acc_perf_data->bandwidth_avg =
            ((double)acc_perf_data->bandwidth_avg / common_divisor *
                acc_perf_data->time_spent) +
            ((double)perf_data->bandwidth / common_divisor * time);
    }
    acc_perf_data->time_spent += time;
}

void
process::PerformanceProcessor::_JsonifyData(lib::Data* air_data, lib::AccData* acc_data,
    air::string_view& node_name_view, uint32_t tid, const char* tname,
    uint64_t hash_value, uint32_t filter_index)
{
    lib::PerformanceData* perf_data = static_cast<lib::PerformanceData*>(air_data);
    std::string node_name;
    node_name.assign(node_name_view.data(), node_name_view.size());
    auto& node = air::json(node_name);
    lib::AccPerformanceData* acc_perf_data = static_cast<lib::AccPerformanceData*>(acc_data);

    auto& node_obj = air::json(node_name + "_" + std::to_string(tid) + "_perf_" + std::to_string(hash_value) + "_" + std::to_string(filter_index));

    std::string filter_item = cfg::GetItemStrWithNodeName(node_name_view, filter_index);

    node_obj["target_id"] = {tid};
    node_obj["index"] = {hash_value};
    node_obj["target_name"] = {tname};
    node_obj["filter"] = {filter_item};

    node_obj["iops"] = {perf_data->iops};
    node_obj["bw"] = {perf_data->bandwidth};
    uint32_t cnt = 1;
    for (const auto& pair : perf_data->packet_cnt)
    {
        node_obj["cnt_" + std::to_string(cnt)] = {
            std::to_string(pair.first) + "(sz)-" +
            std::to_string(pair.second) + "(cnt)"};
        cnt++;
    }

    node_obj["iops_avg"] = {acc_perf_data->iops_avg};
    node_obj["bw_avg"] = {acc_perf_data->bandwidth_avg};

    node["objs"] += {node_obj};
}

void
process::PerformanceProcessor::_InitData(lib::Data* air_data,
    lib::AccData* acc_data)
{
    lib::AccPerformanceData* acc_perf_data = static_cast<lib::AccPerformanceData*>(acc_data);
    lib::PerformanceData* perf_data = static_cast<lib::PerformanceData*>(air_data);

    perf_data->access = 0;
    perf_data->bandwidth = 0;
    perf_data->iops = 0;
    perf_data->packet_cnt.clear();

    if (0 != acc_perf_data->need_erase)
    {
        acc_perf_data->bandwidth_avg = 0;
        acc_perf_data->iops_avg = 0;
        acc_perf_data->time_spent = 0.0;
        acc_perf_data->need_erase = 0;
    }
}
