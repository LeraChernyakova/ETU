cmake_minimum_required(VERSION 3.16.3)
project(GAME_PROJ)

set(CMAKE_CXX_STANDARD 17)

add_executable(GAME_PROJ sources/main.cpp sources/cell.cpp sources/cellObject.cpp sources/field_view.cpp sources/field.cpp sources/game.cpp sources/player.cpp sources/enemyBoss.cpp sources/enemyMove.cpp sources/enemyStand.cpp sources/objectHeal.cpp sources/objectDamage.cpp sources/objectRange.cpp sources/cellView.cpp sources/cellObjectView.cpp
sources/ostreamWrapper.cpp sources/fstreamWrapper.cpp sources/logger.cpp sources/enemy.cpp sources/binds/bind.cpp sources/binds/bindMoveDown.cpp sources/binds/bindPlayer.cpp sources/inputController.cpp sources/binds/bindMoveLeft.cpp sources/binds/bindMoveRight.cpp sources/binds/bindMoveUp.cpp sources/binds/bindFight.cpp sources/binds/bindExit.cpp
headers/cell.h headers/cellObject.h headers/field_view.h headers/field.h headers/game.h headers/player.h headers/enemy.h headers/enemyBoss.h headers/enemyMove.h headers/enemyStand.h headers/objectHeal.h headers/objectDamage.h headers/objectRange.h headers/cellView.h headers/cellObjectView.h
headers/ostreamWrapper.h headers/fstreamWrapper.h headers/logger.h headers/binds/bind.h headers/binds/bindMoveDown.h headers/binds/bindPlayer.h headers/inputController.h headers/binds/bindMoveLeft.h headers/binds/bindMoveRight.h headers/binds/bindMoveUp.h headers/binds/bindFight.h headers/binds/bindExit.h)

target_link_libraries(GAME_PROJ sfml-graphics sfml-window sfml-system -lncurses -g)