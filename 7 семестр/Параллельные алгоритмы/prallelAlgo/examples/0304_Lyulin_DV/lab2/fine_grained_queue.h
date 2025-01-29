#ifndef FINE_GRAINED_QUEUE_H
#define FINE_GRAINED_QUEUE_H

#include <mutex>
#include <condition_variable>
#include <atomic>
#include <functional>
#include <memory>

/// @brief Потокобезопасная очередь с тонкими блокировками на односвязном списке.
/// @details Поддерживает множество производителей и множество потребителей.
/// @tparam T тип элемента очереди.
template < typename T >
class FineGrainedQueue
{
public:
     /// @brief Конструктор.
     FineGrainedQueue();

     /// @brief Завершить работу и все ожидания.
     void finish();

     /// @brief Добавление элемента в очередь.
     /// @param[in] elem добавляемый элемент очереди.
     void push( T&& elem );

     /// @brief Обработка одного элемента очереди, если есть.
     /// @details Когда элементов нет, ждёт, пока появится элементов,
     /// если есть ещё производители.
     /// @param[in] func функция, которая исполнится, если будет получен элемент очереди.
     /// @return true, если элемент был обработан, иначе false.
     bool process( const std::function< void( const T& ) >& func );

private:
     /// @brief Узел односвязного списка.
     struct Node
     {
          T data;
          std::unique_ptr< Node > next;
     };

     const Node* get_back_locked();

     std::condition_variable cond_;          ///< условие для ожидания.
     std::mutex front_mutex_;                ///< мьюеткс для блокировок доступа к первому элементу.
     std::mutex back_mutex_;                 ///< мьюеткс для блокировок доступа к последнему элементу.
     std::unique_ptr< Node > front_;         ///< начало очереди.
     Node *back_;                            ///< конец очереди.
     bool finish_;                           ///< условие окончания работы.
};

#include "fine_grained_queue.inl"

#endif // FINE_GRAINED_QUEUE_H
