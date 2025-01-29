#include <iostream>
#include <queue>
#include <vector>

//Структура, описывающая квадрат
//Содержит три поля типа int - размер стороны, координаты левого верхнего угла
struct Square{
    int size;
    int x_coord;
    int y_coord;
    
    //Конструктор структуры
    Square(int size, int x, int y):size(size), x_coord(x), y_coord(y){}
    //Перегрузка оператора вывода в поток
    friend std::ostream& operator<<(std::ostream& os, const Square& square){
        os << square.x_coord <<' '<< square.y_coord<< ' ' << square.size << std::endl;
        return os;
    }
};

//Класс, описывающий собираемую из квадратов столешниц
/*Поля класса - представление доски в виде матрицы, длина стороны стола, 
количество квадратов и вектор размещенных квадратов*/
class Desk{
private:
    std::vector<std::vector<int>> table;
    int len_side;
    int count_squares;
    std::vector<Square*> list_square;
public:
    //Констурктор от длины стороны стола
    Desk(int n):len_side(n){
        this->table = std::vector<std::vector<int>>();
        for(auto i = 0; i < len_side; i++){
            this->table.push_back(std::vector<int>(n));
        }
        this->list_square = std::vector<Square*>();
        this->count_squares = 0;
        //Проверка делимости для оптимизации алгоритма
        if(n % 2 != 0 && n % 3 != 0){
            this->set_default();
        }
    }
    //Констурктор копирования
    //Принимает в качестве аргумента объект класса по ссылке
    Desk(const Desk& obj):len_side(obj.len_side), count_squares(obj.count_squares){
        this->table = std::vector<std::vector<int>>();
        for(auto i = 0; i < len_side;i++){
            this->table.push_back(std::vector<int>(this->len_side));
        }
        for(auto i = 0; i < len_side; i++){
            for(auto j = 0; j < len_side; j++){
                this->table[i][j] = obj.table[i][j];
            }
        }
        this->list_square = std::vector<Square*>(obj.list_square);
    }
    //Оператор присваивания с копированием
    Desk& operator=(const Desk& obj){
        if(this != &obj){
            this->table = std::vector<std::vector<int>>();
            for(auto i = 0; i < len_side;i++){
                this->table.push_back(std::vector<int>(this->len_side));
            }
            for(auto i = 0; i < len_side; i++){
                for(auto j = 0; j < len_side; j++){
                    this->table[i][j] = obj.table[i][j];
                }
            }
            len_side = obj.len_side;
            count_squares = obj.count_squares;
            list_square = std::vector<Square*>(obj.list_square);
        }
        return *this;
    }
    //Получение значение приватного поля класса len_side
    int get_length_side() const{
        return len_side;
    }
    //Получение значение приватного поля класса list_square
    std::vector<Square*> get_square_list() const{
        return list_square;
    }
    //Получение значение приватного поля класса count_squares
    int get_count_square() const{
        return count_squares;
    }
    //Установка трех квадратов по умолчанию, если сторона не кратна 2 и 3
    //Примененная оптимизация
    //В левый верхний угол устанавливается больший квадрат
    //Два оставшихся ставятся как смежные с ним справа и снизу
    void set_default(){
        this->add_square((len_side+1)/2, 0, 0);
        this->add_square((len_side-1)/2, 0, (len_side+1)/2);
        this->add_square((len_side-1)/2, (len_side+1)/2, 0);
    }
    //Размещение квадрата на доске, заполнением единицами занятые клетки матрицы
    //Принимает на вход размер квадрата и координаты его левого верхнего угла
    void add_square(int size, int x, int y){
        Square* square = new Square(size, x, y);
        for(auto i = x; i < x + size; i++){
            for(auto j = y; j < y + size; j++){
                this->table[i][j] = 1;
            }
        }
        this->list_square.push_back(square);
        this->count_squares++;
    }
    //Проверка на заполненность стола квадратами
    bool is_full(){
		for (int i = 0; i < len_side; i++){
            for (int j = 0; j < len_side; j++){
                if (table[i][j] == 0){
                    return false;
                }
            }
        }		
		return true;
	}
    //Проверка на возможность разместить квадрат
    //Принимает на вход координаты левого верхнего угла квадрата и его размер
    bool can_add(int x, int y, int size){
        if(y+size > this->len_side || x+size > this->len_side){
            return false;
        }
        for(auto i = x; i < x+size; i++){
            for(auto j = y; j < y+size; j++){
                if(this->table[i][j] != 0){
                    return false;
                }
            }
        }
        return true;
    }
    //Получение координаты самой верхней левой свободной клетки
    //Для оптимизации в такие координаты ставится новый квадрат
    std::pair<int, int> empty_cell(){
        for(auto i = 0; i < this->len_side; i++){
            for(auto j = 0; j < this->len_side; j++){
                if(this->table[i][j] == 0){
                    return std::pair<int, int>{i, j};
                }
            }
        }
        return std::pair<int, int>{-1, -1};
    }

};
//Реализация алгоритма поиска с возвратом на основе очереди
//Принимает объект типа класса Desk
//Возвращает минимальное заполнение матрицы квадратами
Desk backtracking(Desk desk){
    std::queue<Desk> queue = std::queue<Desk>();
    queue.push(desk);
    while(!queue.front().is_full()){
        Desk desk_copy = queue.front();
        std::pair<int, int> empty_cell = desk_copy.empty_cell();    
        for(int i = desk.get_length_side() - 1; i > 0 ; i--){
            Desk current = desk_copy;
            if(desk_copy.can_add(empty_cell.first, empty_cell.second, i)){
                current.add_square(i, empty_cell.first, empty_cell.second);
                queue.push(current);
            }
        }
        queue.pop();
    }
    return queue.front();
}
//Функция считывания размера столешницы
//Возвращает считанный размер соответственно
int read_size(){
    int size;
    std::cin>>size;
    return size;
}
//Функция вывода ответа на экран в сооветсвии с требованием задания 
void print_result(Desk printing_answer){
    std::cout << printing_answer.get_count_square() << std::endl;
    for(auto elem:printing_answer.get_square_list()){
        std::cout << *elem;
    }
}
//Функция, запускающая решение поставленной задачи
void solution(){
    int table_size = read_size();
    Desk desk = Desk(table_size);
    Desk answer = backtracking(desk);
    print_result(answer);
}

int main(){
    solution();
    return 0;
}
