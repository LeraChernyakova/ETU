colour(red). % красный
colour(black).% черный
colour(lightblue).% голубой
colour(darkblue).% синий
colour(white).% белый

colour_or_colour(A,B,C) :- C = A ; C = B. % для удобства соотношения владельца машин и их цветов

solve(Ivan,Petr,Max,Sacha,Boris) :-
    Ivan = red, % у Вани красная машина 
    colour(Petr), \+ Petr = Ivan,% у Петра цвет машины не как у Вани 
 \+ member(Petr, [black, darkblue, lightblue]), % у Петра цвет машины не черный, не синий, не голубой
    colour_or_colour(black, darkblue, Max), % у Макса черная и синяя машины
\+ Max = Ivan, \+ Max = Petr, % при этом цвет машины Макса не как у Вани и Петра
    colour(Sacha), \+ member(Sacha, [Ivan, Petr, Max]),% у Саши цвет не как у Вани, Петра , Макса
    colour_or_colour(white, darkblue, Boris),% у Бориса белая и синяя машины
    \+ member(Boris, [Ivan, Petr, Max, Sacha]). % при этома цвет не как у кого либо другого

goal :- solve(Ivan,Petr,Max,Sacha,Boris), write('Ivan:') ,write(Ivan), write(' '),write('Petr:'), write(Petr), write(' '), % вывод результата
write('Max:'),write(Max), write(' '),write('Sacha:'), write(Sacha), write(' '),write('Boris:'), write(Boris), nl.
