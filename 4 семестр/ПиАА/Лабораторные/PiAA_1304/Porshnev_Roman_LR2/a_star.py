from queue import PriorityQueue


class Graph:
    # инициализация необходимых переменных и структур данных
    def __init__(self):
        self.__path = ''  # для сохранения ответа на задачу
        self.__graph_storage = {}  # структура для хранения графа
        self.__start_node = ''  # старт-узел
        self.__end_node = ''  # финиш-узел

    # данный метод запуск логику решения задачи
    def solution(self):
        self.__read_graph()
        self.__a_star()
        self.__print_path()

    # данный метод предназачен для вывода ответа на исходную задачу
    def __print_path(self):
        print(self.__path)

    # данный метод предназначен для считывания графа
    def __read_graph(self):
        self.__start_node, self.__end_node = list(input().split())  # считывание стартового и финишного узла
        while True:
            try:
                node_pair_data = input().split()  # первый узел, второй и вес дуги между ними
                if node_pair_data[0] not in self.__graph_storage.keys():  # если для первого узла это первая дуга
                    self.__graph_storage[node_pair_data[0]] = [(node_pair_data[1], float(node_pair_data[2]))]
                else:  # если для первого узла это не первая дуга
                    self.__graph_storage[node_pair_data[0]].append((node_pair_data[1], float(node_pair_data[2])))
            except:
                break  # закончить считывание

    # входные данные: текущая вершина
    # выходные данные: значение эвристической функции
    # данный метод предназначен для нахождения значения эвристической функции, которая представляет собой
    # модуль разности ASCII-кодов текущего узла и конечного
    def __heuristic(self, current_node):
        return abs(ord(current_node) - ord(self.__end_node))

    # данный метод предназначен для нахождения минимального по стоимости пути между старовым и конечным узлом
    # с помощью алгоритма А*
    def __a_star(self):
        open_nodes = PriorityQueue()  # узлы, которые следует рассмотреть
        open_nodes.put((0, self.__start_node))  # начиная с начального
        weight = {self.__start_node: 0}  # ключ - узел, значение - суммарный вес рёбер, необходимый для достижения узла
        self.__came_from = {
            self.__start_node: None}  # ключ - узел, значение - из какой вершины можно попасть в ключ - узел
        while not open_nodes.empty():
            current_node_name = open_nodes.get()[1]  # извлечь из очереди имя самого приоритетного узла
            if current_node_name == self.__end_node:
                break  # конечный узел достигнут
            if current_node_name not in self.__graph_storage:
                self.__graph_storage[current_node_name] = []  # узел без исходящих из него дуг
            for neighbor_node in self.__graph_storage[current_node_name]:  # для каждого узла смежного с текущим узлом
                neighbor_name = neighbor_node[0]
                weight_between = neighbor_node[1]
                new_weight = weight[current_node_name] + weight_between  # новый текущий вес для соседнего узла
                if neighbor_name not in weight or new_weight < weight[neighbor_name]:
                    # если соседний узел ещё не находится в открытом списке
                    # или вес узла, смежного с текущим, можно уменьшить
                    weight[neighbor_name] = new_weight
                    self.__came_from[neighbor_name] = current_node_name
                    priority = new_weight + self.__heuristic(neighbor_name)  # приоритетность соседнего узла
                    open_nodes.put((priority, neighbor_name))
        self.__recover_path()

    # данный метод предназначен для восстановления пути по записям из словаря между стартовым и конечным узлом
    def __recover_path(self):
        current_node = self.__end_node
        while current_node:
            self.__path += current_node
            current_node = self.__came_from[current_node]
        self.__path = self.__path[::-1]


if __name__ == "__main__":
    graph = Graph()
    graph.solution()
