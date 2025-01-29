class Edge:
    """
    Класс ребра графа
    """
    next = None
    prev = None

    def __init__(self, edge):
        """
        Конструктор класса.
        Аргумент - массив edge, элементами
        которого заполняются поля
        start_vertex, end_vertex и dist.
        """
        self.start_vertex = edge[0]
        self.end_vertex = edge[1]
        self.dist = float(edge[2])


class List:
    """
    Класс двунаправленного списка рёбер
    """

    head = None
    cur = None

    def insert(self, edge):
        """
        Метод вставки ребра edge в список.
        """
        if self.head is None:
            self.head = edge
        else:
            self.cur = self.head
            while self.cur is not None:
                if edge.dist < self.cur.dist:
                    if self.cur == self.head:
                        self.cur.prev = edge
                        edge.next = self.cur
                        self.head = edge
                        break
                    else:
                        prev = self.cur.prev
                        prev.next = edge
                        edge.prev = prev
                        edge.next = self.cur
                        self.cur.prev = edge
                else:
                    if self.cur.next is not None:
                        if edge.dist > self.cur.next.dist:
                            self.cur = self.cur.next
                            continue
                        else:
                            edge.next = self.cur.next
                            edge.prev = self.cur
                            self.cur.next = edge
                            break
                    else:
                        self.cur.next = edge
                        edge.prev = self.cur
                        break
                self.cur = self.cur.next


class Data:
    """
    Класс-структура введённых
    пользователем данных
    """
    start_vertex, end_vertex = '', ''
    edge = ''
    edges = List()
    path = []


def inputKeyboard():
    """
    Функция ввода пользователем данных с клавиатуры.
    Возвращает объект класса Data.
    """
    data = Data()
    i = 0

    while True:
        if i == 1:
            try:
                string = input()
            except EOFError:
                break
            if not string:
                break
            data.edge = Edge(string.split(" "))
            data.edges.insert(data.edge)
        if i == 0:
            data.start_vertex, data.end_vertex = input().split()
            i += 1
            continue
    return data


def writePath(start_vertex, end_vertex, path, list, visited):
    """
    Функция поиска минимального по весу пути
    от вершины start_vertex до вершины end_vertex c помощью жадного алгоритма.
    """
    list.cur = list.head
    while list.cur is not None:
        if list.cur.start_vertex == start_vertex:
            if list.cur in visited:
                list.cur = list.cur.next
                continue
            if list.cur.end_vertex == end_vertex:
                path.append(list.cur.end_vertex)
                path.append(list.cur.start_vertex)
                return
            temp = list.cur
            visited.append(list.cur)
            writePath(list.cur.end_vertex, end_vertex, path, list, visited)
            list.cur = temp
            if list.cur is None:
                break
            if len(path) and path[0] == end_vertex:
                path.append(list.cur.start_vertex)
                return
        list.cur = list.cur.next


data = inputKeyboard()

visited = []

writePath(data.start_vertex, data.end_vertex, data.path, data.edges, visited)
data.path.reverse()
print(''.join(data.path))
