#include "../catch.hpp"

#include "tsp.h"

#include <random>
#include <chrono>
#include <iostream>

using namespace std;

auto randomGraph(const int size) -> Graph
{
    Graph                                  graph        {};
    std::default_random_engine             generator    {};
    std::uniform_real_distribution<double> distribution {1, 100};

    for (int i {0}; i < size; ++i)
    {
        graph.add_vertex(i);
    }

    for (int i {0}; i < size - 1; ++i)
    {
        for (int j {i + 1}; j < size; ++j)
        {
            graph.add_edge(i, j, distribution(generator));
        }
    }

    return graph;
}

auto random_vertex(const int max) -> int
{
    std::default_random_engine generator {};
    std::uniform_int_distribution<int> distribution{0, max};

    return distribution(generator);
}

auto cost(const Graph& graph, const std::vector<int>& path) -> double
{
    double cost     {0};
    auto   vertices {graph.get_vertices()};

    for (uint64_t i {0}; i < path.size() - 1; ++i)
    {
        cost += graph.edge_weight(path[i], path[i + 1]);
    }

    cost += graph.edge_weight(path.back(), path.front());

    return cost;
}

// For a circular path get its reverse.
vector<int> reversed(const vector<int> &path) {
    if (path.empty()) {
        return vector<int> {};
    }
    vector<int> result = {path[0]}; // first item is a start vertex
    result.insert(result.end(), path.rbegin(), path.rend()); // add vertices in reverse order
    result.pop_back(); // remove duplicated start vertex
    return result;
}

// From two possible directions for a circular path choose one with min second vertex.
vector<int> min_dir(const vector<int> &path) {
    if (path.size() <= 1) {
        return path;
    }    
    const auto reversed_path = reversed(path);
    return (path[1] <= reversed_path[1] ? path : reversed_path);
}

TEST_CASE( "[TSP] Empty graph", "[tsp]" ) {
    Graph g {};    
    CHECK( tsp(g, 0) == vector<int> {} );
}

TEST_CASE( "[TSP] Single vertex", "[tsp]" ) {
    Graph g {}; 
    g.add_vertex(0);   
    CHECK( tsp(g, 0) == vector<int> {} );
}

TEST_CASE( "[TSP] One edge", "[tsp]" ) {
    Graph g {{0, 1, 2.5}};
    CHECK( tsp(g, 0) == vector<int> {0, 1} );
}

TEST_CASE( "[TSP] Three vertices, three edges", "[tsp]" ) {
    Graph g {{0, 1, 2.5}, {0, 2, 0.5}, {1, 2, 1.0}};
    const auto result = tsp(g, 0);  
    const auto expected = vector<int> {0, 1, 2};  
    CHECK( min_dir(result) == expected );
}

TEST_CASE( "[TSP] Several vertices", "[tsp]" ) {
    Graph g {{0, 1, 6.0}, {0, 2, 4.0}, {0, 3, 1.0},
             {1, 2, 3.5}, {1, 3, 2.0}, 
             {2, 3, 5.0}};
    const auto result = tsp(g, 0);
    const auto expected = vector<int> {0, 2, 1, 3};
    CHECK( min_dir(result) == expected );
}

TEST_CASE( "[TSP] Many vertices", "[tsp]" ) {
    Graph g {{0, 1, 2.0}, {0, 2, 4.0}, {0, 3, 1.0}, {0, 4, 2.5},
             {1, 2, 3.6}, {1, 3, 6.0}, {1, 4, 3.0}, 
             {2, 3, 7.0}, {2, 4, 5.0}, 
             {3, 4, 9.0}};            
    const auto result = tsp(g, 0);
    const auto expected = vector<int> {0, 3, 2, 1, 4};
    CHECK( min_dir(result) == expected );
}

TEST_CASE( "[TSP] Unreachable vertex", "[tsp]" ) {
    Graph g {{0, 1, 2.5}, {1, 2, 1.0}, {0, 2, 1.0}, {3, 4, 0.7}};
    CHECK( tsp(g, 0) == vector<int> {} );
    CHECK( tsp(g, 3) == vector<int> {} );
}

TEST_CASE( "[TSP] No looped path", "[tsp]" ) {
    Graph g {{0, 1, 2.5}, {0, 2, 1.0}, {2, 3, 7.0} };
    CHECK( tsp(g, 0) == vector<int> {} );
    CHECK( tsp(g, 1) == vector<int> {} );
}

TEST_CASE("[TSP] Time check", "[tsp]")
{
    std::cout << std::fixed;

    int  N      {7};
    auto graph  {randomGraph(N)};
    auto begin  {std::chrono::high_resolution_clock::now()};
    auto result {tspBnb(graph, 0)};
    auto end    {std::chrono::high_resolution_clock::now()};
    std::cout << "[tspBnb] size: " << N << " cost: " << cost(graph ,result) << " time: "
              << std::chrono::duration<double>(end - begin).count() << std::endl;

    begin  = std::chrono::high_resolution_clock::now();
    result = native(graph, 0);
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "[tspNative] size: " << N << " cost: " << cost(graph ,result) << " time: "
              << std::chrono::duration<double>(end - begin).count() << std::endl;

    begin  = std::chrono::high_resolution_clock::now();
    result = greedy(graph, 0);
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "[tspGreedy] size: " << N << " cost: " << cost(graph ,result) << " time: "
              << std::chrono::duration<double>(end - begin).count() << std::endl;

    begin  = std::chrono::high_resolution_clock::now();
    result = tspLocalSearch(graph);
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "[tspLocalSearch] size: " << N << " cost: " << cost(graph ,result) << " time: "
              << std::chrono::duration<double>(end - begin).count() << std::endl;

    N      = 8;
    graph  = randomGraph(N);
    begin  = std::chrono::high_resolution_clock::now();
    result = tspBnb(graph, 0);
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "[tspBnb] size: " << N << " cost: " << cost(graph ,result) << " time: "
              << std::chrono::duration<double>(end - begin).count() << std::endl;

    begin  = std::chrono::high_resolution_clock::now();
    result = native(graph, 0);
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "[tspNative] size: " << N << " cost: " << cost(graph ,result) << " time: "
              << std::chrono::duration<double>(end - begin).count() << std::endl;

    begin  = std::chrono::high_resolution_clock::now();
    result = greedy(graph, 0);
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "[tspGreedy] size: " << N << " cost: " << cost(graph ,result) << " time: "
              << std::chrono::duration<double>(end - begin).count() << std::endl;

    begin  = std::chrono::high_resolution_clock::now();
    result = tspLocalSearch(graph);
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "[tspLocalSearch] size: " << N << " cost: " << cost(graph ,result) << " time: "
              << std::chrono::duration<double>(end - begin).count() << std::endl;

    N      = 9;
    graph  = randomGraph(N);
    begin  = std::chrono::high_resolution_clock::now();
    result = tspBnb(graph, 0);
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "[tspBnb] size: " << N << " cost: " << cost(graph ,result) << " time: "
              << std::chrono::duration<double>(end - begin).count() << std::endl;

    begin  = std::chrono::high_resolution_clock::now();
    result = native(graph, 0);
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "[tspNative] size: " << N << " cost: " << cost(graph ,result) << " time: "
              << std::chrono::duration<double>(end - begin).count() << std::endl;

    begin  = std::chrono::high_resolution_clock::now();
    result = greedy(graph, 0);
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "[tspGreedy] size: " << N << " cost: " << cost(graph ,result) << " time: "
              << std::chrono::duration<double>(end - begin).count() << std::endl;

    begin  = std::chrono::high_resolution_clock::now();
    result = tspLocalSearch(graph);
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "[tspLocalSearch] size: " << N << " cost: " << cost(graph ,result) << " time: "
              << std::chrono::duration<double>(end - begin).count() << std::endl;

    N      = 10;
    graph  = randomGraph(N);
    begin  = std::chrono::high_resolution_clock::now();
    result = tspBnb(graph, 0);
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "[tspBnb] size: " << N << " cost: " << cost(graph ,result) << " time: "
              << std::chrono::duration<double>(end - begin).count() << std::endl;

    begin  = std::chrono::high_resolution_clock::now();
    result = native(graph, 0);
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "[tspNative] size: " << N << " cost: " << cost(graph ,result) << " time: "
              << std::chrono::duration<double>(end - begin).count() << std::endl;

    begin  = std::chrono::high_resolution_clock::now();
    result = greedy(graph, 0);
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "[tspGreedy] size: " << N << " cost: " << cost(graph ,result) << " time: "
              << std::chrono::duration<double>(end - begin).count() << std::endl;

    begin  = std::chrono::high_resolution_clock::now();
    result = tspLocalSearch(graph);
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "[tspLocalSearch] size: " << N << " cost: " << cost(graph ,result) << " time: "
              << std::chrono::duration<double>(end - begin).count() << std::endl;

    N      = 1000;
    graph  = randomGraph(N);
    begin  = std::chrono::high_resolution_clock::now();
    result = greedy(graph, 0);
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "[tspGreedy] size: " << N << " cost: " << cost(graph ,result) << " time: "
              << std::chrono::duration<double>(end - begin).count() << std::endl;

    begin  = std::chrono::high_resolution_clock::now();
    result = tspLocalSearch(graph);
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "[tspLocalSearch] size: " << N << " cost: " << cost(graph ,result) << " time: "
              << std::chrono::duration<double>(end - begin).count() << std::endl;

    N      = 2000;
    graph  = randomGraph(N);
    begin  = std::chrono::high_resolution_clock::now();
    result = greedy(graph, 0);
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "[tspGreedy] size: " << N << " cost: " << cost(graph ,result) << " time: "
              << std::chrono::duration<double>(end - begin).count() << std::endl;

    begin  = std::chrono::high_resolution_clock::now();
    result = tspLocalSearch(graph);
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "[tspLocalSearch] size: " << N << " cost: " << cost(graph ,result) << " time: "
              << std::chrono::duration<double>(end - begin).count() << std::endl;

    N      = 3000;
    graph  = randomGraph(N);
    begin  = std::chrono::high_resolution_clock::now();
    result = greedy(graph, 0);
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "[tspGreedy] size: " << N << " cost: " << cost(graph ,result) << " time: "
              << std::chrono::duration<double>(end - begin).count() << std::endl;

    begin  = std::chrono::high_resolution_clock::now();
    result = tspLocalSearch(graph);
    end    = std::chrono::high_resolution_clock::now();
    std::cout << "[tspLocalSearch] size: " << N << " cost: " << cost(graph ,result) << " time: "
              << std::chrono::duration<double>(end - begin).count() << std::endl;
}
