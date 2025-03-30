/*
	Задание:
	Найти минимальный элемент в заданном списке
	?- min_elem([3,7,1,9,2], X).
	X = 1
	
	Бригада 1 группы 8382 - Кузина, Кулачкова, Мирончик
*/

min_elem([Elem], Elem).
min_elem([Elem | Tail], TailMin) :- min_elem(Tail, TailMin), Elem >= TailMin.
min_elem([Elem | Tail], Elem) :- min_elem(Tail, TailMin), Elem < TailMin.

:-op(100, xfx, min).
Elem min X:- min_elem(X, Elem).