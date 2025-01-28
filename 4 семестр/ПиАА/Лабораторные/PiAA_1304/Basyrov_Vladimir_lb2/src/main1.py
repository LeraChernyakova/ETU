class Greedy_algoritm:
    def __init__(self):
        self.dict_graph, self.alpa, self.path, self.vertex_source, self.vertex_receiver = self.inits()
    def inits(self):#Функция обрабатывает ввод и возвращает:
                                        # dict_graph- словарь, где ключ-вершина, а значение список пар элементов вида
                                        #                 (смежная с вершиной-ключем вершина;вес ребра,соединяющий 2 вершины)
                                        # alpa - словарь вершин ,который каждой вершине сопоставляет минимальную метку
                                        # path - словарь, где ключ - вершина,куда пришли, а значение - вершина, откуда пришли.
                                        # vertex_source - вершина-источник
                                        # vertex_receiver - вершина-приемник
        vertex_source, vertex_receiver = map(str, input().split())
        alpa,path,dict_graph={},{},{}
        while True:
            try:
                for el in input().split('\n'):
                    start, finish, weight = el.split()
                    if not alpa.get(start):
                        alpa.update({start: 100000})
                        path.update({start: ''})
                    if not alpa.get(finish):
                        alpa.update({finish: 100000})
                        path.update({finish: ''})
                    weight = float(weight)
                    if dict_graph.get(start):
                        dict_graph[start].append((finish, weight))
                    else:
                        dict_graph.update({start: [(finish, weight)]})
            except:
                break
        return (dict_graph,alpa,path,vertex_source,vertex_receiver)
    def prepare_to_choose(self):#Функция сортирует словарь для последующего применени жадного алгоритма.Ничего не возвращат и не принимает.
        for i in self.dict_graph:
            self.dict_graph[i].sort(key=lambda x: x[1])
    def solve(self):#Функция, которая возвращает результат работы алгоритма. Ничего не принимает и не возвращает.
        self.prepare_to_choose()
        start=self.vertex_source
        finish=self.vertex_receiver
        res=self.vertex_source
        while finish != self.main_finish:
            if self.dict_graph.get(finish) and self.dict_graph[finish] != []:
                self.path[self.dict_graph[finish][0][0]] = finish
                finish = self.dict_graph[finish].pop(0)[0]
                res += finish
            else:
                res = res[:len(res) - 1]
                finish = self.path[finish]
        return res
def main():
    algoritm=Greedy_algorithm()
    print(algoritm.solve())
if __name__=='__main__':
    main()
