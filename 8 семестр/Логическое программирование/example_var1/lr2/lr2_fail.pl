min_elem([Head|Tail], TailMin) :- min_elem(Tail, TailMin), TailMin =< Head, !.
min_elem([Head|_], Head).

/*Неверный ответ выдается, если правило выглядит как

min_elem([x1,x2,x3,...,xn], x), где xk,x - конкретизированные переменные,

и существует такое xk == x, что для всех m < k: xm < xk*/