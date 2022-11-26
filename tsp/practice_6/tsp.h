#ifndef TSP_H
#define TSP_H

#include "graph.h"

#include <vector>

/**
 * @def bound and branch algorithm for tsp
 */

#define BNB        1

/**
 * @def brute force algorithm for tsp
 */

#define NATIVE     0

/**
 * @def greedy algorithm for tsp
 */

#define GREEDY     1

/**
 * @brief additional functions for tspBnb
 */

auto minPath(const Graph& graph, const std::vector<int>& first, const std::vector<int>& second) -> std::vector<int>;
auto length(const Graph& graph, const std::vector<int>& path) -> double;
auto lowerBound(const Graph& graph, const std::vector<int>& visited) -> double;
auto bnb(const Graph& graph, const std::vector<int>& visited, std::vector<int> best_path) -> std::vector<int>;

/**
 * @brief   Solving TSP by brute-force algorithm
 * @param   graph - source graph
 * @param   start_vertex - start vertex for shortest path
 * @return  shortest path
 */

auto native(const Graph& graph, int start_vertex) -> std::vector<int>;

/**
 * @brief   Solving TSP by bound and branch algorithm
 * @param   graph - source graph
 * @param   start_vertex - start vertex for shortest path
 * @return  shortest path
 */

auto tspBnb(const Graph& graph, int start_vertex) -> std::vector<int>;

/**
 * @brief   Solving TSP with different algorithm
 * @param   graph - source graph
 * @param   start_vertex - start vertex for shortest path
 * @return  shortest path
 */

auto tsp(const Graph &graph, int start_vertex) -> std::vector<int>;

#if GREEDY

/**
 * @brief   Solving TSP by bound and branch algorithm
 * @param   graph - source graph
 * @param   start_vertex - start vertex for shortest path
 * @return  shortest path
 */

auto greedy(const Graph& graph, int start_vertex) -> std::vector<int>;

#endif // GREEDY

#endif // TSP_H