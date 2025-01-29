#include "queueThinLock.h"

QueueThinLock::QueueThinLock():head(new node),tail(head.get()){} // добавляем фиктивный узел

Matrix QueueThinLock::consume(){ // вытаскиваем элемент из очереди
std::unique_ptr<node> old_head=pop_head(); // достаём элемент
return Matrix(*old_head->data.get()); // передаём матрицу
}

void QueueThinLock::produce(Matrix new_value){ // добавление узла в очередь
std::shared_ptr<Matrix> new_data(
std::make_shared<Matrix>(std::move(new_value))); // формируем данные
std::unique_ptr<node> p(new node); // создаём узел
node* const new_tail=p.get(); // передаём ссылку на узел
std::lock_guard<std::mutex> tail_lock(tail_mutex); // блокируем изменения tail
tail->data=new_data; // записываем данные в хвост
tail->next=std::move(p); // записываем указатель на следующий узел
tail=new_tail; // присваиваем новый хвост
isEmpty.notify_one(); // оповещаем консьюмера
}