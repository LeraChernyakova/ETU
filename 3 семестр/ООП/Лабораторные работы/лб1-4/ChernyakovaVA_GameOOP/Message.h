#pragma once

class LogPool;
#include "Levels.h"
#include "LogPool.h"
#include <map>
#include "string"
#include "ctime"

class Message {
private:
    std::map<Levels, std::string> prefixs{
            {Levels::GameObjects, "[GameOBJECT]"},
            {Levels::Gamestatus,  "[STATUS]"},
            {Levels::Errors,      "[ERROR]"}
    };
    std::string text;
    Levels level;
public:
    Message(Levels lvl, const std::string& msg);
    std::string get_prefix() const;
    Levels get_level() const;
    std::string get_text() const;
    void set_level(Levels lvl);
    friend std::ostream& operator<<(std::ostream&, const Message& obj);
    ~Message() = default;
};