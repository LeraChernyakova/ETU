#ifndef LOCK_FREE_QUEUE_H
#define LOCK_FREE_QUEUE_H

#include <atomic>
#include <limits>
#include <unordered_set>

/// @brief Потокобезопасная lock-free очередь Майкла-Скотта.
/// @details Поддерживает множество производителей и множество потребителей.
/// Инвариант класса - head_ указывает на узел не после tail_ (при этом могут совпадать).
/// Для SMR (safe memory reclamation) используется механизм указателей опасности (Hazard Pointers).
/// @tparam T тип элемента очереди.
template < typename T >
class LockFreeQueue
{
public:
     /// @brief Конструктор.
     /// @param[in] thread_count количество потоков, работающих с очередью.
     LockFreeQueue( std::size_t thread_count );

     /// @brief Деструктор.
     ~LockFreeQueue();

     /// @brief Добавление элемента в очередь.
     /// @param[in] elem добавляемый элемент очереди.
     void push( T&& elem );

     /// @brief Взятие одного элемента из очереди, если он есть.
     /// @param[out] elem полученный элемент очереди.
     /// @return true, если элемент был взят, иначе false.
     bool pop( T& elem );

private:
     /// @brief Узел односвязного списка.
     struct Node
     {
          T                    data;         ///< данные узла.
          std::atomic< Node* > next;         ///< указатель на следующий узел.
     };
     using ANodePtr = std::atomic< Node* >;

     /// @brief Поиск и удаление неиспользуемых указателей.
     void scan();

     /// @brief Добавление указателя в массив для отложенного удаления.
     /// @param[in] ptr указатель, который будет отложен для удаления.
     void retire( Node *ptr );

     /// @brief Рекурсивно удалить связный список.
     /// @param ptr указатель на начало связного списка.
     static inline void delete_recursive( const ANodePtr& ptr );

     /// @brief Установка и сохранение текущего номера потока.
     inline void init_thread_num();

     /// @brief Получение указателя опасности для текущего потока.
     /// @param[in] i номер указателя опасности.
     inline ANodePtr& get_hp( std::size_t i );

private:
     /// @brief Максимальное количество указателей опасности в одном потоке.
     constexpr static std::size_t hp_per_thread_ = 2;

     /// @brief Множитель для указания предельного размера массива, по достижении которого вызывается scan().
     /// @details Множитель должен быть больше 1, чтобы scan() гарантированно удалял элементы.
     constexpr static std::size_t batch_ = 2;

     static thread_local std::size_t thread_num_; /// Номер текущего потока для доступа к своей части массивов.

     std::vector< ANodePtr > hazard_ptrs_;        ///< указатели опасности всех потоков.
     std::vector< std::size_t > del_sizes_;       ///< текущие размеры массивов удаления всех потоков.
     std::vector< Node * > del_ptrs_;             ///< удаляемые указатели всех потоков.
     std::atomic_size_t curr_thread_num_;         ///< текущее количество потоков, обратившихся к очереди.

     ANodePtr head_;                         ///< указатель на начало очереди.
     ANodePtr tail_;                         ///< указатель на конец очереди.
};

#include "lock_free_queue.inl"

#endif // LOCK_FREE_QUEUE_H
