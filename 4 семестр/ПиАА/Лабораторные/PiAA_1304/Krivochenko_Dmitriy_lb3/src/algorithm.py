import copy
import queue
import sys
import os

MAX_INT = sys.maxsize
class Node:
    def __init__(self):
        self.path = ""
        self.map = None
        self.cost = None
        self.number = None
        self.amount_of_nodes_visited = None
        self.map_size = None
    def __str__(self):
        result = ""
        for i in range(self.map_size):
            result += str(self.map[i]) + "\n"
        return result
    def __lt__(self, other):
        if (self.cost < other.cost):
            return True
        return False

    def fill_from_file(self, filepath):
        with open(filepath) as textFile:
            self.map = [list(map(int, line.split())) for line in textFile]
        self.map_size = len(self.map[0])
        for i in range(self.map_size):
            for j in range(self.map_size):
                if self.map[i][j] == -1:
                    self.map[i][j] = MAX_INT

def init_root(filepath):
    node = Node()
    node.path = "["
    node.cost = 0
    node.number = 0
    node.amount_of_nodes_visited = 0
    node.fill_from_file(filepath)
    return node


def new_node(parentMatrix, path, amount_of_nodes_visited, src_number,
            dest_number):
    node = Node()
    node.path = path
    if amount_of_nodes_visited != 0:
        node.path += f"{str(src_number + 1)}, "
    node.map = copy.deepcopy(parentMatrix)
    node.map_size = len(node.map[0])
    k = 0
    while (amount_of_nodes_visited != 0 and k < node.map_size):
        node.map[src_number][k] = MAX_INT
        node.map[k][dest_number] = MAX_INT
        k += 1
    node.map[dest_number][0] = MAX_INT
    node.amount_of_nodes_visited = amount_of_nodes_visited
    node.number = dest_number
    return node


def reduce_row_vise(node):
    node_map_copy = node.map
    node_map_map_size = node.map_size
    min_reduction_row = [MAX_INT] * node_map_map_size
    for i in range(node_map_map_size):
        for j in range(node_map_map_size):
            if node_map_copy[i][j] < min_reduction_row[i]:
                min_reduction_row[i] = node_map_copy[i][j]
    for i in range(node_map_map_size):
        for j in range(node_map_map_size):
            if (node_map_copy[i][j] != MAX_INT and min_reduction_row[i] != MAX_INT):
                node_map_copy[i][j] -= min_reduction_row[i]
    return min_reduction_row


def reduce_col_vise(node):
    node_map_copy = node.map
    node_map_map_size = node.map_size
    min_reduction_col = [MAX_INT] * node_map_map_size
    for i in range(node.map_size):
        for j in range(node.map_size):
            if node_map_copy[i][j] < min_reduction_col[j]:
                min_reduction_col[j] = node_map_copy[i][j]
    for i in range(node_map_map_size):
        for j in range(node_map_map_size):
            if (node_map_copy[i][j] != MAX_INT and min_reduction_col[j] != MAX_INT):
                node_map_copy[i][j] -= min_reduction_col[j]
    return min_reduction_col


def calculate_cost(node):
    cost = 0
    row = reduce_row_vise(node)
    col = reduce_col_vise(node)
    for i in range(node.map_size):
        cost += row[i] if row[i] != MAX_INT else 0
        cost += col[i] if col[i] != MAX_INT else 0
    return cost


def solve(filepath):
    pq = queue.PriorityQueue()

    root = init_root(filepath)
    root.cost = calculate_cost(root)
    pq.put((root.cost, root))

    while (not(pq.empty())):
        minNode = pq.get()[1]
        current_number = minNode.number
        if minNode.amount_of_nodes_visited == minNode.map_size - 1:
            minNode.path += f"{str(current_number + 1)}, 1]"
            return minNode.path, minNode.cost

        for j in range(minNode.map_size):
            child = new_node(minNode.map, minNode.path, minNode.amount_of_nodes_visited + 1, current_number, j)
            child.cost = minNode.cost + minNode.map[current_number][j] + calculate_cost(child)
            pq.put((child.cost, child))
