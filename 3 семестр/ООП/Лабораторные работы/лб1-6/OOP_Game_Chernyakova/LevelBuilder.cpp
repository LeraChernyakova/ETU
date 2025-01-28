#include "LevelBuilder.h"
#include "Bomb.h"
#include "Water.h"
#include "Teleport.h"
#include "MapChange.h"
#include "KeyEvent.h"
#include "DoorEvent.h"
#include "PlayerFacade.h"
#include "EventObserverPool.h"
#include "TeleportEventObserver.h"
#include "BombEventObserver.h"
#include "WaterEventObserver.h"
#include "MapEventObserver.h"
#include "KeyEventObserver.h"
#include "DoorEventObserver.h"

std::pair<FieldFacade*, PlayerFacade*> LevelBuilder::make(const FieldScheme& scheme) { //передаем готовую схему
    Cell** array = new Cell * [scheme.height];
    for (int i = 0; i < scheme.height; i++) {
        array[i] = new Cell[scheme.width];
    }
    auto* field = new Field(scheme.width, scheme.height, array);
    auto* field_facade = new FieldFacade(field);
    auto* player_facade = new PlayerFacade(field_facade);
    for (int i = 0; i < scheme.height; i++) {
        for (int j = 0; j < scheme.width; j++) {
            typeEvent(scheme.array[i][j], j, i,
                array[i][j],
                &player_facade->getPlayer(),
                &player_facade->getController(),
                field);
        }
    }
    std::pair<FieldFacade*, PlayerFacade*> out{ field_facade, player_facade };
    return out;
}
void LevelBuilder::typeEvent(CellType type, int x, int y, Cell& cell, Player* player, PlayerController* controller, Field* field) {
    switch (type) {
    case CellType::Default:break;
    case CellType::Player:cell.setActive(true);
        controller->setPosition(x, y);
        break;
    case CellType::Wall:cell.setPatency(false);
        break;
    case CellType::Bomb:
        cell.changeFact(new Bomb(player,
            EventObserverPool::instance().getEventObserver<BombEventObserver>()));
        break;
    case CellType::Water:
        cell.changeFact(new Water(player,
            EventObserverPool::instance().getEventObserver<WaterEventObserver>()));
        break;
    case CellType::Teleport:
        cell.changeFact(new Teleport(controller,
            field,
            EventObserverPool::instance().getEventObserver<TeleportEventObserver>()));
        break;
    case CellType::MapChange:
        cell.changeFact(new MapChange(field,
            player,
            EventObserverPool::instance().getEventObserver<MapEventObserver>()));
        break;
    case CellType::Key:
        cell.changeFact(new KeyEvent(player,
            EventObserverPool::instance().getEventObserver<KeyEventObserver>()));
        break;
    case CellType::Door:
        cell.changeFact(new DoorEvent(player,
            EventObserverPool::instance().getEventObserver<
            DoorEventObserver>()));
        break;
    }
}