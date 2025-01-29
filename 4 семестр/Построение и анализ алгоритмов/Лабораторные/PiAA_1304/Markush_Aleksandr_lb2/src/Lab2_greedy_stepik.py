# Данный класс содержит информацию о пути, который надо найти, а именно: стартовую вершину, конечную, 
# максимальный размер ребра и массив, в котором содержится набор вершин составляющих путь между на началом и концом
class Path:

    # Инициализация класса
    def __init__(self, points):
        self.start_point = points[0]
        self.finish_point = points[1]
        self.way = [self.start_point]
        self.max_edge_len = None

    # Возвращает строковое представление объекта класса как путь между вершинами
    def __str__ (self):
        str = ''
        for element in self.way:
            str += element
        return str


# Данная функция осуществляет считывание входных данных и возвращает объект класса Path и словарь, с вершинами графа
def inputs():
    graph = {}
    path = Path(input().split())
    max_edge_len = 0
    while True:
        try:
            line = input().split()
            if line == []:
                break
            if line[0] not in graph:
                graph[line[0]] = []
            graph[line[0]].append([line[1], float(line[2])])
            if float(line[2]) > max_edge_len:
                max_edge_len = float(line[2])
            path.max_edge_len = max_edge_len
        except (ValueError, EOFError):
            return path, graph


# Данная функция проверяет на то не зашли ли мы в вершину, являющуюся листом графа,
# но которая не является концом нужного нам пути
# На вход принимает вершину графа, словарь, описывающий граф, список пройденных рёбер и объект класса Path
# Возвращает вершину и bool-переменную, в которой содержится информация о том является ли данная вершина листом
def check_deadlock(point, graph, passed, path):
    deadlock = False
    if point not in graph or graph[point] == []:
        path.way.pop()
        for passed_edge in passed:
            if passed_edge[0] == point:
                for edge in graph.items():
                    for node_name in edge[1]:
                        if passed_edge[0] == node_name[0]:
                            edge[1].remove(node_name)
                break
        point = path.way[-1]
        deadlock = True
    return point, deadlock


# Функция ищет ближайшую вершину к нынешней
# На вход получает вершину, объект класса Path, список пройдённых рёбер, словарь, описывающий граф
# Возвращает новую вершину и длину пути до неё
def choose_the_shortest_path(point, path, passed, graph):
    min_edge_length = path.max_edge_len + 1
    new_point = point
    for i in range(len(graph[point])):
        if graph[point][i][1] < min_edge_length and (graph[point][i][0] not in elemnt for elemnt in passed):
            min_edge_length = graph[point][i][1]
            new_point = graph[point][i][0]
    point = new_point
    return point, min_edge_length


# Функция, решающая задачу поиска кратчайшего пути в орграфе с помощью жадного алгоритма
# Возвращает объект класса Path
def find_way():
    path, graph = inputs()
    point = path.start_point
    passed = []
    while point != path.finish_point:
        if point == path.finish_point:
            path.way.append(point)
            break
        point, deadlock = check_deadlock(point, graph, passed, path)
        if deadlock: continue
        point, min_edge_lenght = choose_the_shortest_path(point, path, passed, graph)
        passed.append([point, min_edge_lenght])
        path.way.append(point)
    return path


def main():
    print(find_way())


if __name__ == "__main__":
    main()