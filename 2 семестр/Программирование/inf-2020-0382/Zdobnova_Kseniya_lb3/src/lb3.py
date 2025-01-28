class HouseScheme():
    def __init__(self, number_of_rooms, square, combined_bathroom):
        if square >= 0 and type(combined_bathroom) == bool:
            self.combined_bathroom = combined_bathroom
            self.square = square
            self.number_of_rooms = number_of_rooms
        else:
            raise ValueError('Invalid value')

class CountryHouse(HouseScheme):
    def __init__(self, number_of_rooms, square, combined_bathroom, number_of_floors, land_area):
        super().__init__(number_of_rooms, square, combined_bathroom)
        if number_of_floors >= 0 and land_area >= 0:
            self.land_area = land_area
            self.number_of_floors = number_of_floors
        else:
            raise ValueError('Invalid value')
        
    def __str__(self):
        return 'Country House: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Количество этажей {}, Площадь участка {}.'.format(self.number_of_rooms, self.square, self.combined_bathroom, self.number_of_floors, self.land_area)

    def __eq__(self, object):
        if self.square  == object.square and self.land_area == object.land_area and abs(self.number_of_floors - object.number_of_floors) <= 1:
            return True
        return False

class Apartment(HouseScheme):
    def __init__(self, number_of_rooms, square, combined_bathroom, floor, direction):
        super().__init__(number_of_rooms, square, combined_bathroom)
        if square >= 0 and type(combined_bathroom) == bool and (floor >= 1 and floor <= 15) and (direction == 'N' or direction == 'S' or direction == 'W' or direction == 'E'):
            self.floor = floor
            self.direction = direction
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return 'Apartment: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Этаж {}, Окна выходят на {}.'.format(self.number_of_rooms, self.square, self.combined_bathroom, self.floor, self.direction)
    
class CountryHouseList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if type(p_object) == CountryHouse:
            super().append(p_object)
        else:
            raise TypeError('Invalid type {}'.format(type(p_object)))

    def total_square(self):
        total_area = 0
        for i in range(len(self)):
            total_area += self[i].square
        return total_area

class ApartmentList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        super().extend(filter(lambda x: type(x) == Apartment, iterable))

    def floor_view(self, floors, directions):
        for i in filter(lambda x: floors[0]<= x.floor <= floors[1] and x.direction in directions, self):
            print ('{}: {}'.format(i.direction, i.floor))
