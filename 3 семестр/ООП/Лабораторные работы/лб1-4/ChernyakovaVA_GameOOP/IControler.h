#pragma once

class IControler {
public:
    virtual char get_command() = 0;
    virtual ~IControler() = default;
};