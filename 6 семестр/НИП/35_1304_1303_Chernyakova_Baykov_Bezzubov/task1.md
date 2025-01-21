# Задание 1

## Статья

Название: Defending ChatGPT against Jailbreak Attack via Self-Reminder

Для цитирования: Wu, Fangzhao & Xie, Yueqi & Yi, Jingwei & Shao, Jiawei & Curl, Justin & Lyu, Lingjuan & Chen, Qifeng & Xie, Xing. (2023). Defending ChatGPT against Jailbreak Attack via Self-Reminder. 10.21203/rs.3.rs-2873090/v1.

URL: https://www.google.com/url?q=https://www.researchgate.net/publication/371612143_Defending_ChatGPT_against_Jailbreak_Attack_via_Self-Reminder&sa=D&source=editors&ust=1710357632901019&usg=AOvVaw1b4nBC18ZvzFr38rfH2PVa

## Поставленная цель и задачи

Цель авторов статьи: представить эффективный и простой вариант защиты ChatGPT от Jailbreak атак.

Для достижения поставленной цели авторы ставят перед собой следующие задачи:

1. Создать набор данных Jailbreak для проверки устойчивости метода.
2. Оценить эффективность защиты ChatGPT методом "Самонапоминания".
3. Сравнение производительности ChatGPT с защитой и без нее.

Следует отметить то, что в разделе "Abstract" авторы статьи обосновывают актуальность исследования: рассуждают о значимости защиты от Jailbreak атак и ставят перед собой цель создания эффективного метода защиты.

Разделы, раскрывающие вышеописанные задачи:

* "Dataset Construction" - подробно описывается, что из себя представляют данные, с помощью которых будет проводиться анализ создаваемого метода. Прописаны параметры и в соотвествии с ними проведен отбор данных.
* "Performance Evaluation", "Resilience to Adaptive Attack" - проведена оценка, насколько метод эффективно работает на наборе данных, и сделаны соотвествующие выводы о влиянии инструкций и подсказок Jailbreak на успешность атаки. В "Ablation Study" описывается эксперимент, в котором убираются некоторые компоненты метода защиты "Самонапоминанием" и рассматриваются по отдельности. На основе результатов эксперимента делается вывод о том, что метод эффективен при использовании компонент вместе. "Impact of Tone on the Effectiveness of Defense" - данный раздел отражает, как тон может сделать защиту еще сильнее.
* "Side Effects on Regular User Queries" - проведен сравнительный анализ скорости обработки обычных запросов ChatGPT с учетом защиты и без.

## Тематика статьи

Тематика статьи - исследование и разработка методов защиты LLM от Jailbreak атак.

Авторы статьи предоставляют разработанный метод Self-Remainder для предупреждения Jailbreak атак и демонстрируют анализ успешности данного метода. Результаты исследований показывают уменьшенный процент успешных атак Jailbreak, из чего следует пресечение взлома протоколов этичности и безопасности у ChatGPT.

> Our work raises awareness of the threats posed by Jailbreak Attacks, while our proposed Self-Reminder technique provides a potential for efficiently and effectively improving the secure and responsible use of large language models without additional training.

## Методы обоснования

В данной работе авторы использовали следующие методы исследования:

 1. Эксперимент на собранном наборе данных;

 2. Анализ полученных результатов для ChatGPT:

    * С защитой;
    * Без защиты;
    * С разными настройками защиты.

Для проверки гипотезы, изложенной в данной статье, был собран набор данных, состоящий из 540 образцов, содержащих в себе Jailbreak промпт и вредную инструкцию.

Авторами проведен эксперимент над ChatGPT с защитой и без нее по уязвимости к Jailbreak атакам в следующем формате:

> For all experiments, we test with Chat GPT API gpt-3.5-turbo-0301 five times and report the mean and standard deviation of the results

Анализ результатов представлен в подразделах "Ablation Study", "Side Effects on Regular User Queries" и " Performance Evaluation" раздела "Results".
