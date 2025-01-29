
#include <iostream>
#include<vector>
#include "math.h"
#include <algorithm>
using namespace std;

//структура для хранения ответа в формате (позиция x, позиция y, длина стараны квадрата len)
struct Square{
    int x;
    int y;
    int len;
public:
    Square(int x,int y,int len)
    {
        this->x=x;
        this->y=y;
        this->len=len;
    }
};
//структура для хранения столешницы
// столешница - двумерный массив
// color - количество уже добавленных квадратов
// S - незаполненая площадь столешницы
struct Matrix{
    vector<vector<int>> x;
    int color;
    int S;
public:
    Matrix(vector<vector<int>> x,int n)
    {
        this->x=x;
        this->color=0;
        this->S=n*n;
    }
};

//глобальные переменные
// n - сторона квадрата, которую вводит пользователь
// max_len - максимальная длина стороны квадрата
// record - переменная для фиксация лучшего решения
static int n;
static int max_len;
static int record;

//функция поиска позиции для вставки
pair<int, int> startPosition(vector<vector<int>> x){
    for(int i=n/2;i<n;i++){
        for(int j=n/2;j<n;j++){
            if(x[i][j]==0){
                return {i,j};
            }
        }
    }
    return{-1,-1};
}
//функция вставки квадрата на переданную позицию
Matrix addSquare(Matrix matr,int start_x,int start_y,int len){
    for(int i=start_x;i<start_x+len;i++){
        for(int j=start_y;j<start_y+len;j++){
            matr.x[i][j]=matr.color+1;
        }
    }
    matr.color++;
    matr.S-=len*len;

    return matr;
}
// функция проверки на корректность
bool isCorrect(Matrix matr,int start_x,int start_y,int len){
    if(matr.x[start_x][start_y]!=0 )
        return false;
    if(start_x+len<=n && start_y+len<=n){
        for(int i=start_x;i<start_x+len;i++){
            if(matr.x[i][start_y]!=0 || matr.x[i][start_y+len-1]!=0)
                return false;
        }
        for(int j=start_y;j<start_y+len;j++){
            if(matr.x[start_x][j]!=0 || matr.x[start_x+len-1][j]!=0)
                return false;
        }
    }else
        return false;

    return true;

}
//дополнительная функция для вывода матрицы
void print_sq(vector<vector<int>> arr){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<arr[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}

// функция реализующая метод ветвей и границ
//если вся плита запонена и ответ оптимальнее ранее найденого, то фиксируется новое решение
//если ответ не найден и текущее решение меньше оптимального, то рассматриваются все дополнения текущего решения
void bandb(Matrix matr,vector<vector<int>>&P){

    if(matr.S == 0 && matr.color<record){//решение
        record=matr.color;
        P=matr.x;
        return;
    }else{
        if(matr.color<record){//расширение текущего решения
            for(int len=max_len;len>=1;len--){
                pair<int,int>pos = startPosition(matr.x);
                if(pos.first==-1)
                    return;
                if(isCorrect(matr,pos.first,pos.second,len)){
                    bandb(addSquare(matr,pos.first,pos.second,len),P);
                }
            }
        }
    }

}
//функция для случая с четной стороной
bool evenNumber(){
    if(n%2==0){
        cout<<"4\n";
        cout<<1<<" "<<1<<" "<<n/2<<"\n";
        cout<<1<<" "<<n/2+1<<" "<<n/2<<"\n";
        cout<<n/2+1<<" "<<1<<" "<<n/2<<"\n";
        cout<<n/2+1<<" "<<n/2+1<<" "<<n/2;
        return true;
    }
    return false;
}
//формирование вектора ответа
vector<Square> initSquareList(vector<vector<int>> P){
    vector<Square> sq;
    for(int c=1;c<=record;c++){
        pair<int,int> pos(-1,-1);
        int S=0;
        for(int i=0;i<n;i++){
            for (int j=0;j<n;j++){
                if(c==P[i][j]){
                    S++;
                    if(pos.first==-1 && pos.second==-1){
                        pos.first = i;
                        pos.second = j;
                    }
                }
            }
        }
        sq.push_back(Square(pos.first,pos.second,sqrt(S)));
    }
    return sq;
}
//вывод ответа
void printAnswer(vector<Square> sq, int coefficient){
    cout<<record<<"\n";
    for(int i=0;i<record;i++){//тк индексация начинается с нуля, необходимо прибавить единицу
        cout<<sq[i].x*coefficient+1<<" "<<sq[i].y*coefficient+1<<" "<<sq[i].len*coefficient<<"\n";
    }
}
//начальная оптимизация матрицы
void optimisation(Matrix& matr){
    matr = addSquare(matr,0,0,n/2+1);
    matr = addSquare(matr,n/2+1,0,n/2);
    matr = addSquare(matr,0,n/2+1,n/2);
    max_len = n/2;
}
//функция возвращает коэффициент домножения
int compositNumber(){
    vector<int> prime_list = {2,3,5,7,11,13,17,19,23,29,31,37};
    int coefficient=1;
    if(!count(prime_list.begin(),prime_list.end(),n)) {


        int min_devider;
        for (int i = 0; i < prime_list.size(); i++) {
            if (n % prime_list[i] == 0) {
                min_devider = prime_list[i];
                break;
            }
        }
        coefficient = n / min_devider;
        n = min_devider;//минимальный простой делитель
    }
    return coefficient;
}
int main(){
    //ввод пользователем длины стороны
    cin>>n;
    //Случай для четной стороны
    if(evenNumber())
        return 0;

    vector<vector<int>> x(n,vector<int>(n,0));//текущее решение
    vector<vector<int>> P(n,vector<int>(n,0));//минимальное решение

    record = 2*n+1;//начальная оценка количества квадратов

    //случай, когда сторона составное число
    int coefficient=compositNumber();

    //инициализация структуры
    Matrix matr(x,n);

    //начальная оптимизация
    optimisation(matr);

    //метод ветвей и границ
    bandb(matr,P);

    //вывод ответа
    printAnswer(initSquareList(P),coefficient);

    return 0;
}