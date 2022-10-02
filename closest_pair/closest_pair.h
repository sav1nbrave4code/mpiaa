/**
 * @file    closest_pair.h
 * @author  Savin Anton S. <sav1nru<at>mail.ru>
 * @date    03/10/22
 */

#pragma once

#include <vector>

#include "point.h"

#define NATIVE 0

auto closest_pair(const std::vector<Point> &points) -> std::pair<Point, Point>;
auto native(const std::vector<Point> &points) -> std::pair<Point, Point>;
auto divide_and_conquer(const std::vector<Point> &points) -> std::pair<Point, Point>;
auto closest_pair_between(const std::vector<Point>& left_points,
                          const std::vector<Point>& right_points,
                          double distance) -> std::pair<Point, Point>;