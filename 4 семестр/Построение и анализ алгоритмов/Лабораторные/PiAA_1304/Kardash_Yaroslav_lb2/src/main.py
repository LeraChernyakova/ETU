#импорт потока ввода stdin
#для корректного ввода для stepik
from sys import stdin

#класс вершины графа
class Node:
    def __init__(self, node_name):
        self.node_name = node_name #название вершины
        self.out_edges = [] #исходящие ребра

#Класс ориентированного графа, решающего задачу
class Solve:
    def __init__(self, start_node, finish_node):
        self.start_node = start_node #начальная вершина
        self.finish_node = finish_node #конечная вершина
        self.nodes_dict = {} #словарь всех вершин (name:node)
        self.final_way = "" #конечный путь
        self.viewed_nodes = [] #просмотренные вершины

    #Заполнение графа вершинами и ребрами
    def insert_way(self,way):
        for i in range(2):
            if way[i] not in self.nodes_dict.keys():
                self.nodes_dict[way[i]] = Node(way[i])
        self.nodes_dict[way[0]].out_edges.append((way[1], way[2]))

    # метод, вызывающийся для решения задачи
    def solve(self):
        for elems in self.nodes_dict.keys():
            self.nodes_dict[elems].out_edges.sort()
        current_way = ''
        self.__greedy_search(self.start_node,current_way)

    # Жадный алгоритм поиска пути
    def __greedy_search(self, current_node, current_way):
        if current_node == self.finish_node or self.finish_node in self.final_way:
            current_way+=self.finish_node
            self.final_way = current_way
            return
        #выбрать минимальную непросмотренную вершину
        # и переместиться к ней
        current_way += current_node
        while self.finish_node not in self.final_way:
            min_way = self.__find_min_way(self.nodes_dict[current_node])
            if min_way in self.nodes_dict.keys():
                self.viewed_nodes.append(min_way)
                self.__greedy_search(min_way, current_way)
            else:
                return

    # Нахождение минимальной вершины для жадного алгоритма
    def __find_min_way(self,node):
        if node.out_edges == []:
            return ''
        min_way = 1000
        min_name = ''
        for elems in node.out_edges:
            if elems[0] in self.viewed_nodes:
                continue
            if elems[1]<min_way:
                min_name = elems[0]
                min_way = elems[1]
        return min_name



    #Формат для вывода
    def __str__(self):
        return self.final_way

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


