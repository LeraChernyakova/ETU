class HouseScheme:
    def __init__(self, Rooms, Square, Bath):
        if (Square > 0) and (Rooms > 0) and (type(Bath) == bool):
            self.Rooms = Rooms
            self.Square = Square
            self.Bath = Bath
        else:
            raise ValueError('Invalid value')

class CountryHouse(HouseScheme):
    def __init__(self, Rooms, Square, Bath, Floors, Plottage):
        super().__init__(Rooms, Square, Bath)
        if (Floors > 0) and (Plottage > 0):
            self.Floors = Floors
            self.Plottage = Plottage
        else:
            raise ValueError('Invalid value')
    def __str__(self):
        return "Country House: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Количество этажей {}, Площадь участка {}.".format(self.Rooms, self.Square, self.Bath, self.Floors, self.Plottage)
    def __eq__(self, other):
        if (self.Square == other.Square) and (self.Plottage == other.Plottage) and (abs(self.Floors - other.Floors) <= 1):
            return True
        else:
            return False
  
class Apartment(HouseScheme):
    def __init__(self, Rooms, Square, Bath, Floors, Windows):
        super().__init__(Rooms, Square, Bath)
        if (Floors <= 15) and (Floors >= 1) and (Windows in ['N', 'S', 'W', 'E']):
            self.Floors = Floors
            self.Windows = Windows
        else:
            raise ValueError('Invalid value')
    def __str__(self):
        return "Apartment: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Этаж {}, Окна выходят на {}.".format(self.Rooms, self.Square, self.Bath, self.Floors, self.Windows)

class CountryHouseList(list):
    def __init__(self, name):
        super().__init__(self)
        self.name = name
    def append(self, p_object):
        if isinstance(p_object, CountryHouse):
            super().append(p_object)
        else:
            raise TypeError("Invalid type {}".format(type(p_object)))
    def total_square(self):
        ls = list(map(lambda x: x.Square, self))
        return sum(ls)

class ApartmentList(list):
    def __init__(self, name):
        super().__init__(self)
        self.name = name
    def extend(self, iterable):
        super().extend(list(filter(lambda x: isinstance(x, Apartment), iterable)))
    def floor_view(self, floors, directions):
        res = list(filter(lambda x: (x.Floors <= floors[1]) and (x.Floors >= floors[0]) and (x.Windows in directions), self))
        for i in res:
            print("{}: {}".format(i.Windows, i.Floors))

