#include <iostream>
#include <functional>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <cmath>


/*
 * A priority queue is used to traverse the graph,
 * at the top is the element with the smallest path estimate f = g + h,
 * where g -- actual distance traveled to reach a given node,
 * h -- heuristic evaluation, equal to the difference in the numerical
 * values of the symbols denoting the nodes.
 * Queue elements are tuples consisting of the name of the node, the distance traveled to this node,
 * the name of the node from which the transition to this node was made.
 */
typedef std::priority_queue<std::tuple<char, float, char>, std::vector<std::tuple<char, float, char>>,
        std::function<bool(std::tuple<char, float, char> &, std::tuple<char, float, char> &)>> queue_t;
/*
 * Stores pairs of elements -- the name of the node and the weight of the edge to the this node.
 */
typedef std::vector<std::pair<char, float>> nodes_container;
/*
 * The graph is represented as an associative array, the keys are the names of the nodes, the values are the
 * containers of the nodes in which you can go to from key node.
 */
typedef std::unordered_map<char, nodes_container> graph_t;


/*
 * Class Solver is a class that encapsulates the methods needed to solve the problem.
 */
class Solution
{
public:
    graph_t get_graph();
    std::string find_path(char start_node, char finish_node, graph_t &graph);
private:
    std::string present_result(char finish_node, std::unordered_map<char, char> &path);
};


/*
 * Reads a graph from the input stream and returns it.
 */
graph_t Solution::get_graph()
{
    graph_t graph;
    char source_node, destination_node;
    float weight;

    while (std::cin >> source_node >> destination_node >> weight)
    {
        if (graph.find(source_node) == graph.end())
        {
            graph[source_node] = nodes_container();
        }
        graph[source_node].emplace_back(destination_node, weight);
    }

    return graph;
}

/*
 * Finds a path using A* algorithm.
 */
std::string Solution::find_path(char start_node, char finish_node, graph_t &graph)
{
    auto cmp = [&finish_node](std::tuple<char, float, char> &left, std::tuple<char, float, char> &right)
    {
        float left_heuristics = std::get<1>(left) + (float) std::abs(finish_node - std::get<0>(left));
        float right_heuristics = std::get<1>(right) + (float) std::abs(finish_node - std::get<0>(right));
        return left_heuristics > right_heuristics;
    };
    queue_t queue(cmp);
    std::unordered_map<char, char> path;
    std::unordered_map<char, float> best_distance;

    queue.emplace(start_node, 0, 0);

    while (!queue.empty())
    {
        auto current_item = queue.top();
        char current_node = std::get<0>(current_item);
        float distance = std::get<1>(current_item);
        char previous_node = std::get<2>(current_item);
        queue.pop();

        if (path.find(current_node) != path.end() && best_distance[current_node] <= distance)
        {
            continue;
        }

        path[current_node] = previous_node;
        best_distance[current_node] = distance;

        if (current_node == finish_node)
        {
            break;
        }

        for (auto neighbor_node: graph[current_node])
        {
            char next_node = neighbor_node.first;
            float next_node_distance = distance + neighbor_node.second;
            queue.emplace(next_node, next_node_distance, current_node);
        }

    }

    return present_result(finish_node, path);
}

/*
 * Represents the path to the finish node as a string, using an associative array,
 * the keys are the names of nodes, values are the nodes from which the transition to key node was made.
 */
std::string Solution::present_result(char finish_node, std::unordered_map<char, char> &path)
{
    std::string result;
    char current_node = finish_node;

    while (current_node)
    {
        result.insert(0, 1, current_node);
        current_node = path[current_node];
    }

    return result;
}


int main()
{
    char start_node, finish_node;
    std::cin >> start_node >> finish_node;

    Solution s;
    graph_t graph = s.get_graph();
    std::cout << s.find_path(start_node, finish_node, graph) << '\n';

    return 0;
}
