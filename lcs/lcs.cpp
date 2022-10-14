/**
 * @file    lcs.cpp
 * @author  Anton S. Savin <sav1nru<at>mail.ru>
 * @date    14/10/22
 */

#include "lcs.h"

auto lcs(const std::string& first, const std::string& second) -> std::string
{
#if NATIVE
    return native(first, second);
#else
    return dynamic(first, second);
#endif
}

auto native(const std::string &first, const std::string &second) -> std::string
{
    if (first.empty() || second.empty())
    {
        return "";
    }

    std::string first_substring  {first.substr(1)};
    std::string second_substring {second.substr(1)};

    if (first[0] == second[0])
    {
        return first[0] + native(first_substring, second_substring);
    }

    std::string first_pattern  {native(first_substring, second)};
    std::string second_pattern {native(first, second_substring)};

    return first_pattern.size() > second_pattern.size() ? first_pattern : second_pattern;
}

auto dynamic(const std::string &first, const std::string &second) -> std::string
{

    if (first.empty() || second.empty())
    {
        return "";
    }

    std::string result  {};
    uint64_t**  matrix  {new uint64_t*[first.size() + 1]};

    for (uint64_t i {0}; i < first.size() + 1; ++i)
    {
        matrix[i] = new uint64_t[second.size() + 1]{};
    }

    for (uint64_t i {1}; i < first.size() + 1; ++i)
    {
        for (uint64_t j {1}; j < second.size() + 1; ++j)
        {
            if (first[i - 1] == second[j - 1])
            {
                matrix[i][j] = matrix[i - 1][j - 1] + 1;
            }
            else
            {
                matrix[i][j] = std::max(matrix[i - 1][j], matrix[i][j - 1]);
            }
        }
    }

    uint64_t row    {first.size()};
    uint64_t column {second.size()};

    while (row && column)
    {
        if (first[row - 1] == second[column - 1])
        {
            result.push_back(first[row - 1]);
            --row;
            --column;
        }
        else if (matrix[row - 1][column] == matrix[row][column])
        {
            --row;
        }
        else
        {
            --column;
        }
    }

    std::reverse(result.begin(), result.end());

    for (uint64_t i {0}; i < first.size() + 1; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;

    return result;
}


