#include <iostream>
#include <map>
#include <vector>
#include "math.h"
#include <algorithm>
#include <float.h>
#include <limits.h>
//граф, который вводит пользователь
std::map <char, std::vector<std::pair<char,float>>> graph;
//словарь для оценки пути от вершины
std::map<char,float> costFromVertecies;
//словарь для оценки полного пути
std::map<char,float> costFullWayFromVerticies;
//словарь для определения вершины, через которую были произведены улучшения
std::map<char,char> parentList;

//функция инициализации графа
//пока пользователь вводит корректные данные, они записываются в граф
void initializationOfGraph(){
    char firstInputVertice,secondInputVertice;
    float lengthBetweenInputVerticies;
    while(std::cin >> firstInputVertice >> secondInputVertice >> lengthBetweenInputVerticies){
        std::pair<char,float> temporaryElement(secondInputVertice,lengthBetweenInputVerticies);

        graph[firstInputVertice].push_back(temporaryElement);

        costFromVertecies[firstInputVertice] = INT_MAX;
        costFromVertecies[secondInputVertice] = INT_MAX;
    }
}

//эврестическая функция
float heuristicFunction(char startVertice, char endVertice){
    return abs(int(endVertice) - int(startVertice));
}

//функция для нахождения минимальной вершине (по оценки пути)
char findMinimalVerticeByCost(std::vector<char> QueueOfVertices){
    char currentVertice = QueueOfVertices[0];
    int minimalCost = INT_MAX;
    for(int i = 0; i < QueueOfVertices.size(); i++){
        if(minimalCost >= costFullWayFromVerticies[QueueOfVertices[i]]) {
            currentVertice = QueueOfVertices[i];
            minimalCost = costFullWayFromVerticies[QueueOfVertices[i]];
        }
    }
    return currentVertice;
}

//функция, которая реализует алгоритм А стар
//пока список вершин не пуст (или не найлено решение), находится лучшая вершина из списка. Она удаляется из этого списка и добавляется в список просмотренных вершин.
// Далее проверяется можно ли улучшить через данную вершину путь до смежных с ней вершин
bool Astar(char startVertice,char goalVertice){
    std::vector<char> VisitedVertices;
    std::vector<char> QueueOfVertices;
    QueueOfVertices.push_back(startVertice);
    costFromVertecies[startVertice] = 0;
    costFullWayFromVerticies[startVertice] = costFromVertecies[startVertice] + heuristicFunction(startVertice, goalVertice);

    while(QueueOfVertices.size() != 0){
        char currentVertice = findMinimalVerticeByCost(QueueOfVertices);

        std::remove(QueueOfVertices.begin(), QueueOfVertices.end(),currentVertice);
        QueueOfVertices.resize(QueueOfVertices.size() - 1);

        if (currentVertice == goalVertice){
            return true;
        }

        VisitedVertices.push_back(currentVertice);

        for(int i = 0; i < graph[currentVertice].size(); i++){
            char temporaryVertice = graph[currentVertice][i].first;
            float temprorayScoreFromCurrentVertice = costFromVertecies[currentVertice] + graph[currentVertice][i].second;

            if (count(VisitedVertices.begin(),VisitedVertices.end(),temporaryVertice) != 0 && temprorayScoreFromCurrentVertice >= costFromVertecies[temporaryVertice]){
                continue;
            }

            if(count(VisitedVertices.begin(),VisitedVertices.end(),temporaryVertice)==0 || temprorayScoreFromCurrentVertice < costFromVertecies[temporaryVertice]){
                if(temprorayScoreFromCurrentVertice < costFromVertecies[temporaryVertice]){
                    parentList[temporaryVertice] = currentVertice;
                    costFromVertecies[temporaryVertice] = temprorayScoreFromCurrentVertice;

                }
                costFullWayFromVerticies[temporaryVertice] = costFromVertecies[temporaryVertice] + heuristicFunction(temporaryVertice,goalVertice);

                if (count(QueueOfVertices.begin(),QueueOfVertices.end(),temporaryVertice) == 0){
                    QueueOfVertices.push_back(temporaryVertice);
                }
            }
        }
    }
    return false;
}
//функция для нахождения оптимального пути через метки, по которым улучшались вершины(словарь parent)
std::vector<char> getBestWayBetweenTwoVertices(char endVertice){
    std::vector<char> bestWayBetweenTwoVertices;
    bestWayBetweenTwoVertices.push_back(endVertice);
    char temporaryVertice = endVertice;
    while(parentList[temporaryVertice]){
        bestWayBetweenTwoVertices.push_back(parentList[temporaryVertice]);
        temporaryVertice = parentList[temporaryVertice];
    }
    return bestWayBetweenTwoVertices;
}

//функция для вывод в консоль найденного пути
void printBestWayBetweenTwoVertices(std::vector<char> bestWayBetweenTwoVertices){
    for(int i = bestWayBetweenTwoVertices.size() - 1; i >= 0; i--){
        std::cout << bestWayBetweenTwoVertices[i];
    }
}
int main() {
    //начальная и конечная вершины
    char startVertice, endVertice;

    //получение начальной и конечной вершин
    std::cin >> startVertice >> endVertice;

    //инициализация графа
    initializationOfGraph();

    //алгоритм A стар
    Astar(startVertice,endVertice);

    //вывод на экран
    printBestWayBetweenTwoVertices(getBestWayBetweenTwoVertices(endVertice));

    return 0;
}
