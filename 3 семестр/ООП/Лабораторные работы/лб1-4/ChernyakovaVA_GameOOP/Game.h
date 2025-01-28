#pragma once

class MediatorObject;
class Field;
class WinEvent;
class FieldView;

#include "FieldView.h"
#include "Player.h"
#include "PlayerView.h"
#include "MediatorObject.h"
#include "IMediator.h"
#include "WinEvent.h"
#include "FieldGen.h"
#include "R_Column_Walls.h"
#include "R_Row_Walls.h"
#include "R_Rand_Walls.h"
#include "R_Player_Spawn.h"
#include "R_Rand_Events.h"
#include "R_Field_Size.h"
#include "R_Win_Cell.h"
#include "FieldEventGen.h"
#include "PlayerEventGen.h"

class Game : public MediatorObject {
public:
    enum STATUS {
        START,
        INPROGRESS,
        WIN,
        DEFEAT,
        END
    };
    Game();
    void initialize_field(int level_num);
    void start();
    STATUS get_status() const;
    void set_status(STATUS stat);
    void set_step(Player::Moves cur);
    ~Game() override;
private:
    Field* field;
    Player* player;
    FieldView* field_view;
    PlayerView* player_view;
    Player::Moves cur_step;
    std::map<int, std::function<Field* (Player*)>> levels_gens;
    void loop();
    void reaction();
    void is_end();
    STATUS status;
};

