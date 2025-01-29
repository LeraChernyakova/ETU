#include "RoughLock.h"

RoughLock::RoughLock()
{

};

Matrix RoughLock::consume()
{
    std::unique_lock<std::mutex> lock(this->mut);
    consumed.wait(lock, [&]() -> bool 
    {
        return !queue.empty(); 
    });
    Matrix matrix = queue.front();
    queue.pop(); 
    lock.unlock(); // разблок
    return matrix;
}

 void RoughLock::produce(Matrix& matrix)
 {
    std::unique_lock<std::mutex> lock(this->mut); // блок
    queue.push(matrix);
    lock.unlock(); // разблок
    consumed.notify_one(); 
}

