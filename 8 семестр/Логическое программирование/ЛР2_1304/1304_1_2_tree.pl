% Вариант 1.
% Бригада 1 группы 1304 - Чернякова, Ярусова, Байков, Мамин.
% Задание 2. Деревья: Создайте предикат, проверяющий, что дерево является двоичным справочником.

% Пустое дерево - двоичный справочник
is_ordered_check(nil, _, _):-!.

% Проверка на соответствие определению двоичного справочника
% Лист - просто число, не tr(VALUE, nil, nil)
is_ordered_check(Value, Min, Max):-
integer(Value),(Max = nil,!; Value < Max),(Min = nil,!; Value > Min).

% Проверка на соответствие определению двоичного справочника
% Рекурсивные вызовы для проверки всех правых и левых поддеревьев
is_ordered_check(tr(Root, Left, Right), Min, Max):- 
(Max = nil,!; Root < Max),(Min = nil,!; Root > Min), 
is_ordered_check(Left, Min, Root), is_ordered_check(Right, Root, Max). 

% Начальный вызов программы
% nil - в качестве начального значения для Min и Max
is_ordered(BTree):-is_ordered_check(BTree, nil, nil).