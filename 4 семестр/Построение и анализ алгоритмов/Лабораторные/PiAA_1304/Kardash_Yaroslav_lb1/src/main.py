#для копирования матриц импортирован метод deepcopy
from copy import deepcopy

#класс, реализующий решение задачи
class Board:
    def __init__(self,size):
        self.size = size #размер поля
        self.square = self.size*self.size #площадь поля (используется как метрика)
        self.board = [[0 for _ in range(size)]for _ in range(size)] #матрица, где 0 - незанятые квадратами клетки
        self.result = [] #координаты и размеры вставленных кусков
        self.record = 50 #количество кусков (итоговое)
        self.simp_numb = [2,3,5,7,11,13,17,19,23,29,31,37] #простые числа до 40

    #метод решения задачи, вызываемый из main
    def solve(self):
        # если размер стороны четный, оптимальным решением будет разбиение поля на 4 квадрата со сторонами size/2
        if self.size %2 == 0:
            self.record = 4
            self.result.append([0,0,self.size//2])
            self.result.append([0,self.size//2,self.size//2])
            self.result.append([self.size//2,0,self.size//2])
            self.result.append([self.size//2,self.size//2,self.size//2])
            return
        #для составных чисел оптимальным заполнением будет оптимальное заполнение для квадрата со стороной наименьшего делителя, пропорционально увеличенное
        if self.size not in self.simp_numb:
            for elem in self.simp_numb:
                if self.size%elem == 0:
                    coef = self.size//elem
                    small_board = Board(elem)
                    break
            small_board.solve()
            self.record = small_board.record
            for i in range(self.record):
                self.result.append([])
                for j in range(3):
                    app_elem = small_board.result[i][j] * coef
                    self.result[i].append(app_elem)
            return
        #для простых чисел необходимо найти заполнение с помощью перебора
        self.__best_begin()
        counter = 3 #счетчик для количества вставленных квадратов
        board = deepcopy(self.board)
        free_square = self.square -  ((self.size+1)//2)**2 - 2*((self.size+1)//2 -1)**2
        result = deepcopy(self.result) #массив с форматным выводом
        self.__recursive_find(board,counter,free_square, result)
        self.result.sort()

    #рекурсивный поиск оптимальной вставки
    #принимает текущее заполнение поля и списка результатов, счетчик вставленных квадратов и свободную площадь
    def __recursive_find(self,board,counter,free_square,result):
        if counter>=self.record:
            return
        for i in range(self.size//2+1): #перебор строк
            for j in range(self.size//2+1): #перебор столбцов
                if board[i][j] != 0:
                    continue
                for k in range(self.size//2, 0, -1): #перебор возможных размеров квадратов (ограничен первоначальной вставкой)
                    if self.__is_insert(board,k,j,i):
                            new_board = self.__insert(board,k,j,i,counter+1)
                            new_result = deepcopy(result)
                            new_result.append([i,j,k])
                            if free_square-k*k >0:
                                if free_square - k*k == 3: #если оставшаяся площадь == 3 вариатива в расстановке кубиков нет
                                    new_board = self.__insert_last(new_board,counter,new_result)
                                    continue
                                self.__recursive_find(new_board,counter+1,free_square-k*k,new_result)
                                if (i!=0 and j !=0): #перебор вставок не в верхний левый угол - повторение уже проверенных расстановок с точностью до поворота
                                    return
                            else:
                                if counter < self.record: #сравнение с текущим рекордом
                                    self.board = deepcopy(new_board)
                                    self.record = counter+1
                                    self.result = deepcopy(new_result)
                                return
                            if k == 1:
                                return

    # Оптимизация. Лучшая начальная вставка
    def __best_begin(self):
        for i in range(self.size//2,self.size):
            for j in range(self.size//2,self.size):
                self.board[i][j] = 1
        self.result.append([self.size//2,self.size//2,(self.size+1)//2])

        for i in range(self.size//2):
            for j in range(self.size//2+1,self.size):
                self.board[i][j] = 2
        self.result.append([0,self.size//2+1,(self.size+1)//2-1])

        for i in range(self.size//2+1,self.size):
            for j in range (self.size//2):
                self.board[i][j] = 3
        self.result.append([self.size // 2 + 1,0, (self.size + 1) // 2 - 1])
        pass

    #проверка на возможность вставки кубика со стороной side на позицию x y
    def __is_insert(self,board,side,x,y):
        for i in range(y,y+side):
            for j in range(x,x+side):
                if board[i][j] !=0:
                    return False
        return True

    #вставка кубика размера side с номером numb на позицию x y
    def __insert(self,board,side,x,y,numb):
        new_board = deepcopy(board)
        for i in range(y,y+side):
            for j in range(x,x+side):
                new_board[i][j] = numb
        return new_board

    #вставка последних трех кубиков размером 1*1
    def __insert_last(self,board,counter,result):
        c = 1
        for i in range(self.size//2+1):
            for j in range(self.size//2+1):
                if board[i][j] == 0:
                    board[i][j] = counter+c
                    result.append([i,j,1])
                    c+=1
        return board

    # формат для вывода
    def __str__(self):
        if self.record == 50 or self.result == []:
            return ""
        result = str(self.record)+'\n'
        for i in range(self.record):
            result = result + str(self.result[i][0]+1)+ ' '+str(self.result[i][1]+1)+' ' +str(self.result[i][2])+'\n'
        return result


if __name__=="__main__":
    n = int(input())
    board = Board(n)
    board.solve()
    print(board)