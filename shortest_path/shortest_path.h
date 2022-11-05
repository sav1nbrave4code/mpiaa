/**
 * @file    shortest_path.h
 * @author  Anton S. Savin <sav1nru<at>mail.ru>
 * @date    05/11/22
 */

#include "graph.h"

#include <vector>

/**
 * @param   graph - undirected weighted graph to be searched
 * @param   start_vertex - starting vertex
 * @param   end_vertex - terminal peak
 * @return  vertices vector of shortest path between start_vertex and end_vertex in graph
 */
auto shortest_path(const Graph &graph, int start_vertex, int end_vertex) -> std::vector<int>;

/**
 * @param   parent - an array of predecessor vertices in the shortest path
 * @param   start_vertex - starting vertex
 * @param   end_vertex - terminal peak
 * @return  vertices vector of shortest path between start_vertex and end_vertex in graph
 */
auto build_path(std::map<int, int>& parent, int start_vertex, int end_vertex) -> std::vector<int>;