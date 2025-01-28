#include <cstdio>
#include "ISubject.h"

void ISubject::attach(IObserver* observer) {
    observers.push_back(observer);
};

void ISubject::detach(IObserver* obs) {
    std::remove(observers.begin(), observers.end(), obs);
}

void ISubject::notify() {
    for (auto obs : observers) {
        obs->update();
    }
}