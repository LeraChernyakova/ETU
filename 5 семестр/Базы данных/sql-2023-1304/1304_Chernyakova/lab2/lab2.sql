create schema if not exists school_schema;

create table school_schema.Teacher(
    teacher_id serial primary key,
    teacher_name varchar(50) not null,
    teacher_surname varchar(50) not null,
    teacher_patronymic varchar(50)
);

create table school_schema.Classroom(
    classroom_number int,
    primary key (classroom_number)
);

create table school_schema.Teacher_classroom(
    teacher_id int,
    classroom_number int,
    primary key (teacher_id, classroom_number),
    foreign key (teacher_id) references school_schema.Teacher(teacher_id) on delete cascade,
    foreign key (classroom_number) references school_schema.Classroom(classroom_number) on delete cascade
);

create table school_schema.Subject(
    subject_id serial primary key,
    subject_name varchar(50) not null
);

create table school_schema.Teacher_subject(
    teacher_id int,
    subject_id int,
    primary key (teacher_id, subject_id),
    foreign key (teacher_id) references school_schema.Teacher(teacher_id) on delete cascade,
    foreign key (subject_id) references school_schema.Subject(subject_id) on delete cascade
);

create table school_schema.Class(
    class_number int,
    class_letter varchar(2),
    primary key (class_number, class_letter)
);

create table school_schema.Student(
    student_id serial primary key,
    student_name varchar(50) not null,
    student_surname varchar(50) not null,
    class_number int,
    class_letter varchar(2),
    foreign key (class_number, class_letter) references school_schema.Class(class_number, class_letter) on delete cascade
);

create table school_schema.Grade(
    grade_id serial primary key,
    student_id int,
    quater_number int,
    subject_id int,
    mark int,
    foreign key (student_id) references school_schema.Student(student_id) on delete cascade,
    foreign key (subject_id) references school_schema.Subject(subject_id) on delete cascade
);

create table school_schema.Schedule(
    schedule_id serial primary key,
    day_name varchar(30) not null,
    lesson_number int,
    subject_id int,
    teacher_id int,
    classroom_number int,
    class_number int,
    class_letter varchar(2),
    foreign key (subject_id) references school_schema.Subject(subject_id) on delete cascade,
    foreign key (teacher_id) references school_schema.Teacher(teacher_id) on delete cascade,
    foreign key (classroom_number) references school_schema.Classroom(classroom_number) on delete cascade,
    foreign key (class_number, class_letter) references school_schema.Class(class_number, class_letter) on delete cascade
);

insert into school_schema.Teacher(teacher_name, teacher_surname, teacher_patronymic) values
    ('Иванов', 'Александр', 'Петрович'),
    ('Смирнова', 'Мария', 'Игоревна'),
    ('Петров', 'Андрей', 'Сергеевич'),
    ('Козлов', 'Елена', 'Владимировна'),
    ('Соколов', 'Игорь', 'Анатольевич'),
    ('Волкова', 'Наталья', 'Александровна'),
    ('Михайлов', 'Артем', 'Дмитриевич'),
    ('Передерий', 'Ольга', null);

insert into school_schema.Classroom(classroom_number) values
    (101), (205), (220), (135), (310), (222), (112), (300), (315);

insert into school_schema.Teacher_classroom(teacher_id, classroom_number) values
    (7, 101), (2, 205), (5, 220), (8, 135), (1, 310), (3, 112), (6, 300);

insert into school_schema.Subject(subject_name) values
    ('Математика'), ('Русский язык'), ('История'), ('Физика'), ('Биология'), ('Химия'), ('Иностранный язык'),
    ('Литература'), ('География'), ('Искусство');

insert into school_schema.Teacher_subject(teacher_id, subject_id) values
    (2, 1), (5,1), (7, 2), (1, 2), (3, 3), (1, 4), (4, 5), (4, 6), (7, 7), (1, 8), (8, 9), (6, 10);

insert into school_schema.Class(class_number, class_letter) values
    (5, 'А'), (5, 'Б'), (6, 'Б'), (6, 'Г'), (7, 'В'), (7, 'Д'), (8, 'А'), (9, 'А');

insert into school_schema.Student(student_name, student_surname, class_number, class_letter) values
    ('Басалаев', 'Леонид', 5, 'А'),
    ('Кудашкина', 'Анастасия', 5, 'А'),
    ('Карасев', 'Алексей', 5, 'Б'),
    ('Максимлчкина', 'Софья', 5, 'Б'),
    ('Мангутов', 'Тимур', 6, 'Б'),
    ('Аракчеева', 'Арина', 6, 'Г'),
    ('Чернякова', 'Валерия', 7, 'В'),
    ('Дубровин', 'Игорь', 7, 'Д'),
    ('Никитин', 'Никита', 8, 'А'),
    ('Бомштейн', 'Юлия', 9, 'А');

insert into school_schema.Grade(student_id, quater_number, subject_id, mark) values
    (1, 1, 2, 4),
    (2, 1, 10, 5),
    (3, 1, 5, 3),
    (4, 1, 3, 3),
    (5, 1, 1, 4),
    (6, 1, 9, 4),
    (7, 1, 6, 5),
    (8, 1, 4, 5),
    (9, 1, 7, 5),
    (10, 1, 8, 3);

insert into school_schema.Schedule(day_name, lesson_number, subject_id, teacher_id, classroom_number, class_number, class_letter) values
    ('Понедельник', 1, 2, 1, 310, 5,'А'),
    ('Понедельник', 2, 1, 5, 220, 5,'А'),
    ('Понедельник', 3, 3, 3, 112, 5,'Б'),
    ('Понедельник', 4, 5, 4, 220, 5,'Б'),
    ('Вторник', 1, 7, 7, 101, 6,'Б'),
    ('Вторник', 2, 1, 2, 205, 6,'Б'),
    ('Вторник', 5, 9, 8, 135, 6,'Г'),
    ('Вторник', 6, 8, 1, 310, 6,'Г'),
    ('Среда', 5, 4, 1, 310, 7,'В'),
    ('Среда', 6, 10, 6, 300, 7,'В'),
    ('Среда', 3, 2, 1, 310, 7,'Д'),
    ('Среда', 4, 5, 4, 315, 7,'Д'),
    ('Четверг', 1, 6, 4, 135, 8,'А'),
    ('Четверг', 2, 3, 3, 112, 8,'А'),
    ('Пятница', 1, 9, 8, 135, 9,'А'),
    ('Пятница', 2, 4, 1, 310, 9,'А');

select subject_name
from school_schema.Subject
    inner join school_schema.Schedule using(subject_id)
where class_number = 9 and class_letter = 'А' and day_name = 'Пятница' and lesson_number = 2;

select teacher_name, teacher_surname, teacher_patronymic
from school_schema.Teacher
    inner join school_schema.Schedule using(teacher_id)
where class_letter = 'Б' and class_number = 6;

select classroom_number from school_schema.Schedule
where lesson_number = 5 and day_name = 'Среда' and class_number = 7 and class_letter = 'В';

select class_number, class_letter
from school_schema.Schedule
    inner join school_schema.Teacher using(teacher_id)
    inner join school_schema.Subject using(subject_id)
where teacher_name = 'Козлов' and teacher_surname = 'Елена' and teacher_patronymic = 'Владимировна'
and subject_name = 'Биология';

select day_name, lesson_number, class_number,class_letter, subject_name,
(teacher_name, teacher_surname, teacher_patronymic) as teacher
from school_schema.Schedule
    inner join  school_schema.Subject using(subject_id)
    inner join  school_schema.Teacher using(teacher_id)
    inner join  school_schema.Classroom using(classroom_number)
where class_letter = 'Б' and class_number = 6;

select count(student_id)
from school_schema.Student
    inner join school_schema.Class using(class_number, class_letter)
where class_number = 5 and class_letter = 'А';




