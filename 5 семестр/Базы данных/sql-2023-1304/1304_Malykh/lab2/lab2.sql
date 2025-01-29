DROP TABLE IF EXISTS syllabus CASCADE;
DROP TABLE IF EXISTS department_specialty CASCADE;
DROP TABLE IF EXISTS specialty_code CASCADE;
DROP TABLE IF EXISTS specialty CASCADE;
DROP TABLE IF EXISTS phones CASCADE;
DROP TABLE IF EXISTS department CASCADE;
DROP TABLE IF EXISTS head CASCADE;
DROP TABLE IF EXISTS faculty CASCADE;



CREATE TABLE faculty
(
    faculty_name VARCHAR(50) PRIMARY KEY
);


CREATE TABLE head
(
    head_id   SERIAL       NOT NULL PRIMARY KEY,
    full_name VARCHAR(100) NOT NULL,
    degree    VARCHAR(50)  NOT NULL,
    rank      VARCHAR(50)  NOT NULL
);

CREATE TABLE department
(
    department_name VARCHAR(50) PRIMARY KEY,
    faculty_name    VARCHAR(50) NOT NULL,
    head_id         INTEGER,
    FOREIGN KEY (faculty_name)
        REFERENCES faculty (faculty_name)
        ON DELETE CASCADE,
    FOREIGN KEY (head_id)
        REFERENCES head (head_id)
        ON DELETE SET NULL
);


CREATE TABLE phones
(
    number          VARCHAR(11) PRIMARY KEY,
    department_name VARCHAR(50) NOT NULL,
    FOREIGN KEY (department_name)
        REFERENCES department (department_name)
        ON DELETE CASCADE
);


CREATE TABLE specialty_code
(
    code           VARCHAR(10)  NOT NULL PRIMARY KEY,
    specialty_name VARCHAR(100) NOT NULL,
    degree         VARCHAR(100) NOT NULL,
    UNIQUE (specialty_name, degree)
);


CREATE TABLE specialty
(
    specialty_id SERIAL      NOT NULL PRIMARY KEY,
    code         VARCHAR(10) NOT NULL,
    duration     INTEGER     NOT NULL,
    study_form   VARCHAR(30) NOT NULL,
    UNIQUE (code, duration, study_form),
    FOREIGN KEY (code)
        REFERENCES specialty_code (code)
        ON DELETE RESTRICT
);


CREATE TABLE syllabus
(
    syllabus_id      SERIAL       NOT NULL PRIMARY KEY,
    discipline_name  VARCHAR(150) NOT NULL,
    semester         INTEGER      NOT NULL,
    control_form     VARCHAR(50)  NOT NULL,
    lecture_hours    INTEGER      NOT NULL,
    practice_hours   INTEGER      NOT NULL,
    lab_hours        INTEGER      NOT NULL,
    coursework_hours INTEGER      NOT NULL
);


CREATE TABLE department_specialty
(
    syllabus_id     INTEGER     NOT NULL,
    specialty_id    INTEGER     NOT NULL,
    department_name VARCHAR(50) NOT NULL,
    FOREIGN KEY (syllabus_id)
        REFERENCES syllabus (syllabus_id)
        ON DELETE CASCADE,
    FOREIGN KEY (specialty_id)
        REFERENCES specialty (specialty_id)
        ON DELETE CASCADE,
    FOREIGN KEY (department_name)
        REFERENCES department (department_name)
        ON DELETE CASCADE
);



INSERT INTO faculty(faculty_name)
VALUES ('ФКТИ'),
       ('ГФ');

INSERT INTO head (full_name, degree, rank)
VALUES ('Лисс Анна Александровна', 'Кандидат технических наук', 'Доцент'),
       ('Бутусов Денис Николаевич', 'Кандидат технических наук', 'Доцент'),
       ('Куприянов Михаил Степанович', 'Доктор технических наук', 'Профессор'),
       ('Цехановский Владислав Владимирович', 'Кандидат технических наук', 'Профессор'),
       ('Шарахина Лариса Валентиновна', 'Кандидат философских наук', 'Доцент');

INSERT INTO department(department_name, faculty_name, head_id)
VALUES ('МО ЭВМ', 'ФКТИ', 1),
       ('САПР', 'ФКТИ', 2),
       ('ВТ', 'ФКТИ', 3),
       ('ИС', 'ФКТИ', 4),
       ('СО', 'ГФ', 5);

INSERT INTO phones(number, department_name)
VALUES ('78122342682', 'МО ЭВМ'),
       ('78122343675', 'САПР'),
       ('78122342503', 'ВТ'),
       ('78123461719', 'ИС'),
       ('78122342773', 'ИС'),
       ('78123464547', 'СО'),
       ('78126551374', 'СО');

INSERT INTO specialty_code(code, specialty_name, degree)
VALUES ('01.03.02', 'Прикладная математика и информатика', 'Бакалавриат'),
       ('09.04.04', 'Программная инженерия', 'Магистратура'),
       ('09.03.01', 'Информатика и вычислительная техника', 'Бакалавриат'),
       ('09.03.02', 'Информационные системы и технологии', 'Бакалавриат'),
       ('42.03.01', 'Реклама и связи с общественностью', 'Бакалавриат');

INSERT INTO specialty(code, duration, study_form)
VALUES ('01.03.02', 4, 'Очная'),
       ('09.04.04', 2, 'Очная'),
       ('09.04.04', 3, 'Заочная'),
       ('09.03.01', 4, 'Очная'),
       ('09.03.01', 5, 'Вечерняя'),
       ('09.03.02', 4, 'Очная'),
       ('42.03.01', 6, 'Заочная');


INSERT INTO syllabus(discipline_name,
                     semester, control_form, lecture_hours,
                     practice_hours, lab_hours, coursework_hours)
VALUES ('Математический анализ', 1, 'Экзамен', 90, 90, 0, 0),
       ('Математический анализ', 2, 'Экзамен', 90, 70, 0, 0),
       ('Математический анализ', 3, 'Текущий контроль', 90, 45, 0, 0),
       ('Программирование', 1, 'Экзамен', 60, 60, 60, 16),
       ('Программирование', 2, 'Экзамен', 60, 60, 60, 16),
       ('Машинное обучение', 9, 'Экзамен', 20, 20, 60, 20),
       ('Управление разработкой ПО', 10, 'Текущий контроль', 20, 20, 40, 20),
       ('Машинное обучение', 9, 'Текущий контроль', 20, 20, 60, 20),
       ('Управление разработкой ПО', 10, 'Текущий контроль', 0, 10, 40, 20),
       ('Математический анализ', 1, 'Экзамен', 90, 90, 0, 0),
       ('Математический анализ', 2, 'Текущий контроль', 45, 45, 0, 0),
       ('Схемотехника', 3, 'Экзамен', 90, 90, 90, 40),
       ('Математический анализ', 1, 'Экзамен', 90, 90, 0, 0),
       ('Математический анализ', 2, 'Текущий контроль', 45, 45, 0, 0),
       ('Программирование', 1, 'Экзамен', 50, 30, 50, 40),
       ('Программирование', 2, 'Экзамен', 50, 30, 90, 20),
       ('Математический анализ', 1, 'Экзамен', 20, 20, 0, 0),
       ('Математический анализ', 2, 'Текущий контроль', 20, 20, 0, 0),
       ('Программирование', 1, 'Экзамен', 50, 30, 50, 40),
       ('Программирование', 2, 'Экзамен', 50, 30, 90, 20),
       ('Аппаратное обеспечение искусственного интеллекта', 5, 'Текущий контроль', 60, 60, 30, 0),
       ('Программирование', 1, 'Экзамен', 50, 30, 50, 40),
       ('Программирование', 2, 'Экзамен', 50, 30, 50, 40),
       ('Физика', 2, 'Экзамен', 60, 60, 100, 0),
       ('Архитектура информационных систем', 3, 'Текущий контроль', 60, 0, 50, 50),
       ('Архитектура информационных систем', 4, 'Текущий контроль', 60, 0, 50, 0),
       ('Теория и практика рекламы', 2, 'Экзамен', 70, 70, 0, 40),
       ('Основы маркетинга', 1, 'Экзамен', 70, 70, 0, 20),
       ('Математический анализ', 1, 'Зачет', 40, 30, 0, 0);



INSERT INTO department_specialty(specialty_id, department_name, syllabus_id)
VALUES (1, 'МО ЭВМ', 1),
       (1, 'МО ЭВМ', 2),
       (1, 'МО ЭВМ', 3),
       (1, 'МО ЭВМ', 4),
       (1, 'МО ЭВМ', 5),
       (2, 'МО ЭВМ', 6),
       (2, 'МО ЭВМ', 7),
       (3, 'МО ЭВМ', 8),
       (3, 'МО ЭВМ', 9),
       (4, 'САПР', 10),
       (4, 'САПР', 11),
       (4, 'САПР', 12),
       (4, 'ВТ', 13),
       (4, 'ВТ', 14),
       (4, 'ВТ', 15),
       (4, 'ВТ', 16),
       (5, 'ВТ', 17),
       (5, 'ВТ', 18),
       (5, 'ВТ', 19),
       (5, 'ВТ', 20),
       (5, 'ВТ', 21),
       (6, 'ИС', 22),
       (6, 'ИС', 23),
       (6, 'ИС', 24),
       (6, 'ИС', 25),
       (6, 'ИС', 26),
       (7, 'СО', 27),
       (7, 'СО', 28),
       (7, 'СО', 29);


/* Названия дисциплин, которые читаются более одного семестра? */

SELECT discipline_name
FROM syllabus
GROUP BY discipline_name
HAVING COUNT(DISTINCT semester) > 1;


/* Общее количество часов, отводимых на лабораторные работы в одном из семестров,
   проведение которых обеспечивает определенная кафедра? */

SELECT SUM(lab_hours) AS Количество_часов
FROM department_specialty
         INNER JOIN syllabus USING (syllabus_id)
WHERE department_name = 'ИС'
  AND semester = 2
GROUP BY department_name;


-- Название дисциплин, по которым проводятся лабораторные работы на факультете?
SELECT DISTINCT discipline_name
FROM department
         INNER JOIN department_specialty USING (department_name)
         INNER JOIN syllabus USING (syllabus_id)
WHERE faculty_name = 'ФКТИ'
  AND lab_hours > 0;


/* Разница в часах, отведенных по каждой дисциплине на лабораторные и
   практические занятия в одном из семестров на заданном факультете? */

SELECT discipline_name, ABS(SUM(lab_hours) - SUM(practice_hours)) AS Разница
FROM department
         INNER JOIN department_specialty USING (department_name)
         INNER JOIN syllabus USING (syllabus_id)
WHERE faculty_name = 'ФКТИ'
  AND semester = 3
GROUP BY discipline_name;


-- Дисциплины, по которым выполняют курсовые работы студенты указанной специальности?

SELECT DISTINCT discipline_name
FROM specialty_code
         INNER JOIN specialty USING (code)
         INNER JOIN department_specialty USING (specialty_id)
         INNER JOIN syllabus USING (syllabus_id)
WHERE specialty_name = 'Информационные системы и технологии'
  AND department_name = 'ИС'
  AND study_form = 'Очная'
  AND degree = 'Бакалавриат'
  AND coursework_hours > 0;


-- Для каких специальностей читается указанная дисциплина?
SELECT specialty_name, study_form, degree, department_name
FROM specialty_code
         INNER JOIN specialty USING (code)
         INNER JOIN department_specialty USING (specialty_id)
         INNER JOIN syllabus s USING (syllabus_id)
WHERE discipline_name = 'Математический анализ'
GROUP BY specialty_name, study_form, degree, department_name;


/* Какое количество дисциплин входит в учебный план подготовки студентов по
   указанной специальности, и сколько лет осуществляется подготовка? */
SELECT COUNT(syllabus_id) AS Количество_дисциплин, duration AS Продолжительность_подготовки
FROM specialty_code
         INNER JOIN specialty USING (code)
         INNER JOIN department_specialty USING (specialty_id)
         INNER JOIN syllabus USING (syllabus_id)
WHERE specialty_name = 'Реклама и связи с общественностью'
  AND study_form = 'Заочная'
  AND degree = 'Бакалавриат'
  AND department_name = 'СО'
GROUP BY duration;
