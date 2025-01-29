#импорт потока ввода stdin
#для корректного ввода для stepik
from sys import stdin

#импорт очереди с приоритетом
#для построения алгоритма А*
from queue import PriorityQueue

#класс вершины графа
class Node:
    def __init__(self, node_name):
        self.node_name  = node_name #название вершины
        self.out_edges = [] #исходящие ребра
        self.heuristic = 0 #эвристика
        self.cost_path = 100000 #+Б - пока не найден путь до верщины
        self.prev_node = '' #откуда попал в вершину

#Класс ориентированного графа, решающего задачу
class Solve:
    def __init__(self,start,finish):
        self.start_node = start #начальная вершина
        self.finish_node = finish #конечная вершина
        self.nodes = {} #словарь всех вершин (name:node)
        self.viewed = [] #вершины, до которых найден оптимальный путь
        self.queue = PriorityQueue() #просматриваемые вершины

    #Заполнение графа вершинами и ребрами
    def insert_way(self,way):
        for i in range(2):
            if way[i] not in self.nodes.keys():
                self.nodes[way[i]] = Node(way[i])
        self.nodes[way[0]].out_edges.append((way[1], way[2]))

    #метод, вызывающийся для решения задачи
    def solve(self):
        for elems in self.nodes.keys():
            self.nodes[elems].out_edges.sort()
            self.nodes[elems].heuristic = abs(ord(elems) - ord(self.finish_node))
        self.nodes[self.start_node].cost_path = 0
        self.__astar_seach()

    #Поиск пути алгоритмом А*
    def __astar_seach(self):
        #поместить start в очередь
        h = self.nodes[self.start_node].heuristic
        g = self.nodes[self.start_node].cost_path
        current_node_elem = [h+g,self.start_node]
        self.queue.put(current_node_elem)
        #обход графа
        while not self.queue.empty():
            if current_node_elem[1] == self.finish_node:
                break
            current_node_elem = self.queue.get() #извлечение элемента с самым высоким приоритетом
            self.viewed.append(current_node_elem)
            #обход по смежным с текущей извлеченной вершиной
            for way in self.nodes[current_node_elem[1]].out_edges:
                if self.nodes[current_node_elem[1]].cost_path + way[1] < self.nodes[way[0]].cost_path:
                    self.nodes[way[0]].prev_node = current_node_elem[1]
                    self.nodes[way[0]].cost_path = self.nodes[current_node_elem[1]].cost_path + way[1]
                    h = self.nodes[way[0]].heuristic
                    g = self.nodes[way[0]].cost_path
                    self.queue.put([h+g,way[0]])

    #Формат для вывода
    def __str__(self):
        result = ""
        current_node = self.nodes[self.finish_node].node_name
        while current_node!='':
            result+=current_node
            current_node = self.nodes[current_node].prev_node
        return result[::-1]

#ввод данных для построения графа
def input_data():
    start_node_name, finish_node_name = input().split()
    graph = Solve(start_node_name, finish_node_name)
    input_edges = ' '
    for input_edges in stdin:
        input_edges = input_edges.split()
        if input_edges == []:
            break
        input_edges[2] = float(input_edges[2])
        graph.insert_way(input_edges)
    return graph

if __name__ == '__main__':
    graph = input_data()
    graph.solve()
    print(graph)
    pass


