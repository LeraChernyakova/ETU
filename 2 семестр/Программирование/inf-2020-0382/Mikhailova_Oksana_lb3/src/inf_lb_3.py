class HouseScheme:
    
    def __init__(self, count_rooms, square, combined_bath):
        if (square >= 0) and (type(combined_bath) == bool):
            self.count_rooms = count_rooms
            self.square = square
            self.combined_bath = combined_bath
        else:
            raise ValueError('Invalid value')
            
class CountryHouse(HouseScheme): 
    
    def __init__(self, count_rooms, square, combined_bath, count_floors, land_area):
        super().__init__(count_rooms, square, combined_bath)
        self.count_floors = count_floors
        self.land_area = land_area

    def __str__(self):
        return 'Country House: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Количество этажей {}, Площадь участка {}.'.format(self.count_rooms, self.square, self.combined_bath, self.count_floors, self.land_area)

    def __eq__(self, other):
        if (self.square == other.square) and (self.land_area == other.land_area) and (abs(self.count_floors - other.count_floors) <= 1):
            return True
        else:
            return False
    
class Apartment(HouseScheme): 
    
    def __init__(self, count_rooms, square, combined_bath, floor, window):
        super().__init__(count_rooms, square, combined_bath)
        if (floor >= 1) and (floor <= 15) and (window in ['N', 'S', 'W', 'E']):
            self.floor = floor
            self.window = window
        else: 
            raise ValueError('Invalid value')

    def __str__(self):
        return 'Apartment: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Этаж {}, Окна выходят на {}.'.format(self.count_rooms, self.square, self.combined_bath, self.floor, self.window)
 
    
class CountryHouseList(list):
    def __init__(self, name):
        self.name = name
        
    def append(self, p_object):
        if type(p_object) == CountryHouse:
            super().append(p_object)
        else:
            raise TypeError('Invalid type {}'.format(type(p_object)))

    def total_square(self):
        total_square = 0
        for i in self:
            total_square += i.square
        return total_square
        
class ApartmentList(list):
    def __init__(self, name):
        self.name = name

    def extend(self, iterable):
        iterable = list(filter(lambda x: type(x) == Apartment, iterable))
        super().extend(iterable)

    def floor_view(self, floors, directions):
        check = list(filter(lambda x: x.floor >= floors[0] and x.floor <= floors[1] and x.window in directions, self))
        for i in check:
            print('{}: {}'.format(i.window, i.floor))
  
