#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
#include <random>
#include <chrono>

#include <vector>
#include <list>
#include <set>

// Returns shuffled sequence of unique numbers of specified size, with values from start to start + size - 1.
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

int main(int argc, char **argv) {
    const int N = (argc > 1 ? std::stoi(argv[1]) : 10);
    const int M = N / 10;
    std::cout << std::fixed;

    /**
     * @brief   Containers for the tests
     */
    std::vector<int> vector {};
    std::list<int>   list   {};
    std::set<int>    set    {};


    const auto items = shuffled_sequence(N);

    /**
     * @brief   Insertion for vector
     */
    auto begin = std::chrono::high_resolution_clock::now();
    for (const auto& item: items)
    {
        vector.push_back(item);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "vector insert back time: " << std::chrono::duration<double>(end - begin).count() << std::endl;
    vector.clear();
    begin    = std::chrono::high_resolution_clock::now();
    for (const auto& item: items)
    {
        vector.insert(vector.begin(), item);
    }
    end      = std::chrono::high_resolution_clock::now();
    std::cout << "vector insert begin time: " << std::chrono::duration<double>(end - begin).count() << std::endl;

    /**
     * @brief   Insertion for list
     */
    begin = std::chrono::high_resolution_clock::now();
    for (const auto& item: items)
    {
        list.push_back(item);
    }
    end   = std::chrono::high_resolution_clock::now();
    std::cout << "list insert back time: " << std::chrono::duration<double>(end - begin).count() << std::endl;
    list.clear();
    begin = std::chrono::high_resolution_clock::now();
    for (const auto& item: items)
    {
        list.insert(list.begin(), item);
    }
    end   = std::chrono::high_resolution_clock::now();
    std::cout << "list insert begin time: " << std::chrono::duration<double>(end - begin).count() << std::endl;

    /**
     * @brief   Insertion for set
     */
    begin = std::chrono::high_resolution_clock::now();
    for (const auto& item: items)
    {
        set.insert(item);
    }
    end   = std::chrono::high_resolution_clock::now();
    std::cout << "set insert time: " << std::chrono::duration<double>(end - begin).count() << std::endl;


    /**
     * @brief   Linear search in vector
     */
    int  counter          = 0;
    auto items_for_search = random_sequence(M, 2 * M);
    begin                 = std::chrono::high_resolution_clock::now();
    for (const auto& item: items_for_search)
    {
        auto iter = std::find(vector.begin(), vector.end(), item);
        if (iter != vector.end())
        {
            ++counter;
        }
    }
    end                   = std::chrono::high_resolution_clock::now();
    std::cout << "vector linear search time: " << std::chrono::duration<double>(end - begin).count() << std::endl;
    std::cout << "vector linear search found " << counter << " items" << std::endl;

    /**
     * @brief   Linear search in list
     */
    counter = 0;
    begin   = std::chrono::high_resolution_clock::now();
    for (const auto& item: items_for_search)
    {
        auto iter = std::find(list.begin(), list.end(), item);
        if (iter != list.end())
        {
            ++counter;
        }
    }
    end     = std::chrono::high_resolution_clock::now();
    std::cout << "list linear search time: " << std::chrono::duration<double>(end - begin).count() << std::endl;
    std::cout << "list linear search found " << counter << " items" << std::endl;

    /**
     * @brief   Binary search in set
     */
    counter = 0;
    begin   = std::chrono::high_resolution_clock::now();
    for (const auto& item: items_for_search)
    {
        auto iter = set.find(item);
        if (iter != set.end())
        {
            ++counter;
        }
    }
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "set binary search time: " << std::chrono::duration<double>(end - begin).count() << std::endl;
    std::cout << "set binary search found " << counter << " items" << std::endl;
}
