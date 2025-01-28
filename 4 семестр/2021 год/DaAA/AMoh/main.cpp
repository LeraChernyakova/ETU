#include <iostream>
#include <vector>
#include <algorithm>
#include "FF.hpp"

int main(){
    char globalStartNodeChar, globalEndNodeChar;
    char startNodeChar, endNodeChar;
    int componentCount, flowCapacityValue;

    cin >> componentCount >> globalStartNodeChar >> globalEndNodeChar;
    Graph graph(globalStartNodeChar, globalEndNodeChar);
    for(int i = 0; i < componentCount; i++){  // adding all componetns
        cin >> startNodeChar >> endNodeChar >> flowCapacityValue;
        graph.push_back(new GraphComponent(startNodeChar, endNodeChar, flowCapacityValue));
    }
    graph.findGraphFlow(); // Ford-Fulkerson
    graph.printAnswer(); // output result
    return 0;
}
