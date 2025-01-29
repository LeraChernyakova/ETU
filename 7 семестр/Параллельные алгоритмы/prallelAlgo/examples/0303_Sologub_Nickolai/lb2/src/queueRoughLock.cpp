#include "queueRoughLock.h"


 QueueRoughLock::QueueRoughLock()// инициализирует очередь
{};


 Matrix QueueRoughLock::consume(){

    std::unique_lock<std::mutex> lock(this->mut); // залочить очередь

    consumed.wait(lock, [&]() -> bool 
    {
        return !queue.empty(); 
    }); // ждём пока не появятся элементы в очереди

    Matrix matrix = queue.front(); // вытаскиваем матрицу из очереди

    queue.pop(); // извлекаем элемент

    lock.unlock(); // разблокировать очередь

    
    return matrix; // возвращаем полученную матрицу
}

 void QueueRoughLock::produce(Matrix& matrix){
    std::unique_lock<std::mutex> lock(this->mut); // залочить очередь
    queue.push(matrix); // поместить матрицу в очередь


    lock.unlock(); // разлочить очередь

    consumed.notify_one(); // оповестить консьюмера
}

