#include "duplicates.h"
#include "../catch.hpp"

#include <algorithm>
#include <iostream>
#include <random>

std::vector<int> shuffled_sequence(int size, int start = 0)
{
    std::vector<int> result(size);
    iota(result.begin(), result.end(), start);
    random_shuffle(result.begin(), result.end());
    return result;
}

// Returns sequence of random numbers of specified size, with values from 0 to max.
std::vector<int> random_sequence(int size, int max)
{
    std::default_random_engine generator;
    std:: uniform_int_distribution<int> distribution(0, max);
    std::vector<int> result;
    for (int i = 0; i < size; i++) {
        result.push_back(distribution(generator));
    }
    return result;
}

std::vector<int> uniqe_vector(int size)
{
    std::vector<int> result;
    for (int i {0}; i < size; ++i)
    {
        result.push_back(i);
    }
    return result;
}

template <class T>
std::vector<T> sorted(const typename std::vector<T> &data) {
    typename std::vector<T> sorted_data = data;
    std::sort(sorted_data.begin(), sorted_data.end());
    return sorted_data;
}

TEST_CASE ("Empty array") {
    const std::vector<int> data = {};
    CHECK_FALSE(has_duplicates(data));
    CHECK(sorted(get_duplicates(data)) == std::vector<int> {});
}

TEST_CASE ("Single element") {
    const std::vector<int> data = {1};
    CHECK_FALSE(has_duplicates(data));
    CHECK(sorted(get_duplicates(data)) == std::vector<int> {});
}

TEST_CASE ("Many elements") {
    const std::vector<int> data = {2, 1, -4, 7};
    CHECK_FALSE(has_duplicates(data));
    CHECK(sorted(get_duplicates(data)) == std::vector<int> {});
}

TEST_CASE ("Many elements, one duplicate") {
    const std::vector<int> data = {2, -3, 0, 2, 7, 1};
    CHECK(has_duplicates(data));
    CHECK(sorted(get_duplicates(data)) == std::vector<int> {2});
}

TEST_CASE ("Many elements, many duplicates") {
    const std::vector<int> data = {2, -3, 0, 2, 1, -3, 4, 1, -1, 2};
    CHECK(has_duplicates(data));
    CHECK(sorted(get_duplicates(data)) == std::vector<int> {-3, 1, 2});
}

TEST_CASE ("Single duplicated elem") {
    const std::vector<int> data = {4, 4, 4, 4};
    CHECK(has_duplicates(data));
    CHECK(sorted(get_duplicates(data)) == std::vector<int> {4});
}

TEST_CASE("Time check")
{
    const int N = 100000;
    std::cout << std::fixed;

    /**
     * @brief   Container for time tests
     */
    std::vector<int> vector;
    vector.resize(N);

    /**
     * @brief   Same values
     */
    std::fill(vector.begin(), vector.end(), N);
    auto begin = std::chrono::high_resolution_clock::now();
    CHECK(has_duplicates(vector));
    auto end   = std::chrono::high_resolution_clock::now();
    std::cout << "has_duplicates (same) time: " << std::chrono::duration<double>(end - begin).count() << std::endl;

    begin = std::chrono::high_resolution_clock::now();
    CHECK(get_duplicates(vector) == std::vector<int> {N});
    end   = std::chrono::high_resolution_clock::now();
    std::cout << "get_duplicates (same) time: " << std::chrono::duration<double>(end - begin).count() << std::endl;
    vector.clear();

    /**
     * @brief   Random values
     */
    vector = random_sequence(N, N);
    begin  = std::chrono::high_resolution_clock::now();
    CHECK(has_duplicates(vector));
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "has_duplicates (random) time: " << std::chrono::duration<double>(end - begin).count() << std::endl;

    begin  = std::chrono::high_resolution_clock::now();
    vector = get_duplicates(vector);
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "get_duplicates (random) time: " << std::chrono::duration<double>(end - begin).count() << std::endl;
    vector.clear();

    /**
     * @brief   Unique values
     */
    vector = uniqe_vector(N);
    begin  = std::chrono::high_resolution_clock::now();
    CHECK_FALSE(has_duplicates(vector));
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "has_duplicates (unique) time: " << std::chrono::duration<double>(end - begin).count() << std::endl;

    begin  = std::chrono::high_resolution_clock::now();
    CHECK(get_duplicates(vector).empty());
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "get_duplicates (unique) time: " << std::chrono::duration<double>(end - begin).count() << std::endl;
}
