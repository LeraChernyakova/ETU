import sys
from time import perf_counter


def lower_bound(graph, v, visited):
    """
    Вычисляет нижнюю границу стоимости гамильтонова цикла для оставшихся вершин
    :param graph: матрица смежности графа
    :param v: текущая вершина
    :param visited: список посещённых вершин
    :return: нижняя граница стоимости гамильтонова цикла для оставшихся вершин
    """
    bound = 0
    for i in range(len(graph)):
        if not visited[i]:
            min_edge = sys.maxsize
            for j in range(len(graph)):
                if i != j and graph[i][j] < min_edge:
                    min_edge = graph[i][j]
            bound += min_edge
    return bound


def recursive_search(graph, v, visited, curr_len, min_len, min_path):
    """
    Рекурсивно ищет кратчайший гамильтонов цикл, начиная с вершины v,
    и обновляет минимальную длину и соответствующий путь при
    нахождении лучшего решения.
    :param graph: Матрица смежности, представляющая граф
    :param v: Текущая вершина, с которой начинается рекурсивный вызов.
    :param visited: Список булевых значений, отображающий посещенные вершины (True - посещена, False - не посещена).
    :param curr_len: Текущая длина пути.
    :param min_len: Список из одного элемента, содержащий минимальную длину гамильтонова цикла.
    :param min_path: Список из одного элемента, содержащий минимальный гамильтонов цикл.
    :return: None
    """
    visited[v] = True

    all_visited = all(visited)
    if all_visited:
        if graph[v][0] != sys.maxsize:
            curr_len += graph[v][0]
            if curr_len < min_len[0]:
                min_len[0] = curr_len
                min_path[0] = [i for i, visited in enumerate(visited) if
                               visited] + [0]
        visited[v] = False
        return

    for neighbor in range(len(graph)):
        if neighbor == v:
            continue
        if not visited[neighbor] and graph[v][neighbor] != sys.maxsize:
            bound = lower_bound(graph, neighbor, visited) + curr_len + \
                    graph[v][neighbor]
            if bound < min_len[0]:
                recursive_search(graph, neighbor, visited, curr_len + graph[v][neighbor],
                    min_len, min_path)
    visited[v] = False


def shortest_hamiltonian_cycle(graph):
    """
    Ищет кратчайший гамильтонов цикл для заданного графа, представленного матрицей смежности.
    :param graph: Матрица смежности
    :return: Минимальная длина пути и сам путь
    """
    visited = [False] * len(graph)
    min_len = [sys.maxsize]
    min_path = [None]
    recursive_search(graph, 0, visited, 0, min_len, min_path)
    return min_len[0], min_path[0]


def read_graph_from_file(filename):
    """
    Считывает матрицу смежности графа из текстового файла и возвращает ее в виде списка списков.
    :param filename: Имя файла
    :return: Минимальная длина пути и сам путь
    """
    file = open(filename, 'r')
    size = int(file.readline())
    graph = []
    for line in file.readlines():
        row = [int(x) if x != "inf" and x != '-' else sys.maxsize for x in
               line.strip().split()]
        graph.append(row)
    return graph


filename = "input.txt"
graph = read_graph_from_file(filename)

start_time = perf_counter()
length, path = shortest_hamiltonian_cycle(graph)
elapsed_time = (perf_counter() - start_time) * 1000  # Время в миллисекундах
if path is not None:
    ans_path = list(map(lambda x: x + 1, path))
    print(f"{ans_path}, {length}, {elapsed_time:.5f}mс")
else:
    print("Нет существует гамильтонова цикла")
