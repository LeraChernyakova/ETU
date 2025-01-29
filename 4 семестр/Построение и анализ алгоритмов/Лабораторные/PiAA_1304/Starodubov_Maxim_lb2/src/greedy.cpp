#include <iostream>
#include <functional>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <stack>


/*
 * A priority queue is used to store nodes that can be jumped to from the current node,
 * at the top is the element with the lowest edge weight.
 * The queue stores elements as value pairs node name - edge weight.
 */
typedef std::priority_queue<std::pair<char, float>, std::vector<std::pair<char, float>>,
        std::function<bool(std::pair<char, float> &, std::pair<char, float> &)>> nodes_queue;
/*
 * The graph is represented as an associative array, the keys are the names of the nodes, the values are the
 * queues of the nodes in which you can go to from key node.
 */
typedef std::unordered_map<char, nodes_queue> graph_t;


/*
 * Class Solver is a class that encapsulates the methods needed to solve the problem.
 */
class Solution
{
public:
    graph_t get_graph();
    std::string find_path(char start_node, char finish_node, graph_t &graph);
private:
    std::string present_result(std::stack<char> &stack);
};


/*
 * Reads a graph from the input stream and returns it.
 */
graph_t Solution::get_graph()
{
    auto cmp = [](std::pair<char, float> &left, std::pair<char, float> &right)
    { return left.second > right.second; };
    graph_t graph;
    char source_node, destination_node;
    float weight;

    while (std::cin >> source_node >> destination_node >> weight)
    {
        if (graph.find(source_node) == graph.end())
        {
            graph[source_node] = nodes_queue(cmp);
        }
        graph[source_node].emplace(destination_node, weight);
    }

    return graph;
}

/*
 * Finds a path using greedy algorithm.
 */
std::string Solution::find_path(char start_node, char finish_node, graph_t &graph)
{
    std::stack<char> stack;
    stack.push(start_node);

    while (!stack.empty())
    {
        char current_node = stack.top();

        if (current_node == finish_node)
        {
            break;
        }

        if (graph[current_node].empty())
        {
            stack.pop();
            continue;
        }

        stack.push(graph[current_node].top().first);
        graph[current_node].pop();
    }

    return present_result(stack);
}

/*
 * Represents the contents of the passed stack as a string,
 * with the top element of the stack at the end of the string.
 */
std::string Solution::present_result(std::stack<char> &stack)
{
    std::string result;

    while (!stack.empty())
    {
        result.insert(0, 1, stack.top());
        stack.pop();
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
