import queue 

class Graph:
    # Инициализация класса
    def __init__(self):
        self.start_node = None
        self.end_node = None
        self.nodes = dict()
        self.path = ''

    # Метод, в котором происходит считывание входных данных
    def read(self):
        self.start_node, self.end_node = input().split()
        while True:
            try:
                from_node, in_node, weight = input().split()
                if from_node in self.nodes:
                    self.nodes[from_node].append([in_node, float(weight)])
                else:
                    self.nodes[from_node] = [[in_node, float(weight)]]
            except:
                break

    # Метод, реализующий эвристическую функцию
    # На вход принимает следующую вершины, в которую можно перейти
    # Возвращает разницу между кодами символов финальной вершины и вершины, поступившей на вход
    def heuristics(self, node):
        return abs(ord(node) - ord(self.end_node))
    
    # Метод, который возвращает список кортежей примыкающих вершин к текущей
    def get_neighbors(self, node):
        return self.nodes[node]
    
    # Метод, который строит и выводит путь, найденный алгоритмом A*
    # На вход получает словарь, составленный по принципу откуда пришли к текущей вершине
    def build_path(self, came_from):
        current_node = self.end_node
        while current_node != None:
            self.path += current_node
            current_node = came_from[current_node]
        self.path = self.path[::-1]
        print(self.path)


    # Метод, реализующий алгорит A*
    def a_star(self):
        nodes_queue = queue.PriorityQueue()
        nodes_queue.put((0, self.start_node))
        
        came_from = {}
        came_from[self.start_node] = None
    
        cost_so_far = {}
        cost_so_far[self.start_node] = 0

        while not nodes_queue.empty():
            current_node = nodes_queue.get()[1]

            if current_node == self.end_node:
                break
            
            if current_node in self.nodes.keys():
                neighbors = self.get_neighbors(current_node)
                for next_node, cost_next_node in neighbors:
                    new_cost = cost_so_far[current_node] + cost_next_node
                    if next_node not in cost_so_far or new_cost < cost_so_far[next_node]:
                        cost_so_far[next_node] = new_cost
                        priority = new_cost + self.heuristics(next_node)
                        nodes_queue.put((priority, next_node))
                        came_from[next_node] = current_node

        self.build_path(came_from)

# Функция, в которой создается экземпляр класса Graph
# и вызываются методы, которые реализуют поиск кратчайшего пути алгоритмом A*
def solve():
    graph = Graph()
    graph.read()
    graph.a_star()

solve()

