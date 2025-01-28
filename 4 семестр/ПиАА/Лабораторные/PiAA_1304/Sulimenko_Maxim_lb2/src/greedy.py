class Solve:

    def __init__(self) -> None:
        self.graph = dict()
        self.startNode = None
        self.endNode = None
        self.isPathFound = False
        self.path = None
        
    #   Выводит ответ в нужном формате
    def print_final_path(self):
        print(self.path)

    #   Считывает входные данные и составляет граф в виде словаря
    def read_input(self):
        self.startNode, self.endNode = input().split()
        while True:
            try:
                from_node, in_node, weight = input().split()
                if from_node in self.graph:
                    self.graph[from_node].append([in_node, float(weight)])
                else:
                    self.graph[from_node] = [[in_node, float(weight)]]
            except:
                break

    #   Сортирует значения по весу рёбер
    def sort_keys_in_dict(self):
        for key in self.graph:
            self.graph[key].sort(key=lambda elem: elem[1])

    #   Инициализирует решение жадным алгоритмом
    def start_greedy_algorithm(self):
        self.read_input()
        self.sort_keys_in_dict()
        self.iterate_greedy_algorithm(self.startNode, self.startNode)

    #   Строит путь жадным алгоритмом
    def iterate_greedy_algorithm(self, currentNode, currentPath):
        if self.isPathFound:
            return
        if currentNode == self.endNode:
            self.path = currentPath
            self.isPathFound = True
            return
        if self.graph.get(currentNode):
            for nodes in self.graph[currentNode]:
                nextNode = nodes[0]
                nextPath = currentPath + nextNode
                self.iterate_greedy_algorithm(nextNode, nextPath)


#   Функция, которая создаёт экземпляр класса solve
#   и запускает необходимые для решения функции
def get_solution():
    solution = Solve()
    solution.start_greedy_algorithm()
    solution.print_final_path()


get_solution()
