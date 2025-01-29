from queue import PriorityQueue


class Solve:

    def __init__(self) -> None:
        self.path_found = False
        self.path = None
        self.graph = None
        self.start_node = None
        self.end_node = None

#   Выводит ответ в требуемом на Stepik формате (строка, содержащая путь)

    def printSolution(self) -> None:
        print(self.path)

#   Составляет граф по входным данным, записывает граф в виде словаря, где
#   ключ - узел-родитель, а значение - список дочерних узлов
    def getDictGraphFromInput(self) -> None:
        graph = {}
        self.start_node, self.end_node = input().split()
        while True:
            try:
                for elem in input().split('\n'):
                    cur_start_node, cur_end_node, cur_length = elem.split()
                    if graph.get(cur_start_node) is None:
                        graph[cur_start_node] = [(cur_end_node,
                                                  float(cur_length))]
                    else:
                        graph[cur_start_node] += [(cur_end_node,
                                                   float(cur_length))]
            except:
                break
        self.graph = graph

#   Сортирует список дочерних узлов по весу рёбер
    def sortKeysInGraphDict(self):
        for key in self.graph:
            self.graph.update(
                {key: sorted(self.graph[key], key=lambda x: x[1])})

#   Вычисляет  эвристическое значения для данного узла
    def heuristic(self, node_to_check: str):
        return abs(ord(self.end_node) - ord(node_to_check))

#   Инициализирует решение жадным алгоритмом
    def startSolutionGreedy(self):
        self.getDictGraphFromInput()
        self.sortKeysInGraphDict()
        self.iterateGreedy(self.start_node, f"{self.start_node}")

#   Инициализирует решениеалгоритмом А*
    def startSolutionAStar(self) -> None:
        self.getDictGraphFromInput()
        self.iterateAStar()

#   Строит путь жадным алгоритмом
    def iterateGreedy(self, cur_node: str, cur_path: str) -> None:
        if self.path_found is True:
            return
        if cur_node == self.end_node:
            self.path = cur_path
            self.path_found = True
            return
        if self.graph.get(cur_node) is not None:
            for elem in self.graph[cur_node]:
                self.iterateGreedy(elem[0], cur_path + f"{elem[0]}")


#   Строит путь алгоритмом А*
    def iterateAStar(self):
        weighted_node_queue = PriorityQueue()
        parents = {}
        cost_sheet = {}
        weighted_node_queue.put((0, self.start_node))
        parents[self.start_node] = None
        cost_sheet[self.start_node] = 0
        while not weighted_node_queue.empty():
            cur_node = weighted_node_queue.get()[1]
            if cur_node == self.end_node:
                break
            if self.graph.get(cur_node) != None:
                for next_node, next_weight in self.graph.get(cur_node):
                    new_cost = cost_sheet[cur_node] + next_weight
                    if next_node not in cost_sheet or new_cost < cost_sheet[
                            next_node]:
                        cost_sheet[next_node] = new_cost
                        new_priority = new_cost + self.heuristic(next_node)
                        weighted_node_queue.put((new_priority, next_node))
                        parents[next_node] = cur_node
        cur_node = self.end_node
        self.path = f"{self.end_node}"
        while cur_node != self.start_node:
            cur_node = parents[cur_node]
            self.path += cur_node
        self.path = self.path[::-1]

if __name__ == "__main__":
    solution = Solve()
    solution.startSolutionGreedy()
    solution.printSolution()
