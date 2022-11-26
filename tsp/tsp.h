#ifndef TSP_H
#define TSP_H

#include "graph.h"
#include <vector>

using vertex_pair = std::pair<int, int>;
using double_pair = std::pair<vertex_pair, vertex_pair>;

/**
 * @def     bound and branch algorithm for tsp
 */

#define BNB        1

/**
 * @def     brute force algorithm for tsp
 */

#define NATIVE     0

/**
 * @def     greedy algorithm for tsp
 */

#define GREEDY     1

/**
 * @brief   local search algorithm for tsp
 */

#define LOCAL      1

/**
 * @brief additional functions for tspBnb
 */

auto minPath(const Graph& graph, const std::vector<int>& first, const std::vector<int>& second) -> std::vector<int>;
auto length(const Graph& graph, const std::vector<int>& path) -> double;
auto lowerBound(const Graph& graph, const std::vector<int>& visited) -> double;
auto bnb(const Graph& graph, const std::vector<int>& visited, std::vector<int> best_path) -> std::vector<int>;


#if LOCAL

/**
 * @brief   additional functions for tspLocalSearch
 */

auto transform(const std::vector<int>& path, int first, int second) -> std::vector<int>;
auto twoOpt(const Graph& graph, const std::vector<int>& path) -> std::vector<int>;
auto checkNonAdjacentPair(const vertex_pair& first_pair, const vertex_pair& second_pair) -> bool;

#endif  // LOCAL

/**
 * @brief       solving TSP by brute-force algorithm
 * @param       graph - source graph
 * @param       start_vertex - start vertex for shortest path
 * @return      shortest path
 */

auto native(const Graph& graph, int start_vertex) -> std::vector<int>;

/**
 * @brief       solving TSP by bound and branch algorithm
 * @param       graph - source graph
 * @param       start_vertex - start vertex for shortest path
 * @return      shortest path
 */

auto tspBnb(const Graph& graph, int start_vertex) -> std::vector<int>;

/**
 * @brief       solving TSP with different algorithm
 * @param       graph - source graph
 * @param       start_vertex - start vertex for shortest path
 * @return      shortest path
 */

auto tsp(const Graph &graph, int start_vertex) -> std::vector<int>;

#if LOCAL

/**
 * @brief       solving tsp by local search (2-opt)
 * @param       graph
 * @return      shortest path
 */

auto tspLocalSearch(const Graph& graph) -> std::vector<int>;

#endif  // LOCAL

#if GREEDY

/**
 * @brief       solving TSP by bound and branch algorithm
 * @param       graph - source graph
 * @param       start_vertex - start vertex for shortest path
 * @return      shortest path
 */

auto greedy(const Graph& graph, int start_vertex) -> std::vector<int>;

#endif  // GREEDY

#endif  // TSP_H
