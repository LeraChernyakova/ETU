#ifndef THREAD_SAFE_QUEUE_H
#define THREAD_SAFE_QUEUE_H

#include <mutex>
#include <condition_variable>
#include <functional>
#include <queue>

/// @brief Потокобезопасная очередь.
/// @details Поддерживает множество производителей и множество потребителей.
/// @tparam T тип элемента очереди.
template < typename T >
class ThreadSafeQueue
{
public:
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
     std::queue< T > queue_;                 ///< внутреннее представление очереди.
     std::condition_variable cond_;          ///< условие для ожидания.
     std::mutex mutex_;                      ///< мьюеткс для блокировок.
     bool finish_{ false };                  ///< условие окончания работы.
};

#include "thread_safe_queue.inl"

#endif // THREAD_SAFE_QUEUE_H
