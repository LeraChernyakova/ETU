import queue
import sys


def h(start_node, finish_node): # эвристическая функция
	return abs(ord(finish_node) - ord(start_node))

class Node: #хранения узлов был реализован
	def __init__(self, name, value_curnode_desnode, distance_startnode_curnode):
		self.name = name 
		self.value_curnode_desnode = value_curnode_desnode #значение оценивается от текущего состояния до целевого состояния
		self.distance_startnode_curnode = distance_startnode_curnode #расстояние от начального состояния до текущего состояния

	def f(self): #Метод f возвращает оценку на длину пути, проходящего через данный узел
		return self.distance_startnode_curnode + self.value_curnode_desnode(self.name)

	def __lt__(self, other): #Метод __lt__ был переопределен таким образом, чтобы при сравнении двух узлов меньше был тот, у которого меньше значение оценивающей функции
		first, second = self.f(), other.f()
		if first == second:#сравниваются значения эвристической функции
			return self.value_curnode_desnode(self.name) < self.value_curnode_desnode(other.name)
		return first < second


def reconstruct_path(came_from, current): #функция для реконструировать путь
	total_path = [current]
	while current in came_from.keys():
		current = came_from[current]
		total_path.insert(0, current)
	return total_path


def A_star(graph, start, goal, heuristic, gpaths): #Алгоритм А* 
#Первый параметр graph содержит представление графа
#start -название стартового узла
#goal -название конечного узла
#heuristic -эвристическую функцию 
#gpaths -словарь представляющий расстояние до узлов
	q = queue.PriorityQueue() #PriorityQueue очередь будет содержать экземпляры класса Node с переопределенным методом __lt__
	q.put(Node(start, heuristic, 0))
	came_from = {}

	while not q.empty(): #условием выхода из которого является пустота очереди
		current = q.get()
		if current.distance_startnode_curnode > gpaths[current.name]: #Если значение поля больше, значит, пока этот узел лежал в очереди, значение минимального пути до него уже уменьшилось, и элемент уже был обработан
			continue
		if current.name == goal: # Если название текущего узла совпадает с названием конечного узла, то возвращается путь до нее, восстановленный с помощью функции reconstruct_path, формирующей путь по словарю came_from и названию конечного узла
			return reconstruct_path(came_from, current.name)
		if current.name not in graph.keys(): #Если ни одно из вышеуказанных условий не выполнено, то перебираются все соседи текущей вершины
			continue
		for neighbor, distance in graph[current.name]:
			tentative_gscore = current.distance_startnode_curnode + distance
			if tentative_gscore < gpaths[neighbor]: #Если путь через текущую вершину к соседу оказался меньше предыдущего кратчайшего пути до соседней вершины, то расстояние до нее обновляется, и в очередь добавляется соответствующий элемент
				came_from[neighbor] = current.name
				gpaths[neighbor] = tentative_gscore
				q.put(Node(neighbor, heuristic, tentative_gscore))
	return None #Если после цикла while путь так и не был найден, возвращается значение None.


def main():
	for line in sys.stdin:
		source, destination, distance = line.split()
		new_node = (destination, float(distance))
		if destination not in gpaths.keys():
			gpaths[destination] = float("Inf")
		if source in graph.keys():
			graph[source].append(new_node)
		else:
			graph[source] = [new_node]

	heuristic = lambda x: h(x, end_node)
	path = A_star(graph, start, end_node, heuristic, gpaths)
	if path:
		print(''.join(path))

if __name__ == "__main__":
	start, end_node = input().split()
	gpaths = {}
	graph = {}
	gpaths[start] = 0
	main()