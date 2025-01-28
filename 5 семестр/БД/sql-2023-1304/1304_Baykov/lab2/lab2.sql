CREATE TABLE book (
	book_id SERIAL PRIMARY KEY,
	title VARCHAR(50) NOT NULL,
	year_of_publication INT NOT NULL,
	date_of_receipt DATE NOT NULL,
	date_of_deletion DATE,
	cipher INT NOT NULL
);

CREATE TABLE author (
	author_id SERIAL PRIMARY KEY,
	author_name VARCHAR(255)
);

CREATE TABLE publisher (
	publisher_id SERIAL PRIMARY KEY,
	publisher_name VARCHAR(255)
);

CREATE TABLE author_book (
	author_id SERIAL,
	book_id SERIAL,
	FOREIGN KEY (author_id) REFERENCES author (author_id),
	FOREIGN KEY (book_id) REFERENCES book (book_id),
	PRIMARY KEY (author_id, book_id)
);

CREATE TABLE publisher_book (
	publisher_id SERIAL,
	book_id SERIAL,
	FOREIGN KEY (publisher_id) REFERENCES publisher (publisher_id),
	FOREIGN KEY (book_id) REFERENCES book (book_id),
	PRIMARY KEY (publisher_id, book_id)
);

CREATE TABLE reading_hall (
	hall_number INT NOT NULL,
	hall_name VARCHAR(255) NOT NULL,
  	PRIMARY KEY(hall_number, hall_name),
	capacity INT NOT NULL
);

CREATE TABLE library_visitor (
	passport_number VARCHAR(10) NOT NULL PRIMARY KEY,
	hall_number INT NOT NULL,
  	hall_name VARCHAR(255) NOT NULL,
	FOREIGN KEY (hall_number, hall_name) REFERENCES reading_hall (hall_number, hall_name),
	card_number INT NOT NULL,
	surname VARCHAR(255) NOT NULL,
	birth_date DATE NOT NULL,
	address VARCHAR(255) NOT NULL,
	phone_number VARCHAR(11) NOT NULL,
	education VARCHAR(255),
	academic_degree VARCHAR(255)
);

CREATE TABLE reading_hall_has_book (
	book_id SERIAL,
	hall_number INT NOT NULL,
  	hall_name VARCHAR(255) NOT NULL,
	FOREIGN KEY (hall_number, hall_name) REFERENCES reading_hall (hall_number, hall_name),
	FOREIGN KEY (book_id) REFERENCES book (book_id),
	amount INT NOT NULL,
	PRIMARY KEY (book_id, hall_number, hall_name)
);

CREATE TABLE visitor_has_book (
	book_id SERIAL,
	passport_number VARCHAR(10) NOT NULL,
	FOREIGN KEY (book_id) REFERENCES book (book_id),
	FOREIGN KEY (passport_number) REFERENCES library_visitor (passport_number),
	date_of_receipt DATE NOT NULL,
	PRIMARY KEY (book_id, passport_number)
);

INSERT INTO author (author_name)
VALUES 
	('Достоевский Ф.М.'),
	('Булгаков М.А.'),
    ('Ахматова А.А.'),
    ('Есенин С.А.'),
    ('Солженицын А.И.'),
	('Толстой Л.Н.'),
	('Пушкин А.С.'),
	('Чехов А.П.'),
	('Набоков В.В.'),
	('Тургенев И.С.');

INSERT INTO publisher (publisher_name)
VALUES 
	('Эксмо'),
	('АСТ'),
	('Алгоритм'),
	('Азбука'),
	('Амфора'),
	('АРМАДА'),
	('РИПОЛ классик'),
	('Книжный мир'),
	('Манн, Иванов и Фербер'),
	('Красная площадь');

INSERT INTO book (title, year_of_publication, date_of_receipt, date_of_deletion, cipher)
VALUES 
	('Война и мир', 1869, '2021-10-21', NULL, 10),
	('Евгений Онегин', 1833, '2021-10-30', NULL, 32),
	('Вишневый сад', 1903, '2021-11-21', '2023-01-21', 43),
	('Мастер и Маргарита', 1966, '2012-09-21', '2023-01-22', 21),
	('Лолита', 1958, '2021-07-18', NULL, 33),
	('Отцы и дети', 1860, '2018-01-21', NULL, 73),
	('Дым', 1867, '2019-12-13', NULL, 5),
	('Письма матери', 1924, '2020-06-11', NULL, 11),
	('Реквием', 1963, '2021-03-25', NULL, 17),
	('Один день Ивана Денисовича', 1962, '2023-01-09', NULL, 22),
	('Дубровский', 1833, '2022-12-22', NULL, 37),
	('Идиот', 1869, '2020-04-14', NULL, 81),
	('Воскресение', 1899, '2017-05-05', NULL, 99);

INSERT INTO publisher_book (publisher_id, book_id)
VALUES
	(1, 1),
	(1, 2),
	(2, 3),
	(3, 4),
	(4, 5),
	(5, 6),
	(6, 7),
	(7, 8),
	(8, 9),
	(9, 10),
	(10, 11),
	(2, 12),
	(3, 13);
	
INSERT INTO author_book (author_id, book_id)
VALUES
	(1, 12),
	(2, 4),
	(3, 9),
	(4, 8),
	(5, 10),
	(6, 1),
	(6, 13),
	(7, 2),
	(7, 11),
	(8, 3),
	(9, 5),
	(10, 6),
	(10, 7);

INSERT INTO reading_hall (hall_number, hall_name, capacity)
VALUES
	(1, 'Читальный', 20),
	(2, 'Читальный', 22),
	(1, 'Лекционный', 100),
	(1, 'Компьютерный', 40),
	(2, 'Компьютерный', 32);

INSERT INTO library_visitor (passport_number, hall_number, hall_name, card_number, surname, birth_date, address, phone_number, education, academic_degree)
VALUES
	('9876543210', 1, 'Читальный', 1234, 'Иванов', '2000-01-01', 'ул. Пушкина, д. 10, Кв. 5', '79123456789', 'высшее', NULL),
	('1234567890', 1, 'Читальный', 5678, 'Сидоров', '1995-12-25', 'ул. Лермонтова, д. 5, Кв. 8', '79234567890', 'среднее', NULL),
	('8765432109', 2, 'Читальный', 7890, 'Басангова', '1992-03-17', 'ул. Толстого, д. 8, Кв. 2', '79456789012', 'среднее', NULL),
	('9870123456', 1, 'Лекционный', 4321, 'Думкин', '1988-06-15', 'ул. Гагарина, д. 15, Кв. 13', '79345678901', 'высшее', 'магистр'),
	('5432109876', 1, 'Компьютерный', 8901, 'Сидоров', '1999-11-30', 'ул. Достоевского, д. 3, Кв. 7', '79567890123', 'высшее', 'доктор'),
	('6543210987', 2, 'Компьютерный', 9012, 'Минин', '2007-08-10', 'ул. Пушкина, д. 20, Кв. 9', '79678901234', 'среднее', NULL),
	('2109876543', 1, 'Читальный', 3456, 'Депп', '1990-05-20', 'ул. Ленина, д. 1, Кв. 4', '79789012345', 'высшее', 'бакалавр'),
	('3210987654', 1, 'Лекционный', 4567, 'Хэнкс', '2005-09-12', 'ул. Горького, д. 12, Кв. 6', '79890123456', 'высшее', 'магистр'),
	('1098765432', 1, 'Компьютерный', 5678, 'Мартин', '1987-07-05', 'ул. Пушкина, д. 25, Кв. 1', '79901234567', 'среднее', NULL),
	('7654321098', 2, 'Читальный', 6789, 'Иванов', '1994-02-08', 'ул. Лермонтова, д. 7, Кв. 3', '79012345678', 'высшее', 'доктор');

INSERT INTO reading_hall_has_book (book_id, hall_number, hall_name, amount)
VALUES
	(1, 1, 'Читальный', 10),
	(2, 1, 'Читальный', 21),
	(3, 1, 'Читальный', 32),
	(4, 2, 'Читальный', 11),
	(5, 2, 'Читальный', 5),
	(6, 2, 'Читальный', 7),
	(7, 1, 'Лекционный', 8),
	(8, 1, 'Лекционный', 45),
	(9, 1, 'Лекционный', 11),
	(10, 1, 'Компьютерный', 23),
	(11, 1, 'Компьютерный', 43),
	(12, 1, 'Компьютерный', 1),
	(13, 2, 'Компьютерный', 1),
	(10, 2, 'Компьютерный', 6),
	(11, 2, 'Компьютерный', 7),
	(2, 2, 'Компьютерный', 8);
	
INSERT INTO visitor_has_book (book_id, passport_number, date_of_receipt)
VALUES
	(1, '9876543210', '2022-07-15'),
	(2, '1234567890', '2023-02-28'),
	(4, '8765432109', '2022-11-10'),
	(7, '9870123456', '2023-09-03'),
	(10, '5432109876', '2022-05-19'),
	(13, '6543210987', '2021-12-31'),
	(3, '2109876543', '2022-08-22'),
	(9, '3210987654', '2023-03-12'),
	(12, '1098765432', '2023-10-05'),
	(5, '7654321098', '2022-07-27'),
	(2, '9876543210', '2022-04-15'),
	(3, '1234567890', '2021-01-02'),
	(5, '8765432109', '2021-11-21'),
	(8, '9870123456', '2021-09-09'),
	(11, '5432109876', '2022-06-26'),
	(11, '6543210987', '2021-03-16');

SELECT book.title, library_visitor.surname, library_visitor.passport_number
FROM book
	INNER JOIN visitor_has_book USING(book_id)
	INNER JOIN library_visitor USING(passport_number)
ORDER BY library_visitor.surname, library_visitor.passport_number;

SELECT title, cipher FROM book
WHERE cipher = 99 OR cipher = 81;

SELECT title, cipher FROM book
WHERE title = 'Реквием' OR title = 'Лолита';

SELECT book.title, library_visitor.surname, library_visitor.passport_number, visitor_has_book.date_of_receipt
FROM book
	INNER JOIN visitor_has_book USING(book_id)
	INNER JOIN library_visitor USING(passport_number)
ORDER BY library_visitor.surname, visitor_has_book.date_of_receipt;

SELECT library_visitor.surname, library_visitor.passport_number
FROM library_visitor
	INNER JOIN visitor_has_book USING(passport_number)
WHERE  visitor_has_book.date_of_receipt <= CURRENT_DATE - INTERVAL '1 month'
GROUP BY (library_visitor.surname, library_visitor.passport_number);

SELECT library_visitor.surname, library_visitor.passport_number
FROM visitor_has_book
	INNER JOIN  library_visitor USING(passport_number)
WHERE visitor_has_book.book_id IN (
	SELECT reading_hall_has_book.book_id FROM reading_hall_has_book
	GROUP BY reading_hall_has_book.book_id
	HAVING SUM(reading_hall_has_book.amount) <= 2) 
ORDER BY library_visitor.surname;

SELECT COUNT(*) AS "Количесво читателей" FROM library_visitor;


SELECT COUNT(*) AS "Количество читателей младше 20" FROM library_visitor
WHERE birth_date > CURRENT_DATE - INTERVAL '20 year';
