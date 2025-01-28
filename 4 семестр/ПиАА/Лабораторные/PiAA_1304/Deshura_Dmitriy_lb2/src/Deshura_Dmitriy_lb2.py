# Функция удаления вершины point_name из графа graph. Возвращает 
#  изменённую копию графа
# Считаю, что было бы лучше во время обхода графа удалять не пройденные 
#  рёбра, а сразу пройденные вершины.
def delete_point (graph, point_name):
    graph = graph.copy()
    if point_name in graph.keys():
        del graph[point_name]
    for key in graph.keys():
        if point_name in graph[key].keys():
            del graph[key][point_name]
    return graph


# Функция удаления ребра (start_rib_point, end_rib_point) из 
#  графа graph. Возвращает изменённую копию графа.
def delete_rib (graph, start_rib_point, end_rib_point):
    graph = graph.copy()
    del graph[start_rib_point][end_rib_point]
    return graph


# Функция обхода графа graph в глубину от точки start_point к 
#  точке stop_point и строит путь way (если мы будем обходить граф в 
#  глубину и записывать посещённые точки на пути к stop_point, то на 
#  выходе получим путь от входной точки к конечной). Добавим лишь то,
#  что на каждом шаге будем выбирать ребро с наименьшим весом из
#  доступных и удалять рёбра по которым мы прошли.
def depth_first_search_solution (graph, current_point, stop_point, way=""):
    way += chr(current_point)
    if current_point != stop_point:
        if current_point in graph.keys():
            steps = sorted(graph[current_point].items(), key=lambda elem : elem[1])
            buf = None
            i = 0
            while not buf and i < len(steps):
                buf = depth_first_search_solution(delete_rib(graph, current_point, steps[i][0]), steps[i][0], stop_point, way)
                i += 1
            return buf
        else:
            return None
    else:
        return way


class a_star_point:
    # Класс, представляющий точку графа в формате, удобном для
    #  алгоритма А*. Имеет следующие поля:
        # name      - Имя точки (ASCII код символа)
        # weight    - Вес точки
        # parent    - Из какой точки доступен кратчайший путь
        # distance  - Расстояние до заданной точки

    def __init__(self, name=None, weight=None, parent=None, distance=None):
        self.name = name            
        self.weight = weight        
        self.parent = parent        
        self.distance = distance


# Функция восстановления пути для алгоритма А*. Принимает список
#  просмотренных вершин и вершину, до которой необходимо восстановить
#  путь.
# Возвращает сам путь.
def restore_path (checked_points, finish_point):
    way = chr(finish_point)
    iter_point = finish_point
    while checked_points[iter_point].parent:
        iter_point = checked_points[iter_point].parent
        way = chr(iter_point) + way

    return way


# Функция нахождения кратчайшего пути при помощи алгоритма А*. На вход
#  принимает граф graph, текущей рассматриваемую точку current_point,
#  конечную точку stop_point, набор рассматриваемых вершин
#  selected_points и набор просмотренных вершин checked_points. Для
#  старта необходимо передать в качестве selected_points словарь из
#  стартовой вершины, представленной в формате объекта a_star_point.
# Вызывает функцию restore_path для восстановлния пути по набору
#  рассмотренных вершин и возвращает сам путь.
def a_star_solution (graph, current_point, stop_point, selected_points={}, checked_points={}):
    checked_points[current_point] = selected_points[current_point]
    del selected_points[current_point]

    if current_point == stop_point:
        way = restore_path(checked_points, stop_point)
        return way

    if current_point in graph.keys():
        for iter_point in graph[current_point].keys():
            new_obj_weight = checked_points[current_point].weight + graph[current_point][iter_point]
            new_obj_distance = stop_point - iter_point

            iter_point_obj = a_star_point(name=iter_point, weight=new_obj_weight, parent=current_point, distance=new_obj_distance)
            old_iter_point_obj = None if iter_point not in selected_points.keys() else selected_points[iter_point]
            
            if old_iter_point_obj and iter_point_obj.weight < old_iter_point_obj.weight:
                selected_points[iter_point] = iter_point_obj
            
            if iter_point in checked_points.keys() and iter_point_obj.weight < checked_points[iter_point].weight:
                    selected_points[iter_point] = iter_point_obj

            if not old_iter_point_obj and iter_point not in checked_points.keys():
                    selected_points[iter_point] = iter_point_obj

    min_selected_point = min(selected_points.values(), key=lambda elem: elem.weight + elem.distance)
    for iter_point in selected_points.values():
        if min_selected_point.weight + min_selected_point.distance == iter_point.weight + iter_point.distance and iter_point.distance < min_selected_point.distance:
            min_selected_point = iter_point

    return a_star_solution(graph, min_selected_point.name, stop_point, selected_points, checked_points)


# Функция считывания графа. Производим считывание, пока можем, получив
#  исключение, - завершаем считывание. Граф представляет собой словарь
#  из вершин, которые в свою очередь представляют словарь исходящих
#  рёбер и их весов.
# Возвращает считанный граф.
def read_graph ():
    graph = {}
    while True:
        try:
            data = input()
            start_edge_point, end_edge_point, weight = data.split()
            start_edge_point, end_edge_point = ord(start_edge_point), ord(end_edge_point)
            weight = float(weight)
            if not start_edge_point in graph.keys():
                graph[start_edge_point] = {}

            graph[start_edge_point][end_edge_point] = weight
        except:
            break
    return graph


if __name__ == "__main__":
    start_point, finish_point = map(ord, input().split())
    graph = read_graph()

    # print(depth_first_search_solution(graph, start_point, finish_point))

    # start_point_obj = a_star_point(start_point, 0, None, start_point - start_point)
    # print(a_star_solution(graph, start_point, finish_point, {start_point: start_point_obj}))
