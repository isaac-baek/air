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

#ifndef AIR_COLLECTION_HISTOGRAM_WRITER_H
#define AIR_COLLECTION_HISTOGRAM_WRITER_H

#include "src/collection/writer/Writer.h"
#include "src/lib/Data.h"

namespace collection
{
class HistogramWriter : public Writer
{
public:
    HistogramWriter(void)
    {
    }
    virtual ~HistogramWriter(void)
    {
    }
    inline void
    LogData(lib::Data* data, uint64_t u_value) override
    {
        if (nullptr == data)
        {
            return;
        }
        lib::HistogramData* hist_data {static_cast<lib::HistogramData*>(data)};
        int64_t value {static_cast<int64_t>(u_value)};

        if (false == hist_data->access)
        {
            hist_data->period_min_value = value;
            hist_data->period_max_value = value;
        }
        else
        {
            if (hist_data->period_min_value > value)
            {
                hist_data->period_min_value = value;
            }
            if (hist_data->period_max_value < value)
            {
                hist_data->period_max_value = value;
            }
        }

        if (hist_data->bucket_lower_bound > value)
        {
            hist_data->period_underflow++;
        }
        else if (hist_data->bucket_upper_bound < value)
        {
            hist_data->period_overflow++;
        }
        else
        {
            uint64_t bucket_index {0};
            switch (hist_data->bucket_type)
            {
                case lib::BucketType::LINEAR:
                    bucket_index = (value - hist_data->bucket_lower_bound) /
                        hist_data->bucket_scale;
                    break;
                case lib::BucketType::EXPONENTIAL:
                    bucket_index = hist_data->bucket_zero_index;
                    if (0 < value)
                    {
                        while (value)
                        {
                            value /= hist_data->bucket_scale;
                            bucket_index++;
                        }
                    }
                    else if (0 > value)
                    {
                        while (value)
                        {
                            value /= hist_data->bucket_scale;
                            bucket_index--;
                        }
                    }
                    break;
            }
            if (bucket_index < hist_data->bucket_size)
            {
                hist_data->period_bucket[bucket_index]++;
            }
        }

        hist_data->access = true;
    }
    int
    SetSamplingRate(uint32_t rate) override
    {
        return 0;
    }
};

} // namespace collection

#endif // AIR_COLLECTION_HISTOGRAM_WRITER_H
