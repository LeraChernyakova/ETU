/*
	Бригада 1 группы 8382 - Кузина, Кулачкова, Мирончик
	
    Задание 1.
    1. Определить, является ли заданный список упорядоченным по возрастанию или убыванию.

    ?- is_ordered([1,2,3], X).
    X = asc

    ---- 

    Вывод программы: 
        asc - по возрастанию
        desc - по убыванию
        not_ordered - список не отсортирован
*/

is_ordered([], asc).
is_ordered([], desc).
is_ordered([_], asc).
is_ordered([_], desc).
is_ordered([X,Y|Tail], asc) :- X =< Y, is_ordered([Y|Tail], asc).
is_ordered([X,Y|Tail], desc) :- X >= Y, is_ordered([Y|Tail], desc).
is_ordered(Arr, not_ordered) :- \+is_ordered(Arr, asc), \+is_ordered(Arr, desc).

/*
    Задание 2.
    1. Создайте предикат, проверяющий, что дерево является двоичным справочником. 

    ?- is_ordered(tr(2,tr(7, nil, nil),tr(3,tr(4, nil, nil), tr(1, nil, nil)))).
    No

    ----

    Программа поддерживает неполные деревья:
        <Число>                 <=> tr(<Число>, nil, nil)
        tr(<Число>)             <=> tr(<Число>, nil, nil)
        tr(<Число1>, <Число2>)  <=> tr(<Число1>, <Число2>, nil)

    Например:

    ?- is_ordered(tr(1,-1,1)). 
    Yes

    ?- is_ordered(tr(1,1,1)).  
    No

    ?- is_ordered(tr(1,tr(1),1)). 
    No

    ?- is_ordered(tr(1,tr(0),1)). 
    Yes
*/

is_ordered_inner(nil, _, _).
is_ordered_inner(Value, Min, Max) :- integer(Value), is_ordered_inner(tr(Value), Min, Max).
is_ordered_inner(tr(Value), Min, Max) :- is_ordered_inner(tr(Value, nil), Min, Max).
is_ordered_inner(tr(Value, Left), Min, Max) :- is_ordered_inner(tr(Value, Left, nil), Min, Max).
is_ordered_inner(tr(Value, Left, Right), Min, Max) :- is_clamped(Value, Min, Max), is_ordered_inner(Left, Min, Value), is_ordered_inner(Right, Value, Max).

is_clamped(Value, Min, Max) :- integer(Value), (Min = nil,!; Value >= Min), (Max = nil,!; Value < Max).

is_ordered(Tree) :- is_ordered_inner(Tree, nil, nil),!.