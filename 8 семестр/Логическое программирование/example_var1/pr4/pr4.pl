/*
    Входные точки в программу - fast_consult и smart_consult
*/

:- dynamic(illness/2).
:- initialization(load_default_illnesses).

% Вспомогательные методы. Они в принципе есть в swipl, но GNU Prolog немножко тупее 

pairs_values([], []).
pairs_values([_-Value | Other], [Value | OtherValues]) :-
    pairs_values(Other, OtherValues).

map_list_to_pairs(_, [], []).
map_list_to_pairs(ExtractKeyFunction, [ListItem | ListTail], [PairsListItemKey-ListItem | PairsListTail]) :-
    map_list_to_pairs(ExtractKeyFunction, ListTail, PairsListTail),
    call(ExtractKeyFunction, ListItem, PairsListItemKey).

intersection([], _, []).
intersection([Elem1 | Tail1], List2, Intersection) :-
    intersection(Tail1, List2, TailIntersection),
    (memberchk(Elem1, List2), Intersection = [Elem1 | TailIntersection], !;
    Intersection = TailIntersection).

% Базовая информация о заболеваниях

add_illness_symptoms(_, []).
add_illness_symptoms(Name, [Symptom | Tail]) :-
    add_illness_symptoms(Name, Tail),
    (\+illness(Name, Symptom) *-> assertz(illness(Name, Symptom))).

load_default_illnesses :-
    retractall(illness(_,_)),
    add_illness_symptoms('Prostuda', ['Temperatura']),
    add_illness_symptoms('Korona', ['Temperatura', 'Headache']),
    add_illness_symptoms('Autism', ['Knife in head']).

all_illnesses(Illnesses) :-
    findall(A, illness(A,_), Temp),
    sort(Temp, Illnesses).

all_symptoms(Symptoms) :-
    findall(A, illness(_,A), Temp),
    sort(Temp, Symptoms).

all_illness_symptoms(Illness, IllnessSymptoms) :- 
    findall(A, illness(Illness, A), Temp),
    sort(Temp, IllnessSymptoms).

% Логика по определению заболеваний пациента

find_illness_probability(Illness, PatientSymptoms, Probability) :-
    all_illness_symptoms(Illness, IllnessSymptoms),
    intersection(PatientSymptoms, IllnessSymptoms, MatchedSymptoms),
    length(MatchedSymptoms, MatchedCount),
    length(IllnessSymptoms, MaxCount),
    Probability is MatchedCount / MaxCount.

make_illnesses_conclusions([], _, []).
make_illnesses_conclusions([Illness | TailIllnesses], PatientSymptoms, Conclusions) :-
    make_illnesses_conclusions(TailIllnesses, PatientSymptoms, TailConclusions),
    find_illness_probability(Illness, PatientSymptoms, Probability),
    (Probability > 0 -> 
        Conclusions = [illness_conclusion(Illness, Probability) | TailConclusions]; 
        Conclusions = TailConclusions).

extract_conclusion_probability(illness_conclusion(_, Probability), Probability).
find_illnesses(RawPatientSymptoms, SortedConclusions) :-
    sort(RawPatientSymptoms, PatientSymptoms),
    all_illnesses(Illnesses),
    make_illnesses_conclusions(Illnesses, PatientSymptoms, Conclusions),
    map_list_to_pairs(extract_conclusion_probability, Conclusions, ConclusionsPairs),
    keysort(ConclusionsPairs, SortedConclusionsPairs),
    pairs_values(SortedConclusionsPairs, SortedConclusions).

% Вывод заключений

write_conclusions([]).
write_conclusions([illness_conclusion(Illness, Probability) | Other]) :-
    write_conclusions(Other),
    format('You have ~w with ~w probability\n', [Illness, Probability]).


% Упрощенное определение болезни (заранее заданы симптомы)

fast_consult(PatientSymptoms) :-
    find_illnesses(PatientSymptoms, Conclusions),
    length(Conclusions, ConclusionsCount),
    (ConclusionsCount > 0 -> 
        write_conclusions(Conclusions);
        write('You have not any illnesses\n')).

% Поспрашиваем юзера, что у него болит?

ask_symptoms([],[]).
ask_symptoms([Symptom | Other], PatientSymptoms) :- 
    format('Do you have a ~w? ', [Symptom]),
    read(Answer),
    (Answer = 'fuck', write('Okey, but results might be not so accurate.\n'), PatientSymptoms = [], !;
    Answer = 'yes', ask_symptoms(Other, OtherSymptoms), PatientSymptoms = [Symptom | OtherSymptoms], !;
    Answer = 'no', ask_symptoms(Other, PatientSymptoms), !;
    write('Wtf have you written??? I want to hear just "yes" or "no" (and don''t forget to add "." at the end).\n'), ask_symptoms([Symptom | Other], PatientSymptoms), !
    ).

smart_consult :- 
    all_symptoms(Symptoms),
    ask_symptoms(Symptoms, PatientSymptoms),
    write('Hmm, let me think a little...\n'),
    fast_consult(PatientSymptoms).