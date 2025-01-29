CREATE TABLE owner (
	passport VARCHAR(11) PRIMARY KEY,
	surname VARCHAR(255),
	name VARCHAR(255),
	patronymic VARCHAR(255)
); 

CREATE TABLE ring (
	ring_number serial PRIMARY KEY
);

CREATE TABLE breed (
	breed_name VARCHAR(255) PRIMARY KEY,
	ring_number serial,
	FOREIGN KEY (ring_number) REFERENCES ring (ring_number)
);

CREATE TABLE club (
	club_id serial PRIMARY KEY,
	club_name VARCHAR(255),
	participants_number INT
);

CREATE TABLE expert (
	expert_id serial PRIMARY KEY,
	surname VARCHAR(255),
	name VARCHAR(255),
	club_id serial,
	ring_number serial,
	FOREIGN KEY (club_id) REFERENCES club (club_id),
	FOREIGN KEY (ring_number) REFERENCES ring (ring_number)
);

CREATE TABLE dog (
	dog_number serial PRIMARY KEY,
	owner_passport VARCHAR(11),
	breed_name VARCHAR(255),
	FOREIGN KEY (owner_passport) REFERENCES owner (passport),
	FOREIGN KEY (breed_name) REFERENCES breed (breed_name),
	pedigree_document_number INT NOT NULL,
	mother_nickname VARCHAR(255),
	father_nickname VARCHAR(255),
	nickname VARCHAR(255),
	age INT,
	vaccination_date DATE
);

CREATE TABLE dog_expert_estimate (
	dog_number serial,
	expert_id serial,
	FOREIGN KEY (dog_number) REFERENCES dog (dog_number),
	FOREIGN KEY (expert_id) REFERENCES expert (expert_id),
	estimate INT,
	PRIMARY KEY (dog_number, expert_id)
);

CREATE TABLE club_numbers (
	dog_number serial,
	club_id serial,
	FOREIGN KEY (dog_number) REFERENCES dog (dog_number),
	FOREIGN KEY (club_id) REFERENCES club (club_id),
	PRIMARY KEY (dog_number, club_id)
);




INSERT INTO ring
VALUES (DEFAULT), (DEFAULT), (DEFAULT), (DEFAULT), (DEFAULT); 
       
INSERT INTO breed (breed_name, ring_number)
VALUES ('Немецкая овчарка', 1),
       ('Доберман', 1),
       ('Померанский шпиц', 2),
       ('Йоркширский терьер', 3),
       ('Бультерьер', 4),
       ('Пудель', 5);
        
INSERT INTO club (club_name, participants_number)
VALUES ('Фаворит', 4),
       ('Оскар', 4),
       ('Статус', 4),
       ('Звезда', 3),
       ('Победа', 2);   
       
INSERT INTO expert (club_id, ring_number, surname, name)
VALUES (1, 1, 'Кардаш', 'Ярослав'),
       (2, 1, 'Шаврин', 'Алексей'),
       (2, 1, 'Дешура', 'Дмитрий'),
       (3, 3, 'Ефремов', 'Артем'),
       (4, 4, 'Есенина', 'Анастасия'),
       (5, 5, 'Насекина', 'Алена'),
       (5, 2, 'Лепс', 'Григорий');

INSERT INTO owner (passport, surname, name, patronymic)
VALUES ('1111 222222', 'Потолов', 'Олег', 'Алексеевич'),
       ('2222 333333', 'Зубов', 'Александр', 'Андреевич'),
       ('3333 444444', 'Башкирев', 'Алексей', 'Владимирович'),
       ('4444 555555', 'Иванов', 'Иван', 'Иванович'),
       ('5555 666666', 'Добрицкий', 'Ярослав', 'Валерьевич'),
       ('6666 777777', 'Игнатьев', 'Владимир', 'Владимирович'),
       ('7777 888888', 'Бочаров', 'Никита', 'Игоревич'),
       ('8888 999999', 'Данилов', 'Дмитрий', 'Семенович');
       
INSERT INTO dog
VALUES (DEFAULT, '1111 222222', 'Немецкая овчарка', 1111111, 'Элис', 'Арчи', 'Рекс', 5, '2023-10-01'),
       (DEFAULT, '1111 222222', 'Доберман', 1111112, 'Меган', 'Дизель', 'Рокс', 7, '2023-09-27'),
       (DEFAULT, '2222 333333', 'Немецкая овчарка', 2222221, 'Меган', 'Дизель', 'Рокс', 8, '2023-09-06'),
       (DEFAULT, '2222 333333', 'Доберман', 2222222, 'Элис', 'Арчи', 'Рекс', 6, '2023-09-06'),
       (DEFAULT, '3333 444444', 'Немецкая овчарка', 3333331, 'Элли', 'Оливер', 'Раймонд', 7, '2023-09-12'),
       (DEFAULT, '3333 444444', 'Доберман', 3333332, 'Эмма', 'Руди', 'Алекс', 9, '2023-09-23'),
       (DEFAULT, '4444 555555', 'Немецкая овчарка', 4444441, 'Герда', 'Пит', 'Балу', 5, '2023-09-29'),
       (DEFAULT, '4444 555555', 'Пудель', 4444442, 'Витта', 'Мэверик', 'Гектор', 5, '2023-09-22'),
       (DEFAULT, '5555 666666', 'Бультерьер', 5555551, 'Грейт', 'Веня', 'Барон', 8, '2023-09-15'),
       (DEFAULT, '5555 666666', 'Пудель', 5555552, 'Инга', 'Ефим', 'Герой', 4, '2023-09-16'),
       (DEFAULT, '6666 777777', 'Бультерьер', 6666661, 'Лейла', 'Джанго', 'Кекс', 4, '2023-09-03'),
       (DEFAULT, '6666 777777', 'Пудель', 6666662, 'Скай', 'Зевс', 'Моджо', 7, '2023-09-08'),
       (DEFAULT, '7777 888888', 'Померанский шпиц', 7777771, 'Руни', 'Мич', 'Зефирка', 4, '2023-10-01'),
       (DEFAULT, '7777 888888', 'Йоркширский терьер', 7777772, 'Барби', 'Ник', 'Пряник', 4, '2023-09-28'),
       (DEFAULT, '8888 999999', 'Померанский шпиц', 8888881, 'Джесси', 'Зик', 'Ерошка', 6, '2023-09-20'),
       (DEFAULT, '8888 999999', 'Йоркширский терьер', 8888882, 'Кристи', 'Сириус', 'Цезарь', 6, '2023-09-17'),
       (DEFAULT, '8888 999999', 'Йоркширский терьер', 8888883, 'Фокс', 'Арчи', 'Тимка', 7, '2023-09-17');

INSERT INTO club_numbers
VALUES (1, 1), (2, 1),
       (3, 1), (4, 1),
       (5, 2), (6, 2),
       (7, 2), (8, 2),
       (9, 3), (10, 3),
       (11, 3), (12, 3),
       (13, 5), (14, 5),
       (15, 4), (16, 4),
       (17, 4);

INSERT INTO dog_expert_estimate (dog_number, expert_id, estimate)
VALUES (1, 1, 9), (3, 1, 6), (5, 1, 8), (7, 1, 7),
       (1, 2, 10), (3, 2, 7), (5, 2, 9), (7, 2, 8),
       (2, 3, 7), (4, 3, 10), (6, 3, 8),
       (8, 6, 10), (10, 6, 10), (12, 6, 8),
       (9, 5, 8), (11, 5, 9),
       (14, 4, 5), (16, 4, 7), (17, 4, 8),
       (13, 7, 10), (15, 7, 10);




  SELECT breed.ring_number, dog.dog_number, owner.surname, owner.name, owner.patronymic
    FROM owner
         INNER JOIN dog ON owner.passport = dog.owner_passport
         INNER JOIN breed USING(breed_name)
ORDER BY breed.ring_number, dog.dog_number, owner.surname, owner.name, owner.patronymic;
 

  SELECT club.club_id, dog.breed_name
    FROM club
         INNER JOIN club_numbers USING(club_id)
         INNER JOIN dog USING(dog_number)
GROUP BY club.club_id, dog.breed_name
ORDER BY club.club_id, dog.breed_name;


WITH dog_places AS (
	SELECT dog.breed_name, dog.dog_number, ROUND(AVG(dog_expert_estimate.estimate), 2) AS Estimate,
		   DENSE_RANK() OVER (PARTITION BY dog.breed_name ORDER BY ROUND(AVG(dog_expert_estimate.estimate), 2) DESC) AS place
	  FROM dog
		   INNER JOIN dog_expert_estimate USING(dog_number)
	GROUP BY dog.breed_name, dog.dog_number
	ORDER BY dog.breed_name, Estimate DESC
)
  SELECT club.club_id, club.club_name, dog_places.place, COUNT(dog_places.place)
    FROM club
         INNER JOIN club_numbers USING(club_id)
	     INNER JOIN dog_places USING(dog_number)
GROUP BY club.club_id, club.club_name, dog_places.place
ORDER BY club.club_id, dog_places.place;


  SELECT dog.breed_name, expert.expert_id, expert.name, expert.surname
    FROM dog
         INNER JOIN dog_expert_estimate USING(dog_number)
         INNER JOIN expert USING(expert_id)
GROUP BY dog.breed_name, expert.expert_id
ORDER BY dog.breed_name;


  SELECT dog.breed_name, COUNT(*)
    FROM dog
GROUP BY dog.breed_name
ORDER BY dog.breed_name;
