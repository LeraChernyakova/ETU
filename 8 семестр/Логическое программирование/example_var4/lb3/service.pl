% Динамическое объявление предиката symptom/2
:- dynamic(symptom/2).
:- dynamic(diagnosis/1).

% Предикат для загрузки данных из файла
load_data(File) :-
    open(File, read, Stream),      % Открыть файл для чтения
    read_data(Stream),             % Прочитать данные из файла
    close(Stream).                 % Закрыть файл

% Предикат для чтения данных из потока
read_data(Stream) :-
    repeat,
    read(Stream, Term),            % Прочитать следующий терм из потока
    ( Term == end_of_file          % Если достигнут конец файла, прервать цикл
    ; process_data(Term),          % Обработать прочитанный терм
      fail                          % Продолжить цикл чтения
    ).

% Предикат для обработки прочитанных данных
process_data(end_of_file) :- !.    % Если достигнут конец файла, завершить обработку
process_data(symptom(Symptom, Problem)) :-
    assertz(symptom(Symptom, Problem)). % Добавить факт в базу знаний


 %Определение правила для диагностики
diagnosis(Problem) :- symptom(_, Problem).


diagnose :-
    write('otvetit_na_voprosy_o_simptomah_neispravnosti_kompyutera'), nl,
    diagnose_issue.

% правило для определения у пользователя основноых симптомов
diagnose_issue :-
    symptom(Symptom, Problem),
    write('Est li u vas simptom: '), write(Symptom), write('? (yes/no)'), nl,
    read(Response),
    (Response == yes -> assertz(diagnosis(Problem)); true),
    findall(Prob, diagnosis(Prob), Problems),
    fail. % Continue checking other malfunction symptoms
diagnose_issue :-
    write('Vozmozhnye neispravnosti:'), nl,
    findall(Prob, diagnosis(Prob), Problems),
    list_problems(Problems).
diagnose_issue :-
    !. % стоп когда все симптомы найдены

% правило для вывода причин неисправностей
list_problems([]) :- write('Nevozmozhno opredelit prichinu neispravnosti.').
list_problems([Prob]) :- write('Veroyatnaya prichina neispravnosti: '), write(Prob), write('.'), nl.
list_problems([Prob|Rest]) :-  write(Prob), write(', '), list_problems(Rest).

start_diagnosis :- load_data('symptoms.pl'),retractall(diagnosis(_)),diagnose, retractall(diagnosis(_)).