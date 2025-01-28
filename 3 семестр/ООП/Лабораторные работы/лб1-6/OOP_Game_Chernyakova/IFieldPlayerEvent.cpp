#include "IFieldPlayerEvent.h"

IFieldPlayerEvent::IFieldPlayerEvent(Field* field, Player* player) {
    this->field = field;
    this->player = player;
}