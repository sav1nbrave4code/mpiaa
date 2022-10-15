/**
 * @file    activities.h
 * @author  Anton S. Savin <sav1nru<at>mail.ru>
 * @date    14/10/22
 */

#ifndef ACTIVITIES_H
#define ACTIVITIES_H

#include <vector>

#include "activity.h"

/**
 * @define  NATIVE
 * @brief   if defined 1 - get_max_activities uses native, if 0 - uses greedy
 */

#define NATIVE 0

/**
 * @function    get_max_activities
 * @param       activities
 * @brief       uses native native or greedy functions for solution
 * @return      subset of mutually compatible processes of maximum size
 */

auto get_max_activities(const std::vector<Activity> &activities) -> std::vector<Activity>;

/**
 * @function    native
 * @param       activities
 * @brief       uses brute force to find subset of mutually compatible processes of maximum size
 * @return      subset of mutually compatible processes of maximum size
 */

auto native(const std::vector<Activity> &activities) -> std::vector<Activity>;

/**
 * @function    greedy
 * @param       activities
 * @brief       uses greedy algorithm to find subset of mutually compatible processes of maximum size
 * @return      subset of mutually compatible processes of maximum size
 */

auto greedy(const std::vector<Activity> &activities) -> std::vector<Activity>;

#endif // ACTIVITIES_H
