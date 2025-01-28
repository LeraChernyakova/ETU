#pragma once

class IEvent {
public:
    virtual void event() = 0;
    virtual IEvent* clone() = 0;
    virtual ~IEvent() = default;
    virtual bool isActive() = 0;
};