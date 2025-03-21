# Ответы на ключевые вопросы

## Основные определения

Для начала введем определения терминов, упоминаемых в данном документе.
- Инфраструктура - набор вычислительных ресурсов, необходимый для работы программного обеспечения.
- Облачная платформа - сервис, предоставляющий доступ к виртуальной инфраструктуре через API. Под доступом подразумевается получение, изменение и очистка вычислительных ресурсов.
- Кластер - группа из одного или нескольких серверов, объединены в единый инфраструктурный ресурс. В рамках данной работы будут использоваться только виртуальная инфраструктура на базе облачной платформы. 
- Кластер Kubernetes - кластер, на котором запускаются контейнеризированные приложения под управлением (оркестрацией) ПО Kubernetes. 
- Управление ресурсами облачной платформы - создание и очистка облачной инфраструктуры, необходимой для работы кластера.
- Микросервисы  [1] - единица, моделируемая вокруг предметной области бизнеса и выпускаемая независимо, используется в рамках микросервисной архитектуры и взаимодействует с другими микросервисами по сети.
- Микросервисная архитектура - подход к проектированию распределенной системы, при котором основное приложение делится на микросервисы.
- Задача - набор действий или же операций в системе, необходимых для реализации какой-либо бизнес-функции
- Задача в микросервисной архитектуре - задача, требующая координации нескольких микросервисов для выполнения
- Транзакция Базы Данных [2] - неделимая логическая единица работы в СУБД, позволяющая представить несколько операций (задача) в виде единого шага.
- ACID [2] - аббревиатура для описания свойств, которыми должна обладать транзакция Базы Данных:
  - Атомарность (A - atomicity) - все операции будут выполнены целиком или не будут выполнены вовсе
  - Согласованность (C - consistency) - транзакция приводит систему из одного допустимого состояния в другое допустимое, сохраняя все инварианты
  - Изолированность (I - isolation) - несколько параллельно выполняемых транзакций выполняются без влияния друг на друга 
  - Долговечность (D - durability) - после завершения транзакции все данные хранятся постоянно и сохраняются в случае отказов системы
- Транзакция распределенной системы [1] - способ группировки приложением нескольких операций (задачи) в одну логическую единицу. Для распределенной системы не всегда требуются все свойства ACID (конкретнее - изолированности).
- Транзакционность распределенной системы - свойство обеспечивать выполнение всех задач в рамках транзакций.
- Надежность ПО [3] - свойство системы продолжать работать корректно даже при неблагоприятных обстоятельствах (в случае аппаратных или программных сбоев либо ошибок пользователя)
- Отказоустойчивость системы [3] - свойство системы продолжать работу в случае сбоя вычислительных ресурсов. В контексте микросервисной архитектуры также в случае сбоев в конкретных микросервисах.

## Проблема
Обеспечение транзакционности распределенной системы для функционирования кластеров Kubernetes.

## Актуальность

В большинстве современных систем необходимо обеспечивать согласованность и атомарность выполнения операций, распределенные системы - не исключение, но в них эта задача является более сложной по сравнению с ПО на базе монолитных архитектур [1, 4, 5].

В отсутствие транзакционности в распределенной системе могут возникать следующие проблемы:
- потеря данных при частичных отказах: разрывах сети, сбоях в микросервисах [2, 3];
- состояния гонки, приводящие к неожиданным ошибкам [3];
- неконсистентность полученных данных или объектов при частичных отказах [4];
- усложнение поддержки ввиду неочевидности возникающих сбоев [2].

В рамках данной работы рассматривается управление задачами, затрагивающими управление ресурсами облачной платформы для функционирования кластеров Kubernetes. Для них нужно выполнять множество различных операций:
- взаимодействовать с API облачной платформы: создавать или очищать инфраструктуру клиента; 
- поддерживать актуальное состояние внутри самих кластеров: обновлять набор ПО и его конфигурацию, обеспечивать внутренние данные для Kubernetes;
- хранить необходимую информацию во внутренней базе данных для взаимодействия с пользователем и обслуживания инфраструктуры.

Конкретно в этой системе так же необходимо обеспечение транзакционности для гарантии отказоустойчивости ПО и согласованности данных, полученных в результате выполняемых задач. В связи с распределенностью системы и разнородностью операций в рамках выполняемых задач несогласованность данных в каком-либо из ресурсов затрудняет сопровождение продукта. Поэтому помимо сокращения общего числа возникающих сбоев обеспечение транзакционности также позволит более точно определять причины возникающих ошибок.

## Объект исследования
Управление выполнением задач в распределенной системе, обеспечивающей функционирование кластеров Kubernetes.

## Предмет исследования
Архитектурные подходы обеспечения транзакционности выполняемых задач в распределенных системах.

## Цель
Определить архитектурный подход обеспечения транзакционности при выполнении задач для функционирования кластеров Kubernetes.

## Задачи
1. Определение критериев отбора подходов, подходящих для решения поставленной задачи.
2. Обзор существующих подходов обеспечения транзакционности распределенной системы.
3. Сравнение найденных подходов.
4. Предоставление рекомендаций по построению архитектуры распределенной системы.

## Список использованных источников
1. Newman S. Building microservices. – "O'Reilly Media, Inc.", 2021
2. А. Петров. Распределенные данные. Алгоритмы работы современных систем хранения информации. – "Питер", 2021
3. М. Клеппман. Высоконагруженные приложения. Программирование, масштабирование, поддержка. – "Питер", 2018.
4. Э. Таненбаум, М. ван Стеен. Распределенные системы. Принципы и парадигмы. – "Питер", 2003
5. Richardson C. Microservices patterns: with examples in Java. – "Simon and Schuster", 2018
