parent(tom, bob).
parent(ann, bob).
parent(tom, liza).
parent(bob, mary).
parent(bob, luk).
parent(luk, kate).
parent(bob, sasha).
parent(alice, sasha).
parent(agata, kate).
parent(mary, april).
parent(kirill, april).
parent(ella, kirill).
parent(elza,mary).
parent(olga,agata).
male(kirill).
male(tom).
male(bob).
male(luk).
female(elza).
female(olga).
female(ella).
female(april).
female(kate).
female(liza).
female(mary).
female(ann).
female(sasha).
female(agata).
female(alice).

%Dil невестка, Y мать/отец или брат 
dil(MDil, Y):-
female(Dil),
(
%для сына
male(Child),
parent(Y, Child),
isMarried(Dil, Child);
%для брата брата
male(Y),
male(X),
isSibling(X, Y),
isMarried(Dil, X);
%для брата сестры
female(Y),
male(X),
isSibling(X, Y),
isMarried(Dil, X)
),
female(MDil),
parent(MDil,Dil).

sil(MSil, X):- %MSil - мать зятя
male(Sil),
%для дочери
(
male(X), %FATHER
female(Daughter),
parent(X, Daughter),
isMarried(Daughter,Sil);

%для брата сестры
male(X),
female(Sister),
isSibling(X,Sister),
isMarried(Sister,Sil);

%для сестры сестры
female(X),
female(Sister),
isSibling(X,Sister),
isMarried(Sister,Sil)
),
female(MSil),
parent(MSil,Sil).

mil(Mil,X):-
female(Mil),
female(Wife),
male(X),
isMarried(X,Wife),
parent(Mil,Wife).

isMarried(X, Y):-
parent(X, Z),
parent(Y, Z).

isSibling(X, Y):-
X \= Y,
parent(Z, X),
parent(Z, Y).











