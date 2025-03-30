/*
    Лабораторная работа №4 по дисциплине "Логическое программирование"

    Задание: Миссионеры и каннибалы 
	К берегу реки подошли 3 миссионера и 3 каннибала. Как им всем безопасно переправиться на другой берег, 
	используя двухместную лодку, если каннибалы могут съесть миссионеров, оказавшихся в меньшинстве? 
	(вывести порядок перемещений).

    Выполнили: Байков Е.С., Мамин Р.А, Чернякова В.А., Ярусова Т.В..
*/

% Проверка безопасности соотношения каннибалов и миссионеров
safe(M, C):- M >= C; M =:= 0.

% Проверка валидности следующего шага
is_valid_step(M, C) :- safe(M, C), M >= 0, C >= 0.

% Запуск поиска решения
go:-
    write('boat_to_right(M, C) - lodka plivet na praviy bereg s M missionerami i C cannibalami'), nl,
    write('boat_to_left(M, C) - lodka plivet na leviy bereg s M missionerami i C cannibalami'), nl,
    move([3, 3], [0, 0], [], r, [[3,3,0,0]]).

% Конечное состояние, являющееся решением задачи
move([0, 0], [3, 3], P, _, _):- reverse(P, ReversedP), write(ReversedP).

/*
	MLeft, CLeft - миссионеры и каннибалы на левом берегу соответственно
    MRight, CRight - миссионеры и каннибалы на правом берегу соответственно 
    P - список передвижений лодки 
    r - направление лодки (r - вправо, l - влево)
    Visited - список посещенных состояний, состоянием называется список [MLeft, CLeft, MRight, CRight]
    Каждый блок программы проверяет возможность рассадки в лодку миссионеров и каннибалов варианты:
        (1, 0), (0, 1), (2, 0), (0, 2), (1, 1) - первое число отвечает за миссионеров в лодке, второе за каннибалов.
*/
move([MLeft, CLeft], [MRight, CRight], P, r, Visited):-
    (
    (
        NewMLeft is MLeft - 1, NewMRight is MRight + 1,
        is_valid_step(NewMLeft, CLeft), is_valid_step(NewMRight, CRight),
        \+ member([NewMLeft, CLeft, NewMRight, CRight], Visited),
        move([NewMLeft, CLeft], [NewMRight, CRight], [boat_to_right(1, 0)|P], l, [[NewMLeft, CLeft, NewMRight, CRight]|Visited])
    );
    (
        NewCLeft is CLeft - 1, NewCRight is CRight + 1,
        is_valid_step(MLeft, NewCLeft), is_valid_step(MRight, NewCRight),
        \+ member([MLeft, NewCLeft, MRight, NewCRight], Visited),
        move([MLeft, NewCLeft], [MRight, NewCRight], [boat_to_right(0, 1)|P], l, [[MLeft, NewCLeft, MRight, NewCRight]|Visited]));
    (
        NewMLeft is MLeft - 2, NewMRight is MRight + 2,
        is_valid_step(NewMLeft, CLeft), is_valid_step(NewMRight, CRight),
        \+ member([NewMLeft, CLeft, NewMRight, CRight], Visited),
        move([NewMLeft, CLeft], [NewMRight, CRight], [boat_to_right(2, 0)|P], l, [[NewMLeft, CLeft, NewMRight, CRight]|Visited])
    );
    (
        NewMLeft is MLeft - 1, NewCLeft is CLeft - 1, NewMRight is MRight + 1, NewCRight is CRight + 1,
        is_valid_step(NewMLeft, NewCLeft), is_valid_step(NewMRight, NewCRight), 
        \+ member([NewMLeft, NewCLeft, NewMRight, NewCRight, r], Visited),
        move([NewMLeft, NewCLeft], [NewMRight, NewCRight], [boat_to_right(1, 1)|P], l, [[NewMLeft, NewCLeft, NewMRight, NewCRight]|Visited])
    );
    (
        NewCLeft is CLeft - 2, NewCRight is CRight + 2,
        is_valid_step(MLeft, NewCLeft), is_valid_step(MRight, NewCRight),
        \+ member([MLeft, NewCLeft, MRight, NewCRight], Visited),
        move([MLeft, NewCLeft], [MRight, NewCRight], [boat_to_right(0, 2)|P], l, [[MLeft, NewCLeft, MRight, NewCRight]|Visited])
    )).

move([MLeft, CLeft], [MRight, CRight], P, l, Visited):-
    ((
        NewMLeft is MLeft + 1, NewMRight is MRight - 1,
        is_valid_step(NewMLeft, CLeft), is_valid_step(NewMRight, CRight), 
        \+ member([NewMLeft, CLeft, NewMRight, CRight], Visited),
        move([NewMLeft, CLeft], [NewMRight, CRight], [boat_to_left(1, 0)|P], r, [[NewMLeft, CLeft, NewMRight, CRight]|Visited]));
    (
        NewCLeft is CLeft + 1, NewCRight is CRight - 1,
        is_valid_step(MLeft, NewCLeft), is_valid_step(MRight, NewCRight), 
        \+ member([MLeft, NewCLeft, MRight, NewCRight], Visited),
        move([MLeft, NewCLeft], [MRight, NewCRight], [boat_to_left(0, 1)|P], r, [[MLeft, NewCLeft, MRight, NewCRight]|Visited]));
    (
        NewMLeft is MLeft + 2, NewMRight is MRight - 2,
        is_valid_step(NewMLeft, CLeft), is_valid_step(NewMRight, CRight), 
        \+ member([NewMLeft, CLeft, NewMRight, CRight], Visited),
        move([NewMLeft, CLeft], [NewMRight, CRight], [boat_to_left(2, 0)|P], r, [[NewMLeft, CLeft, NewMRight, CRight]|Visited]));
    (
        NewCLeft is CLeft + 2, NewCRight is CRight - 2,
        is_valid_step(MLeft, NewCLeft), is_valid_step(MRight, NewCRight),
        \+ member([MLeft, NewCLeft, MRight, NewCRight], Visited),
        move([MLeft, NewCLeft], [MRight, NewCRight], [boat_to_left(0, 2)|P], r, [[MLeft, NewCLeft, MRight, NewCRight]|Visited]));
    (
        NewMLeft is MLeft + 1, NewCLeft is CLeft + 1, NewMRight is MRight - 1, NewCRight is CRight - 1,
        is_valid_step(NewMLeft, NewCLeft), is_valid_step(NewMRight, NewCRight),
        \+ member([NewMLeft, NewCLeft, NewMRight, NewCRight], Visited),
        move([NewMLeft, NewCLeft], [NewMRight, NewCRight], [boat_to_left(1, 1)|P], r, [[NewMLeft, NewCLeft, NewMRight, NewCRight]|Visited]));
    (
        move([MLeft, CLeft], [MRight, CRight], [boat_to_left(0,0)|P], r, Visited)
    )).
