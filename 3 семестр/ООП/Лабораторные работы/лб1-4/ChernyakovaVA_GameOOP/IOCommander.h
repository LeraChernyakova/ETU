#pragma once


class MediatorObject;

#include "Player.h"
#include "MediatorObject.h"
#include "IMediator.h"
#include "LogPool.h"
#include "iostream"

class IOCommander : public MediatorObject {
private:
    std::vector<Levels> read_levels();
    int level_num;
public:
    IOCommander() = default;
    void create_logger();
    void read_level_num();
    int get_level() const;
    bool get_approve() const;
    void Defeat() const;
    void Victory() const;
};