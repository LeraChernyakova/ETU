class Graph:
    # инициализация необходимых переменных и структур данных
    def __init__(self):
        self.__path = ''  # для сохранения ответа на задачу
        self.__graph_storage = {}  # структура для хранения графа
        self.__start_node = ''  # старт-узел
        self.__end_node = ''  # финиш-узел
        self.__path_was_found = False
        self.__visited_nodes = {}

    # данный метод запуск логику решения задачи
    def solution(self):
        self.__read_graph()
        self.__greedy_algorithm(self.__start_node, self.__start_node)
        self.__print_path()

    # выход: путь из стартового узла в финишный
    # данцный метод предназачен для вывода ответа на исходную задачу
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
                self.__visited_nodes[node_pair_data[0]] = False  # первый узел ещё не посещён
                self.__visited_nodes[node_pair_data[1]] = False  # как и второй, это нужно для жадного алгоритма
            except:
                break  # закончить считывание

    # данный метод предназначен для отбора непросмотренных вершин в текущем состоянии рекурсии
    # входные данные: список смежных вершин с данной
    # выходные данные: список непросмотренных смежных вершин с данной
    def __get_unexplored_neighbors(self, neighbors_info):
        unexplored_neighbors = []
        for node_info in neighbors_info:
            if not self.__visited_nodes[node_info[0]]:  # если вершина не посещалась ранее
                unexplored_neighbors.append(
                    node_info)  # то добавить её и вес входящего в неё ребра из данной вершины в список
        return unexplored_neighbors

    # данный рекурсивный метод предназначен для поиска пути в графе по заданному жадному алгоритму
    def __greedy_algorithm(self, current_node, path):
        if self.__path_was_found:
            return
        elif current_node == self.__end_node:  # если финишный узел достигнут
            self.__path = path  # записать полученный путь
            self.__path_was_found = True  # отметить, что ответ найдён
            return
        elif current_node not in self.__graph_storage:  # если узел висячий и не финишный узел
            return  # то из него точно не выходят дуги, можно остановить поиск
        unexplored_neighbors = self.__get_unexplored_neighbors(self.__graph_storage[current_node])
        sorted_neighbors_weight = sorted(unexplored_neighbors, key=lambda node_data: node_data[
            1])  # сортировка непосещённых узлов по весам входящих в них дуг из текущей вершины
        self.__visited_nodes[current_node] = True  # пометить текущую вершину, что она посещена
        for node_info in sorted_neighbors_weight:
            self.__greedy_algorithm(node_info[0], path + node_info[0])


if __name__ == "__main__":
    graph = Graph()
    graph.solution()
