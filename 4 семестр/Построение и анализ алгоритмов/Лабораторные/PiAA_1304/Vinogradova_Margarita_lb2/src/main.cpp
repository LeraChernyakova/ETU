#include <iostream>
#include <map>
#include <vector>
#include "math.h"
#include <algorithm>
#include <float.h>

// граф храниться в формате вершина -> массив смежных вершин в виде пары (вершина, вес пути)
std::map <char, std::vector<std::pair<char,float>>> graph;
//переменная для хранения итогового пути
std::vector<char> bestWayBetweenTwoVertices;

//функция инициализации графа
//пока пользователь вводит корректные данные, они записываются в граф
void initializationOfGraph(){
    char firstInputVertice,secondInputVertice;
    float lengthBetweenInputVerticies;
    while(std::cin >> firstInputVertice >> secondInputVertice >> lengthBetweenInputVerticies){
        std::pair<char,float> temporaryElement(secondInputVertice,lengthBetweenInputVerticies);
        graph[firstInputVertice].push_back(temporaryElement);
    }
}

//функция вывода в консоль пути
void printBestWayBetweenTwoVertices(){
    for(int i = 0; i < bestWayBetweenTwoVertices.size(); i++){
        std::cout << bestWayBetweenTwoVertices[i];
    }
}

//функция, которая реализует жадный алгоритм, проходится по всем смежным вершинам и находит самый дешевый путь
//если пути равны, то сравниваются их ASCII символы
//просмотренная вершина удаляется из графа, если все смежные с переданной вершины просмотрены, то удаляется верхняя вершина из пути
void greedAlgorithm(char startVertice){

    float minimalLengthBetweenStartVerticeAndAdjacent = FLT_MAX;
    int indexOfElementWithMinimalLength = 0;
    int minimalChar = 'z';

    for(int i = 0; i < graph[startVertice].size(); i++){

        if(minimalLengthBetweenStartVerticeAndAdjacent > graph[startVertice][i].second){
            minimalLengthBetweenStartVerticeAndAdjacent = graph[startVertice][i].second;
            indexOfElementWithMinimalLength = i;
        }
        if(minimalLengthBetweenStartVerticeAndAdjacent == graph[startVertice][i].second){
            if(minimalChar > graph[startVertice][i].first){
                minimalChar = graph[startVertice][i].first;
                indexOfElementWithMinimalLength = i;
            }
        }
    }

    if (graph[startVertice].size() == 0){
        bestWayBetweenTwoVertices.pop_back();
    }else{
        bestWayBetweenTwoVertices.push_back(graph[startVertice][indexOfElementWithMinimalLength].first);
        std::remove(graph[startVertice].begin(), graph[startVertice].end(),graph[startVertice][indexOfElementWithMinimalLength]);
        graph[startVertice].resize(graph[startVertice].size() - 1);
    }
}


int main() {

    //получение стартовой вершины и конечной вершины
    char startVertice, endVertice;
    std::cin >> startVertice >> endVertice;

    //инициализация графа
    initializationOfGraph();

    //добавление стартовой вершины в путь
    bestWayBetweenTwoVertices.push_back(startVertice);

    //пока не достигнута конечная вершина, вызывается функция жадного поиска
    while(count(bestWayBetweenTwoVertices.begin(),bestWayBetweenTwoVertices.end(),endVertice) == 0){
        greedAlgorithm(bestWayBetweenTwoVertices[bestWayBetweenTwoVertices.size() - 1]);
    }

    //вывод итогового пути
    printBestWayBetweenTwoVertices();

    return 0;
}
