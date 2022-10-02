#include <sstream>
#include <random>
#include <utility>
#include <iostream>

#include "closest_pair.h"
#include "../catch.hpp"

using namespace std;

namespace Catch {
	template<> 
	struct StringMaker<Point> {
    	static string convert(const Point &p) {
    		ostringstream out;
    		out << p;
    		return out.str();
        } 
    };

	template<> 
    struct StringMaker<pair<Point, Point>> {
    	static string convert(const pair<Point, Point> &p) {
    		ostringstream out;
    		out << "{" << p.first << ", " << p.second << "}";
    		return out.str();
        } 
    };
}

auto random_point(const double min ,const double max) -> Point
{
    std::default_random_engine             generator    {};
    std::uniform_real_distribution<double> distribution {min, max};
    Point                                  point        {distribution(generator), distribution(generator)};

    return point;
}

pair<Point, Point> ordered(const pair<Point, Point> &p) {
	return p.first <= p.second ? p : std::make_pair(p.second, p.first);
}

TEST_CASE( "No points" ) {    
    CHECK_THROWS( closest_pair({}) );    
}

TEST_CASE( "Single point" ) {    
    CHECK_THROWS( closest_pair({Point(1, 1)}) );
}

TEST_CASE( "Two points" ) {    
    CHECK( ordered(closest_pair({
    	Point(2, 3), Point(3, 4)})) == make_pair(Point(2, 3), Point(3, 4)) );
}

TEST_CASE( "Three points" ) {
    CHECK( ordered(closest_pair({
    	Point(2, 3), Point(1, 9), Point(6, 2)})) == make_pair(Point(2, 3), Point(6, 2)) );
}

TEST_CASE( "Duplicate points" ) {    
    CHECK( ordered(closest_pair({
    	Point(2, 3), Point(2, 3), Point(3, 4)})) == make_pair(Point(2, 3), Point(2, 3)) );
}

TEST_CASE( "Same x coordinate" ) {    
    CHECK( ordered(closest_pair({
        Point(2, 9), Point(2, 4), 
        Point(2, 1), Point(2, -8)})) == make_pair(Point(2, 1), Point(2, 4)) );
}

TEST_CASE( "Many points" ) {
    CHECK( ordered(closest_pair({
    	Point(2, 3), Point(0, 4), Point(11, 9), Point(2, 8),
    	Point(4, 4), Point(3, 6), Point(6, 5), Point(1, 9)})) == make_pair(Point(1, 9), Point(2, 8)) );
}

TEST_CASE( "Negative points" ) {
    CHECK( ordered(closest_pair({
    	Point(-5, 6), Point(1, 2), Point(4, -2), Point(-9, 0),
    	Point(-1, -2), Point(0, 7), Point(2, -1), Point(-3, 1)})) == make_pair(Point(2, -1), Point(4, -2)) );
}

TEST_CASE( "Closest points are from stripe" ) {
    CHECK( ordered(closest_pair({
        Point(-1, 20), Point(-1.5, 10), Point(-2, -10), Point(-2.7, -20),
        Point(-10, 20), Point(-10.5, 10), Point(-11.7, -10), Point(-12.2, -20),
        Point(1, 21), Point(1.5, 11), Point(2, -9), Point(2.7, -19),
        Point(10, 21), Point(10.5, 11), Point(11.7, -9), Point(12.2, -19)})) == make_pair(Point(-1, 20), Point(1, 21)) );
}

TEST_CASE("Time check")
{
    int                N      {1000};
    std::vector<Point> points {};

    for (int i {0}; i < N; ++i)
    {
        points.push_back(random_point(-i, i % N + 5));
    }

    auto begin  {std::chrono::high_resolution_clock::now()};
    auto result {closest_pair(points)};
    auto end    {std::chrono::high_resolution_clock::now()};

    std::cout << std::fixed;
    std::cout << N << " time: " << std::chrono::duration<double>(end - begin).count() << std::endl;
    std::cout << result.first << ' ' << result.second << std::endl;
    points.clear();

    N = 10000;
    for (int i {0}; i < N; ++i)
    {
        points.push_back(random_point(-i, i % N + 5));
    }

    begin  = std::chrono::high_resolution_clock::now();
    result = closest_pair(points);
    end    = std::chrono::high_resolution_clock::now();

    std::cout << N << " time: " << std::chrono::duration<double>(end - begin).count() << std::endl;
    std::cout << result.first << ' ' << result.second << std::endl;
    points.clear();

    N = 100000;
    for (int i {0}; i < N; ++i)
    {
        points.push_back(random_point(-i, i %N + 5));
    }

    begin  = std::chrono::high_resolution_clock::now();
    result = closest_pair(points);
    end    = std::chrono::high_resolution_clock::now();

    std::cout << N << " time: " << std::chrono::duration<double>(end - begin).count() << std::endl;
    std::cout << result.first << ' ' << result.second << std::endl;
    points.clear();

}