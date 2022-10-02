/**
 * @file    closest_pair.cpp
 * @author  Savin Anton S. <sav1nru<at>mail.ru>
 * @date    03/10/22
 */

#include <stdexcept>
#include <limits>
#include <algorithm>
#include <cmath>

#include "closest_pair.h"

auto closest_pair(const std::vector<Point> &points) -> std::pair<Point, Point>
{
	if (points.size() < 2)
    {
        throw std::invalid_argument{"Not enough points"};
    }

    auto result {std::make_pair(Point{}, Point{})};

#if NATIVE
    result = native(points);
#else
    result = divide_and_conquer(points);
#endif

    return  result;
}

auto native(const std::vector<Point> &points) -> std::pair<Point, Point>
{
    auto result           {std::make_pair(Point{}, Point{})};
    auto minimal_distance {std::numeric_limits<double>::infinity()};

    for (std::uint64_t i {0}; i < points.size() - 1; ++i)
    {
        for (std::uint64_t j {i + 1}; j < points.size(); ++j)
        {
            if (points[i].distance(points[j]) < minimal_distance)
            {
                minimal_distance = points[i].distance(points[j]);
                result           = std::make_pair(points[i], points[j]);
            }
        }
    }

    return result;
}

auto closest_pair_between(const std::vector<Point>& left_points,
                          const std::vector<Point>& right_points,
                          double distance) -> std::pair<Point, Point>
{
    auto               result          {std::make_pair(left_points.back(), right_points.front())};
    double             median          {(left_points.back().x + right_points.front().x) / 2};
    std::vector<Point> points_in_range {};

    for(const auto& point: left_points)
    {
        if (std::abs(median - point.x) < distance)
        {
            points_in_range.push_back(point);
        }
    }
    for(const auto& point: right_points) {
        if (std::abs(median - point.x) < distance) {
            points_in_range.push_back(point);
        }
    }

    std::sort(points_in_range.begin(), points_in_range.end(), [](const Point& lhs, const Point& rhs) -> bool
    {
        return lhs.y < rhs.y;
    });

    for (std::uint64_t i {0}; i < points_in_range.size() - 1; ++i)
    {
        for (std::uint64_t j {i + 1}; j < points_in_range.size(); ++j)
        {
            if (std::abs(points_in_range[i].y - points_in_range[j].y) > distance)
            {
                break;
            }
            if (points_in_range[i].distance(points_in_range[j]) < result.first.distance(result.second))
            {
                result = std::make_pair(points_in_range[i], points_in_range[j]);
            }
        }
    }

    return result;
}

auto divide_and_conquer(const std::vector<Point> &points) -> std::pair<Point, Point>
{
    if (points.size() <= 3)
    {
        return native(points);
    }

    auto               result           {std::make_pair(Point(), Point())};
    auto               sorted_points    {points};
    std::vector<Point> right_half       {};
    std::vector<Point> left_half        {};

    std::sort(sorted_points.begin(), sorted_points.end(), [](const Point& lhs, const Point& rhs) -> bool
    {
        return lhs.x < rhs.x;
    });

    for (std::uint64_t i {0}; i < sorted_points.size() / 2; ++i)
    {
        right_half.push_back(sorted_points[i]);
    }
    for (std::uint64_t i {sorted_points.size() / 2}; i < sorted_points.size(); ++i)
    {
        left_half.push_back(sorted_points[i]);
    }

    auto right_pair       {native(right_half)};
    auto left_pair        {native(left_half)};
    auto minimal_distance {std::min(right_pair.first.distance(right_pair.second),
                                    left_pair.first.distance(left_pair.second))};
    auto middle_pair      {closest_pair_between(left_half, right_half, minimal_distance)};
    auto right_distance   {right_pair.first.distance(right_pair.second)};
    auto left_distance    {left_pair.first.distance(left_pair.second)};
    auto middle_distance  {middle_pair.first.distance(middle_pair.second)};

    if (left_distance >= right_distance && right_distance <= middle_distance)
    {
        result = right_pair;
    }
    else if (right_distance >= left_distance && left_distance <= middle_distance)
    {
        result = left_pair;
    }
    else
    {
        result = middle_pair;
    }

    return result;
}

