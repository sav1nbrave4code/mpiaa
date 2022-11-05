#include "min_spanning_tree.h"

#include <map>
#include <algorithm>

auto min_spanning_tree(const Graph &graph, const int start_vertex) -> std::vector<std::pair<int, int>>
{
    std::vector<std::pair<int, int>> result            {};
    std::vector<int>                 adjacent_vertices {};
    std::vector<int>                 vertices          {graph.get_vertices()};

	std::map<int, double>            min_weight {};
    std::map<int, int>               parent     {};

    int    last_vertex {};
    double min         {};

    for (int i {0}; i < static_cast<int>(graph.get_vertices().size()); ++i)
    {
        min_weight[i] = std::numeric_limits<double>::infinity();
    }

    min_weight[start_vertex] = 0;

    while (!vertices.empty())
    {
        min = std::numeric_limits<double>::infinity();

        for (const auto& vertex : vertices)
        {
            if (min_weight[vertex] < min)
            {
                min         = min_weight[vertex];
                last_vertex = vertex;
            }
        }

        adjacent_vertices = graph.get_adjacent_vertices(last_vertex);

        for (const auto& vertex : adjacent_vertices)
        {
            if (std::find(vertices.begin(), vertices.end(), vertex) != vertices.end()
            && min_weight[vertex] > graph.edge_weight(last_vertex, vertex))
            {
                min_weight[vertex] = graph.edge_weight(last_vertex, vertex);
                parent[vertex]     = last_vertex;
            }
        }

        vertices.erase(std::find(vertices.begin(), vertices.end(), last_vertex));
    }

    for (int i {0}; i < static_cast<int>(graph.get_vertices().size()); ++i)
    {
        if (i != start_vertex)
        {
            result.emplace_back(i, parent[i]);
        }
    }

	return result;
}
