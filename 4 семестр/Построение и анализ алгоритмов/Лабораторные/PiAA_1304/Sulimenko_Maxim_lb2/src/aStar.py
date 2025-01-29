from queue import PriorityQueue


class Solve:
    def __init__(self):
        self.graph = dict()
        self.startNode = None
        self.endNode = None
        self.path = ''

    #   Считывает входные данные и составляет граф в виде словаря
    def read_input(self):
        self.startNode, self.endNode = input().split()
        while True:
            try:
                parent, child, cost = input().split()
                if parent in self.graph:
                    self.graph[parent].append([child, float(cost)])
                else:
                    self.graph[parent] = [[child, float(cost)]]
            except:
                break

    # Метод, реализующий эвристическую функцию
    def get_heuristics(self, node):
        return abs(ord(node) - ord(self.endNode))

    # Метод, который строит путь в необходимом формате
    def build_path(self, previousNode):
        currentNode = self.endNode
        while currentNode is not None:
            self.path += currentNode
            currentNode = previousNode[currentNode]
        self.path = self.path[::-1]
        print(self.path)

    # Метод, который реализует алгорит A*
    def start_a_star_algorithm(self):
        graphQueue = PriorityQueue()
        graphQueue.put((0, self.startNode))
        previousNode = {self.startNode: None}
        intermediateCost = {self.startNode: 0}

        while not graphQueue.empty():
            currentNode = graphQueue.get()[1]
            if currentNode == self.endNode:
                break
            if currentNode in self.graph:
                adjacentNodes = self.graph[currentNode]
                for nextNode, costOfNextNode in adjacentNodes:
                    newCost = intermediateCost[currentNode] + costOfNextNode
                    if nextNode not in intermediateCost or newCost < intermediateCost[nextNode]:
                        intermediateCost[nextNode] = newCost
                        priority = newCost + self.get_heuristics(nextNode)
                        graphQueue.put((priority, nextNode))
                        previousNode[nextNode] = currentNode

        self.build_path(previousNode)


#   Функция, которая создаёт экземпляр класса solve
#   и запускает необходимые для решения функции
def get_solution():
    solution = Solve()
    solution.read_input()
    solution.start_a_star_algorithm()


get_solution()
