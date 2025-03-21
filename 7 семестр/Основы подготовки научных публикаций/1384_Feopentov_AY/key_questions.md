# Ответы на ключевые вопросы

## Проблема
Сложность для клиентов онлайн-магазинов в подборе подходящих товаров
 
## Актуальность
Эффективность работы сотрудников интернет-магазинов и удовлетворенность клиентов зависят от точности и скорости подбора их заказов. Недостаточная функциональность текущих инструментов[1] приводит к ошибкам в подборе, увеличению времени обработки запросов и снижению общей производительности.
Современные административные панели интернет-магазинов нередко сталкиваются с проблемами оптимизации SELECT-запросов SQL, используемых для обработки данных о запчастях. Низкая точность оценки селективности таких запросов может приводить к выбору неоптимальных планов выполнения, увеличивая время выполнения запросов и снижая производительность системы[2].
Внедрение алгоритмов, учитывающих аналоги и корреляции характеристик запчастей, а также оптимизация SQL-запросов, могут существенно ускорить процесс подбора [3]. Кроме того, использование продвинутых методов веб-разработки и работы с данными позволяет повысить качество работы администраторов [4], [5].
## Объект исследования
Сайт для администрирования поиска и подбора товаров в интернет-магазинах.

## Предмет исследования
Эффективность алгоритма поиска автозапчастей, измеряемая точностью подбора аналогов, скоростью выполнения запросов и учётом корреляций характеристик.

## Цель
Разработать алгоритм для поиска автозапчастей, учитывающий аналоги, корреляции характеристик и предпочтения клиентов для использования в административных панелях интернет-магазинов.

## Задачи
1. Провести обзор и сравнение существующих методов поиска автозапчастей в интернет-магазинах.
2. Исследовать алгоритмы обработки данных их критерии с учетом аналогов и корреляций характеристик.
3. Разработать алгоритм поиска, учитывающий специфику данных автозапчастей.

## Список использованных источников 
1. Ефимов А.М. V8 запчасти / Ефимов А.М. [Электронный ресурс] //  : [сайт]. — URL: https://v8-zap.ru/
2. Никишанин, Р. О. ОПТИМИЗАЦИЯ SQL-ЗАПРОСОВ В ВЕБ-ПРИЛОЖЕНИИ, НАПИСАННОМ НА RUBY ON RAILS [Текст] / Р. О. Никишанин //URL:https://cyberleninka.ru/article/n/optimizatsiya-sql-zaprosov-v-veb-prilozhenii-napisannom-na-ruby-on-rails
3. Ефимов А.М. AUTOARTIS/ Ефимов А.М. [Электронный ресурс] //  : [сайт]. — URL: https://autoartis.ru/
4. Кузнецов, М. В. PHP. Практика создания Web-сайтов [Текст] / М. В. Кузнецов . Санкт-Петербург: БХВ-Петербург, 2019 — 439 c.
5. Урусов, Т. Т. Создание веб-приложения интернет-магазина  с использованием современных инструментов разработки. [Текст] / Т. Т. Урусов // URL:https://cyberleninka.ru/article/n/sozdanie-veb-prilozheniya-internet- magazina-s-ispolzovaniem-sovremennyh-instrumentov-razrabotki