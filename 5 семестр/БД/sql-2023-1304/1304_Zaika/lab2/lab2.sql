CREATE TABLE Shop(shop_number INT NOT NULL, class_name VARCHAR NOT NULL);
INSERT INTO Shop VALUES (22, 'econom'),(23, 'top'),(34, 'lux');

CREATE TABLE ShopPurchaseFromBase(shop_number INT NOT NULL, base_name VARCHAR NOT NULL);
INSERT INTO ShopPurchaseFromBase VALUES (32, 'First Base'),(32, 'Cold Meat'),(32, 'Drinks and Water'),(23, 'First Base'),(23, 'Baked sun'),(22, 'First Base'),(22, 'Drinks and Water');

CREATE TABLE Base(base_name VARCHAR NOT NULL);
INSERT INTO Base VALUES ('First Base'),('Cold Meat'),('Drinks and Water'),('Baked Sun');

CREATE TABLE Department(department_number INT NOT NULL, shop_number INT NOT NULL, manager_passport_number INT NOT NULL);
INSERT INTO Department VALUES (1, 23, 23451234),(2, 23, 54323412),(1, 22, 65437780),(2, 22, 54332355),(3, 22, 45340099),(4, 22, 54432200),(1, 34, 12347878),(2, 34, 45312349);

CREATE TABLE ProductInDepartment(department_number INT NOT NULL, product_name VARCHAR NOT NULL, poduct_amount INT);
INSERT INTO ProductInDepartment VALUES (1, 'milk', 30),(1, 'butter', 15),(2, 'bread', 20),(2, 'cookies', 30),(3, 'water', 40),(3, 'juice', 10),(4, 'meat', 50),(4, 'sausage', 30);

CREATE TABLE Product(product_name VARCHAR NOT NULL, grade INT);
INSERT INTO Product VALUES ('milk', 1),('butter', 1),('bread', 1),('water', 1),('meat', 2),('juice', 2),('sausage', 3),('cookies', 3);

CREATE TABLE ProductInBase(base_name VARCHAR NOT NULL, product_name VARCHAR NOT NULL, product_amount INT);
INSERT INTO ProductInBase VALUES ('First Base', 'milk', 600),('First Base', 'butter', 300),('Cold Meat', 'meat', 1000),('Cold Meat', 'sausage', 800),('Drinks and Water', 'water', 1500),('Drinks and Water', 'juice', 500),('Baked Sun', 'cookies', 100);

CREATE TABLE Class(class_name VARCHAR NOT NULL);
INSERT INTO Class VALUES ('lux'),('econom'),('top');

CREATE TABLE Price(product_name VARCHAR NOT NULL, class_name VARCHAR NOT NULL, retail_price INT);
INSERT INTO Price VALUES ('milk', 'lux', 100),('butter', 'lux', 200),('bread', 'lux', 80),('water', 'lux', 70),('meat', 'top', 300),('juice', 'top', 150),('sausage', 'econom', 250),('cookies', 'econom', 100);

CREATE TABLE Manager(passport_number INT NOT NULL, name VARCHAR, surname VARCHAR, patronymic VARCHAR);
INSERT INTO Manager VALUES (23451234, 'Ivan', 'Andreev', 'Andreevich'),(54323412, 'Katerina', 'Yagoda', 'Nikolaevna'),(65437780, 'Nikolai', 'Dmitrov', 'Aleskandrovich'),(54332355, 'Aleskandr', 'Smirnov', 'Alekseevich'),(45340099, 'Lybov', 'Mikola', 'Olegovna'),(54432200, 'Mihail', 'Tatrintsev', 'Ivanovich'),(12347878, 'Tatyana', 'Rubleva', 'Timofeevna'),(45312349, 'Grigoriy', 'Ivanov', 'Dmitovich');

ALTER TABLE Shop ADD PRIMARY KEY (shop_number, class_name);
ALTER TABLE ShopPurchaseFromBase ADD PRIMARY KEY (shop_number, base_name);
ALTER TABLE Base ADD PRIMARY KEY (base_name);
ALTER TABLE Department ADD PRIMARY KEY (department_number, shop_number);
ALTER TABLE ProductInDepartment ADD PRIMARY KEY (department_number, product_name);
ALTER TABLE Product ADD PRIMARY KEY (product_name);
ALTER TABLE ProductInBase ADD PRIMARY KEY (base_name, product_name);
ALTER TABLE Class ADD PRIMARY KEY (class_name);
ALTER TABLE Price ADD PRIMARY KEY (product_name, class_name);
ALTER TABLE Manager ADD PRIMARY KEY (passport_number);

ALTER TABLE Shop ADD CONSTRAINT shop_class_name FOREIGN KEY (class_name) REFERENCES Class (class_name);
ALTER TABLE Department ADD CONSTRAINT department_manager_passport_number FOREIGN KEY (manager_passport_number) REFERENCES Manager (passport_number);
ALTER TABLE ProductInBase ADD CONSTRAINT bip_base_name FOREIGN KEY (base_name) REFERENCES Base (base_name);
ALTER TABLE ProductInBase ADD CONSTRAINT bip_product_name FOREIGN KEY (product_name) REFERENCES Product (product_name);
ALTER TABLE Price ADD CONSTRAINT price_product_name FOREIGN KEY (product_name) REFERENCES Product (product_name);
ALTER TABLE Department ADD shop_class_name VARCHAR;
ALTER TABLE Department ADD CONSTRAINT dep_shop_number FOREIGN KEY (shop_number, shop_class_name) REFERENCES Shop (shop_number, class_name);
ALTER TABLE Department ADD CONSTRAINT dep_manager_passport_number FOREIGN KEY (manager_passport_number) REFERENCES Manager (passport_number);
ALTER TABLE ProductInDepartment ADD department_shop_number INT;
ALTER TABLE ProductInDepartment ADD CONSTRAINT department_number FOREIGN KEY (department_number, department_shop_number) REFERENCES Department (department_number, shop_number);
ALTER TABLE ProductInDepartment ADD CONSTRAINT product_name FOREIGN KEY (product_name) REFERENCES Product (product_name);

SELECT shop.shop_number, productindepartment.product_name
FROM shop
JOIN department
ON shop.shop_number = department.shop_number
JOIN productindepartment
ON department.department_number = productindepartment.department_number
ORDER BY shop.shop_number;
SELECT base.base_name, productinbase.product_name
FROM base
JOIN productinbase
ON base.base_name = productinbase.base_name
WHERE productinbase.product_amount > 0
ORDER BY base.base_name;

UPDATE productindepartment
SET poduct_amount = 0
WHERE product_name = 'milk';
SELECT productindepartment.product_name, productinbase.base_name
FROM productindepartment
JOIN productinbase
ON productindepartment.product_name = productinbase.product_name
WHERE productindepartment.poduct_amount = 0 AND productinbase.product_amount > 0
ORDER BY productindepartment.product_name;

SELECT shop.shop_number, productindepartment.product_name,  productindepartment.department_number, productindepartment.poduct_amount
FROM shop
JOIN department
ON shop.shop_number = department.shop_number
JOIN productindepartment
ON department.department_number = productindepartment.department_number
ORDER BY shop.shop_number, productindepartment.department_number;

SELECT shop.shop_number, department.department_number, manager.name, manager.surname, manager.patronymic
FROM shop
JOIN department
ON shop.shop_number = department.shop_number
JOIN manager
ON department.manager_passport_number = manager.passport_number
ORDER BY shop.shop_number, department.department_number;

SELECT productindepartment.department_number, productindepartment.product_name, productindepartment.poduct_amount * price.retail_price AS total_product_price
FROM productindepartment
JOIN price
ON productindepartment.product_name = price.product_name
ORDER BY productindepartment.department_number;

SELECT productinbase.base_name, productinbase.product_amount
FROM productinbase
WHERE productinbase.product_name = 'water';