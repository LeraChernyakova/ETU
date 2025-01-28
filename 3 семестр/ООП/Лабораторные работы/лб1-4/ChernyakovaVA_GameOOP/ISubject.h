#pragma once

#include "IObserver.h"
#include <vector>
#include <algorithm>

class ISubject {
private:
    std::vector<IObserver*> observers;
public:
    void attach(IObserver* observer);
    void detach(IObserver* observer);
    void notify();
    ~ISubject() = default;
};
