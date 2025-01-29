#include "model/Flows.h"
int main() {
    std::vector<std::pair<int, int>> CP = {{5, 7}, {20, 10}, {10 ,10}, {10,2}};
    for(auto& cp : CP){
        Flows flows(10, cp.first, cp.second);
        std::cout << "Consumer: " << cp.first << " Producer: " << cp.second << " Time:\n";
        flows.run();
    }

    return 0;
}
