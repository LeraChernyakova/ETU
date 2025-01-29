CREATE TABLE Subject
(
    subject_id	SERIAL	NOT NULL PRIMARY KEY,
  	title	VARCHAR(64)	NOT NULL UNIQUE	
  
);


CREATE TABLE Class
(
    class_id	SERIAL	NOT NULL PRIMARY KEY,
    number	INT        NOT NULL,
    paralel	VARCHAR(2)	NOT NULL 
);

CREATE TABLE Student
(
    student_id	SERIAL	NOT NULL PRIMARY KEY,
    name    VARCHAR(64) NOT NULL,
    surname    VARCHAR(64) NOT NULL,
  	patronimic    VARCHAR(64) NOT NULL,
    class_id         INTEGER,
    FOREIGN KEY (class_id)
        REFERENCES Class (class_id)
        ON DELETE CASCADE
);

CREATE TABLE Mark
(
    mark_id	SERIAL	NOT NULL PRIMARY KEY,
    mark INTEGER NOT NULL,
  	subject_id         INTEGER,
    student_id         INTEGER,
    FOREIGN KEY (subject_id)
        REFERENCES Subject (subject_id)
        ON DELETE CASCADE,
   FOREIGN KEY (student_id)
        REFERENCES Student (student_id)
        ON DELETE CASCADE
);

CREATE TABLE Teacher
(
    teacher_id  SERIAL      NOT NULL PRIMARY KEY,
    name    VARCHAR(64) NOT NULL,
    surname    VARCHAR(64) NOT NULL,
  	patronimic    VARCHAR(64) NOT NULL
);







CREATE TABLE Lesson
(
    lesson_id      SERIAL       NOT NULL PRIMARY KEY,
    teacher_id INTEGER,
  	subject_id INTEGER,
  FOREIGN KEY (subject_id)
        REFERENCES Subject (subject_id)
        ON DELETE CASCADE,
   FOREIGN KEY (teacher_id)
        REFERENCES Teacher (teacher_id)
        ON DELETE CASCADE
  
);

CREATE TABLE Cabinet(
	cabinet_id      SERIAL       NOT NULL PRIMARY KEY,
    number INTEGER
);


CREATE TABLE Owner
(
    teacher_id INTEGER,
  	cabinet_id INTEGER,
  	FOREIGN KEY (cabinet_id)
        REFERENCES Cabinet (cabinet_id)
        ON DELETE CASCADE,
   FOREIGN KEY (teacher_id)
        REFERENCES Teacher (teacher_id)
        ON DELETE CASCADE
);

CREATE TABLE Schedule
(
  	schedule_id      SERIAL       NOT NULL PRIMARY KEY,
  	lesson_id INTEGER,
    class_id INTEGER,
  	cabinet_id INTEGER,
  	day VARCHAR(32) NOT NULL,
  	number_lesson INTEGER NOT NULL,
  	
   FOREIGN KEY (cabinet_id)
        REFERENCES Cabinet (cabinet_id)
        ON DELETE CASCADE,
  FOREIGN KEY (class_id)
        REFERENCES Class (class_id)
        ON DELETE CASCADE,
  FOREIGN KEY (lesson_id)
        REFERENCES Lesson (lesson_id)
        ON DELETE CASCADE
);

INSERT INTO Subject(title)
VALUES ('Русский Язык'),
		('Литература'),
       ('География'),
       ('Математика'),
       ('Биология'),
       ('Химия'),
       ('Информатика');
INSERT INTO Class(number,paralel)
VALUES ('7','а'),
		('8','б'),
        ('9','в'),
        ('7','б'),
        ('9','б');
INSERT INTO Student (name,surname,patronimic,class_id)
VALUES ('Артур','Мусаев','Илдарович',1),
	   ('Александр','Маркуш','Евгеньевич',1),
       ('Михаил','Новицкий','Дмитриевич',2),
       ('Егор','Лобанов','Александрович',3),
       ('Роман','Поршнев','Александрович',4),
       ('Владимир','Басыров','Александрович',2),
       ('Дмитрий','Кривоченко','Игоревич',1),
       ('Даниил','Павлов','Кузиминичев',3),
       ('Никита','Петухов','Евгенич',5),
       ('Эдуард','Васильев','Федорович',4),
       ('Евгений','Павлов','Андреевич',3),
       ('Александр','Петров','Андреевич',3),
       ('Даниил','Сидоров','Станиславович',3);

INSERT INTO Mark(mark,student_id,subject_id)
VALUES (5,1,1),
       (4, 1,1),
       (4, 2,1),
       (3, 2,2),
       (2, 3,2),
       (5,4,3),
       (3,5,4),
       (1,6,5),
       (4,2,2);
       

INSERT INTO Teacher(name,surname,patronimic)
VALUES ('Евгений','Иванов','Иванович'),
	   ('Александр','Пожидаев','Евгеньевич'),
       ('Ярослав','Коптелов','Юрьевич'),
       ('Владимир','Кирьянчиков','Александрович'),
       ('Светлана','Федорова','Александровна'),
       ('Наталья','Кузьмина','Николавная');

INSERT INTO Lesson(teacher_id,subject_id)
VALUES (1,1),
		(2,1),
        (3,3),
        (4,2),
        (5,2),
        (6,3),
        (1,4),
        (2,5),
        (3,6),
        (4,3);
        
INSERT INTO Cabinet(number)
VALUES (27),
		(30),
        (55),
        (12),
        (21),
        (29),
        (45),
        (41),
        (5);

INSERT INTO Owner(teacher_id,cabinet_id)
VALUES (1, 1),
       (2, 2),
       (4,4),
       (5,5),
       (6,6);

INSERT INTO Schedule(lesson_id,class_id,day,number_lesson,cabinet_id)
VALUES
(8,1,'Понедельник',1,2),
(3,2,'Понедельник',1,9),
(5,3,'Понедельник',1,5),
(9,4,'Понедельник',1,8),
(4,5,'Понедельник',1,4),
(5,1,'Понедельник',2,5),
(7,2,'Понедельник',2,1),
(7,3,'Понедельник',2,1),
(2,4,'Понедельник',2,2),
(2,5,'Понедельник',2,2),
(6,1,'Понедельник',3,6),
(3,2,'Понедельник',3,8),
(8,3,'Понедельник',3,2),
(6,4,'Понедельник',3,6),
(8,5,'Понедельник',3,2),
(4,1,'Понедельник',4,4),
(7,2,'Понедельник',4,1),
(7,3,'Понедельник',4,1),
(2,4,'Понедельник',4,2),
(2,5,'Понедельник',4,2),
(4,1,'Понедельник',5,4),
(3,2,'Понедельник',5,7),
(7,3,'Понедельник',5,1),
(4,4,'Понедельник',5,4),
(1,5,'Понедельник',5,1),
(3,1,'Понедельник',6,7),
(1,2,'Понедельник',6,1),
(4,3,'Понедельник',6,4),
(4,4,'Понедельник',6,4),
(7,5,'Понедельник',6,1),
(8,1,'Вторник',1,2),
(8,2,'Вторник',1,2),
(10,3,'Вторник',1,4),
(4,4,'Вторник',1,4),
(5,5,'Вторник',1,5),
(9,1,'Вторник',2,7),
(5,2,'Вторник',2,5),
(3,3,'Вторник',2,8),
(10,4,'Вторник',2,4),
(4,5,'Вторник',2,4),
(1,1,'Вторник',3,1),
(7,2,'Вторник',3,1),
(7,3,'Вторник',3,1),
(4,4,'Вторник',3,4),
(9,5,'Вторник',3,8),
(3,1,'Вторник',4,9),
(4,2,'Вторник',4,4),
(9,3,'Вторник',4,9),
(10,4,'Вторник',4,4),
(5,5,'Вторник',4,5),
(10,1,'Вторник',5,4),
(4,2,'Вторник',5,4),
(1,3,'Вторник',5,1),
(7,4,'Вторник',5,1),
(4,5,'Вторник',5,4),
(3,1,'Вторник',6,9),
(7,2,'Вторник',6,1),
(2,3,'Вторник',6,2),
(10,4,'Вторник',6,4),
(9,5,'Вторник',6,9),
(4,1,'Среда',1,4),
(5,2,'Среда',1,5),
(2,3,'Среда',1,2),
(2,4,'Среда',1,2),
(2,5,'Среда',1,2),
(8,1,'Среда',2,2),
(1,2,'Среда',2,1),
(3,3,'Среда',2,7),
(2,4,'Среда',2,2),
(2,5,'Среда',2,2),
(7,1,'Среда',3,1),
(8,2,'Среда',3,2),
(2,3,'Среда',3,2),
(10,4,'Среда',3,4),
(7,5,'Среда',3,1),
(10,1,'Среда',4,4),
(5,2,'Среда',4,5),
(3,3,'Среда',4,8),
(8,4,'Среда',4,2),
(4,5,'Среда',4,4),
(8,1,'Среда',5,2),
(6,2,'Среда',5,6),
(5,3,'Среда',5,5),
(9,4,'Среда',5,7),
(2,5,'Среда',5,2),
(1,1,'Среда',6,1),
(9,2,'Среда',6,9),
(7,3,'Среда',6,1),
(2,4,'Среда',6,2),
(2,5,'Среда',6,2),
(10,1,'Четверг',1,4),
(3,2,'Четверг',1,8),
(10,3,'Четверг',1,4),
(10,4,'Четверг',1,4),
(3,5,'Четверг',1,8),
(10,1,'Четверг',2,4),
(10,2,'Четверг',2,4),
(4,3,'Четверг',2,4),
(8,4,'Четверг',2,2),
(4,5,'Четверг',2,4),
(7,1,'Четверг',3,1),
(9,2,'Четверг',3,7),
(5,3,'Четверг',3,5),
(2,4,'Четверг',3,2),
(3,5,'Четверг',3,8),
(6,1,'Четверг',4,6),
(5,2,'Четверг',4,5),
(1,3,'Четверг',4,1),
(5,4,'Четверг',4,5),
(1,5,'Четверг',4,1),
(3,1,'Четверг',5,8),
(5,2,'Четверг',5,5),
(3,3,'Четверг',5,8),
(3,4,'Четверг',5,7),
(9,5,'Четверг',5,7),
(7,1,'Четверг',6,1),
(4,2,'Четверг',6,4),
(1,3,'Четверг',6,1),
(10,4,'Четверг',6,4),
(2,5,'Четверг',6,2),
(7,1,'Пятница',1,1),
(3,2,'Пятница',1,9),
(2,3,'Пятница',1,2),
(7,4,'Пятница',1,1),
(6,5,'Пятница',1,6),
(7,1,'Пятница',2,1),
(5,2,'Пятница',2,5),
(9,3,'Пятница',2,7),
(5,4,'Пятница',2,5),
(8,5,'Пятница',2,2),
(9,1,'Пятница',3,7),
(7,2,'Пятница',3,1),
(6,3,'Пятница',3,6),
(4,4,'Пятница',3,4),
(3,5,'Пятница',3,8),
(9,1,'Пятница',4,8),
(5,2,'Пятница',4,5),
(7,3,'Пятница',4,1),
(8,4,'Пятница',4,2),
(3,5,'Пятница',4,7),
(7,1,'Пятница',5,1),
(1,2,'Пятница',5,1),
(4,3,'Пятница',5,4),
(4,4,'Пятница',5,4),
(8,5,'Пятница',5,2),
(10,1,'Пятница',6,4),
(4,2,'Пятница',6,4),
(6,3,'Пятница',6,6),
(7,4,'Пятница',6,1),
(10,5,'Пятница',6,4);




SELECT title FROM Subject
	INNER JOIN Lesson USING(subject_id)
    INNER JOIN Schedule s USING(lesson_id)
    INNER JOIN Class c USING(class_id)
WHERE c.number=7 AND c.paralel='б' 
AND s.day='Понедельник' AND s.number_lesson=3; 



SELECT name,surname,patronimic FROM Teacher
	INNER JOIN Lesson USING(teacher_id)
	INNER JOIN Schedule USING(lesson_id)	
	INNER JOIN Class c USING(class_id)
WHERE c.number=9 AND c.paralel='в'
GROUP BY name,surname,patronimic;


SELECT cab.number FROM Cabinet cab
 	INNER JOIN Schedule s USING(cabinet_id)
    INNER JOIN Class c USING(class_id)
WHERE (c.number=8 AND c.paralel='б' AND s.day='Среда' AND s.number_lesson=5);
 
 
SELECT sch.number_lesson,sub.title,cab.number FROM Schedule sch
 	INNER JOIN Class c USING(class_id)
    INNER JOIN Cabinet cab USING(cabinet_id)
    INNER JOIN Lesson USING(lesson_id)
    INNER JOIN Subject sub USING(subject_id)
WHERE (c.number=7 AND c.paralel='а' AND sch.day='Четверг');
 
 SELECT c.number,c.paralel FROM Class c
    INNER JOIN Schedule USING(class_id)	
 	INNER JOIN Lesson USING(lesson_id)
	INNER JOIN Teacher t USING(teacher_id)
    INNER JOIN Subject s USING(subject_id)
    WHERE t.name = 'Александр' AND t.surname='Пожидаев' AND t.patronimic='Евгеньевич' 
    AND s.title = 'Русский Язык'
 GROUP BY c.number,c.paralel;
 
 SELECT count(*) FROM Student
 	INNER JOIN Class c USING(class_id)
    WHERE c.paralel = 'б' AND c.number=8; 
 
