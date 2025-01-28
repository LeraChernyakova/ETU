from math import inf

# класс узла
class Node:
    def __init__(self, name, adjacent, previous=None):
        self.cost_to_reach = inf
        self.previous_node = previous
        self.letter_name = name
        self.adjacents = adjacent
    #добавление ребер к вершине
    def add_adjacent(self, adj, dist):
        self.adjacents += [(adj, dist)]

    def __str__(self):
        return self.letter_name

# эвристическая функция
def Heuristic(currentNode, finish):
    return abs(ord(finish.letter_name) - ord(currentNode.letter_name))

# построение пути
def build_path(to_node):
    path = ''
    while to_node != None:
        path += str(to_node)
        to_node = to_node.previous_node
    return path[::-1]

# функция выбора вершины для перемещения
def choose_node(reachable, finish):
    min_cost = inf
    best_node = None

    for node in reachable:
        cost_start_to_node = node.cost_to_reach
        cost_node_to_goal = Heuristic(node, finish)
        total_cost = cost_start_to_node + cost_node_to_goal

        if min_cost > total_cost:
            min_cost = total_cost
            best_node = node

    return best_node

# функция поиска пути
def A_star(start_node, end_node):
    reachable = [start_node]
    explored = []
    while reachable:
        node = choose_node(reachable, end_node)
        if node == end_node:
            return build_path(end_node)
        reachable.remove(node)
        explored.append(node)
        new_reachable = node.adjacents
        for elem in new_reachable:
            adjacent = elem[1]
            dist = elem[0]
            if adjacent not in reachable:
                reachable.append(adjacent)

            if node.cost_to_reach + dist < adjacent.cost_to_reach:
                adjacent.previous_node = node
                adjacent.cost_to_reach = node.cost_to_reach + dist
    return None

#считывание графа в словарь
start_way, finish_way = input().split()
graph = {}
input_string = input().split()
while input_string:
    node1, node2, dist = input_string[0], input_string[1], float(
        input_string[2])
    if node2 not in graph.keys():
        graph[node2] = Node(node2, [])
    if node1 not in graph.keys():
        graph[node1] = Node(node1, [(dist, graph[node2])])
    else:
        graph[node1].add_adjacent(dist, graph[node2])
    try:
        input_string = input().split()
    except:
        break
graph[start_way].cost_to_reach = 0
print(A_star(graph[start_way], graph[finish_way]))
