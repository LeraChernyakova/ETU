:- dynamic(phone/3). % Телефоны будем динамически считывать из бд
:- dynamic(dbLoad/0). % Факт о загруженной бд добавим динамически
% список всех доступных функций телефонов.
fLst(['obshchenie', 'fotografiya', 'videozvonki', 'multimedia', 'igry', 'mobilnyy_ofis', 'navigatsiya', 'monitoring_zdorovya']).

% Выбор осуществляется выбором цифры, поэтому
% необходимо описать предикат взятия элемента списка по индексу
getByIndex([X], 0, X):-!.
getByIndex([H|_], 0, H):-!.
getByIndex([_|T], I, E) :- NewIndex is I-1, getByIndex(T, NewIndex, E).

% Добавление факта о телефоне из бд.
addPhoneFact(Stop, Stop):- !.
addPhoneFact(Index, Stop):-
    read(Fact), % Считываем факт
    Fact \== end_of_file, % если не достигли конца файла продолжаем
    assertz((Fact)), % Добавляем полученный факт
    Tmp is Index + 1, % Увеличиваем счётчик
    addPhoneFact(Tmp, Stop). % Раскручиваем рекурсию

% Метод для управления счётчиком фактов
addPhoneFacts:-
    addPhoneFact(0, 22),
    true. % добавлено, чтобы метод не возвращал no 

load_db:-
    \+dbLoad,!, % если бд не загружена, то загружаем
    see('phones.pl'), % открываем файл
    addPhoneFacts, % Добавляем факты
    seen, % Закрываем файл
    assertz((dbLoad)). % если дошли до сюда, то добавляем факт о загрузке дб

load_db:- true. % если бд загружена, то возвращаем истину

% Красиво выводим выбор для пользователя
printChoiceFunction(_, [ ]):- !.
printChoiceFunction(N, [H|T]):-
    write(N), write('.'), write(' '), write(H), nl,
    N1 is N + 1,
    printChoiceFunction(N1, T).

% Оформляев вывод функций
printChoice:-
    write('Vyberite nuzhnuyu funktsiyu:'), nl,
    fLst(L),
    printChoiceFunction(1, L),
    write('0. exit'), nl, nl. % Оставляем пользователю возможность закончить выбор

% Считываем выбор пользователя
makeChoice(Choice):-
    read(Num), Num > 0, !, % Если выбрана функция, то определяем что выбрал пользователь
    Index is Num - 1, fLst(L), getByIndex(L, Index, Choice).

% Функция отрисовки функций и последующий выбор одной из функций
userChoice(Choice):-
    printChoice,
    makeChoice(Choice),!.

% Функция для фильтрации телефонов по их функциям    
getFilteredPhones(FuncList, Phones) :-
    true, % checkFunctions может не найти у телефона функцию из списка, возвращаем истину
    % Используем предикт findall из стандартной библиотеки для поиска телефонов с указанными функциями
    findall(Name, (phone(Name, Functions, _), checkFunctions(FuncList, Functions)), Phones).

% Функция проверка, что в функциях телефона есть необходимые функции  
checkFunctions([], _).
checkFunctions([Func|T], Functions) :-
    member(Func, Functions),  % Используем предикат нахождения элемента в списке
    checkFunctions(T, Functions). % продолжаем искать оставшиеся предикаты

% Красивый вывод подходящих телефонов 
printPhones([ ]):- !.
printPhones([H | T]):-
    phone(H, Funcs, Descr),
    write('Model: '), write(H), nl,
    write('Funkcii: '), write(Funcs), nl,
    write('Opisanie: '), write(Descr), nl, nl,
    printPhones(T).

% Функция объеденяющая в себе отрисовку, выбор пользователя и последующую логику программы
userStart(FuncList):-
    userChoice(CurrentChoice), !,
    getFilteredPhones([CurrentChoice | FuncList], Phones),
    printPhones(Phones),
    userStart([CurrentChoice | FuncList]).

% Вход в программу
start:-
    load_db, % загружаем бд перед использованием 
    userStart([]). % запускаем основную логику программы