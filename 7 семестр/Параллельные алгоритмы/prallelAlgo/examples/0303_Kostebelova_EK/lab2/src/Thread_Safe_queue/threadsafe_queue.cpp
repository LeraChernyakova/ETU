#include <condition_variable>
#include <mutex>
#include <queue>

//очередь с "грубой" блокировкой
template <typename T>
class threadsafe_queue {
private:
    std::queue<T> queue;
    std::mutex mutex;
    std::condition_variable condition;
public:
    void add(T element) {
        std::unique_lock<std::mutex> lock(mutex);
        queue.push(element);
        condition.notify_one();
    }

    T get() {
        std::unique_lock<std::mutex> lock(mutex);
        condition.wait(lock, [&] {
            return !queue.empty();
        });
        T element = queue.front();
        queue.pop();
        return element;
    }
};
