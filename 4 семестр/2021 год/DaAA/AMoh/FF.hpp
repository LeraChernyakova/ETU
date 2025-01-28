using namespace std;

class GraphComponent{
public:
    char startNode, endNode;
    int flowCapacity, flowCurrent = 0;
    bool isFull = false, isEmpty = true, isReversed = false;
    GraphComponent(char startNode, char endNode, int flowCapacity) : startNode(startNode), endNode(endNode), flowCapacity(flowCapacity){
        if(flowCapacity == 0)
            isFull = true;
    };
    ~GraphComponent()= default;;

    int getPossibleFlow(){
        return isReversed ? flowCurrent : flowCapacity - flowCurrent;
    };

    void addFlow(int additionalFlow){
        if(isReversed)
            flowCurrent -= additionalFlow;
        else
            flowCurrent += additionalFlow;
        isFull = (flowCurrent == flowCapacity);
        isEmpty = (flowCurrent == 0);
    };
};

bool compLexicographic(GraphComponent* a, GraphComponent* b){
    char aStart = a->startNode, aEnd = a->endNode, bStart = b->startNode, bEnd = b->endNode;
    return ( (aStart<bStart) || ((aStart==bStart)&&(aEnd<bEnd)) );
}

bool compSpecial(GraphComponent* a, GraphComponent* b){
    if(a == nullptr)
        return false;
    else if(b == nullptr)
        return true;
    int aStart = int(a->startNode), aEnd = int(a->endNode), bStart = int(b->startNode), bEnd = int(b->endNode);
    if(a->isReversed)
        swap(aStart, aEnd);
    if(b->isReversed)
        swap(bStart, bEnd);
    return ( (abs(aStart-aEnd)<abs(bStart-bEnd)) || ((abs(aStart-aEnd)==abs(bStart-bEnd))&&(aEnd<bEnd)) );
}

class Graph{
public:
    char globalStart, globalEnd;
    int globalFlow = 0;
    vector<GraphComponent*> componentVector, visitedComponentVector, wayVector, componentCandidates;

    Graph(char globalStart, char globalEnd) : globalStart(globalStart), globalEnd(globalEnd){};

    ~Graph(){
        for(auto & i : componentVector)
            delete i;
    };

    void push_back(GraphComponent* component){
        componentVector.push_back(component);
    };

    void printAnswer(){
        printf("%d\n", globalFlow);
        for(auto & i : componentVector)
            printf("%c %c %d\n", i->startNode, i->endNode, i->flowCurrent);
    };

    bool isUniqueWayNode(GraphComponent* component){
        char checkNode = component->isReversed ? component->startNode : component->endNode;
        if(wayVector.empty()){
            if(globalStart == checkNode)
                return false;
            return true;
        } else {
            for(auto & i : wayVector)
                if( ((i->startNode == checkNode) && (!i->isReversed)) || ((i->endNode == checkNode) && (i->isReversed)) )
                    return false;
            return true;
        }
    };

    bool isVisitedComponent(GraphComponent* component){
        for(auto & i : visitedComponentVector)
            if(i == component)
                return true;
        return false;
    };

    GraphComponent* getBestWayComponent(char startNewNode){
        GraphComponent* componentReturn = nullptr;
        componentCandidates.clear();


        for(auto & i : componentVector)
            if((i->startNode == startNewNode)||(i->endNode == startNewNode))
                componentCandidates.push_back(i);

        for(int i = 0; i < componentCandidates.size(); i++)
            if(isVisitedComponent(componentCandidates[i])){
                componentCandidates.erase(componentCandidates.begin() + i);
                i--;
            }

        for(int i = 0; i < componentCandidates.size(); i++){
            if(componentCandidates[i]->endNode == startNewNode)
                componentCandidates[i]->isReversed = true;
            if(!isUniqueWayNode(componentCandidates[i])){
                componentCandidates[i]->isReversed = false;
                visitedComponentVector.push_back(componentCandidates[i]);
                componentCandidates.erase(componentCandidates.begin() + i);
                i--;
            }
        }

        for(int i = 0; i < componentCandidates.size(); i++)
            if(((componentCandidates[i]->isReversed) && (componentCandidates[i]->isEmpty)) || (!(componentCandidates[i]->isReversed) && (componentCandidates[i]->isFull))){
                componentCandidates[i]->isReversed = false;
                componentCandidates.erase(componentCandidates.begin() + i);
                i--;
            }

        for(int i = 0; i < componentCandidates.size(); i++)
            if(compSpecial(componentCandidates[i], componentReturn)){
                if(componentReturn != nullptr)
                    componentReturn->isReversed = false;
                componentReturn = componentCandidates[i];
            } else {
                componentCandidates[i]->isReversed = false;
            }
        if(componentReturn != nullptr)
            visitedComponentVector.push_back(componentReturn);
        return componentReturn;
    };

    bool findWay(){
        GraphComponent* newWayComponent;
        visitedComponentVector = wayVector;
        while(true){
            newWayComponent = getBestWayComponent(
                    wayVector.size() == 0 ? globalStart : (
                            wayVector.back()->isReversed ? wayVector.back()->startNode : wayVector.back()->endNode
                    ));
            if(newWayComponent == nullptr){
                if(wayVector.empty()){
                    return false;
                } else {
                    wayVector.pop_back();
                }
            } else {
                wayVector.push_back(newWayComponent);
                if(wayVector.back()->endNode == globalEnd)
                    return true;
            }
        }
    };

    void addWayFlow(){
        int wayFlow = wayVector[0]->getPossibleFlow(), firstComponentIndexDrop = 0;

        for(int i = 1; i < wayVector.size(); i++)
            if(wayFlow > wayVector[i]->getPossibleFlow()){
                wayFlow = wayVector[i]->getPossibleFlow();
                firstComponentIndexDrop = i;
            }
        globalFlow += wayFlow;
        for(auto & i : wayVector){
            i->addFlow(wayFlow);

        }
        for(int i = wayVector.size()-1; i >= firstComponentIndexDrop; i--){
            wayVector.back()->isReversed = false;
            wayVector.pop_back();
        }
        visitedComponentVector = wayVector;
    }

    void findGraphFlow(){
        sort(componentVector.begin(), componentVector.end(), compLexicographic);
        while(findWay()){
            addWayFlow();
        }
    };
};