:- dynamic(variables/2).
set(Var, Val) :- (\+variables(Var, _), !; retract(variables(Var, _))), assertz(variables(Var, Val)).
get(Var, Val) :- variables(Var, Val).

:- dynamic(stored/5).
store(LeftMiss, LeftCann, BoatMiss, BoatCann, Side) :-
    \+stored(LeftMiss, LeftCann, BoatMiss, BoatCann, Side),
    assertz(stored(LeftMiss, LeftCann, BoatMiss, BoatCann, Side)).

go :-
    set(type_limit, 3),
    set(boat_limit, 2),
    get(type_limit, TypeLimit),
    on_left(TypeLimit, TypeLimit, 0, 0).

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

on_left(LeftMiss, LeftCann, BoatMiss, BoatCann) :-
    is_valid(LeftMiss, LeftCann, BoatMiss, BoatCann),
    store(LeftMiss, LeftCann, BoatMiss, BoatCann, left),
    ((BoatMiss + BoatCann > 0, on_right(LeftMiss, LeftCann, BoatMiss, BoatCann), writeln('-> drive to the right'));
    (LM is LeftMiss + 1, BM is BoatMiss - 1, on_left(LM, LeftCann, BM, BoatCann), writeln('missioner left the boat'));
    (LC is LeftCann + 1, BC is BoatCann - 1, on_left(LeftMiss, LC, BoatMiss, BC), writeln('cannibal left the boat'));
    (LM is LeftMiss - 1, BM is BoatMiss + 1, on_left(LM, LeftCann, BM, BoatCann), writeln('missioner entered the boat'));
    (LC is LeftCann - 1, BC is BoatCann + 1, on_left(LeftMiss, LC, BoatMiss, BC), writeln('cannibal entered the boat'))).

on_right(0, 0, 0, 0).

on_right(LeftMiss, LeftCann, BoatMiss, BoatCann) :-
    is_valid(LeftMiss, LeftCann, BoatMiss, BoatCann),
    store(LeftMiss, LeftCann, BoatMiss, BoatCann, right),
    ((BoatMiss + BoatCann > 0, on_left(LeftMiss, LeftCann, BoatMiss, BoatCann), writeln('-> drive to the left'));
    (BM is BoatMiss - 1, on_right(LeftMiss, LeftCann, BM, BoatCann), writeln('missioner left the boat'));
    (BC is BoatCann - 1, on_right(LeftMiss, LeftCann, BoatMiss, BC), writeln('cannibal left the boat'));
    (BM is BoatMiss + 1, on_right(LeftMiss, LeftCann, BM, BoatCann), writeln('missioner entered the boat'));
    (BC is BoatCann + 1, on_right(LeftMiss, LeftCann, BoatMiss, BC), writeln('cannibal entered the boat'))).
