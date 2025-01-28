import datetime
from random import randint
inf=100000#бесконечное число
maximum_number=inf-10000#граница, все числа выше которой приравниваются к бесконечности.
class My_matrix:#класс матрицы весов.
    def __init__(self,matrix,rang:int,rows:list,columns:list):#иницализация: matrix - двумерный массив, хранящий таблицу вершин
                                                                             #rang - ранг этой матрицы
                                                                             #rows - числа от 1 до rang по горизонтали.Нужно для восстановление пути.
                                                                             #columns - числа от 1 до rang по вертикали. Нужно для восстановления пути..
        self.matrix=matrix
        self.rang=rang
        self.rows=rows
        self.columns=columns
    def get_rang(self):#Метод, ничего не принимает и возвращает ранг матрицы
        return self.rang
    def minimum_of_row(self,i:int):#метод, принимающий i и  возвращающий минимум в i строчке
        return min(self.matrix[i])
    def minimim_of_column(self,i:int):#метод, принимающий i и возвращающий минимум в i столбце.
        return min([x[i] for x in self.matrix])
    def reduction_row(self,i:int,subtrahend:int):#метод редукии по строке.В i строке из каждого элемента вычитается subrtrahend.Ничего не возвращает.
        self.matrix[i]=[x-subtrahend for x in self.matrix[i]]
    def reduction_column(self,i:int,subtrahend:int):#метод редукии по столбцу.В i столбце из каждого элемента вычитается subrtrahend.Ничего не возвращает.
        for j in range(self.rang):
            self.matrix[i][j]-=subtrahend
    def reduction_rows(self):#метод ничего не принимает и не возвращает.В каждой строке вычитает минимум этой строки.
        vector_rows=self.return_vector_rows()
        for i in range(self.rang):
            if vector_rows[i]<maximum_number:
                self.reduction_row(i,vector_rows[i])
    def reduction_columns(self):#метод ничего не принимает и не возвращает.В каждом столбце вычитает минимум этого столбца.
        vector_columns = self.return_vector_columns()
        for i in range(self.rang):
            if vector_columns[i]<maximum_number:
                self.reduction_column(i, vector_columns[i])
    def return_vector_rows(self):#функция ничего не принимает и возвращает вектор минимальных значений по строкам.
        return [self.minimum_of_row(x) for x in range(self.rang)]
    def return_vector_columns(self):#функция ничего не принимает и возвращает вектор минимальных значений по столбцам.
        return [self.minimim_of_column(x) for x in range(self.rang)]
    def sum_vector_rows(self):#вычисляет сумму по минимумам строк.Метод ничего не принимает.
        return sum(self.return_vector_rows())
    def sum_vector_columns(self):#вычисляет сумму по минимумам столбцов.Метод ничего не принимает
        return sum(self.return_vector_rows())
    def estimate_null_square(self):#метод, который ничего не принимает и возвращает нулевую клетку с максимальной оценкой.
        null_elements=[]
        for i in range(self.rang):
            for j in range(self.rang):
                if not self.matrix[i][j]:
                    save_element=self.matrix[i][j]
                    self.set_inf_of_number(i,j)
                    null_elements.append((self.minimum_of_row(i)+self.minimim_of_column(j),i,j))
                    self.matrix[i][j]=save_element
        return max(null_elements,key=lambda x:x[0])
    def delete_column_number(self,i):#метод, который удаляет в column i номер.Принимает i и возвращает новый вектор.
        vector=self.columns.copy()
        vector.pop(i)
        return vector
    def delete_row_number(self,i):#метод, который удаляет в row i номер. Принимает i и возвращает новый вектор.
        vector=self.rows.copy()
        vector.pop(i)
        return vector
    def set_inf_of_number(self,i:int,j:int):#метод, который устанавливает клетке i строки и j столбца inf. Принимает i и j и ничего не возвращает.
        self.matrix[i][j]=inf
    def return_edge(self,i,j):#метод, который возвращает ребро, состощее из i и j вершины.Вовзращает это ребро и принимает i и j.
        return (self.rows[i],self.columns[j])
    def reduction_matrix(self,i:int,j:int):#метод, который удаляет i строку и j столбец.Возвращает получившуюся матрицу и принимает i и j .
        self.set_inf_of_number(j,i)
        return [[col[1] for col in enumerate(row[1]) if col[0]!=j] for row in enumerate(self.matrix) if row[0]!=i]
    def copy(self):#метод, который копирует исходную матрицу. Ничего не принимает и возвращает копию Mymatrix.
        return My_matrix(self.matrix.copy(),self.rang,self.rows.copy(),self.columns.copy())
    def is_deadlock(self):#метод, который проверяет, является ли данная матрица тупиковой(нельзя пойти в новую вершину). Ничего не принимает и возвращает True - если тупик, иначе False.
        for i in range(self.rang):
            if self.minimum_of_row(i)<maximum_number:
                return False
        return True
class Node_tree:#класс дерева метода ветвей и границ.
    def __init__(self,matrix:My_matrix,parent,edge=None):#инициализация: matrix - класс матрицы Mymatrx.
                                                                        #lower_estimate - оценка, необходимая очереди с приоритетом.
        self.matrix=matrix                                              #parent - родитель исходного узла
        self.lower_estimate=0                                           #edge - ребро,включенное на данном уровне.Если ребро не включено,edge=None.
        self.parent=parent
        self.edge=edge
    def set_lower_estimate(self,is_root:bool,choose_element:int=None):#метод, который устанавливает исходную оценку.Принимает is_root- явлеятся ли узел корнем и choose_element - элемент, который при не включении ребра принимает участие в формировании оценки.Ничего не возвращает
        if choose_element:
            self.lower_estimate = self.parent.get_lower_estimate()+choose_element
        else:
            if is_root:
                self.lower_estimate=self.matrix.sum_vector_rows() + self.matrix.sum_vector_columns()
            else:
                self.lower_estimate = self.parent.get_lower_estimate() + self.matrix.sum_vector_rows() + self.matrix.sum_vector_columns()
    def get_lower_estimate(self):#метод, который ничего не принимает и возвращает оценку.
        return self.lower_estimate
class Priory_queue:#Класс очереди с приоритетом, необходимый для выполнения поставленной задачи
    def __init__(self):
        self.arr=[]
        self.len=0
    def add(self,node:Node_tree):#добавляет элемент в очередь. node- добавляемый элемент. Ничего не возвращает
        len_arr=self.get_len()
        i=0
        while i<len_arr and node.get_lower_estimate()>self.arr[i].get_lower_estimate():
            i+=1
        if i==len_arr:
            self.arr.append(node)
        else:
            self.arr.insert(i,node)
        self.len+=1
    def remove(self)->Node_tree:#Удаление самого приоритетного элемента. Ничего не принимает и возвращает удаляемый элемент.
        self.len-=1
        return self.arr.pop(0)
    def get_len(self):#Возвращает длину очереди.
        return self.len
class Algoritm:#класс-алгоритм.
    def __init__(self,root_node:Node_tree):#иницализация:root_node - корень дерева, priory_queue - очередь с приоритетом.
        self.root_node=root_node
        self.priory_queue=Priory_queue()
    def get_edges(self,vertex):#метод, которая получает ребра, по которым был построен итоговый путь.Возвращает список ребер и принимает vertex - лист исходного дерева.
        res=[(vertex.matrix.rows[0],vertex.matrix.columns[0])]
        while vertex.parent:
            if vertex.edge:
                res.append(vertex.edge)
            vertex=vertex.parent
        res.reverse()
        return res
    def get_near_answer(self,vertex):#метод, который возвращает список вершин и вес итогового пути.Принимает vertex- лист дерева.
        arr=self.get_edges(vertex)
        answer=[arr[0][0]]
        vertex=arr[0][1]
        answer.append(vertex)
        n=0
        while answer[0]!=vertex:
            for i in arr:
                if i[0]==vertex:
                    n+=1
                    vertex=i[1]
                    answer.append(vertex)
                    break
        weight=0
        for i in arr:
            weight+=self.root_node.matrix.matrix[i[0]-1][i[1]-1]
        return answer,weight
    def get_answer(self):#метод, который представляет исходный алгоритм и возвращает результат - список вершин, в том порядке, по которому по ним прошел коммивояжер и вес пути.
        if self.root_node.matrix.get_rang()==2:
            return ([self.root_node.matrix.rows[0],self.root_node.matrix.rows[1]],self.root_node.matrix.matrix[0][1]+self.root_node.matrix.matrix[1][0])
        save_matrix=self.root_node.matrix.matrix.copy()
        self.root_node.matrix.reduction_rows()
        self.root_node.matrix.reduction_columns()
        self.root_node.set_lower_estimate(True)
        self.priory_queue.add(self.root_node)
        while True:
            leaf=self.priory_queue.remove()
            if leaf.matrix.is_deadlock():
                continue
            if leaf.matrix.get_rang()==1:
                self.root_node.matrix.matrix = save_matrix
                answer,weight=self.get_near_answer(leaf)
                if len(answer)==self.root_node.matrix.get_rang()+1:
                    return answer,weight
                else:
                    continue
            leaf.matrix.reduction_rows()
            leaf.matrix.reduction_columns()
            remove_element=leaf.matrix.estimate_null_square()
            new_matrix=My_matrix(leaf.matrix.reduction_matrix(remove_element[1],remove_element[2]),leaf.matrix.get_rang()-1,leaf.matrix.delete_row_number(remove_element[1]),leaf.matrix.delete_column_number(remove_element[2]))
            left_vertex=Node_tree(new_matrix,leaf,leaf.matrix.return_edge(remove_element[1],remove_element[2]))
            left_vertex.set_lower_estimate(False)
            right_vertex=Node_tree(leaf.matrix.copy(),leaf)
            right_vertex.set_lower_estimate(False,right_vertex.matrix.matrix[remove_element[1]][remove_element[2]])
            right_vertex.matrix.set_inf_of_number(remove_element[1],remove_element[2])
            self.priory_queue.add(right_vertex)
            self.priory_queue.add(left_vertex)
def main():
    f=open("test4.txt",'r')
    arr=f.readlines()
    matrix=[]
    rang=0
    for i in arr:
        rang+=1
        vector=i.replace('-',str(inf)).split()
        vector[rang-1]=inf
        vector=list(map(int,vector))
        matrix.append(vector)
    time_start=datetime.datetime.now()
    root_Node=Node_tree(My_matrix(matrix,rang,[x for x in range(1,rang+1)],[x for x in range(1,rang+1)]),None)
    algoritm=Algoritm(root_Node)
    print(algoritm.get_answer(),datetime.datetime.now()-time_start)
if __name__=='__main__':
    main()
