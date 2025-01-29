import queue


# Данный класс содержит информацию о пути, который надо найти, а именно стартовую вершину, конечную
# и массив, в котором содержится набор вершин составляющих путь мужду на началом и концом
class Path:

    # Инициализация класса
    def __init__(self, points):
        self.start_point = points[0]
        self.finish_point = points[1]
        self.way = [self.start_point]

    # Возвращает строковое представление объекта класса как путь между вершинами
    def __str__(self):
        path_str = ''
        for element in self.way[::-1]:
            path_str += element
        return path_str


# Данная функция осуществляет считываение с клавиатуры и возвращает объект класса Path и словарь, с вершинами графа
def inputs():
    graph = {}
    path = Path(input().split())
    max_length = 0
    while True:
        try:
            line = input().split()
            if line == []:
                break
            if line[0] not in graph:
                graph[line[0]] = []
            graph[line[0]].append([line[1], float(line[2])])
            if float(line[2]) > max_length:
                max_length = float(line[2])
        except (ValueError, EOFError):
            return path, graph


# Данная функция формирует ответ к заданию
# На вход подаётся объет класса Path, последнюю пройденную вершину и словарь,
# описывающий из какой вершины мы пришли в данную 
# Возвращает объект класса Path
def form_answer(path, current_node, came_from):
    path.way = [current_node]
    node = path.finish_point
    while node != path.start_point:
        node = came_from[current_node]
        path.way.append(node)
        current_node = node
    return path


# Данная функция решает задачу использую алгоритм A* для поиска кратчайшего пути в орграфе
# Возвращает объект класса Path
def find_way():
    path, graph = inputs()
    nodes_queue = queue.PriorityQueue(maxsize = 0)
    nodes_queue.put((0, path.start_point))
    came_from = {}
    cost_so_far = {}
    cost_so_far[path.start_point] = 0
    current_node = None
    while not nodes_queue.empty():
        current_node = nodes_queue.get()[1]
        if current_node == path.finish_point: break
        if current_node in graph:
            for next in graph[current_node]:
                new_cost = cost_so_far[current_node] + next[1]
                if next[0] not in cost_so_far or new_cost < cost_so_far[next[0]]:
                    cost_so_far[next[0]] = new_cost
                    priority = new_cost + abs(ord(next[0]) - ord(path.finish_point))
                    nodes_queue.put((priority, next[0]))
                    came_from[next[0]] = current_node
    return form_answer(path, current_node, came_from)


def main():
    print(find_way())


if __name__ == "__main__":
    main()
    