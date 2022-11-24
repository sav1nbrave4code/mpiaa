#include "graph.h"

#include <vector>

#define NATIVE 1

#if not NATIVE

auto minPath(const Graph& graph, const std::vector<int>& first, const std::vector<int>& second) -> std::vector<int>;
auto length(const Graph& graph, const std::vector<int>& path) -> double;
auto lowerBound(const Graph& graph, const std::vector<int>& visited) -> double;
auto bnb(const Graph& graph, const std::vector<int>& visited, std::vector<int> best_path) -> std::vector<int>;
auto tspBnb(const Graph& graph, int start_vertex) -> std::vector<int>;

#else

auto native(const Graph& graph, int start_vertex) -> std::vector<int>;

#endif

auto tsp(const Graph &graph, int start_vertex) -> std::vector<int>;

auto greedy(const Graph& graph, int start_vertex) -> std::vector<int>;
