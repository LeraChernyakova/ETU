#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>

template <typename T>
class FineBlockingQueue
{
private:
    struct Node
    {
        std::shared_ptr<T> value;
        std::unique_ptr<Node> next;
    };
    
    std::unique_ptr<Node> head = nullptr;
    Node* tail = nullptr;
    std::mutex headMutex;
    std::mutex tailMutex;
    std::condition_variable cv;

    Node* getTail(){
        std::lock_guard<std::mutex> lock(tailMutex);
        return tail;
    }
public:
    FineBlockingQueue():
                        head(new Node),
                        tail(head.get()){}
    FineBlockingQueue(const FineBlockingQueue&)=delete;
    FineBlockingQueue& operator= (const FineBlockingQueue&)=delete;
    
    void push(T item)
    {
        auto newData = std::make_shared<T>(std::move(item));
        auto newNode = std::make_unique<Node>();
        {
            std::lock_guard<std::mutex> lock(tailMutex);
            tail->value = newData;
            auto* newTail = newNode.get();
            tail->next = std::move(newNode);
            tail = newTail;
        }
        cv.notify_one();
    }

    T pop()
    {
        std::unique_lock<std::mutex> lock(headMutex);
        cv.wait(lock, [this]{
            return head.get() != getTail();
        });
        auto oldHead = std::move(head);
        head = std::move(oldHead->next);
        return *(oldHead->value);
    }
};
