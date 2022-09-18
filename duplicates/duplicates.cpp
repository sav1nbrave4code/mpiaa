#include "duplicates.h"

#include <algorithm>

bool native_realization = false;

bool has_duplicates(const std::vector<int> &data) {
    if (data.empty())
    {
        return false;
    }
    for (auto first = data.begin(), second = first + 1; second != data.end(); ++second)
    {
        if (*first == *second) {
            return true;
        }
    }
    return false;
}

std::vector<int> get_duplicates(const std::vector<int> &data) {
    std::vector<int> result;
    if (data.empty())
    {
        return result;
    }
    if (native_realization)
    {
        for (auto first = data.begin(); first != data.end(); ++first)
        {
            for (auto second = first + 1; second != data.end(); ++second)
            {
                if (*first == *second && std::find(result.begin(), result.end(), *first) == result.end())
                {
                    result.push_back(*first);
                }
            }
        }
    }
    else
    {
        std::vector sorted_data {data};
        std::sort(sorted_data.begin(), sorted_data.end());
        for (size_t i {0}; i < sorted_data.size() - 1; ++i)
        {
            if (sorted_data[i] == sorted_data[i + 1] &&
                std::find(result.begin(), result.end(), sorted_data[i]) == result.end())
            {
                result.push_back(sorted_data[i]);
            }
        }
    }
    return result;
}
