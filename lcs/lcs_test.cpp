#include <random>
#include <chrono>
#include <iostream>
#include <string>

#include "../catch.hpp"
#include "lcs.h"

static const char*   alphabet      {"0123456789"
                                    "abcdefghijklmnopqrstuvwxyz"
                                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
static const uint8_t alphabet_size {62};

auto random_string(const uint64_t size) -> std::string
{
    std::random_device              random_device {};
    std::mt19937                    generator     {random_device()};
    std::uniform_int_distribution<> distribution  {0, alphabet_size};
    std::string                     result        {};

    for (uint64_t i {0}; i < size; ++i)
    {
        result += alphabet[distribution(generator)];
    }

    return result;
}


TEST_CASE( "Both strings are empty" ) {
    CHECK( lcs("", "") == "" );
}

TEST_CASE( "One string is empty" ) {
    CHECK( lcs("", "abcd") == "" );
    CHECK( lcs("abcd", "") == "" );
}

TEST_CASE( "Equal strings" ) {
    CHECK( lcs("abcd", "abcd") == "abcd" );
}

TEST_CASE( "Substring" ) {
    CHECK( lcs("abab", "ab") == "ab" );
}

TEST_CASE( "Substring in the middle" ) {
    CHECK( lcs("xyaban", "abarab") == "aba" );
}

TEST_CASE( "Subsequences" ) {
    CHECK( lcs("nahybser", "iunkayxbis") == "naybs" );
    CHECK( lcs("z1artunx", "yz21rx") == "z1rx" );
    CHECK( lcs("z1arxzyx1a", "yz21rx") == "z1rx" );
    CHECK( lcs("yillnum", "numyjiljil") == "yill" );
}

TEST_CASE( "Reverse subsequence" ) {
    auto result = lcs("xablar", "ralbax");
    CHECK( (result == "aba" || result == "ala") ); 
}

TEST_CASE("Time check")
{
    auto N      {10};
    auto first  {random_string(N)};
    auto second {random_string(N / 2)};
    auto begin  {std::chrono::high_resolution_clock::now()};
    auto result {lcs(first, second)};
    auto end    {std::chrono::high_resolution_clock::now()};

    std::cout << std::fixed;
    std::cout << N << " time: " << std::chrono::duration<double>(end - begin).count() << std::endl;
    std::cout << "result: " << result.size() << std::endl;

#if NATIVE
    N      = 20;
    first  = random_string(N);
    second = random_string(N / 2);
    begin  = std::chrono::high_resolution_clock::now();
    result = lcs(first, second);
    end    = std::chrono::high_resolution_clock::now();

    std::cout << N << " time: " << std::chrono::duration<double>(end - begin).count() << std::endl;
    std::cout << "result: " << result.size() << std::endl;

    N      = 22;
    first  = random_string(N);
    second = random_string(N / 2);
    begin  = std::chrono::high_resolution_clock::now();
    result = lcs(first, second);
    end    = std::chrono::high_resolution_clock::now();

    std::cout << N << " time: " << std::chrono::duration<double>(end - begin).count() << std::endl;
    std::cout << "result: " << result.size() << std::endl;

    N      = 25;
    first  = random_string(N);
    second = random_string(N / 2);
    begin  = std::chrono::high_resolution_clock::now();
    result = lcs(first, second);
    end    = std::chrono::high_resolution_clock::now();

    std::cout << N << " time: " << std::chrono::duration<double>(end - begin).count() << std::endl;
    std::cout << "result: " << result.size() << std::endl;

#else
    N      = 20;
    first  = random_string(N);
    second = random_string(N / 2);
    begin  = std::chrono::high_resolution_clock::now();
    result = lcs(first, second);
    end    = std::chrono::high_resolution_clock::now();

    std::cout << N << " time: " << std::chrono::duration<double>(end - begin).count() << std::endl;
    std::cout << "result: " << result.size() << std::endl;

    N      = 22;
    first  = random_string(N);
    second = random_string(N / 2);
    begin  = std::chrono::high_resolution_clock::now();
    result = lcs(first, second);
    end    = std::chrono::high_resolution_clock::now();

    std::cout << N << " time: " << std::chrono::duration<double>(end - begin).count() << std::endl;
    std::cout << "result: " << result.size() << std::endl;

    N      = 25;
    first  = random_string(N);
    second = random_string(N / 2);
    begin  = std::chrono::high_resolution_clock::now();
    result = lcs(first, second);
    end    = std::chrono::high_resolution_clock::now();

    std::cout << N << " time: " << std::chrono::duration<double>(end - begin).count() << std::endl;
    std::cout << "result: " << result.size() << std::endl;

    N      = 100;
    first  = random_string(N);
    second = random_string(N / 2);
    begin  = std::chrono::high_resolution_clock::now();
    result = lcs(first, second);
    end    = std::chrono::high_resolution_clock::now();

    std::cout << N << " time: " << std::chrono::duration<double>(end - begin).count() << std::endl;
    std::cout << "result: " << result.size() << std::endl;

    N      = 1000;
    first  = random_string(N);
    second = random_string(N / 2);
    begin  = std::chrono::high_resolution_clock::now();
    result = lcs(first, second);
    end    = std::chrono::high_resolution_clock::now();

    std::cout << N << " time: " << std::chrono::duration<double>(end - begin).count() << std::endl;
    std::cout << "result: " << result.size() << std::endl;

    N      = 10000;
    first  = random_string(N);
    second = random_string(N / 2);
    begin  = std::chrono::high_resolution_clock::now();
    result = lcs(first, second);
    end    = std::chrono::high_resolution_clock::now();

    std::cout << N << " time: " << std::chrono::duration<double>(end - begin).count() << std::endl;
    std::cout << "result: " << result.size() << std::endl;
#endif

}
