# Ответы на ключевые вопросы

## Проблема
Оценка селективности запросов в корпоративных реляционных СУБД при наличии корреляций между атрибутами данных.

## Актуальность
Точность оценки селективности запросов играет ключевую роль в процессе оптимизации выполнения запросов в реляционных системах управления базами данных (СУБД) [1]. Оптимизатор выбирает наиболее эффективный план исполнения на основе статистической информации [2], от чего напрямую зависит производительность системы. В условиях постоянного роста объемов данных и усложнения структуры запросов погрешности в оценке селективности могут приводить к выбору неоптимальных планов выполнения, что существенно снижает производительность СУБД [3]. Учет корреляций между атрибутами при оценке селективности позволит повысить точность оценок и, как следствие, улучшить качество оптимизации запросов, что особенно важно при работе с большими объемами данных.

## Объект исследования
Методы статистической оценки селективности запросов в корпоративной реляционной СУБД.

## Предмет исследования
Точность оценки селективности запросов при использовании корреляционного анализа между атрибутами данных.

## Цель
Разработка методов повышения точности оценки селективности SELECT-запросов, включающих операции соединения таблиц (JOIN), агрегации (GROUP BY) и фильтрации по нескольким атрибутам в корпоративных реляционных СУБД на основе корреляционного анализа данных.

## Задачи
1. Обзор существующих методов оценки селективности запросов.
2. Определение критериев для сравнения существующих методов.
3. Исследование влияния корреляций между атрибутами на точность оценки селективности.

## Список использованных источников
1. Wu W. et al. Towards a better cardinality estimation //Proceedings of the 2020 ACM SIGMOD International Conference on Management of Data. – 2020. – С. 2006-2021.
2. Lan H., Bao Z., Peng Y. A survey on advancing the dbms query optimizer: Cardinality estimation, cost model, and plan enumeration //Data Science and Engineering. – 2021. – Т. 6. – С. 86-101.
3. Leis V. et al. How good are query optimizers, really? //Proceedings of the VLDB Endowment. – 2015. – Т. 9. – №. 3. – С. 204-215.
