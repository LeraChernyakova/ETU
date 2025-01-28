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
        
    # Метод, реализующий поиск кратчайшего пути жадным алгоритмом
    def greedy_algorithm(self):
        for key in self.nodes.keys():
            self.nodes[key].sort(key=lambda elem: elem[1])
        
        self.path = self.start_node
        while self.path[-1] != self.end_node:
            current_node = self.path[-1]
            if (self.nodes[current_node][0][0] not in self.nodes.keys()) and \
                (self.nodes[current_node][0][0] != self.end_node):
                self.nodes[current_node].pop(0)
            self.path += self.nodes[current_node][0][0]

    # Функция, которая выводит путь на экран
    def print_answer(self):
        print(self.path)

# Функция, в которой создается экземпляр класса Graph
# и вызываются методы, которые реализуют поиск кратчайшего пути жадным алгоритмом
def solve():
    graph = Graph()
    graph.read()
    graph.greedy_algorithm()
    graph.print_answer()

solve()

