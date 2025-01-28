#pragma once

#include "IFieldPlayerEvent.h"
#include "IMapEventObserver.h"
#include "Logger.h"

class MapChange : public IFieldPlayerEvent {
public:
    void event();
    MapChange(Field* field, Player* player, IMapEventObserver* observer = nullptr);
    IEvent* clone() override;
    void setObserver(IMapEventObserver* obs);
    bool isActive() override;
private:
    IMapEventObserver* observer;
};