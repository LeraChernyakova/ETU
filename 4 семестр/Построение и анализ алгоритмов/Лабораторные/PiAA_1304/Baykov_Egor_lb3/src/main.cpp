#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <algorithm>

#define START_VERTEX 0
#define START_PATH_WEIGHT 0
#define INFINITY_STRING "inf"
#define DASH_STRING "-"

// Class contains information about path and helps operate with vertexes
class Path
{
public:
    // Constructor of class
    Path()
    {
        path_weight = INT32_MAX;
    }

    // getter of path length
    int get_path_length() const
    {
        return path.size();
    }

    // getter of path weight
    int get_path_weight() const
    {
        return path_weight;
    }

    // setter of path weight
    void set_path_weight(int weight)
    {
        path_weight = weight;
    }

    // method set path default values
    void set_default()
    {
        path_weight = INT32_MAX;
        path.clear();
    }

    // getter of last vertex in path
    int get_last_element() const
    {
        return path.back();
    }

    // method adds new vertex in the path
    void add_vertex(int vertex)
    {
        path.push_back(vertex);
    }

    // method checks presence of certain vertex in path
    bool is_vertex_in_path(int vertex)
    {
        return std::find(path.begin(), path.end(), vertex) != path.end();
    }

    // method delete last vertex in path
    void delete_last_vertex()
    {
        path.pop_back();
    }

    // method prints information of path in human-readable format
    void print_path_info()
    {
        for (auto vertex : path)
        {
            std::cout << vertex + 1 << " ";
        }
        std::cout << ", weight = " << path_weight << "\n";
    }

private:
    std::vector<int> path; // the structure of path - common vector of int
    int path_weight;       // weight of path
};

// Class salesman solves TSP
class Salesman
{
public:
    // Constructor of class Salesman create new path with start vertex and start weigth
    // default start vertex - 0 (1) and start weight - 0
    // initializes fields is_found_best_path and lower_edge
    Salesman()
    {
        current_path.add_vertex(START_VERTEX);
        current_path.set_path_weight(START_PATH_WEIGHT);
        is_found_best_path = false;
        lower_edge = 0;
    }

    // method reads information from file
    void read_data(std::string file_name)
    {
        std::fstream file;
        file.open(file_name);
        if (file.is_open())
        {
            file >> vertex_amount;
            matrix = std::vector<std::vector<int>>();
            std::string temporary_string;
            for (int i = 0; i < vertex_amount; ++i)
            {
                matrix.push_back(std::vector<int>());
                for (int j = 0; j < vertex_amount; ++j)
                {
                    file >> temporary_string;
                    if (temporary_string == DASH_STRING || temporary_string == INFINITY_STRING)
                    {
                        matrix[i].push_back(0);
                    }
                    else
                    {
                        matrix[i].push_back(stoi(temporary_string));
                    }
                }
            }
        }
    }

    // method runs reading, finding path and printing methods and times.
    void start(std::string file_name)
    {
        auto begin = std::chrono::steady_clock::now();
        read_data(file_name);
        find_lower_edge();
        find_shortest_path(current_path);
        auto end = std::chrono::steady_clock::now();
        time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        print_answer();
    }

    // method finding shortest Hamiltonian cycle in graph by backtracking
    void find_shortest_path(Path current_path)
    {
        if (current_path.get_path_length() == vertex_amount)
        {
            if (matrix[current_path.get_last_element()][START_VERTEX] != 0 &&
                current_path.get_path_weight() + matrix[current_path.get_last_element()][START_VERTEX] < minimal_path.get_path_weight())
            {
                minimal_path = current_path;
                minimal_path.add_vertex(START_VERTEX);
                minimal_path.set_path_weight(current_path.get_path_weight() + matrix[current_path.get_last_element()][START_VERTEX]);
                if (minimal_path.get_path_weight() == lower_edge)
                {
                    is_found_best_path = true;
                }
                return;
            }
        }
        for (int i = 0; i < vertex_amount; ++i)
        {
            if (matrix[current_path.get_last_element()][i] != 0 && !current_path.is_vertex_in_path(i))
            {
                if (current_path.get_path_weight() + matrix[current_path.get_last_element()][i] < minimal_path.get_path_weight())
                {
                    current_path.set_path_weight(current_path.get_path_weight() + matrix[current_path.get_last_element()][i]);
                    current_path.add_vertex(i);
                    find_shortest_path(current_path);
                    current_path.delete_last_vertex();
                    current_path.set_path_weight(current_path.get_path_weight() - matrix[current_path.get_last_element()][i]);
                    if (is_found_best_path)
                    {
                        return;
                    }
                }
            }
        }
        return;
    }

    // method prints answer in human-readable format
    void print_answer()
    {
        if (minimal_path.get_path_weight() == INT32_MAX)
        {
            std::cout << "There is not any path\n";
            return;
        }
        minimal_path.print_path_info();
        std::cout << "Time: " << time.count() << " ms";
    }

    // find lower edge of objective function
    void find_lower_edge()
    {
        std::vector<std::vector<int>> matrix_copy = matrix;
        for (auto &row : matrix_copy)
        {
            for (int i = 0; i < vertex_amount; ++i)
            {
                if (row[i] == 0)
                {
                    row[i] = INT32_MAX;
                }
            }
        }
        for (auto &row : matrix_copy)
        {
            int minimum = *std::min_element(row.begin(), row.end());
            lower_edge += minimum;
            for (int i = 0; i < vertex_amount; ++i)
            {
                row[i] -= minimum;
            }
        }

        for (int i = 0; i < vertex_amount; ++i)
        {
            int minimum = INT32_MAX;
            for (auto row : matrix_copy)
            {
                minimum = row[i] < minimum ? row[i] : minimum;
            }
            lower_edge += minimum;
        }
    }

private:
    std::vector<std::vector<int>> matrix; // matrix of arcs
    Path minimal_path;                    // minimal path which is printed as an answer
    Path current_path;                    // the path to check for minimum weight
    int vertex_amount;                    // amount of vertexes in graph
    std::chrono::milliseconds time;       // the path to check for minimum weight
    int lower_edge;                       // lower edge of objective function
    bool is_found_best_path;              // flag that shows the minimal path's already found
};

// main function
int main()
{
    for (int i = 1; i <= 5; ++i)
    {
        auto salesman = Salesman();
        salesman.start("test" + std::to_string(i) + ".txt");
    }
    return 0;
}