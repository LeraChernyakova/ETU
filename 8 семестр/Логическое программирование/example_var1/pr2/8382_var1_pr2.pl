% Практика 2 - Вариант 1
% Создайте предикат, вычисляющий неотрицательную степень целого числа.
% Бригада 1 группы 8382 - Кузина, Кулачкова, Мирончик

% Проверяем, что показатель степени задан и является числом
pow(_, N, _) :- var(N), write('exponent is not a number').
pow(_, N, _) :- \+integer(N),write('exponent is not integer').

% Проверяем, что основание степени задано и является числом
pow(X, _, _) :- var(X), write('base is not a number').
pow(X, _, _) :- \+integer(X),write('base is not integer').

pow(_, 0, 1).
pow(X, N, Y) :- nonvar(N), nonvar(X), N > 0, N1 is N - 1, pow(X, N1, Y1), Y is X * Y1.