class HouseScheme:
    def __init__(self, rooms_number, square, bathroom):
        # validation
        if square < 0 or type(bathroom) != bool:
            raise ValueError("Invalid value")
        self.rooms_number = rooms_number
        self.square = square
        self.bathroom = bathroom
        
class CountryHouse(HouseScheme): # Класс должен наследоваться от HouseScheme
    def __init__(self, rooms_number, square, bathroom, floors_number, land_area):
        super().__init__(rooms_number, square, bathroom)
        if land_area < 0 or floors_number < 0:
            raise ValueError('Invalid value')
        self.floors_number = floors_number
        self.land_area = land_area

    def __str__(self):
        return \
        'Country House: Количество жилых комнат {0}, Жилая площадь {1}, Совмещенный санузел {2}, Количество этажей {3}, Площадь участка {4}.'.format(self.rooms_number, self.square, self.bathroom, self.floors_number, self.land_area) 
    

    def __eq__(self, obj):
        if self.square == obj.square and self.land_area == obj.land_area \
        and abs(self.floors_number - obj.floors_number) < 2:
            return True
        return False
    
    
class Apartment(HouseScheme):
    def __init__(self, rooms_number, square, bathroom, floor_number, windows_direct):
        super().__init__(rooms_number, square, bathroom)
        if floor_number < 1 or floor_number > 16 or windows_direct not in \
        ('N', 'S', 'W', 'E'):
            raise ValueError('Invalid value')
        self.floor_number = floor_number
        self.windows_direct = windows_direct

    def __str__(self):
        return \
        'Apartment: Количество жилых комнат {0}, Жилая площадь {1}, Совмещенный санузел {2}, Этаж {3}, Окна выходят на {4}.'.format(self.rooms_number, self.square, self.bathroom, self.floor_number, self.windows_direct) 
    

class CountryHouseList(list): # список деревенских домов -- "деревня", наследуется от класса list
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if not isinstance(p_object, CountryHouse):
            raise TypeError('Invalid type {}'.format(type(p_object)))
        super().append(p_object)

    def total_square(self):
        return sum([house.square for house in self.__iter__()])
        
class ApartmentList(list): # список городских квартир -- ЖК, наследуется от класса list
    def __init__(self, name):
        super().__init__()
        self.name = name
    
    def extend(self, iterable):
        valid_iterable = list(filter(lambda x: isinstance(x, Apartment), iterable))
        super().extend(valid_iterable)
        
    def floor_view(self, r, directs):
        apartments = list(filter(lambda x: x.floor_number in range(r[0], r[1] + 1) and \
        x.windows_direct in directs, self.__iter__()))
        message = '\n'.join(list(map(lambda x: x.windows_direct + ': ' + str(x.floor_number), apartments)))
        print(message)


