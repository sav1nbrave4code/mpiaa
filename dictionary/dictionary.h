#pragma once

#include <string>
#include <functional>
#include <vector>
#include <list>
#include <cmath>

using HashFunction = std::function<uint32_t(const std::string&)>;

/**
* @function    hash_1
* @function    hash_2
* @function    hash_3
* @brief       Three different implementations of hash-functions
*/

auto hash_1(const std::string& string)-> uint32_t;
auto hash_2(const std::string& string) -> uint32_t;
auto hash_3(const std::string& string) -> uint32_t;

/**
 * @class   Dictionary
 * @brief   Realization of hash-table (unordered map) with simple operations
 */

class Dictionary {

using KeyValue = std::pair<std::string, std::string>;

public:
    Dictionary(HashFunction hash = std::hash<std::string> {}, int num_of_buckets = 1000);
    ~Dictionary() = default;

public:
    auto set(const std::string &key, const std::string &value) -> void;
    auto get(const std::string &key) const -> std::string;
    auto size() const -> int;
    auto clear(int num_of_buckets = 1000) -> void;

private:
    std::vector<std::list<KeyValue>> table          {};
    HashFunction                     hash_function  {};
};
