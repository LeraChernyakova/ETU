#include "threads.h"
#include "ctime"
int main() {
    //std::cout << std::ctime(nullptr);
    int threadsNum = 32;
    Threads threads(threadsNum);
    threads.run();
    //std::ctime(nullptr);
    return 0;
}
