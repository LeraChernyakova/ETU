import time
# Этот модуль предоставляет различные функции для управления значениями времени
from copy import deepcopy
# Операция глубокого копирования произвольных объектов Python
from math import inf
# Положительная бесконечность с плавающей запятой


class Vertex:
    """Класс вершины графа"""
    def __init__(self, amount_of_neighbours: int) -> None:
        """
        Инициализирует вершину
        :param amount_of_neighbours: количество смежных вершин с данной
        """
        self.__distances = dict()
        for i in range(amount_of_neighbours):
            self.__distances[i] = inf
        self.__sorted_indexes = list()

    def get_distance_cost(self, index: int) -> float:
        """
        Возвращает стоимость пути между вершиной и смежной с ней
        :param index: индекс смежной вершины
        :return: стоимость пути между вершиной и смежной с ней
        """
        return self.__distances[index]

    def set_distance_cost(self, index: int, cost: int) -> None:
        """
        Устанавливает стоимость пути между вершиной и смежной с ней
        :param index: индекс смежной вершины
        :param cost: стоимость пути между вершиной и смежной с ней
        :return:
        """
        self.__distances[index] = cost

    def sort_indexes(self) -> None:
        """
        Сортирует индексы смежных вершин с данной
        :return:
        """
        self.__sorted_indexes = list(map(lambda x: x[0], sorted(self.__distances.items(), key=lambda x: x[1])))

    def get_sorted_indexes(self) -> list[int]:
        """
        Возвращает список отсортированных индексов смежных вершин с данной
        :return: список отсортированных индексов смежных вершин с данной
        """
        return self.__sorted_indexes


class Graph:
    """Класс графа"""
    def __init__(self, size: int) -> None:
        """
        Инициализирует граф
        :param size: количество вершин в графе
        """
        self.__size = size
        self.__graph_matrix = [Vertex(size) for _ in range(size)]

    def get_graph_size(self) -> int:
        """
        Возврашает количество вершин в графе
        :return: количество вершин в графе
        """
        return self.__size

    def get_distance_cost_between_vertexes(self, source: int, destination: int) -> float:
        """
        Возвращает стоимость пути между двумя вершинами
        :param source: индекс первой вершины
        :param destination: индекс второй вершины
        :return: стоимость пути между двумя вершинами
        """
        return self.__graph_matrix[source].get_distance_cost(destination)

    def set_distance_cost_between_vertexes(self, source: int, destination: int, cost: int) -> None:
        """
        Устанавливает стоимость пути между двумя вершинами
        :param source: индекс первой вершины
        :param destination: индекс второй вершины
        :param cost: стоимость пути между двумя вершинами
        :return:
        """
        self.__graph_matrix[source].set_distance_cost(destination, cost)

    def get_way_cost(self, distances: list[int]) -> int:
        """
        Возварщает стоимость пути
        :param distances: список индексов вершин
        :return: стоимость пути
        """
        summary_cost = 0

        for i in range(1, len(distances)):
            summary_cost += self.__graph_matrix[distances[i-1]].get_distance_cost(distances[i])

        return summary_cost

    def get_vertex(self, index: int) -> Vertex:
        """
        Возвращает вершину графа
        :param index: индекс вершины
        :return: вершина графа
        """
        return self.__graph_matrix[index]

    def sort_indexes_of_each_vertex(self) -> None:
        """
        Сортирует индексы смежных вершин у каждой вершины графа
        :return:
        """
        for vertex in self.__graph_matrix:
            vertex.sort_indexes()


class Solution:
    """Класс решения"""
    def __init__(self, graph_matrix) -> None:
        """
        Инициализирует класс решения
        :param graph_matrix: матрица графа
        """
        self.__graph_matrix = graph_matrix
        self.__best_way = list()
        self.__best_way_cost = inf

    def __find_best_way_by_greedy(self, start_vertex_index: int = 0, excluded_vertexes: list[int] = None) -> list[int]:
        """
        Ищет минимальный гамильтонов цикл жадным алгоритмом
        :param start_vertex_index: индекс начальной вершины
        :param excluded_vertexes: список индексов просмотренных вершин
        :return: список индексов вершин в минимальном гамильтоновом цикле
        """
        if excluded_vertexes is None:
            excluded_vertexes = list()
        greedy_way = [start_vertex_index]

        while len(greedy_way) + len(excluded_vertexes) < self.__graph_matrix.get_graph_size():
            cur_vertex_index = greedy_way[-1]
            sorted_indexes = self.__graph_matrix.get_vertex(cur_vertex_index).get_sorted_indexes()
            for index in sorted_indexes:
                if (index in greedy_way) or (index in excluded_vertexes):
                    continue
                greedy_way.append(index)
                break
            if cur_vertex_index == greedy_way[-1]:
                break
        greedy_way.append(start_vertex_index)

        return greedy_way

    def __find_min_spanning_tree_cost(self, start_vertex_index: int, excluded_vertexes: list[int]) -> int:
        """
        Ищет стоимость минимального остового дерева
        :param start_vertex_index: индекс начальной вершины
        :param excluded_vertexes: список индексов просмотренных вершин
        :return: стоимость минимального остового дерева
        """
        min_spanning_tree_cost = 0
        visited_vertexes = []
        visited_indexes_stack = [start_vertex_index]

        while len(visited_indexes_stack) > 0:
            cur_vertex_index = visited_indexes_stack[-1]
            min_cost_index = -1
            sorted_indexes = self.__graph_matrix.get_vertex(cur_vertex_index).get_sorted_indexes()
            for index in sorted_indexes:
                if index in visited_vertexes or index in visited_indexes_stack or index in excluded_vertexes:
                    continue
                if self.__graph_matrix.get_distance_cost_between_vertexes(cur_vertex_index, index) == inf:
                    break
                min_cost_index = index
            if min_cost_index == -1:
                visited_vertexes.append(visited_indexes_stack.pop())
            else:
                visited_indexes_stack.append(min_cost_index)
                min_spanning_tree_cost += self.__graph_matrix.get_distance_cost_between_vertexes(cur_vertex_index, min_cost_index)

        return min_spanning_tree_cost

    def __find_best_way_by_branch_and_bound(self, current_way: list[int], current_way_cost: int) -> None:
        """
        Ищет минимальный гамильтонов цикл методом ветвей и границ
        :param current_way: текущий путь
        :param current_way_cost: стоимость текущего пути
        :return:
        """
        if current_way_cost >= self.__best_way_cost:
            return
        if len(current_way) == self.__graph_matrix.get_graph_size():
            new_cost = current_way_cost + self.__graph_matrix.get_distance_cost_between_vertexes(current_way[-1], current_way[0])
            if new_cost < self.__best_way_cost:
                new_way = deepcopy(current_way)
                new_way.append(current_way[0])
                self.__best_way_cost = new_cost
                self.__best_way = new_way
            return
        if current_way_cost + self.__graph_matrix.get_graph_size() - len(current_way) + 1 >= self.__best_way_cost:
            return
        if current_way_cost + self.__find_min_spanning_tree_cost(current_way[-1], current_way) >= self.__best_way_cost:
            return

        for i in range(self.__graph_matrix.get_graph_size()):
            if i in current_way:
                continue
            current_way.append(i)
            next_way_cost = current_way_cost + self.__graph_matrix.get_distance_cost_between_vertexes(current_way[-2], current_way[-1])
            self.__find_best_way_by_branch_and_bound(current_way, next_way_cost)
            current_way.pop()

    def find_best_way(self) -> list[int]:
        """
        Ищет минимальный гамильтонов цикл методом ветвей и границ с оптимизацией
        :return: список индексов вершин в минимальном гамильтоновом цикле
        """
        self.__best_way = self.__find_best_way_by_greedy(0, [])
        self.__best_way_cost = self.__graph_matrix.get_way_cost(self.__best_way)

        for i in range(self.__graph_matrix.get_graph_size()):
            self.__find_best_way_by_branch_and_bound([i], 0)

        return self.__best_way


class TSPSolverFromFile:
    """Класс решения задачи коммивояжера, считывающий исходные данные с файла"""
    def __init__(self, file_name: str) -> None:
        """
        Инициализирует класс решения задачи коммивояжера, считывающий исходные данные с файла
        :param file_name: имя файла для считывания исходных данных
        """
        self.__file_name = file_name
        self.__size_of_graph_matrix = None
        self.__graph_matrix = None
        self.__solver = None
        self.__answer_way = list()
        self.__answer_way_cost = None
        self.__work_time = None

    def __init_graph_from_file(self) -> None:
        """
        Инициализирует граф из исходных данных из файла
        :return:
        """
        file = open(self.__file_name, 'r')
        self.__size_of_graph_matrix = int(file.readline())
        self.__graph_matrix = Graph(self.__size_of_graph_matrix)
        self.__solver = Solution(self.__graph_matrix)

        vertex_index = 0
        for line in file:
            formatted_row = list(map(lambda x: inf if x.strip() in ["inf", "-"] else int(x), line.split()))
            for i in range(len(formatted_row)):
                self.__graph_matrix.set_distance_cost_between_vertexes(vertex_index, i, formatted_row[i])
            vertex_index += 1

        file.close()

    def __format_way(self) -> None:
        """
        Форматирует список индексов вершин минимального гамильтонова цикла для заданного формата ответа
        :return:
        """
        for i in range(len(self.__answer_way)):
            self.__answer_way[i] += 1

    def solve(self) -> None:
        """
        Решает задачу коммивояжера
        :return:
        """
        self.__init_graph_from_file()
        start_time = time.time()
        self.__graph_matrix.sort_indexes_of_each_vertex()
        self.__answer_way = self.__solver.find_best_way()
        self.__answer_way_cost = self.__graph_matrix.get_way_cost(self.__answer_way)
        self.__work_time = (time.time() - start_time) * 1000
        self.__format_way()

    def print_answer(self) -> None:
        """
        Печатает ответ на задачу коммивояжера в заданном формате
        :return:
        """
        if self.__answer_way_cost != inf:
            print(self.__answer_way, self.__answer_way_cost, str(self.__work_time) + "mc")
        else:
            print("В данном графе нет гамильтонова цикла")


if __name__ == "__main__":
    solver = TSPSolverFromFile("test.txt")

    solver.solve()
    solver.print_answer()
