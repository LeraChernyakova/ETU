CREATE TABLE IF NOT EXISTS cleaner
(
    id_cleaner integer NOT NULL,
    name text COLLATE pg_catalog."default" NOT NULL,
    second_name text COLLATE pg_catalog."default",
    patronymic text COLLATE pg_catalog."default",
    CONSTRAINT cleaner_pkey PRIMARY KEY (id_cleaner)
);
   
CREATE TABLE IF NOT EXISTS cleaning
(
    week_day text COLLATE pg_catalog."default" NOT NULL,
    floor integer NOT NULL,
    id_cleaner integer NOT NULL,
    CONSTRAINT cleaning_pkey PRIMARY KEY (week_day, floor),
    CONSTRAINT cleaning_id_cleaner_fkey FOREIGN KEY (id_cleaner)
        REFERENCES cleaner (id_cleaner)
); 
            
CREATE TABLE IF NOT EXISTS room_type
(
    bed_amount integer NOT NULL,
    price numeric NOT NULL,
    CONSTRAINT room_type_pkey PRIMARY KEY (bed_amount)
);
    
CREATE TABLE IF NOT EXISTS client
(
    passport integer NOT NULL,
    name text COLLATE pg_catalog."default" NOT NULL,
    second_name text COLLATE pg_catalog."default",
    patronymic text COLLATE pg_catalog."default",
    city text COLLATE pg_catalog."default",
    CONSTRAINT client_pkey PRIMARY KEY (passport)
);
    
CREATE TABLE IF NOT EXISTS room
(
    room_number integer NOT NULL,
    bed_amount integer NOT NULL,
    phone integer,
    floor integer NOT NULL,
    CONSTRAINT room_pkey PRIMARY KEY (room_number),
    CONSTRAINT room_bed_amount_fkey FOREIGN KEY (bed_amount)
        REFERENCES room_type (bed_amount)

);

CREATE TABLE IF NOT EXISTS room_reserve
(
    room_number integer NOT NULL,
    passport integer NOT NULL,
    check_in_date date NOT NULL,
    check_out_date date,
    CONSTRAINT room_reserve_pkey PRIMARY KEY (room_number, passport, check_in_date),
    CONSTRAINT room_reserve_passport_fkey FOREIGN KEY (passport)
        REFERENCES client (passport),
    CONSTRAINT room_reserve_room_number_fkey FOREIGN KEY (room_number)
        REFERENCES room (room_number)
);




INSERT INTO client(passport, name, second_name, patronymic, city)
 VALUES (1234123456, 'Саша','Привет', 'Викторовна','Санкт-Петербург'),
 		(1234123457, 'Маша','Пока', 'Сергеевна', 'Тихвин'),
		(1234123458,'Паша','Здравствуй' ,null,'Санкт-Петербург'),
		(1234123459, 'Даша','Добрый' ,null,'Санкт-Петербург'),
		(1234123460, 'Саша','Злой' ,null,'Екатеринбург'),
		(1234123461,'Александр','Нормальный' ,null,'Москва'),
		(1234123462,'Виктория','Мать' ,'Сергеевна','Курск'),
		(1234123463, 'Вадик','Немать' ,'Сергеевич','Санкт-Петербург');

INSERT INTO room_type(bed_amount, price)
VALUES (1, 1000.00),
 		(2, 1500.00),
 		(3, 2500.00),
 		(4, 3500.00),
 		(5, 5000.00);

INSERT INTO room (room_number, bed_amount, phone, floor)
VALUES (12, 1, 8945647, 2),
 		(13, 2, 8955647, 1),
		(176, 1, 4945647, 3),
		(14, 3, 8954647, 1),
		(121, 1, 8945697, 2),
 		(11, 2, 8995647, 3);


INSERT INTO room_reserve (room_number, passport, 
						   check_in_date, check_out_date)
VALUES (12, 1234123456, '2023-03-22', '2023-03-25'),
 		(13, 1234123458, '2023-03-22', '2023-03-28'),
		(176, 1234123460, '2023-03-22', '2023-03-26'),
		(13, 1234123462, '2023-03-22', null),
		(14, 1234123461, '2023-03-22', null);

INSERT INTO cleaner(id_cleaner, name, second_name, patronymic)
VALUES (1, 'Виталий','Сергеевич', 'Викторовна'),
 		(2, 'Арина','Арина', 'Васильевич'),
		(3,'Паша','Петров' ,null),
		(4, 'Даша','Фёдоров' ,null),
		(5, 'Саша','Иванов' ,null),
		(6,'Александр','Коробкин' ,null),
		(7,'Виктория','Крутой' ,'Николаевич'),
		(8, 'Василий','Кружка' ,'Сергеевич');

INSERT INTO cleaning(week_day, floor, id_cleaner)
VALUES ('Mon', 2, 1),
 		('Wed', 1, 2),
 		('Sun', 3, 1),
 		('Sat', 4, 3),
 		('Fri', 3, 4),
 		('Thu', 2, 5);




SELECT passport, name,second_name, patronymic, city
FROM client
INNER JOIN room_reserve USING(passport)
WHERE room_number  = '12' AND check_in_date IS NOT NULL 
	AND check_out_date IS NOT NULL; 
	
SELECT passport, name,second_name, patronymic, city
FROM client
WHERE city  = 'Санкт-Петербург'; 

SELECT client.name, room_number, week_day,cleaner.id_cleaner,cleaner.name
FROM client
INNER JOIN room_reserve USING(passport)
INNER JOIN room USING(room_number)
INNER JOIN cleaning USING(floor)
INNER JOIN cleaner USING(id_cleaner)
WHERE client.name = 'Саша' AND week_day = 'Mon'; 

SELECT COUNT(*) AS AMOUNT
FROM room
WHERE room_number NOT IN (
SELECT room_number
FROM room_reserve
where check_in_date IS NOT NULL AND check_out_date IS NULL
);

INSERT INTO cleaner (id_cleaner, name, second_name, patronymic)
VALUES (10, 'Вадим', 'Иванов', 'Иванович');




DELETE FROM cleaner
WHERE id_cleaner = 10; 

UPDATE cleaning 
SET week_day = 'Wed' 
WHERE week_day = 'Mon' AND id_cleaner = 2;

UPDATE room_reserve 
SET check_out_date = current_date
WHERE passport = 1234123456;

INSERT INTO client(passport, name, second_name, patronymic, city)
VALUES (1234123470, 'Саша','Опять', 'Витальевна','Санкт-Петербург');

INSERT INTO room_reserve (room_number, passport, 

						   check_in_date, check_out_date)
VALUES (12, 1234123470, current_date,null);

