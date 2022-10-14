/**
 * @file    lcs.hpp
 * @author  Anton S. Savin <sav1nru<at>mail.ru>
 * @date    14/10/22
 */

#ifndef LCS_H
#define LCS_H

#include <string>

/**
 * @define  NATIVE
 * @brief   if defined 1 - lcs uses native, if 0 lcs uses dynamic
 */

#define NATIVE 0

/**
 * @function    lcs
 * @param       first
 * @param       second
 * @brief       uses native or dynamic functions for solution
 * @return      longest common sequence
 */

auto lcs(const std::string &first, const std::string &second) -> std::string;

/**
 * @function    native
 * @param       first
 * @param       second
 * @brief       uses brute force method to find LCS of two strings
 * @return      longest common sequence
 */

auto native(const std::string &first, const std::string &second) -> std::string;

/**
 * @function    dynamic
 * @param       first
 * @param       second
 * @brief       uses matrix of recurrent values and find LCS by it
 * @return      longest common sequence
 */

auto dynamic(const std::string &first, const std::string &second) -> std::string;

#endif // LCS_H
