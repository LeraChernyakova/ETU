#include <condition_variable>
#include <mutex>

//очередь с "тонкой" блокировкой
template <typename T>
class finegrained_queue {
private:
    struct Node {
        std::shared_ptr<T> value;
        std::unique_ptr<Node> next;
    };

    std::mutex head_mutex;
    std::unique_ptr<Node> head;
    std::mutex tail_mutex;
    Node* tail;
    std::condition_variable condition;

    Node* get_tail() {
        std::lock_guard<std::mutex> tail_lock(tail_mutex);
        return tail;
    }

    std::unique_ptr<Node> pop_head() {
        std::unique_ptr<Node> old_head = std::move(head);
        head = std::move(old_head->next);
        return old_head;
    }

    std::unique_lock<std::mutex> wait_for_data() {
        std::unique_lock<std::mutex> head_lock(head_mutex);
        condition.wait(head_lock, [&] {
            return head.get() != get_tail();
        });
        return std::move(head_lock);
    }

    std::unique_ptr<Node> wait_pop_head() {
        std::unique_lock<std::mutex> head_lock(wait_for_data());
        return pop_head();
    }

public:
    finegrained_queue(): head(new Node), tail(head.get()) {}
    finegrained_queue(const finegrained_queue& other)=delete;
    finegrained_queue& operator=(const finegrained_queue& other)=delete;

    void add(T element) {
        std::shared_ptr<T> new_element(
            std::make_shared<T>(
                std::move(element)
            )
        );
        std::unique_ptr<Node> pointer(new Node);
        {
            std::lock_guard<std::mutex> tail_lock(tail_mutex);
            tail->value = new_element;
            Node* const new_tail = pointer.get();
            tail->next = std::move(pointer);
            tail = new_tail;
        }
        condition.notify_one();
    }

    T get() {
        std::unique_ptr<Node> const old_head = wait_pop_head();
        return *(old_head->value);
    }
};
