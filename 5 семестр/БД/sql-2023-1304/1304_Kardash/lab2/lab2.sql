CREATE TABLE driver(passport_date VARCHAR(11), registry_number VARCHAR(12), route_number VARCHAR(5), class VARCHAR(5), experience DECIMAL);
INSERT INTO driver VALUES ('1123987643', 'a778bk198', '222','B',1);
INSERT INTO driver VALUES ('7610123467','Х859ВО18','234','C',10),('4361590852','Е691КМ35','156','D',21),('4811829613','К936СХ76','181','B',12),('4721888851','С645ХМ75','222','E',7),('4733810936','С369СХ40','222','C',9),('4735505207','А522ЕК87','181','C',31);

CREATE TABLE salary (class VARCHAR(5), experience DECIMAL, salary DECIMAL);
INSERT INTO salary VALUES ('B',1,30000),('C',10,37000),('D',21,40000),('B',12,32500),('E',7,39000),('C',9,36500),('C',31,42000);

CREATE TABLE type_bus(type VARCHAR(20),capacity INT);
INSERT INTO type_bus VALUES ('city',40),('intercity',80),('mini',25);

CREATE TABLE route( route_number VARCHAR(10), start_point VARCHAR(20), end_point VARCHAR(20), time_start_point VARCHAR(20), time_end_point VARCHAR(20),  movement_interval INT, length INT);
INSERT INTO route (route_number, start_point,end_point, time_start_point, time_end_point, movement_interval, length) VALUES ('222', 'Cheremushki','Lesistoe','6:00', '22:00' ,60,30), ('234','Mokroe', 'Bor', '8:00', '23:00', 120, 60), ('156','Lesistoe', 'Bor', '6:40','22:40',90,60), ('181', 'railway station', 'Lesistoe', '4:00', '21:00', 40, 20);

CREATE TABLE bus (registry_number VARCHAR(12), status_id INT, passport_date VARCHAR(11), route_number VARCHAR(10), type VARCHAR(20));
INSERT INTO bus(registry_number, status_id, passport_date, route_number, type) VALUES ('a778bk198',0,'1123987643', '222','mini'), ('Х859ВО18',0,'7610123467','234','city'), ('Е691КМ35',0,'4361590852', '156','intercity'), ('К936СХ76',0,'4811829613','181','city'), ('С645ХМ75',1,'4721888851','222', 'mini'), ('С369СХ40',0,'4733810936','222','intercity'), ('А522ЕК87',0,'4735505207','181','intercity'), ('A122TM60',2,'','156','mini');

CREATE TABLE status(status_id INT NOT NULL, is_properly BOOLEAN, fail_reason VARCHAR(20));                    
INSERT INTO status (status_id, is_properly, fail_reason) VALUES (0,true,'bus work correct'), (1, false,'bus breakdown'), (2,false,'no driver');

CREATE TABLE trip(passport_date VARCHAR(11), registry_number VARCHAR(12), route_number VARCHAR(10), date DATE,time TIME);
INSERT INTO trip (passport_date, registry_number, route_number, date,time) VALUES ('1123987643', 'a778bk198', '222', '2023-08-10','06:00'),('1123987643', 'a778bk198', '222', '2023-08-10','07:00'), ('4733810936','С369СХ40','222','2023-08-10','14:00'), ('7610123467','Х859ВО18','234','2023-08-10','08:00'),('4361590852','Е691КМ35','156','2023-08-10','06:40'),('4361590852','Е691КМ35','156','2023-08-10','08:10'),('4811829613','К936СХ76','181','2023-08-10','04:00'),('4735505207','А522ЕК87','181','2023-08-10','04:40'),('4733810936','С369СХ40','222','2023-08-10','20:00'),('4811829613','К936СХ76','181','2023-08-10','06:00');

ALTER TABLE driver ADD PRIMARY KEY (passport_date);
ALTER TABLE salary ADD PRIMARY KEY (class,experience);
ALTER TABLE type_bus ADD PRIMARY KEY (type);
ALTER TABLE route ADD PRIMARY KEY (route_number);
ALTER TABLE bus ADD PRIMARY KEY (registry_number);
ALTER TABLE status ADD PRIMARY KEY (status_id);
ALTER TABLE trip ADD PRIMARY KEY (passport_date,registry_number,route_number,date,time);
ALTER TABLE driver ADD CONSTRAINT driver_bus FOREIGN KEY (registry_number) REFERENCES bus (registry_number);
ALTER TABLE driver ADD CONSTRAINT driver_route FOREIGN KEY (route_number) REFERENCES route (route_number);
ALTER TABLE driver ADD CONSTRAINT driver_salary FOREIGN KEY (class,experience) REFERENCES salary (class,experience);
ALTER TABLE bus ADD CONSTRAINT bus_driver FOREIGN KEY (route_number) REFERENCES route (route_number);
ALTER TABLE bus ADD CONSTRAINT bus_status FOREIGN KEY (status_id) REFERENCES status (status_id);
ALTER TABLE bus ADD CONSTRAINT bus_type FOREIGN KEY (type) REFERENCES type_bus (type);

Select driver.route_number, passport_date, time_start_point, time_end_point
From driver Join route On driver.route_number = route.route_number
Order By driver.route_number

SELECT registry_number, route_number
FROM bus
ORDER BY route_number;

SELECT route_number,start_point,end_point
FROM route
WHERE start_point ='Lesistoe' OR end_point ='Lesistoe'
GROUP BY route_number,start_point,end_point;


SELECT route_number, time_start_point, time_end_point
FROM route
GROUP BY route_number;

SELECT route_number,length 
FROM route
GROUP BY route_number;

SELECT sum(length) AS Общая_протяженность
FROM route;

Select registry_number as Невышедшие_автобусы, fail_reason, bus.status_id
From bus Join status On bus.status_id = status.status_id
Where bus.status_id <> 0
