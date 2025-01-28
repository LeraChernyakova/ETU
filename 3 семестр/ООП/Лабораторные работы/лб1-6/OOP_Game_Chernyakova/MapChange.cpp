#include "MapChange.h"
#include "Water.h"

void MapChange::event() {
    IEvent* water = new Water(player);
    int count = 0;
    for (int i = 0; i < field->getHeight(); i++) {
        for (int j = 0; j < field->getWidth(); j++) {
            if (field->getCellEvent(j, i) == nullptr && count < 5 && field->getCell(j, i).getPatency() == 1) {
                field->setCellEvent(j, i, water);
                count++;
            }
        }
    }
    if (observer)
        observer->onMapEventInvoked();
}
MapChange::MapChange(Field* field, Player* player, IMapEventObserver* observer) : IFieldPlayerEvent(field, player), observer(observer) {}
IEvent* MapChange::clone() {
    return new MapChange(field, player, observer);
}
void MapChange::setObserver(IMapEventObserver* obs) {
    observer = obs;
}
bool MapChange::isActive() {
    return true;
}