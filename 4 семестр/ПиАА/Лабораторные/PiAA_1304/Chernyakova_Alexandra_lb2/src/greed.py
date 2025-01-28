class Way:  # класс пути, хранит стоимость пути до вершины и саму вершину
    def __init__(self, weight, vertex):
        self.weight = weight 
        self.vertex = vertex 

    def get_weight(self): 
        return self.weight

    def get_vertex(self): 
        return self.vertex


def inputs():  # функция считывания входных параметров
    graph = {}  # словарь графа вида vertex : [Way(), Way()...]
    while True:
        try:
            first_vert, second_vert, weight = input().split()  # считывание из какой вершины путь, в какую вершину и стоимость пути
            if not first_vert: 
                return graph
            if graph.get(first_vert):  # если в словаре уже есть такой ключ
                ways = graph.get(first_vert)
                ways.append(Way(float(weight), second_vert))
                graph[first_vert] = ways  
            else:  # если в словаре нет такого ключа
                graph[first_vert] = [Way(float(weight), second_vert)] 
        except (ValueError, EOFError):
            return graph 


def is_min_vertex(vertex, graph):  # функция поиска самого дешевого пути для вершины vertex в графе graph
    ways = graph.get(vertex) 
    if ways is None or ways == []:  # если путей вообще не было или были тупиковые, то возвращается сама вершина vertex
        return vertex
    min_way = ways[0].get_weight()  
    min_vert = ways[0].get_vertex() 
    for way in ways:  # рассмотрение всех путей из вершины vertex и поиск самого дешевого
        if way.get_weight() < min_way:
            min_way = way.get_weight()  
            min_vert = way.get_vertex() 
    return min_vert  


def main():
    first_vertex, last_vertex = input().split()  # считывание начальной и конечной вершин
    graph = inputs() 
    vert = first_vertex  # текущая вершина
    result = [first_vertex] 
    while vert != last_vertex:  
        if vert == is_min_vertex(vert, graph):  # если  пути из данной вершины в графе нет
            result.pop() 
            ways = graph.get(result[-1])
            for i in range(len(ways)): 
                if ways[i].get_vertex() == vert: 
                    ways.pop(i) 
                    break
            graph[result[-1]] = ways
            vert = result[-1] 
        else:
            vert = is_min_vertex(vert, graph) 
            result.append(vert)  
    print("".join(result))  


if __name__ == "__main__":
    main()