#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>



/*
    Класс Node реализует хранение своего имени, а также узлов, в которые из него можно попасть и веса дуг до этих узлов
*/
class Node{
    private:
        char name;                                  // Имя узла
        std::unordered_map <Node*, int> children;   // Словарь дочерних узлов с весами дуг до них
        std::vector <Node*> visited_children;       // Вектор просмотренных дочерних узлов
        
        bool isVisitedChild(Node* child_node);      // Метод, возвращающий значение, просмотрен ли уже дочерний узел или нет

    public:
        Node(char name);                                // Конструктор класса, реализует установку имени узла
        char getName();                                 // Метод, реализующий передачу имени узла
        void addChild(Node* child_node, int weight);    // Метод, реализующий добавление дочернего узла с весом дуги до него
        std::unordered_map <Node*, int> getChildren();  // Метод, реализующий передачу словаря дочерних узлов и весов дуг до них
        Node* getBestChild();                           // Метод, возвращающий лучший дочерний узел, для жадного алгоритма
};

/*
    Конструктор класса, устанавливающий имя узла
    Args:
        - name (char) - имя узла
*/
Node::Node(char name){
    this->name = name;
};

/*
    Метод, возвращающий значение, просмотрен ли уже дочерний узел или нет
*/
bool Node::isVisitedChild(Node* child_node){
    return std::binary_search(this->visited_children.begin(), this->visited_children.end(), child_node);
}

/*
    Метод класса, возвращающий имя узла
    Returns:
        - name (char) - имя узла
*/
char Node::getName(){
    return this->name;
};

/*
    Метод, реализующий добавление дочернего узла и веса дуги до него в словарь
    Args:
        - child_node (Node*) - дочерний узел
        - weight (int) - вес дуги до дочернего узла
*/
void Node::addChild(Node* child_node, int weight){
    this->children.insert(std::pair <Node*, int>(child_node, weight));
};

/*
    Метод, реализующий возвращение словаря дочерних узлов с весами дуг до них
    Returns:
        - children (std::unordered_map <Node*, int>) - словарь дочерних узлов с весами дуг до них 
*/
std::unordered_map <Node*, int> Node::getChildren(){
    return this->children;
};

/*
    Метод, возвращающий лучший дочерний узел, для жадного алгоритма
*/    
Node* Node::getBestChild(){
    int min_weight = 10000;
    Node* best_child = nullptr;

    for (auto i = this->children.begin(); i != this->children.end(); ++i){
        if (this->isVisitedChild(i->first) == false){
            if (i->second < min_weight || (i->second == min_weight && (int)i->first->getName() < (int)best_child->getName())){
                min_weight = i->second;
                best_child = i->first;
            }
        }
    }

    if (best_child != nullptr){
        this->visited_children.emplace_back(best_child);
    }
    return best_child;
};                  




/*
    Класс Graph реализует хранение всех узлов графа
*/
class Graph{
    private:
        std::vector <Node*> nodes;          // Вектор всех узлов графа

        bool isPresentNode(char node_name); // Метод, реализующий проверку наличия в графе узла по его имени

    public:
        Graph();                                                                    // Конструктор класса
        Node* getNode(char node_name);                                              // Метод, реализующий доступ к узлу по его имени
        void addBranch(char first_node_name, char second_node_name, int weight);    // Метод, реализующий добавление в граф узлов и весов дуг между ними
        ~Graph();                                                                   // Деструктор класса
};

/*
    Конструктор класса, реализующий предварительное выделение памяти под вектор узлов
*/
Graph::Graph(){
    this->nodes.reserve(10);
};

/*
    Метод, реализующий проверку наличия в графе узла по его имени
    Args:
        - node_name (char) - имя искомого узла
    Returns:
        - is_present (bool) - есть или нет узел в графе
*/
bool Graph::isPresentNode(char node_name){
    bool is_present = false;
    for (Node* i_node : this->nodes){
        if (node_name == i_node->getName()){
            is_present = true;
            break;
        }
    }
    return is_present;
};

/*
    Метод, возвращающий узел графа, с соответствующим именем
    Args:
        - node_name (char) - имя узла
    Returns:
        - node (Node*) - обьект узла
*/
Node* Graph::getNode(char node_name){
    Node* node = nullptr;
    for (Node* i_node : this->nodes){
        if (node_name == i_node->getName()){
            node = i_node;
            break;
        }
    }
    return node;
};

/*
    Метод, реализующий добавление в граф узлов и весов дуг между ними
    Args:
        - first_node_name (char) - узел, из которого есть дуга
        - second_node_name (char) - узел в который есть дуга
        - weight (int) - вес дуги
*/
void Graph::addBranch(char first_node_name, char second_node_name, int weight){
    Node* first_node = nullptr;
    Node* second_node = nullptr;

    // Проверка наличия первого узла в графе
    if (!this->isPresentNode(first_node_name)){
        this->nodes.emplace_back(new Node(first_node_name));
    }
    first_node = this->getNode(first_node_name);

    // Проверка наличия второго узла в графе
    if (!this->isPresentNode(second_node_name)){
        this->nodes.emplace_back(new Node(second_node_name));
    }
    second_node = this->getNode(second_node_name);

    // Добавление дочернего узла первому с весом дуги
    first_node->addChild(second_node, weight);
};

/*
    Деструктор класса, реализующий удаление всех узлов из памяти
*/
Graph::~Graph(){
    for (Node* node : this->nodes){
        delete node;
    }
};




/*
    Класс Solver реализует решение исходной задачи и хранение всех необходимых для этого полей и методов
*/
class Solver{
    private:
        Graph* graph;               // Граф вершин и ребер
        Node* start_node;           // Стартовый узел
        Node* end_node;             // Кончный узел
        std::vector <Node*> path;   // Вектор вершин, составляющих путь от стартовой вершины, до конца

        std::unordered_map<Node*, Node*> came_from_dict;    // Словарь, где ключ - вершина, значение - вершина откуда в нее пришли
        std::unordered_map<Node*, int> path_cost_dict;      // Словарь, где ключ - вершина, значение - оценка сложности пути
        
        typedef std::pair<int, Node*> PQElement;    
        std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> priority_queue;     // Очередь с приоритетом из стандартной библиотеки

        inline int getHeuristic(char node_name, char end_node_name);    // Метод, реализующий вычисление эвристической оценки
        void reconstructPath();                                         // Метод, реализующий восстановление пути для алгоритма A*

    public:
        Solver();               // Конструктор класса
        void GreedyAlgorithm(); // Метод, реализующий решение задачи жадным алгоритмом (использует GreadyAlgorithmR)
        void AStarAlgorithm();  // Метод, реализующий решение задачи алгоритмом A*
        void printPath();       // Метод, реализующий вывод ответа (пути)
        ~Solver();              // Деструктор класса
};

/*
    Метод, реализующий вычисление эвристической оценки
    Args:
        - node_name (char) - имя узла, эвристика которого расчитывается
        - end_node_name (char) - имя узла, до которого рассчитывается эвристика
    Returns:
        - heuristic (int) - эвристическая оценка
*/
inline int Solver::getHeuristic(char node_name, char end_node_name){
    int heuristic = std::abs((int)node_name - (int)end_node_name);
    return heuristic;
}

/*
    Конструктор класса, реализующий считываение входных данных, создание и заполнение начальными значениями полей класса
*/
Solver::Solver(){
    // Считывание имен начального и конечного узла
    char start_node_name;
    char end_node_name;
    std::cin >> start_node_name >> end_node_name;
    
    // Создание графа
    this->graph = new Graph();

    // Заполнение графа
    char first_node_name;
    char second_node_name;
    float weight;
    while (std::cin >> first_node_name >> second_node_name >> weight){
        this->graph->addBranch(first_node_name, second_node_name, weight);
    }

    // Запоминаем начальный и конечный узел
    this->start_node = this->graph->getNode(start_node_name);
    this->end_node = this->graph->getNode(end_node_name);
};

/*
    Метод, реализующий решение задачи жадным алгоритмом
*/
void Solver::GreedyAlgorithm(){
    Node* best_node = this->start_node;
    this->path.emplace_back(best_node);

    while (best_node != this->end_node){
        best_node = best_node->getBestChild();
        if (best_node == nullptr || std::binary_search(this->path.begin(), this->path.end(), best_node)){
            if (best_node == nullptr){
                this->path.pop_back();
            }
            best_node = this->path.back();
            this->path.pop_back();
        }
        this->path.emplace_back(best_node);     
    }
}

/*
    Метод, реализующий решение задачи алгоритмом A*
*/
void Solver::AStarAlgorithm(){
    this->priority_queue.emplace(0, this->start_node);          // Помещаем стартовую вершину в очередь с приоритетом 0 
    this->came_from_dict[this->start_node] = this->start_node;  // Указываем, что пришли в эту вершину из нее самой
    this->path_cost_dict[this->start_node] = 0;                 // Указываем оценку сложности пути 0
    
    // Цикл по всем вершинам в очереди
    while (!priority_queue.empty()){
        Node* current_node = this->priority_queue.top().second;   // Извлекаем самый приоритерный узел
        this->priority_queue.pop();                               // Удаляем самый приоритетный узел из очереди

        // Проверка конца алгоритма
        if (current_node == this->end_node) {
            break;
        }

        // Цикл по всем дочерним узлам текущего
        std::unordered_map <Node*, int> children = current_node->getChildren();
        for (auto i = children.begin(); i != children.end(); ++i) {
            Node* next_node = i->first;
            int branch_weight = i->second;
            int new_cost = this->path_cost_dict[current_node] + branch_weight;   // Оценка сложности пути до новой вершины

            // Проверка возможности улучшить путь до этой вершины
            if (this->path_cost_dict.find(next_node) == this->path_cost_dict.end() || new_cost < this->path_cost_dict[next_node]){
                // Улучшение сложности пути до вершины 
                this->path_cost_dict[next_node] = new_cost;

                // Помещение вершины в очередь с новым приоритетом
                int priority = new_cost + this->getHeuristic(next_node->getName(), this->end_node->getName());
                this->priority_queue.emplace(priority, next_node);

                // Помечаем откуда улучшили путь в вершину
                this->came_from_dict[next_node] = current_node;
            }
        }
    }
    this->reconstructPath();
}

/*
    Метод, реализующий восстановление пути
*/
void Solver::reconstructPath(){
    Node* current = this->end_node;
    // Проверка отсутствия пути
    if (this->came_from_dict.find(this->end_node) == this->came_from_dict.end()) {
        return;
    }

    // Восстановление пути
    while (current != this->start_node) {
        this->path.emplace_back(current);
        current = came_from_dict[current];
    }
    this->path.push_back(this->start_node);

    // Реверс пути
    std::reverse(this->path.begin(), this->path.end());
};

/*
    Метод, реализующий вывод пути
*/
void Solver::printPath(){
    for (Node* node : path){
        std::cout << node->getName();
    }
    std::cout << std::endl;
};

/*
    Деструктор класса, очищающий память
*/
Solver::~Solver(){
    delete this->graph;
}




/*
    Главная функция, реализующая решение задачи
*/
int main(){
    Solver solver = Solver();
    solver.GreedyAlgorithm();
    solver.printPath();
    return 0;
};
