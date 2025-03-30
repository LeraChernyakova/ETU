% Файл: expert_system.pl
% Экспертная система "Электронный терапевт"
% Лабораторная работа №3 по дисциплине "Логическое программирование"
% Выполнили: Чернякова В.А., Ярусова Т.В., Байков Е.С., Мамин Р.А.

:- dynamic(known/2).
:- dynamic(disease/2).
% known(Simptom, Answer). Answer может быть: da или net.

% Открывает файл с базой знаний, читает все термы и закрывает поток.
load_database(File) :-
    open(File, read, InStream),      % Открываем файл File для чтения
    process_stream(InStream),         % Рекурсивно читаем все термы из потока
    close(InStream).                  % Закрываем поток после чтения
	
% Рекурсивно считывает термы из открытого потока Stream.
% Если достигнут конец файла (end_of_file), завершает чтение,
% иначе обрабатывает текущий терм и продолжает.
process_stream(Stream) :-
    read(Stream, Term),               % Читаем следующий терм из потока
    ( Term == end_of_file ->
         true                       % Если достигнут конец файла, завершаем чтение
    ;
         handle_term(Term),          % Обрабатываем прочитанный терм
         process_stream(Stream)      % Рекурсивно продолжаем чтение
    ).

% Если Term соответствует факту disease/2, сохраняет его в динамической базе знаний.
% Остальные термы игнорируются.
handle_term(disease(Disease, Symptoms)) :-
    assertz(disease(Disease, Symptoms)).
handle_term(_).  % Остальные термы отбрасываем

%% Основной предикат диагностики

diagnose :-
    retractall(known(_,_)),         % Удаляем все ранее сохранённые ответы
    retractall(disease(_,_)),       % Очищаем динамическую базу данных болезней
    load_database('diseases.pl'),   % Загружаем базу знаний из файла "diseases.pl"
    nl, write('Dobro pozhalovat v ekspertnoj sisteme "Elektronnyj terapevt"!'), nl,
    write('Otvechajte, pozhalujsta, na voprosy, vvodja "da" ili "net".'), nl, nl,
    % Получаем список всех болезней из базы знаний
    findall(D, disease(D, _), Diseases),
    diagnose_diseases(Diseases).    % Запускаем диагностику по списку болезней

% Диагностика по списку заболеваний
% Если список болезней пуст, выводим сообщение об отсутствии диагноза.
% Иначе, для каждой болезни проверяем, подтверждены ли все её симптомы.
diagnose_diseases([]) :-
    nl, write('Po vashim simptomam ne najdeno sootvetstvennoe zabolevanie.'), nl.
diagnose_diseases(Diseases) :-
    findall(D, (member(D, Diseases), check_disease(D)), Matched),
    ( Matched = [] ->
         nl, write('Po vashim simptomam ne najdeno sootvetstvennoe zabolevanie.'), nl
      ;
         nl, write('Vozmozhnye zabolevaniya:'), nl,
         print_list(Matched)
    ).

% Для данной болезни Disease извлекает список симптомов и проверяет,
% что пользователь подтвердил наличие каждого симптома.
check_disease(Disease) :-
    disease(Disease, Symptoms),
    check_symptoms(Symptoms).

% Рекурсивно проверяет, что для каждого симптома из списка Symptoms
% пользователь дал положительный ответ (da).
check_symptoms([]).
check_symptoms([Symptom|Rest]) :-
    ask(Symptom),
    known(Symptom, da),
    check_symptoms(Rest).

% Запрос симптома у пользователя
% Если по данному симптому уже получен ответ, используется он; иначе задаётся вопрос.
% При некорректном вводе (не "da" и не "net") происходит повторный запрос.
% Запрос симптома у пользователя с обработкой некорректного ввода
% Запрос симптома у пользователя с обработкой ошибок ввода через catch/3
ask(Symptom) :-
    known(Symptom, _), !.
ask(Symptom) :-
    format('U vas est simptom "~w"? (da/net): ', [Symptom]), nl,
    catch(read(Response), _Error,
          ( write('Nepravilnyy vvod. Poprobuyte eshche raz.'), nl, ask(Symptom) )),
    ( (Response == da ; Response == net) ->
          asserta(known(Symptom, Response))
    ;
          write('Nepravilnyy vvod. Poprobuyte eshche raz.'), nl,
          ask(Symptom)
    ).


	
% Рекурсивный вывод списка заболеваний
print_list([]).
print_list([H|T]) :-
    write('- '), write(H), nl,
    print_list(T).

% Для запуска диагностики вызовите:
% ?- diagnose.