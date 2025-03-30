/*
	Бригада 1 группы 8382 - Кузина, Кулачкова, Мирончик
	Задание: Миссионеры и каннибалы 
	К берегу реки подошли 3 миссионера и 3 каннибала. Как им всем безопасно переправиться на другой берег, 
	используя двухместную лодку, если каннибалы могут съесть миссионеров, оказавшихся в меньшинстве? 
	(вывести порядок перемещений).
*/

:- dynamic(variables/2).
set(Var, Val) :- (\+variables(Var, _), !; retract(variables(Var, _))), assertz(variables(Var, Val)).
get(Var, Val) :- variables(Var, Val).

:- dynamic(stored/5).
store(LeftMiss, LeftCann, BoatMiss, BoatCann, Side) :-
    \+stored(LeftMiss, LeftCann, BoatMiss, BoatCann, Side),
    assertz(stored(LeftMiss, LeftCann, BoatMiss, BoatCann, Side)).

writereversed([H]) :- write(H), nl.
writereversed([H | T]) :- writereversed(T), write(H), nl.

go :-
    set(type_limit, 3),
    set(boat_limit, 2),
    get(type_limit, TypeLimit),
    on_left(TypeLimit, TypeLimit, 0, 0, []).

is_all_alive(Miss, Cann) :- Miss >= Cann; Miss =:= 0.

is_valid(LeftMiss, LeftCann, BoatMiss, BoatCann) :-
    get(type_limit, TypeLimit),
    get(boat_limit, BoatLimit),
    RightMiss = TypeLimit - LeftMiss - BoatMiss,
    RightCann = TypeLimit - LeftCann - BoatCann,
    LeftMiss + BoatMiss =< TypeLimit,
    LeftCann + BoatCann =< TypeLimit,
    BoatMiss + BoatCann =< BoatLimit,
    LeftMiss >= 0, LeftCann >= 0, BoatMiss >= 0, BoatCann >= 0, RightMiss >= 0, RightCann >= 0,
    is_all_alive(LeftMiss, LeftCann),
    is_all_alive(BoatMiss, BoatCann),
    is_all_alive(RightMiss, RightCann).

on_left(LeftMiss, LeftCann, BoatMiss, BoatCann, R) :-
    is_valid(LeftMiss, LeftCann, BoatMiss, BoatCann),
    store(LeftMiss, LeftCann, BoatMiss, BoatCann, left),
    ((BoatMiss + BoatCann > 0, on_right(LeftMiss, LeftCann, BoatMiss, BoatCann, ['-> drive to the right'| R]));
    (LM is LeftMiss + 1, BM is BoatMiss - 1, on_left(LM, LeftCann, BM, BoatCann, ['missioner left the boat'| R]));
    (LC is LeftCann + 1, BC is BoatCann - 1, on_left(LeftMiss, LC, BoatMiss, BC, ['cannibal left the boat'| R]));
    (LM is LeftMiss - 1, BM is BoatMiss + 1, on_left(LM, LeftCann, BM, BoatCann, ['missioner entered the boat'| R]));
    (LC is LeftCann - 1, BC is BoatCann + 1, on_left(LeftMiss, LC, BoatMiss, BC, ['cannibal entered the boat' | R]))).

on_right(0, 0, 0, 0, R) :- writereversed(R).

on_right(LeftMiss, LeftCann, BoatMiss, BoatCann, R) :-
    is_valid(LeftMiss, LeftCann, BoatMiss, BoatCann),
    store(LeftMiss, LeftCann, BoatMiss, BoatCann, right),
    ((BoatMiss + BoatCann > 0, on_left(LeftMiss, LeftCann, BoatMiss, BoatCann, ['-> drive to the left'| R]));
    (BM is BoatMiss - 1, on_right(LeftMiss, LeftCann, BM, BoatCann, ['missioner left the boat'| R]));
    (BC is BoatCann - 1, on_right(LeftMiss, LeftCann, BoatMiss, BC, ['cannibal left the boat'| R]));
    (BM is BoatMiss + 1, on_right(LeftMiss, LeftCann, BM, BoatCann, ['missioner entered the boat'| R]));
    (BC is BoatCann + 1, on_right(LeftMiss, LeftCann, BoatMiss, BC, ['cannibal entered the boat' | R]))).
