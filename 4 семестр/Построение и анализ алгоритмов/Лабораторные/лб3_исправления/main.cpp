#include <iostream>
#include <vector>
#include <algorithm> 
#include <fstream>
#include <regex>
#include <chrono>

// Директива для замены infinity на число
#define infinity 99999999
#define cannot_visited -1

// Класс, реализующий решение задачи коммивояжёра
// Поля класса - граф в матричном виде, размер матрицы,
// стартовая вершина, вектор оптимального пути,
// длина оптимального пути, время работы программы
class GraphMatrix {
    private:
        std::vector<std::vector<int>> graph_matrix; 
        int size_graph_matrix; 
        int start_node; 
        std::vector<int> optimal_path; 
        int length_optimal_path;
        std::chrono::milliseconds working_time;

    public:
        // Конструктор класса от матрицы, считанной из файла
        GraphMatrix(std::vector<std::vector<int>> file_graph_matrix): graph_matrix(file_graph_matrix), size_graph_matrix(file_graph_matrix.size()), 
        start_node(0), length_optimal_path(infinity) {}

        // Метод, строящий минмиальное остовное дерево для текущей вершины
        // Принимает на вход текущую веришину и текущий найденный путь
        // Возвращает длину минимального остовного дерева
        int createMinSpanningTree(int current_node, const std::vector<int>& current_path) {
            int length_tree = 0;
            std::vector<int> include_nodes = {current_node};
            std::vector<int> viewed_nodes;
            while (include_nodes.size() > 0) {
                int min_index = -1;
                int min_current_node = infinity;
                std::vector<int> leaf = graph_matrix[include_nodes.back()];
                for (int i = 0; i < size_graph_matrix; i++) {
                    if (leaf[i] < min_current_node && std::find(current_path.begin(), current_path.end(), i) == current_path.end() \
                    && std::find(include_nodes.begin(), include_nodes.end(), i) == include_nodes.end() && std::find(viewed_nodes.begin(), viewed_nodes.end(), i) == viewed_nodes.end()) {
                        min_current_node = leaf[i];
                        min_index = i;
                    }
                }
                if (min_index == -1) {
                    viewed_nodes.push_back(include_nodes.back());
                    include_nodes.pop_back();
                }
                else {
                    include_nodes.push_back(min_index);
                    length_tree += leaf[min_index];
                }
            }
            return length_tree;
        }

        // Метод выбора следующей вершины, путь до которой должен быть минимален
        // Принимает на вход текующую вершину и путь, матрицу возможности посещения вершин
        // Возвращает индекс, он же и значение, следующей вершиины
        int chooseNextNode(int current_node, std::vector<int> current_path, std::vector<std::vector<int>>& visited_node_matrix) {
            std::vector<int> leaf = graph_matrix[current_node];
            int min_current_node = infinity;
            int min_index = -1;
            for (int i = 0; i < size_graph_matrix; i++) {
                if (leaf[i] < min_current_node && (i != start_node || current_path.size() == size_graph_matrix - 1) \
                && std::find(current_path.begin(), current_path.end(), i) == current_path.end()) {
                    if (visited_node_matrix[current_node][i] == 0) {
                        min_current_node = leaf[i];
                        min_index = i;
                    }
                }
            }
            if (min_index != -1) {
                visited_node_matrix[current_node][min_index] = 1;
            }
            return min_index;
        }

        // Метод поиска оптимального пути
        // Принимает на вход текущую вершину и путь, длину данного пути, матрицу возможности посещения вершин
        // Обновление переменных класса в соотвествии с происходящими изменениями внутри метода
        void findOptimalPath(int current_node, std::vector<int> current_path, int current_length_path, std::vector<std::vector<int>> visited_node_matrix) {
            if (current_length_path > length_optimal_path) { 
                return;
            }
            if (current_length_path + createMinSpanningTree(current_node, current_path) > length_optimal_path) { 
                return;
            }
            if (current_path.size() == size_graph_matrix) {
                if (current_length_path < length_optimal_path) {
                    this->length_optimal_path = current_length_path;
                    this->optimal_path = current_path;
                }
                return;
            }
            while (current_path.size() != size_graph_matrix) {
                if (current_path.size() == size_graph_matrix) {
                    return;
                }
                int next_node = chooseNextNode(current_node, current_path, visited_node_matrix);
                if (next_node == -1) {
                    return;
                }
                std::vector<int> update_path(current_path);
                std::vector<std::vector<int>> update_visited_node_matrix(visited_node_matrix);
                update_path.push_back(next_node);
                findOptimalPath(next_node, update_path, current_length_path + graph_matrix[current_node][next_node], update_visited_node_matrix);
                visited_node_matrix[current_node][next_node] = 1;
            }
            return;
        }

        // Метод запускающий работу алгоритма
        void workAlgorithm() {
            auto start_time = std::chrono::steady_clock::now();
            std::vector<std::vector<int>> visited_nodes_matrix(size_graph_matrix, std::vector<int>(size_graph_matrix, 0));
            for (int i = 0; i < size_graph_matrix; i++) {
                for (int j = 0; j < size_graph_matrix; j++) {
                    if (graph_matrix[i][j] == infinity) {
                        visited_nodes_matrix[i][j] = cannot_visited;
                    }
                }
            }
            findOptimalPath(start_node, optimal_path, optimal_path.size(), visited_nodes_matrix);
            optimal_path.insert(optimal_path.begin(), start_node);
            auto end_time = std::chrono::steady_clock::now();
            working_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        }

        // Перегрузка оператора вывода в поток
        // Вывод отформатированного ответа на экран
        // Принимает на вход поток вывода, объект класса GraphMatrix по ссылке
        // Возвращает объект потока вывода
        friend std::ostream& operator<<(std::ostream& os, const GraphMatrix& graph_matrix) {
            if (graph_matrix.optimal_path.size() < graph_matrix.size_graph_matrix) {
                 os << "There is no path!";
             }
             else {
                os << "[";
                for (int i = 0; i < graph_matrix.optimal_path.size()-1; i++) {
                    os << graph_matrix.optimal_path[i] + 1 << ", ";
                }

                os << graph_matrix.optimal_path.back() + 1 << "], " << graph_matrix.length_optimal_path << ", " << graph_matrix.working_time.count() << "ms";
            }
            return os;
        }
};

// Функция, считывающая матрицу из файла
// Возвращает вектор векторов - считанную матрицу
std::vector<std::vector<int>> readMatrixFile() {
    std::vector<std::vector<int>> matrix;
    std::ifstream file_input("test5.txt");
    std::string line;
    while (getline(file_input, line)) {
        std::string number_to_replace = std::to_string(infinity);
        line = std::regex_replace(line, std::regex("inf"), number_to_replace);
        line = std::regex_replace(line, std::regex("-"), number_to_replace);
        std::istringstream iss(line);
        std::vector<int> row;
        int elements;
        while (iss >> elements) {
            row.push_back(elements);
        }
        matrix.push_back(row);
    }
    return matrix;
}

// Функция, запускающая решение поставленной задачи
void startSolution() {
    std::vector<std::vector<int>> file_graph_matrix = readMatrixFile();
    GraphMatrix graph_matrix(file_graph_matrix);
    graph_matrix.workAlgorithm();
    std::cout << graph_matrix << std::endl;
}

int main() {
    startSolution();
    return 0;
}