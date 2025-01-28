# Модуль для создания очереди приоритетов
import heapq

# Класс, описывающий ориентированный граф
class OrientedGraph():
    
    # Конструктор класса от значения стартовой и конечной вершины, 
    # словаря ребер и их веса
    def __init__(self, start_node, end_node, graph_paths):
        self.start_node = start_node
        self.end_node = end_node
        self.graph_paths = graph_paths
        
    # Сортировка вершин по увеличению расстояния от исходной
    # Принимает на вход экземпляр класса     
    def sorted_graph(self):
        for key in self.graph_paths:
            self.graph_paths[key].sort(key=lambda x:x[1])
    
    # Реализация жадного алгоритма
    # Принимает на вход экземпляр класса
    # Возвращает путь от начальной до конечной вершины   
    def greedy_algorithm(self):
        self.sorted_graph()
        start = self.start_node
        answer = start
        while start != self.end_node:
            next_node = self.graph_paths[start][0][0]
            if next_node not in self.graph_paths.keys() and next_node != self.end_node:
                self.graph_paths[start].pop(0)
            else:
                start = next_node
                answer += start
        return answer
    
    # Эвристическая функция для алгоритма A*
    # Принимает на вход экзмепляр класса и вершину
    # Возвращает близость символов, обозначающих
    # переданную и конечную вершину, в таблице ASCII
    def heuristic_function(self, node):
        return abs(ord(node)-ord(self.end_node))
    
    # Составление корректного ответа для алгоритма A*
    # Принимает на вход экземпляр класса и словарь ребер
    # Возвращает отформатированный ответ в соответствии с заданеим
    def Astar_answer(self, node_from):
        answer = self.end_node
        while node_from[answer[0]]:
            answer = node_from[answer[0]] + answer
        return answer
    
    # Реализация алгоритма A*
    # Принимает на вход экземпляр класса
    # Возвращает путь от начальной до конечной вершины
    def Astar_algorithm(self):
        node_cost = {self.start_node:0}
        pqueue = []
        heapq.heappush(pqueue, (0, self.start_node))
        node_from = {self.start_node: None}
        
        while len(pqueue):
            current = heapq.heappop(pqueue)[1]
            
            if current == self.end_node:
                break
            
            if current in self.graph_paths.keys():
                for node in self.graph_paths[current]:
                    cost = node_cost[current] + node[1]
                    if node[0] not in node_cost or cost < node_cost[node[0]]:
                        node_cost[node[0]] = cost
                        priority = cost + self.heuristic_function(node[0])
                        heapq.heappush(pqueue, (priority, node[0]))
                        node_from[node[0]] = current
                    
        return self.Astar_answer(node_from)
        
# Функция, считывающая ребра графа и их вес
# Возвращает словарь ребер графа и их веса 
def reading_edges():
    graph_paths = dict()
    while True:
        try: 
            for elements in input().split('\n'):
                node1, node2, length = elements.split()
                if node1 not in graph_paths.keys():
                    graph_paths[node1] = [[node2, float(length)]]
                else:
                    graph_paths[node1] += [[node2, float(length)]]
        except:
            break
    return graph_paths

# Функция, запускающая решение поставленной задачи
def solution():
    start_node, end_node = input().split()
    graph_paths = reading_edges()
    graph = OrientedGraph(start_node, end_node, graph_paths)
    print(graph.greedy_algorithm())
    print(graph.Astar_algorithm())

# Условие для запуска программы
if __name__ == "__main__":
    solution()
    