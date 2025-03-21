# Исследование решений динамическим алгоритмом задач коммивояжера и двухуровневой задачи о назначении в условиях их сведения друг к другу

Ключевые слова: граф, задача коммивояжера, двухуровневая задача о назначении, точность, вычислительная сложность

## Аннотация
Текущий файл является демонстрацией формата решения. В данной работе была рассмотрена задача коммивояжера и методы ее решения. Были выбраны критерии сравнения, такие как вычислительная сложность, точность решения и тип задач. В процессе анализа выяснилось, что ни один из изученных алгоритмов не соответствует всем этим критериям. В результате были определены новые требования к исследуемому алгоритму.

## Введение

Решения для сложных задач оптимизации из класса NP-трудных широко используются в различных областях.Алгоритм решения задачи коммивояжера применяется для оптимизации затрат на транспортировку и логистику, а так же для поиска отимального пути в навигации[1].Двухуровневая задача о назначениях позволяет более гибко управлять распределением задач и ресурсов, что может пригодиться в производственных задачах на предприятиях.Нахождение более эффективных алгоритмов для решения этих задач приведет к существенной оптимизации текущих процессов и систем.

Целью данной статьи является изучение и анализ существующих алгоритмов решения задачи коммивояжера с последующим применением динамического алгоритма в контексте её связи с двухуровневой задачи о назначении. Объектом исследования выступает алгоритм решения задачи коммивояжера, в то время как предметом исследования является оценка эффективности динамического алгоритма при решении объединённых задач коммивояжера и двухуровневой задачи о назначении.

В ходе проведения исследования были решены задачи, перечисленные ниже.
1. Обзор существующих алгоритмов и методов решения задачи коммивояжёра и двухуровневой задачи о назначении.
2. Определение критериев сравнения эффективности алгоритмов и методов.
3. Сравнение выбранных алгоритмов и методов по выбранным критериям.

## Обзор предметной области

### Принципы отбора аналогов

В роли сравнительных аналогов были рассмотрены алгоритмы и методы, применяемые для решения задачи коммивояжера и двухуровневой задачи о назначении. Основным критерием при выборе аналогов служили пределы применимости соответствующих алгоритмов. Подбор аналогов осуществлялся с использованием ресурсов Google Scholar, электронной библиотеки eLibrary и поисковой системы Google. Для поиска аналогов применялись следующие запросы: "задача коммивояжёра", "двухуровневая задача о назначении", "two-level assignment problem", "tsp problem", "travelling salesman problem".

### Метод полного перебора

Естественный способ решения подобного рода задач. Относится к классу методов поиска решения исчерпыванием всевозможных вариантов.Этот метод обеспечивает оптимальные результаты, однако высокие вычислительные затраты делают его ограниченно применимым в решении практических задач из-за необходимости обработки больших объемов входных данных. [1].

### Муравьиный алгоритм
В статье А. А. Кажарова, В. М. Курейчика "Муравьиные алгоритмы для решения транспортных задач" представлен метаэвристический оптимизационный алгоритм, вдохновленный поведением муравьев при поиске кратчайшего пути от места к месту[2].Муравьи случайным образом выбирают маршруты в графе,при этом откладывая на пути специальное химическое вещество - феромон. Феромоны обновляются в зависимости от эффективности маршрутов.При выборе направления движения муравей исходит
не только из желания пройти кратчайший путь, но и из опыта других муравьев, информацию о
котором получает непосредственно через уровень феромонов на каждом пути.  Постепенно муравьи склонны выбирать кратчайшие маршруты, что приводит к нахождению оптимального решения задачи.
### Метод ветвей и границ

В статье Костюка Ю.Л. “Эффективная реализация алгоритма решения задачи коммивояжёра методом ветвей и границ” [3] автор предлагает решение на основе метода ветвей и границ Литтла [4].В модифицированной версии алгоритма осуществляется отсечение частично построенных маршрутов в процессе построения дерева поиска, если предварительная оценка их длины превышает или равна длине ранее построенного наилучшего полного маршрута.

### Жадный алгоритм

Для приближенной оценки жадным алгоритмом производится анализ всех рёбер полного графа, исходящих из вершин. Выбираются наименьшие рёбра в количестве, соответствующем числу вершин. Если эти рёбра образуют гамильтонов цикл, то такое решение считается результатом задачи[5]. В статье В статье Чусовлянкина А.А., Морозенко В.В. “Анализ точности и времени решения задачи коммивояжера с помощью "антижадного" алгоритма” приводится экспериментальная оценка точности решения задачи жадным алгоритмом [6].

### Антижадный алгоритм

В статье Чусовлянкина А.А., Морозенко В.В. “Анализ точности и времени решения задачи коммивояжера с помощью "антижадного" алгоритма” рассматривается алгоритм, основывающийся на последовательном приближении к оптимальному решению за счет удаления ребер в графе по определенным правилам при помощи матрицы состояний [6]. На каждом этапе алгоритма выполняется поиск самого длинного нерассмотренного ребра в графе. Это ребро может либо быть выбрано и зафиксировано, либо удалено из графа, при этом в матрице состояний соответствующим образом отмечается изменение. Если невозможно ни зафиксировать, ни удалить ребро, то решение, полученное на предыдущем этапе, оказывается неверным.

## Критерии сравнения аналогов

### Точность решения

Данный критерий измеряет степень среднего приближения решения алгоритма к оптимальному значению. Оценка осуществляется путём сравнения найденного алгоритмом маршрута с оптимальным маршрутом

### Вычислительная сложность

Данный критерий оценивает зависимость объема работы, которая выполняется некоторым алгоритмом, от размера входных данных (в данном случае — от размерности графа и количества вершин).

### Тип задачи

Данный критерий определяет типы задачи для которых предназначен алгоритм и на которых алгоритм демонстрирует точность выше по сравнению с другими типами. Задача коммивояжера делится по типам графов на асимметричные, симметричные, метрические, евклидовы и другие.

## Таблица сравнения по критериям

| Аналог                           | Вычислительная сложность | Точность решения, % | Тип задачи    |
|----------------------------------|--------------------------|---------------------|---------------|
| Метод полного перебора           | O(n!)                    | 100                 | любая         |
| Муравьиный алгоритм              | O(n^2)                   | 92                  | асимметричная |
| Метод ветвей и границ            | O(n^2 *с^n)              | 95                  | асимметричная |
| Жадный алгоритм                  | O(n^2)                   | 80                  | любая         |
| Антижадный алгоритм              | O(c^n)                   | 97                  | евклидова     |

## Выводы по итогам сравнения

Из представленных алгоритмов и методов ни один не удовлетворяет всем требованиям, включая полиномиальную сложность, точность решения близкую к 100%, и применимость для всех типов задач. Наименьшую вычислительную сложность имеет жадный алгоритм, однако его точность невысока. Метод полного перебора обеспечивает высокую точность, но его вычислительная сложность чрезмерно высока для практического применения. Другие методы обладают более высокой точностью и меньшей сложностью, чем метод полного перебора, но они могут быть эффективно применены только в определенных случаях. Таким образом, нет универсального алгоритма или метода, который бы полностью соответствовал всем требованиям задачи.

## Выбор метода решения

Исходя из поставленной цели и результатов анализа сравнения методов и аналогов и поставленной цели была сформулирована следующая гипотеза:
- разрабатываемый и исследуемый алгоритм решения задачи коммивояжёра и о двухуровневой задачи и о назначении в условиях сведения друг к другу должен обладать свойствами, перечисленными ниже.
    1. Алгоритм решает задачу методом динамического программирования.
    2. Вычислительная сложность такого алгоритма не превышает полиномиальную.
    3. Точность решения не меньше 90%.

## Заключение

В научной статье был проведён обзор методов и алгоритмов для решения задачи коммивояжера. Пять аналогов были отобраны для сравнения по трём критериям: вычислительная сложность, точность решения и тип задачи. Однако ни один из этих методов не является универсальным по всем критериям. Исследование привело к формулировке гипотезы о свойствах разрабатываемого алгоритма для решения задачи коммивояжёра и двухуровневой задачи и назначении. Эти свойства включают метод динамического программирования, низкую вычислительную сложность (не более полиномиальной) и высокую точность решения (не менее 90%).

Более того, исследование может быть расширено путём включения других аналогов и добавлением новых критериев сравнения для более глубокого изучения свойств разрабатываемого алгоритма.

## Список использованных источников

1. Володина Е.В., Студентова Е.А. Практическое применение алгоритма решения задачи коммивояжера // ИВД. 2015. №2-2. URL: https://cyberleninka.ru/article/n/prakticheskoe-primenenie-algoritma-resheniya-zadachi-kommivoyazhera
2. Saiyed A. R. The traveling salesman problem // Indiana State University. – 2012. – Т. 2. – С. 1-15.
3. Кажаров, А. А. Муравьиные алгоритмы для решения транспортных задач / А. А. Кажаров, В. М. Курейчик // Известия Российской академии наук. Теория и системы управления. – 2010. – № 1. – С. 32-45
4. Костюк Юрий Леонидович Эффективная реализация алгоритма решения задачи коммивояжёра методом ветвей и границ // ПДМ. 2013. №2 (20).
5. Little J. D. C., Murty K. G., Sweeney D. W., and Karel C. An Algorithm for the Traveling Salesman Problem // Operations Research. 1963. No. 11. P. 972–989.
6. Gutin G.,Yeo A. The Greedy Algorithm for the Symmetric TSP. University of London, 2002. 1–2.
7. Чусовлянкин А.А., Морозенко В.В. Анализ точности и времени решения задачи коммивояжера с помощью "антижадного" алгоритма // Вестник Пермского университета. Серия: Математика. Механика. Информатика. 2016. №4 (35).
