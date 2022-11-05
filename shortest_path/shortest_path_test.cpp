#include "../catch.hpp"

#include "shortest_path.h"

#include <chrono>
#include <random>
#include <iostream>

using namespace std;

auto random_graph(const int size) -> Graph
{
    std::default_random_engine             engine;
    std::uniform_int_distribution<int>     distribution_vertex {0, size - 1};
    std::uniform_real_distribution<double> distribution_edge   {1, static_cast<double>(size)};

    Graph result {};

    for (int i {0}; i < size; ++i)
    {
        result.add_vertex(i);
    }

    for (uint64_t i {0}; i < result.get_vertices().size(); ++i)
    {
        result.add_edge(distribution_vertex(engine), distribution_vertex(engine), distribution_edge(engine));
    }

    return result;
}

TEST_CASE( "[Path] Empty graph", "[path]" ) {
    Graph g {};    
    CHECK( shortest_path(g, 0, 1) == vector<int> {} );
}

TEST_CASE( "[Path] Single vertex path", "[path]" ) {
    Graph g {{0, 1, 2.5}, {0, 2, 3.0}};    
    CHECK( shortest_path(g, 0, 0) == vector<int> {} );
}

TEST_CASE( "[Path] One edge", "[path]" ) {
    Graph g {{0, 1, 2.5}};
    CHECK( shortest_path(g, 0, 1) == vector<int> {0, 1} );
}

TEST_CASE( "[Path] Two edges", "[path]" ) {
    Graph g {{0, 1, 2.5}, {0, 2, 1.0}};
    CHECK( shortest_path(g, 0, 1) == vector<int> {0, 1} );
}

TEST_CASE( "[Path] Three edges", "[path]" ) {
    Graph g {{0, 1, 2.5}, {0, 2, 1.0}, {2, 1, 0.7}};
    CHECK( shortest_path(g, 0, 1) == vector<int> {0, 2, 1} );
}

TEST_CASE( "[Path] Many edges", "[path]" ) {
    Graph g {{0, 1, 3.0}, {1, 2, 0.5}, {2, 3, 0.5}, {3, 4, 1.0},
             {0, 2, 2.0}, {0, 4, 5.0}, {1, 3, 2.0}, {2, 4, 2.0}};
    CHECK( shortest_path(g, 0, 4) == vector<int> {0, 2, 3, 4} );
    CHECK( shortest_path(g, 4, 0) == vector<int> {4, 3, 2, 0} );
    CHECK( shortest_path(g, 1, 4) == vector<int> {1, 2, 3, 4} );    
}

TEST_CASE( "[Path] Unreachable vertex", "[path]" ) {
    Graph g {{0, 1, 2.5}, {1, 2, 1.0}, {0, 2, 1.0}, {3, 4, 0.7}};
    CHECK( shortest_path(g, 0, 4) == vector<int> {} );
    CHECK( shortest_path(g, 3, 0) == vector<int> {} );
}

TEST_CASE("Time check")
{
    std::cout << std::fixed;

    int  N      {10};
    auto graph  {random_graph(N)};
    auto begin  {std::chrono::high_resolution_clock::now()};
    auto result {shortest_path(graph, 0, N)};
    auto end    {std::chrono::high_resolution_clock::now()};
    std::cout << "size: " << N << " " << std::chrono::duration<double>(end - begin).count() << " "
              << result.size() << std::endl;

    N      = 100;
    graph  = random_graph(N);
    begin  = std::chrono::high_resolution_clock::now();
    result = shortest_path(graph, 0, N);
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "size: " << N << " " << std::chrono::duration<double>(end - begin).count() << " "
              << result.size() << std::endl;

    N      = 1000;
    graph  = random_graph(N);
    begin  = std::chrono::high_resolution_clock::now();
    result = shortest_path(graph, 0, N);
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "size: " << N << " " << std::chrono::duration<double>(end - begin).count() << " "
              << result.size() << std::endl;

    N      = 10000;
    graph  = random_graph(N);
    begin  = std::chrono::high_resolution_clock::now();
    result = shortest_path(graph, 0, N);
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "size: " << N << " " << std::chrono::duration<double>(end - begin).count() << " "
              << result.size() << std::endl;
}
