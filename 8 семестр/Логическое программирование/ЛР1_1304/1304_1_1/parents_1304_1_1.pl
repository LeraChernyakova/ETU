% Задание: создать правила для поиска родственных связей указанный в задании.
% Создать правило возвращающее название типа родства для двух людей.
% Вариант 1 - дядя, невестка (жена сына или жена брата).
% Бригада 1 группы 1304 - Чернякова, Ярусова, Байков, Мамин.

% Создание фактов родитель. parent(X,Y). X родитель Y.
parent(tom, bob).
parent(ann, bob).
parent(tom, liza).
parent(bob, mary).
parent(bob, luk).
parent(luk, kate).
parent(liza, elis).
parent(lilo,kate).
parent(taty, luk).

% Создание фактов мужчина.
male(tom).
male(bob).
male(luk).

% Создание фактов женщина.
female(ann).
female(kate).
female(liza).
female(mary).
female(elis).
female(lilo).
female(taty).

% Правило брат. X является братом Y при условии, что X – мужчина, F – родитель и X и Y и при этом X и Y не являются одним человеком.
brother(X,Y):-male(X),parent(F,X),parent(F,Y),X\=Y.

% Правило дядя. X является дядей Y при условии, что X является братом F и при этом F родитель Y.
uncle(X,Y):-brother(X,F),parent(F,Y).

% Правило брак. X и Y состоят в браке при условии, что X и Y родители F и при этом X и Y не являются одним человеком.
marriage(X,Y):-parent(X,F),parent(Y,F),X\=Y.

% Правило невестка. X является невесткой Y при условии, что X – женщина, X состоит в браке с F и Y является родителем F ИЛИ F является братом Y.
daughterinlaw(X,Y):-female(X),marriage(X,F),(parent(Y,F);brother(F,Y)).

% Правило для вывода родственной связи между двумя людьми.
who(X,Y):-
(parent(X,Y),write(X),write(' parent of '),write(Y));
(brother(X,Y),write(X),write(' brother of '),write(Y));
(uncle(X,Y),write(X),write(' uncle of '),write(Y));
(marriage(X,Y),male(X),write(X),write(' married to '),write(Y));
(daughterinlaw(X,Y),write(X),write(' daughterinlaw of '),write(Y)).