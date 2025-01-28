GCPP = g++ -std=c++17 -g


lab6: main.cpp game.o game_view.o ui_menu_player_actions.o ui_menu_target_select.o field.o field_view.o cell.o cell_view.o cell_entrance.o cell_exit.o cell_object.o cell_object_view.o actor.o enemy.o item.o player.o armor_item.o health_item.o weapon_item.o acolyte.o sentinel.o stalkerbot.o action_combat.o action.o action_move.o action_shoot_ballistic.o observer.o observable.o observer_actor.o global_logger.o ostream_wrapper.o fstream_wrapper.o exit_condition.o player_death_condition.o key_bind_manager.o input_manager.o serializable.o savestream.o class_creator.o class_creator_inserter.o save_exceptions.o
	$(GCPP) $^ -o lab6
clean:
	-rm -f *.o


game.o: game.cpp game.h
	$(GCPP) -c $< -o $@

game_view.o: ui/game_view.cpp ui/game_view.h
	$(GCPP) -c $< -o $@
ui_menu_player_actions.o: ui/ui_menu_player_actions.cpp ui/ui_menu_player_actions.h
	$(GCPP) -c $< -o $@
ui_menu_target_select.o: ui/ui_menu_target_select.cpp ui/ui_menu_target_select.h
	$(GCPP) -c $< -o $@

field.o: field.cpp field.h
	$(GCPP) -c $< -o $@
field_view.o: field_view.cpp field_view.h
	$(GCPP) -c $< -o $@
cell.o: cells/cell.cpp cells/cell.h
	$(GCPP) -c $< -o $@
cell_view.o: cells/cell_view.cpp cells/cell_view.h
	$(GCPP) -c $< -o $@
cell_entrance.o: cells/cell_entrance.cpp cells/cell_entrance.h
	$(GCPP) -c $< -o $@
cell_exit.o: cells/cell_exit.cpp cells/cell_exit.h
	$(GCPP) -c $< -o $@
cell_object.o: cell_object.cpp cell_object.h
	$(GCPP) -c $< -o $@
cell_object_view.o: cell_object_view.cpp cell_object_view.h
	$(GCPP) -c $< -o $@

actor.o: actors/actor.cpp actors/actor.h
	$(GCPP) -c $< -o $@
enemy.o: actors/enemy.cpp actors/enemy.h
	$(GCPP) -c $< -o $@
item.o: actors/item.cpp actors/item.h
	$(GCPP) -c $< -o $@
player.o: actors/player.cpp actors/player.h
	$(GCPP) -c $< -o $@

armor_item.o: actors/items/armor_item.cpp actors/items/armor_item.h
	$(GCPP) -c $< -o $@
health_item.o: actors/items/health_item.cpp actors/items/health_item.h
	$(GCPP) -c $< -o $@
weapon_item.o: actors/items/weapon_item.cpp actors/items/weapon_item.h
	$(GCPP) -c $< -o $@

acolyte.o: actors/enemies/acolyte.cpp actors/enemies/acolyte.h
	$(GCPP) -c $< -o $@
sentinel.o: actors/enemies/sentinel.cpp actors/enemies/sentinel.h
	$(GCPP) -c $< -o $@
stalkerbot.o: actors/enemies/stalkerbot.cpp actors/enemies/stalkerbot.h
	$(GCPP) -c $< -o $@

action.o: actions/action.cpp actions/action.h
	$(GCPP) -c $< -o $@
action_combat.o: actions/action_combat.cpp actions/action_combat.h
	$(GCPP) -c $< -o $@
action_move.o: actions/action_move.cpp actions/action_move.h
	$(GCPP) -c $< -o $@
action_shoot_ballistic.o: actions/action_shoot_ballistic.cpp actions/action_shoot_ballistic.h
	$(GCPP) -c $< -o $@

observer.o: logger/observer.cpp logger/observer.h
	$(GCPP) -c $< -o $@
observable.o: logger/observable.cpp logger/observable.h
	$(GCPP) -c $< -o $@
observer_actor.o: logger/observer_actor.cpp logger/observer_actor.h
	$(GCPP) -c $< -o $@
global_logger.o: logger/global_logger.cpp logger/global_logger.h
	$(GCPP) -c $< -o $@
ostream_wrapper.o: logger/ostream_wrapper.cpp logger/ostream_wrapper.h
	$(GCPP) -c $< -o $@
fstream_wrapper.o: logger/fstream_wrapper.cpp logger/fstream_wrapper.h
	$(GCPP) -c $< -o $@

exit_condition.o: rule/exit_condition.cpp rule/exit_condition.h
	$(GCPP) -c $< -o $@
player_death_condition.o: rule/player_death_condition.cpp rule/player_death_condition.h
	$(GCPP) -c $< -o $@

key_bind_manager.o: input/key_bind_manager.cpp input/key_bind_manager.h
	$(GCPP) -c $< -o $@
input_manager.o: input/input_manager.cpp input/input_manager.h
	$(GCPP) -c $< -o $@

serializable.o: save/serializable.cpp save/serializable.h
	$(GCPP) -c $< -o $@
savestream.o: save/savestream.cpp save/savestream.h
	$(GCPP) -c $< -o $@
class_creator.o: save/class_creator.cpp save/class_creator.h
	$(GCPP) -c $< -o $@
class_creator_inserter.o: save/class_creator_inserter.cpp save/class_creator_inserter.h
	$(GCPP) -c $< -o $@
save_exceptions.o: save/save_exceptions.cpp save/save_exceptions.h
	$(GCPP) -c $< -o $@
