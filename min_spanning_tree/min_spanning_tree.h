#pragma once

#include "graph.h"

#include <vector>

// Return minimal spanning tree for the (connected) graph as array of edges.
auto min_spanning_tree(const Graph &graph, int start_vertex = 0) -> std::vector<std::pair<int, int>>;

