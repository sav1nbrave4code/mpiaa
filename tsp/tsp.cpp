#include "tsp.h"

#include <limits>
#include <algorithm>
#include <iostream>

auto tsp(const Graph &graph, int start_vertex) -> std::vector<int>
{
    try
    {
#if BNB
    return tspBnb(graph, start_vertex);
#endif

#if NATIVE
    return native(graph, start_vertex);
#endif
    }
    catch (...)
    {
        return {};
    }
}

auto minPath(const Graph& graph, const std::vector<int>& first, const std::vector<int>& second) -> std::vector<int>
{
    double first_length  {0};
    double second_length {0};

    for (uint64_t i {0}; i < first.size() - 1; ++i)
    {
        first_length  += graph.edge_weight(first[i], first[i + 1]);
        second_length += graph.edge_weight(second[i], second[i + 1]);
    }

    return first_length < second_length ? first : second;
}

auto length(const Graph& graph, const std::vector<int>& path) -> double
{
    double length {0};

    for (uint64_t i {0}; i < path.size() - 1; ++i)
    {
        length += graph.edge_weight(path[i], path[i + 1]);
    }

    return length;
}

auto lowerBound(const Graph& graph, const std::vector<int>& visited) -> double
{
    std::vector<int> vertices          {graph.get_vertices()};
    std::vector<int> adjacent          {};
    double           min_sum           {0};
    double           min_first_vertex  {0};
    double           min_second_vertex {0};

    for (const auto& first_vertex : visited)
    {
        adjacent          = graph.get_adjacent_vertices(first_vertex);
        min_first_vertex  = std::numeric_limits<double>::infinity();
        min_second_vertex = std::numeric_limits<double>::infinity();

        for (const auto& second_vertex : adjacent)
        {
            if (graph.edge_weight(first_vertex, second_vertex) < min_second_vertex)
            {
                if (graph.edge_weight(first_vertex, second_vertex) < min_first_vertex)
                {
                    min_second_vertex = min_first_vertex;
                    min_first_vertex  = graph.edge_weight(first_vertex, second_vertex);
                }
                else
                {
                    min_second_vertex = graph.edge_weight(first_vertex, second_vertex);
                }
            }
        }

        min_sum += min_first_vertex + min_second_vertex;

        vertices.erase(std::find(vertices.begin(), vertices.end(), first_vertex));
    }

    for (const auto& first_vertex : vertices)
    {
        adjacent          = graph.get_adjacent_vertices(first_vertex);
        min_first_vertex  = std::numeric_limits<double>::infinity();
        min_second_vertex = std::numeric_limits<double>::infinity();

        for (const auto& second_vertex : adjacent)
        {
            if (graph.edge_weight(first_vertex, second_vertex) < min_second_vertex)
            {
                if (graph.edge_weight(first_vertex, second_vertex) < min_first_vertex)
                {
                    min_second_vertex = min_first_vertex;
                    min_first_vertex  = graph.edge_weight(first_vertex, second_vertex);
                }
                else
                {
                    min_second_vertex = graph.edge_weight(first_vertex, second_vertex);
                }
            }
        }

        min_sum += min_first_vertex + min_second_vertex;
    }

    return min_sum / 2;
}

auto bnb(const Graph& graph, const std::vector<int>& visited, std::vector<int> best_path) -> std::vector<int>
{
    if (visited.size() == graph.get_vertices().size())
    {
        return minPath(graph, best_path, visited);
    }

    std::vector<int> vertices      {graph.get_vertices()};
    std::vector<int> next_vertices {};
    std::vector<int> path          {};

    for (const auto& vertex : visited)
    {
        vertices.erase(std::find(vertices.begin(), vertices.end(), vertex));
    }

    for (const auto& vertex : vertices)
    {
        next_vertices = visited;

        next_vertices.push_back(vertex);

        if (lowerBound(graph, next_vertices) < length(graph, best_path))
        {
            path      = bnb(graph, next_vertices, best_path);
            best_path = minPath(graph, best_path, path);
        }
    }

    return best_path;
}

auto tspBnb(const Graph& graph, int start_vertex) -> std::vector<int>
{
    if (graph.get_vertices().size() < 2)
    {
        return {};
    }

    std::vector<int> best_path {graph.get_vertices()};
    std::vector<int> visited   {start_vertex};

    return bnb(graph, visited, best_path);
}

auto native(const Graph& graph, int start_vertex) -> std::vector<int>
{

    if (graph.get_vertices().size() < 2)
    {
        return {};
    }

    std::vector<int> vertices {graph.get_vertices()};
    std::vector<int> result   {};
    double           min_sum  {std::numeric_limits<double>::infinity()};

    do
    {
        if (vertices.front() != start_vertex)
        {
            continue;
        }

        if (!graph.has_edge(vertices.front(), vertices.back()))
        {
            continue;
        }

        bool path_exist {true};

        for (uint64_t i {0}; i < vertices.size() - 1; ++i)
        {
            if (!graph.has_edge(vertices[i], vertices[i + 1]))
            {
                path_exist = false;

                break;
            }
        }

        if (!path_exist)
        {
            continue;
        }

        double path_sum {0};

        for (uint64_t i {0}; i < vertices.size() - 1; ++i)
        {
            path_sum += graph.edge_weight(vertices[i], vertices[i + 1]);
        }

        if (path_sum < min_sum)
        {
            result  = vertices;
            min_sum = path_sum;
        }

    } while (std::next_permutation(vertices.begin(), vertices.end()));

    return result;
}

#if GREEDY

auto greedy(const Graph& graph, int start_vertex) -> std::vector<int>
{
    if (graph.get_vertices().size() < 2)
    {
        return {};
    }

    int              current_vertex {start_vertex};
    std::vector<int> path           {current_vertex};
    std::vector<int> vertices       {graph.get_vertices()};

    while (path.size() < vertices.size())
    {
        auto adjacent_vertices {graph.get_adjacent_vertices(current_vertex)};
        auto min_edge {std::numeric_limits<double>::infinity()};
        auto next_vertex {std::numeric_limits<int>::max()};

        for (const auto& vertex : adjacent_vertices)
        {
            if (std::find(path.begin(), path.end(), vertex) == std::end(path))
            {
                auto copy_edge_wight {graph.edge_weight(vertex, current_vertex)};
                if (copy_edge_wight < min_edge)
                {
                    min_edge    = copy_edge_wight;
                    next_vertex = vertex;
                }
            }
        }
        if (next_vertex == std::numeric_limits<int>::max())
        {
            return std::vector<int> {};
        }

        path.push_back(next_vertex);
        current_vertex = next_vertex;
    }

    return graph.has_edge(current_vertex, start_vertex) ? path : std::vector<int> {};
}
#endif  // GREEDY

#if LOCAL

auto transform(const std::vector<int>& path, const int first, const int second) -> std::vector<int>
{
    std::vector<int> result {path};
    auto             iter1  {std::find(result.begin(), result.end(), first)};
    auto             iter2  {std::find(result.begin(), result.end(), second)};

    std::iter_swap(iter1, iter2);

    return result;
}

auto checkNonAdjacentPair(const vertex_pair& first_pair, const vertex_pair& second_pair) -> bool
{
    return first_pair.first  != second_pair.first
           && first_pair.first  != second_pair.second
           && first_pair.second != second_pair.first
           && first_pair.second != second_pair.second;
}

auto twoOpt(const Graph& graph, const std::vector<int>& path) -> std::vector<int>
{
    std::vector<std::pair<int, int>> result {};
    auto current_path {path};

    for (unsigned i {0}; i < current_path.size() - 1; i += 2)
    {
        result.emplace_back(current_path[i], current_path[i + 1]);
    }

    for (unsigned i {0}; i < result.size() - 1; ++i)
    {
        for (unsigned j {i + 1};j < result.size(); ++j)
        {
            auto old_weight {graph.edge_weight(result[i].first, result[i].second) +
                             graph.edge_weight(result[j].first, result[j].second)};
            auto new_weight {graph.edge_weight(result[i].first, result[j].first) +
                             graph.edge_weight(result[i].second, result[j].second)};
            if (new_weight < old_weight)
            {
                current_path = transform(current_path, result[i].second, result[j].first);
            }
        }
    }

    return current_path;
}

auto tspLocalSearch(const Graph& graph) -> std::vector<int>
{
    if (graph.get_vertices().size() < 2)
    {
        return {};
    }

    std::vector<int> current_path {graph.get_vertices()};

    try
    {

        while (true) {
            std::vector<int> improved_path{twoOpt(graph, current_path)};

            if (length(graph, improved_path) < length(graph, current_path)) {
                current_path = improved_path;
            } else {
                return current_path;
            }
        }
    }
    catch (...)
    {
        return {};
    }
}

#endif  // LOCAL
