def h(a, b):
    """
    Функция, возвращающая эвристическое приближение
    между вершинами a и b
    """
    return float(abs(ord(b) - ord(a)))


def get_nearest_vert(open, closed):
    """
    Функция ищущая ближайшую вершину в массиве open,
    не содержащуюся в closed
    """
    min = 10000
    for i in open:
        if i not in closed:
            if min > open[i]:
                min = open[i]
    for i in open:
        if i not in closed:
            if open[i] == min:
                return i


def ASTAR(start_vertex, end_vertex, graph):
    """
    Функция, выполняющая алгоритм А*.
    Ищет кратчайший путь между вершинами start_vertex и end_vertex графа graph
    """
    closed = []
    G_rate = {start_vertex: 0}
    open = {start_vertex: h(start_vertex, end_vertex)}
    map = {start_vertex: None}
    while len(open):
        current_vertex = get_nearest_vert(open, closed)
        if current_vertex in closed:
            continue
        if current_vertex == end_vertex:
            res = current_vertex
            while map[current_vertex]:
                res += map[current_vertex]
                current_vertex = map[current_vertex]
            res = res[::-1]
            return res
        closed.append(current_vertex)
        for child in graphcurrent_vertex]:
            temp_g = G_rate[current_vertex] + graph[current_vertex][child]
            if child not in open or temp_g < G_rate[child]:
                map[child] = current_vertex
                G_rate[child] = temp_g
                temp_f = temp_g + h(child, end_vertex)
                if child not in open:
                    open[child] = temp_f


if __name__ == '__main__':
    graph = {}
    start_vertex, end_vertex = input().split()
    while True:
        try:
            string = input().split()
        except EOFError:
            break
        if not string:
            break
        if string[0] not in graph.keys():
            graph[string[0]] = {}
        graph[string[0]][string[1]] = float(string[2])
        if string[1] not in graph.keys():
            graph[string[1]] = {}

    print(ASTAR(start_vertex, end_vertex, graph))
