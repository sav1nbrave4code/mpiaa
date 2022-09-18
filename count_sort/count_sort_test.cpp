#include <random>
#include <algorithm>
#include <chrono>
#include <iostream>

#include "../catch.hpp"

#include "count_sort.h"

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

TEST_CASE( "Empty array", "[count_sort]" ) {    
    CHECK( count_sort({}, 0, 0) == std::vector<int> {} );
}

TEST_CASE( "One element array", "[count_sort]" ) {
    CHECK( count_sort({1}, 1, 1) == std::vector<int> {1} );
}

TEST_CASE( "Array from one element", "[count_sort]" ) { 
    CHECK( count_sort({1, 1, 1, 1}, 1, 1) == std::vector<int> {1, 1, 1, 1} );   
}

TEST_CASE( "Sorted array", "[count_sort]" ) {    
    CHECK( count_sort({1, 2, 4, 9}, 1, 9) == std::vector<int> {1, 2, 4, 9} );   
}

TEST_CASE( "Unsorted array", "[count_sort]" ) { 
    CHECK( count_sort({3, 0, -1, 9, 2}, -1, 9) == std::vector<int> {-1, 0, 2, 3, 9} );   
}

TEST_CASE( "Sorted array with duplicates", "[count_sort]" ) {
    CHECK( count_sort({0, 1, 1, 2, 2, 2, 9}, 0, 10) == std::vector<int> {0, 1, 1, 2, 2, 2, 9} );
}

TEST_CASE( "Unsorted array with duplicates", "[count_sort]" ) {
    CHECK( count_sort({9, -1, 2, 1, -1, 3, 9, 2}, -10, 10) == std::vector<int> {-1, -1, 1, 2, 2, 3, 9, 9} );
}

TEST_CASE( "Array with big range", "[count_sort]" ) {
    CHECK( count_sort({1, 0, 1000000, 0, -1000000}, -2000000, 2000000) == std::vector<int> {-1000000, 0, 0, 1, 1000000} );
}

TEST_CASE(" Time check ")
{
    std::vector<int> data   {random_sequence(1000, 1000)};
    std::cout << std::fixed;

    auto begin  = std::chrono::high_resolution_clock::now();
    auto result = count_sort(data, 0 , 1000);
    auto end    = std::chrono::high_resolution_clock::now();
    std::cout << "count_sort time (1000): " << std::chrono::duration<double>(end - begin).count() << std::endl;
    std::cout << "array size: " << result.size() << std::endl;

    begin  = std::chrono::high_resolution_clock::now();
    std::sort(data.begin(), data.end());
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "std::sort time (1000): " << std::chrono::duration<double>(end - begin).count() << std::endl;
    std::cout << "array size: " << data.size() << std::endl;

    data   = random_sequence(10000, 10000);
    begin  = std::chrono::high_resolution_clock::now();
    result = count_sort(data, 0 , 10000);
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "count_sort time (10000): " << std::chrono::duration<double>(end - begin).count() << std::endl;
    std::cout << "array size: " << result.size() << std::endl;

    begin  = std::chrono::high_resolution_clock::now();
    std::sort(data.begin(), data.end());
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "std::sort time (10000): " << std::chrono::duration<double>(end - begin).count() << std::endl;
    std::cout << "array size: " << data.size() << std::endl;

    data   = random_sequence(100000, 100000);
    begin  = std::chrono::high_resolution_clock::now();
    result = count_sort(data, 0 , 100000);
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "count_sort time (100000): " << std::chrono::duration<double>(end - begin).count() << std::endl;
    std::cout << "array size: " << result.size() << std::endl;

    begin  = std::chrono::high_resolution_clock::now();
    std::sort(data.begin(), data.end());
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "std::sort time (100000): " << std::chrono::duration<double>(end - begin).count() << std::endl;
    std::cout << "array size: " << data.size() << std::endl;

    data   = random_sequence(1000000, 1000000);
    begin  = std::chrono::high_resolution_clock::now();
    result = count_sort(data, 0 , 1000000);
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "count_sort time (1000000): " << std::chrono::duration<double>(end - begin).count() << std::endl;
    std::cout << "array size: " << result.size() << std::endl;

    begin  = std::chrono::high_resolution_clock::now();
    std::sort(data.begin(), data.end());
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "std::sort time (1000000): " << std::chrono::duration<double>(end - begin).count() << std::endl;
    std::cout << "array size: " << data.size() << std::endl;

    data   = random_sequence(10000000, 10000000);
    begin  = std::chrono::high_resolution_clock::now();
    result = count_sort(data, 0 , 10000000);
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "count_sort time (10000000): " << std::chrono::duration<double>(end - begin).count() << std::endl;
    std::cout << "array size: " << result.size() << std::endl;

    begin  = std::chrono::high_resolution_clock::now();
    std::sort(data.begin(), data.end());
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "std::sort time (10000000): " << std::chrono::duration<double>(end - begin).count() << std::endl;
    std::cout << "array size: " << data.size() << std::endl;
}