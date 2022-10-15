/**
 * @file    activities.cpp
 * @author  Anton S. Savin <sav1nru<at>mail.ru>
 * @date    14/10/22
 */

#include <cstdint>
#include <algorithm>

#include "activities.h"

auto get_max_activities(const std::vector<Activity> &activities) -> std::vector<Activity>
{
#if NATIVE
    return native(activities);
#else
    return greedy(activities);
#endif
}

auto native(const std::vector<Activity> &activities) -> std::vector<Activity>
{
    if (activities.empty())
    {
        return  {};
    }

    std::vector<Activity> result {};
    std::vector<Activity> subset {};

    for (uint64_t i {0}; i < (decltype(i){1} << activities.size()); ++i)
    {
        for (uint64_t j {0}; j < activities.size(); ++j)
        {
            if (i & (1 << j))
            {
                subset.push_back(activities[j]);
            }
        }

        if (subset.empty())
        {
            continue;
        }

        bool non_intersect {true};

        for (uint64_t j {0}; j < subset.size() - 1 && non_intersect; ++j)
        {
            for (uint64_t k {j + 1}; k < subset.size(); ++k)
            {
                if (subset[j].finish > subset[k].start && subset[k].finish > subset[j].start)
                {
                    non_intersect = false;

                    break;
                }
            }
        }

        if (subset.size() > result.size() && non_intersect)
        {
            result = subset;
        }

        subset.clear();
    }

    return result;
}

auto greedy(const std::vector<Activity> &activities) -> std::vector<Activity>
{
    if (activities.empty())
    {
        return {};
    }

    std::vector<Activity> sorted {activities};

    std::sort(sorted.begin(), sorted.end(), [](const Activity& first, const Activity& second)
    {
        return first.finish < second.finish;
    });

    Activity first_activity      {sorted.front()};
    Activity compatible_activity {sorted.front()};
    auto&&   compatible_iter     {sorted.begin()};

    for (auto&& iter {sorted.begin() + 1}; iter != sorted.end(); ++iter)
    {
        if (first_activity.finish <= iter->start)
        {
            compatible_iter     = iter;
            compatible_activity = *iter;

            break;
        }
    }

    if (first_activity == compatible_activity)
    {
        return {first_activity};
    }

    std::vector<Activity> result {first_activity, compatible_activity};

    for (auto&& iter {compatible_iter}; iter != sorted.end(); ++iter)
    {
        if (compatible_activity.finish <= iter->start)
        {
            result.push_back(*iter);

            compatible_activity = *iter;
        }
    }

    return result;
}
