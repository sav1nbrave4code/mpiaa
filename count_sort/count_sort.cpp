#include "count_sort.h"

std::vector<int> count_sort(const std::vector<int> &array, int min, int max) {
    std::vector<int> result {};
    std::vector<int> counts (max == min ? 1 : max - min + 1);
    for (const auto& item: array)
    {
        ++counts[item - min];
    }
    for (std::size_t i {0}; i < counts.size(); ++i)
    {
        while (counts[i]--)
        {
            result.push_back(static_cast<int>(i) + min);
        }
    }
    return result;
}
