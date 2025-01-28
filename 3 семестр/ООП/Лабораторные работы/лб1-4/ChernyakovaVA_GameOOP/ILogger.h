#pragma once

class Message;

class ILogger {
public:
    virtual void print(const Message& msg) = 0;
    virtual ~ILogger() {};
};