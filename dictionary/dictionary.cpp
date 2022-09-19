#include "dictionary.h"

#include <iostream>

auto hash_1(const std::string& string) -> uint32_t
{
    uint32_t result {0};
    for (auto item: string)
    {
        result += static_cast<uint32_t>(item);
    }
    return result;
}

auto hash_2(const std::string& string) -> uint32_t
{
    uint32_t a      {2};
    uint32_t result {0};
    for (uint32_t i {0}; i < string.size(); ++i)
    {
        result += static_cast<uint32_t>(string[i]) * static_cast<uint32_t>(pow(a, i));
    }
    return result;
}

auto hash_3(const std::string& string) -> uint32_t
{
    uint32_t a      {3};
    uint32_t b      {2};
    uint32_t c      {7};
    uint32_t result {c};
    for (auto item: string)
    {
        result = (result << a | result >> b) + static_cast<uint32_t>(item);
    }
    return result;
}

Dictionary::Dictionary(HashFunction hash, int num_of_buckets) :
    table(num_of_buckets),
    hash_function(hash)
{}

/**
 * @brief   std::find_if using to check is new element has the same key, subject to collisions
 */

auto Dictionary::set(const std::string &key, const std::string &value) -> void
{
    uint32_t index   {hash_function(key) % static_cast<uint32_t>(table.size())};
    auto     element = std::find_if(table[index].begin(), table[index].end(),
                                    [&](const std::pair<std::string, std::string>& item){ return item.first == key; });
    if (element->first == key)
    {
        *element = std::make_pair(key, value);
    }
    else
    {
        table[index].push_back(std::make_pair(key, value));
    }
}

auto Dictionary::get(const std::string &key) const -> std::string
{
    if (!size())
    {
        return "";
    }
    uint32_t index {hash_function(key) % static_cast<uint32_t>(table.size())};
    for (const auto& item: table[index])
    {
        if (item.first == key)
        {
            return item.second;
        }
    }
    return "";
}

auto Dictionary::size() const -> int
{
    int size {0};
    for (const auto& bucket: table) {
    	size += static_cast<int>(bucket.size());
    }
    return size;
}

auto Dictionary::clear(int num_of_buckets) -> void
{
    table.clear();
    table.resize(num_of_buckets);
}

