from queue import PriorityQueue


class Vertex:  # класс вершины графа
    def __init__(self, vertex):
        self.vertex = vertex
        self.ways = []  # список исходящих ребер из вершины
        self.h = 0  # эвристика
        self.g = 10000000  # стоимость пути от начала до вершины
        self.prev = ''


class Graph:  # класс графа
    def __init__(self, first_vertex, last_vertex):
        self.first_vertex = first_vertex
        self.last_vertex = last_vertex
        self.vertexes = {}  # словарь всех вершин вида name:Vertex()
        self.viewed = []  # список вершин, до которых уже найден оптимальный путь
        self.queue = PriorityQueue()  # просматриваемые вершины (очередь с приоритетом)

    def insert(self, way):  # добавление вершин и ребер в граф
        for i in range(2):
            if way[i] not in self.vertexes.keys():  
                self.vertexes[way[i]] = Vertex(way[i])
        self.vertexes[way[0]].ways.append((way[1], way[2]))  # добавление второй вершины в список исходящих путей для первой

    def a_star(self):  # алгоритмом А*
        h = self.vertexes[self.first_vertex].h
        g = self.vertexes[self.first_vertex].g
        vert = [h + g, self.first_vertex]
        self.queue.put(vert)  # добавление начальной вершины в очередь
        while not self.queue.empty():  # обход графа
            if vert[1] == self.last_vertex:
                break
            vert = self.queue.get()  # извлечение вершины с самым высоким приоритетом
            self.viewed.append(vert)
            for way in self.vertexes[vert[1]].ways:  # обход соседей текущей извлеченной вершиной
                if self.vertexes[vert[1]].g + way[1] < self.vertexes[way[0]].g:  # если найден более дешевый путь
                    self.vertexes[way[0]].prev = vert[1]
                    self.vertexes[way[0]].g = self.vertexes[vert[1]].g + way[1]
                    h = self.vertexes[way[0]].h
                    g = self.vertexes[way[0]].g
                    self.queue.put([h + g, way[0]])

    def solve(self):  # метод, вызывающийся в функции main() для решения задачи
        for elem in self.vertexes.keys():  # для всех ключей словаря рассчитывается эвристика
            self.vertexes[elem].h = abs(ord(elem) - ord(self.last_vertex))
        self.vertexes[self.first_vertex].g = 0  # для первой вершины функция g равна 0
        self.a_star()

    def __str__(self):  # вывод итогового пути
        res = ""
        vert = self.vertexes[self.last_vertex].vertex
        while vert != '':
            res += vert
            vert = self.vertexes[vert].prev
        return res[::-1]


def inputs():   # функция считывания входных параметров
    first_vertex, last_vertex = input().split()
    graph = Graph(first_vertex, last_vertex)
    while True:
        try:
            data = input().split()   # считывание из какой вершины путь, в какую вершину и стоимость пути
            if data == []:
                return graph
            data[2] = float(data[2])
            graph.insert(data)  # вставка пути в граф
        except (ValueError, EOFError):
            return graph


def main():
    graph = inputs()
    graph.solve()
    print(graph)


if __name__ == '__main__':
    main()