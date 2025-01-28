#pragma once

class Event {
public:
    virtual void execute() = 0;
    virtual ~Event() = default;
};