#pragma once

#include <unordered_map>
#include <typeinfo>

#include "IEventObserver.h"

class EventObserverPool {
public:
    static  EventObserverPool& instance();
    virtual ~EventObserverPool();
    template<typename T>
    T* getEventObserver() {
        static_assert(std::is_base_of<IEventObserver, T>::value,
            "Event observer (T) must derive from IEventObserver");
        std::size_t id = typeid(T).hash_code();
        if (_observers[id] == nullptr) {
            _observers[id] = new T();
        }
        return reinterpret_cast<T*>(_observers[id]);
    }
    EventObserverPool(const EventObserverPool&) = delete;
    EventObserverPool& operator=(const EventObserverPool&) = delete;
private:
    EventObserverPool() = default;
    std::unordered_map<std::size_t, IEventObserver*> _observers;

};
