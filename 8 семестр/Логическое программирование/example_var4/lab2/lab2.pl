
decimal_to_binary(0, [0]). % терминальное состояние рекурсии
decimal_to_binary(1, [1]). % терминальное состояние рекурсии
decimal_to_binary(N, BinaryList) :- % функция перевода числа N в двочный список BinaryList
    N > 1, % если число меньше 1, функция завершается базовыми случаями
    Quotient is N div 2, % целая часть от деления
    Remainder is N mod 2, % остаток от деления
    decimal_to_binary(Quotient, Rest), % рекурсивный вызов для целой части от деления,
					% чтобы найти двоичное представление этой части 
    append(Rest, [Remainder], BinaryList). % двоичное представление целой части с младшим битом,
					   %чтобы получить полное двоичное представление числа N.


countLeafs(nil, 0).  % Базовый случай: листьев в пустом дереве 0.

countLeafs(tr(_, nil, nil), 1).  % Базовый случай: если узел - лист.

countLeafs(tr(_, Left, Right), Count) :-
    countLeafs(Left, LeftCount),   % Рекурсивно считаем листья в левом поддереве.
    countLeafs(Right, RightCount), % Рекурсивно считаем листья в правом поддереве.
    Count is LeftCount + RightCount. % Суммируем количество листьев в обоих поддеревьях.

 