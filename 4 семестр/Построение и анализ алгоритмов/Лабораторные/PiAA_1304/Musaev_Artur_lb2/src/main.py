#include <iostream>
start, finish = input().split()
graph = {}
input_string = input().split()
#считывание графа в словарь
while input_string:
    node1, node2, dist = input_string[0], input_string[1], float(input_string[2])
    if node1 not in graph.keys():
        graph[node1] = [(dist, node2)]
    else:
        graph[node1].append((dist, node2))
    try:
        input_string = input().split()
    except:
        break
#сортировка ребер по возрастанию
for key in graph.keys():
    graph[key].sort()
#жадный поиск пути
cur = way = start
while cur != finish:
    for elem in graph[cur]:
        if elem[1] == finish or elem[1] in graph.keys() and elem[1] not in way:
            cur = elem[1]
            way += cur
            break
print(way)