# Задание 2

## Статья

Название: Defending ChatGPT against Jailbreak Attack via Self-Reminder

Для цитирования: Wu, Fangzhao & Xie, Yueqi & Yi, Jingwei & Shao, Jiawei & Curl, Justin & Lyu, Lingjuan & Chen, Qifeng & Xie, Xing. (2023). Defending ChatGPT against Jailbreak Attack via Self-Reminder. 10.21203/rs.3.rs-2873090/v1.

URL: <https://www.google.com/url?q=https://www.researchgate.net/publication/371612143_Defending_ChatGPT_against_Jailbreak_Attack_via_Self-Reminder&sa=D&source=editors&ust=1710357632901019&usg=AOvVaw1b4nBC18ZvzFr38rfH2PVa>

## Характеристика используемых данных

### Методы проведения эксперимента

В данной статье описан натурный эксперимент. Используется реальное ChatGPT API gpt-3.5-turbo-0301. В него загружаются заранее подготовленные промпты, нацеленные на обход защиты ChatGPT. Эксперимент проводится как над защищенным методом Самонапоминания ChatGPT, так и над ChatGPT без защиты. Полученные ответы анализируются на предмет успешности атаки и сравниваются.

### Используемые данные и их характеристики

Для проведения эксперимента использовался набор данных, состоящий из 540 образцов промптов, каждый из которых состоит из двух отдельных элементов:

1. Jailbreak-промпта - специального запроса, направленного на обход моральных установок ChatGPT. Источником промптов стал [Jailbreak Website](https://www.jailbreakchat.com/) c 76 jailbreak-промптами, из которых были отсеяны те, что показали эффективность атак менее 20% или требовали ручного исправления под конкретные вредоносные инструкции;
2. Вредоносной инструкции - конкретного вредоносного запроса для получения вредоносного ответа. В набор данных были включены 10 различных вредоносных инструкций, направленных на различные цели. Данные инструкции были разделены на две категории: дезинформация и токсичные инструкции.

Кроме того, для оценки влияния защиты на стандартные запросы был использован датасет бенчмарка GLUE (General Language Understanding Evaluation).

### Способы обработки измерений

Эксперимент проводился для измерения следующих показателей:

1. Оценки эффективности стандартной атаки;
2. Оценка эффективности адаптивной атаки;
3. Исследование влияния абляции;
4. Исследование влияния тона.
5. Побочных эффектов для стандартных запросов;

Формат эксперимента для измерения показателей 1-4 имел следующий вид: эксперимент повторялся по 5 раз для различных промптов, для исследования применялся ChatGPT API gpt-3.5-turbo-0301.

Для полученных в ходе эксперимента результатов рассчитывался ASR - коэффициент успешности атаки, далее эти показатели сравнивались между собой.

Для того, чтобы оценить эффективность адаптивных атак, дополнительно авторами промпты дополнялись формулировками, которые были направлены на обход механизма защиты методом Self-Reminder. Пример адаптивных атак представлен на рис. 3 статьи.
Далее проводился эксперимент в формате, описанном выше. На основе полученных данных вычислялся ASR для двух вариантов адаптивных атак, а так же для атаки без адаптации. Полученные результаты сравнивались между собой.

Для исследования влияния абляции менялся подход к защите: вместо инкапсуляции пользовательского запроса в системный промпт с самонапоминанием использовались схемы только-префикс и только-суффикс. Далее проводился стандартный эксперимент и вычислялся ASR для защищенного режима, режима без защиты, защищенного только суффиксом и только префиксом.
Полученные результаты сравнивались между собой.

Для исследования влияния тона системные промпты дополнялись предупрежденим и похвалой. Далее повторялся эксперимент и вычислялся ASR для стандартного напоминания, для напоминания в похвальном тоне и для напоминания в предупреждающем тоне. Полученные результаты сравнивались между собой.

Для исследования побочных эффектов для стандартных запросов использовался бенчмарк GLUE, по его результатам рассчитаны следующие показатели:

1. Оценка F1;
2. Корреляция Спирмана;
3. Корреляция Мэттьюса;
4. Точность.

Полученные показатели сравниваются для ChatGPT с защитой и без нее.

### Правомерность выводов по итогам эксперимента

Эксперименты проводились на одинаковых данных датасета, что исключает влияние различных входных данных на полученные результаты. Кроме того, эксперимент проводился несколько раз и для анализа использовались средние значения, что снижает влияние того, что LLM являются вероятностными алгоритмами. Исходя из этого, можно сделать вывод о том, что полученные результы правомерны.

## Характеристика выводов

### Соответствие результата и цели/задачам статьи

#### Сравнение достигнутых результатов и поставленных целей

По анализу итога работы и поставленных целей и задач можно сделать вывод, что авторы успешно достигли желаемого результата, представив эффективный и простой вариант защиты ChatGPT от Jailbreak атак, путем создания набора данных Jailbreak, оценки эффективности метода и сравнения производительности ChatGPT с защитой и без нее. Достижение своей цели авторы отмечают в разделе _"Discussion"_.

#### Степень раскрытия результатов

Цель авторов статьи - представить эффективный и простой вариант защиты ChatGPT от Jailbreak атак.

В разделе _"Discussion"_ они результируют, что представленный способ защиты восполнит пробелы в имеющихся исследованиях. Также подчеркивают эффективность метода, который раскрывает потенциал LLM для защиты за счет уже имеющихся у них возможностей, в чем и заключается простота. Данные рассуждения авторов подчеркивают, что им удалось добиться поставленной цели в полной мере.

Авторы статьи ставили перед собой определенный ряд задач для достижения цели.

1. Создать набор данных Jailbreak для проверки устойчивости метода.
В качестве результата выполнения данной задачи авторы в разделе _"Result"_ подразделе _"Dataset Construction"_ описывают процесс создания 540 образцов для набора данных и описывают, что они из себя представляют: это вредоносная инструкция и призыв к Jailbreak. Такие данные помогут оценить защиту методом от потенциальных противников. Конкретные вредоносные инструкции и примеры образцов, используемые в исследовании, авторы представили в таблице 1 и на рисунке 1 соотвественно.

2. Оценить эффективность защиты ChatGPT методом "Самонапоминания".
Результатом выполнения данной задачи стало проведение сравнительного анализа эффективности защиты на данных, созданных в рамках предыдущей задачи. Авторы представили этот анализ в разделе _"Result"_ подразделе _"Performance Evaluation"_. В ходе анализа авторами было выявлено, как защита GhatGPT описываемым методом снижает успешность Jailbreak атаки, а также различие показателя успешности атаки на ChatGPT с защитой при разных вредоносных инструкциях. В среднем защита методом Self-Reminder снижает успешность атак с 67.21% до 19.34%, но более точные результаты в зависимости от комбинации подсказок и вредоносных инструкци приведены для ознакомления в статье на рисунке 2 и в таблице 2.

3. Сравнение производительности ChatGPT с защитой и без нее.
Сравнительный анализ производительности ChatGPT представлен авторами в качестве результата текущей задачи. Данный анализ содержится в разделе _"Result"_ подразделе _"Side Effects on Regular User Queries"_. В качестве эксперимента авторы замеряли производительность в течении пяти раз на задачах по пониманию естественного языка. Конкретные полученные значения и сравнение авторы приводят в 3 таблице статьи. В результате сделан вывод, что производительность обычного ChatGPT и с защитой сопоставимы.

Таким образом, так как каждый из разделов, описывающих задачи, сопровождается кратким подытогом, и в заключении приведён вывод, объединяющий все промежуточные результаты в конечный, то можно говорить о том, что степень раскрытия результатов можно оценить как высокую.

#### Направления дальнейших исследований

Авторы рассматривают направления для дальнейших исследований в данной предметной области. Они планируют разработать схему представленного способа защиты, которая будет более адаптируемой, а также более продвинутые фреймворки.

> Therefore, in future work, we aim to develop more adaptable self-reminding schemes and advanced frameworks that can further improve safety, trustworthiness, and responsibility without compromising functionality or generating uninformative claims in LLMs.

### Достигнутый результат

#### Чем является результат

Поскольку ChatGPT имеет тенденцию к сильному следованию инструкциям многие jailbreak атаки используют это качество против языковой модели. Авторами предложен простой, но довольно эффективный способ снизить процент успешности атак. Результатом их исследования является техника "самонапоминания" для ChatGPT. Ее суть заключается в том, что каждый промпт, отправленный пользователем, обрамляется в напоминине для AI. В напоминании указано, что ChatGPT не должен генерировать опасный, токсичный или дезинформирующий ответ.

Первоначально тесты сравнивают различные вариации jailbreak атак и их успешность. Авторы демонстрируют сравнение успешности jailbreak атак с использованием "самонапоминания" и без. Затем проверяется успешность jailbreak атак при применении различных способов самонапоминания. Были использованы вариации напоминания в начале и в конце промта, а также отдельно в конце и в начале. Также проведены тесты, которые показывают сравнение разных формулировок самонапоминания, среди которых были: обычное напоминание, поощрение и предупреждение.

Авторы отмечают, что метод не лишен недостатков, потому что многообразие запросов пользователя огромно и невозможено покрыть все возможные сценарии.

#### Характер результата

Результат является прикладным, поскольку его можно применять для предупреждения Jailbreak атак и защиты от них.

#### Характеристики результата

Разработанный авторами метод демонстрирует снижение успешности Jailbreak атак. При обычных пользовательских запросах показатель успешности составляет примерно 67%, а при запросах обернутых в специальные ремарки указывающие ChatGPT на то, что он не должен наносить вред или дизинформировать пользователя своим ответом, успешность атак снижена примерно в три раза (~19%). Также были проведены исследования с психологической точки зрения, где в обертке были использованы слова напоминающие, предупреждающие и поощрающие ChatGPT. В среднем напоминание и поощрение работают лучше нежели предепреждения.

#### Границы применимости результата и степень его универсальности

Результат применим для любых промптов, которые имеют в себе цель взломать этичность ответа. Однако степень универсальности не высока, поскольку данная техника, пока что не может перекрыть все многообразие пользовательских запросов.

#### Недостатки полученного решения

Метод зависим от конкретного запроса пользователя. Если запрос содержит в себе наличие слов, которые указываю ChatGPT игнорировать инструкции сверху, часть из таких запросов может пройти, что указывает на успешность Jailbreak атаки и неуспешность метода самонапоминания.

#### Нераскрытые вопросы

При анализе статьи возникли вопросы, которые авторы могли бы раскрыть:

- Какие виды Jailbreak атак существуют и как на них реагирует данный метод? (Например, использование шантажа или просьба написать вредоносную информацию на выдуманном языке)
- Будет ли данный метод успешен на других LLM?
