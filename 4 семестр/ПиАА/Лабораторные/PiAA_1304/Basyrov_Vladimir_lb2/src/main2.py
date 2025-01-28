class Priory_queue:#Класс очереди с приоритетом, необходимый для выполнения поставленной задачи
    def __init__(self,alpa):# alpa- словарь вершин ,который каждой вершине сопоставляет минимальную метку
        self.arr=[]
        self.alpa=alpa
        self.len=0
    def add(self,node,evristic):#добавляет элемент в очередь. node- добавляемый элемент, evristic-эвристика данного элемента. Ничего не возвращает
        len_arr=self.get_len()
        i=0
        while i<len_arr and self.alpa[node]+evristic>self.alpa[self.arr[i][0]]+self.arr[i][1]:
            i+=1
        if i==len_arr:
            self.arr.append((node,evristic))
        else:
            self.arr.insert(i,(node,evristic))
        self.len+=1
    def remove(self):#Удаление самого приоритетного элемента. Ничего не принимает и возвращает удаляемый элемент.
        self.len-=1
        return self.arr.pop(0)
    def get_len(self):#Возвращает длину очереди.
        return self.len
class A_star:
    def __init__(self):#Инициализация
        self.dict_graph,self.alpa,self.is_viewed,self.path,self.vertex_source,self.vertex_receiver=self.inits()
        self.queue=[]
    def inits(self):#Функция обрабатывает ввод и возвращает:
                                        # dict_graph- словарь, где ключ-вершина, а значение список пар элементов вида
                                        #                 (смежная с вершиной-ключем вершина;вес ребра,соединяющий 2 вершины)
                                        # alpa - словарь вершин ,который каждой вершине сопоставляет минимальную метку
                                        # is_viewed - словаь, показывающий, просмотрена ли данная вершина
                                        # path - словарь, где ключ - вершина,куда пришли, а значение - верщина, откуда пришли.
                                        # vertex_source- вершина-источник
                                        # vertex_receiver - вершина-приемник
        vertex_source, vertex_receiver = map(str, input().split())
        is_viewed,alpa,path,dict_graph={},{},{},{}
        while True:
            try:
                for el in input().split('\n'):
                    start, finish, weight = el.split()
                    if not is_viewed.get(start):
                        alpa.update({start: 100000})
                        is_viewed.update({start: False})
                        path.update({start: ''})
                    if not is_viewed.get(finish):
                        alpa.update({finish: 100000})
                        is_viewed.update({finish: False})
                        path.update({finish: ''})
                    weight = float(weight)
                    if dict_graph.get(start):
                        dict_graph[start].append((finish, weight))
                    else:
                        dict_graph.update({start: [(finish, weight)]})
            except:
                break
        return (dict_graph,alpa,is_viewed,path,vertex_source,vertex_receiver)
    def heuristic(self,node):#Функция,принимающая вершину и возвразающая ее эвристическую оценку.
        return ord(self.vertex_receiver)-ord(node)
    def prepare_to_choose(self):#Функция, инициализирующая начальные данные. Ничего не принимает и не возвращает
        for i in self.dict_graph:
            self.dict_graph[i].sort(key=lambda x: x[1])
        self.alpa[self.vertex_source]=0
        self.queue=Priory_queue(self.alpa)
        self.queue.add(self.vertex_source,self.heuristic(self.vertex_source))
    def restore_answer(self):#Функция, которая восстанавливает ответ. Ничего не принимает и возвращает непосредственно ответ на задачу.
        res = ''
        while self.vertex_receiver != self.vertex_source:
            res += self.vertex_receiver
            self.vertex_receiver = self.path[self.vertex_receiver]
        return self.vertex_source+res[::-1]
    def solving(self):#Основная функция поиска ответа. Ничего не принимает и возвращает ответ
        self.prepare_to_choose()
        while self.queue.get_len():
            start_node,heuristic_for_start=self.queue.remove()
            if self.is_viewed[start_node] or not self.dict_graph.get(start_node) or heuristic_for_start+self.alpa[start_node]>=self.alpa[self.vertex_receiver]:
                continue
            self.is_viewed[start_node]=True
            for finish_node,edge in self.dict_graph[start_node]:
                heuristic = self.heuristic(finish_node)
                if  self.alpa[start_node]+edge<self.alpa[finish_node]:
                    self.alpa[finish_node]=self.alpa[start_node]+edge
                    self.path[finish_node]=start_node
                if not self.is_viewed[finish_node]:
                    self.queue.add(finish_node,heuristic)
        return self.restore_answer()
def main():
    algoritm=A_star()
    print(algoritm.solving())
if __name__ == "__main__":
    main()
