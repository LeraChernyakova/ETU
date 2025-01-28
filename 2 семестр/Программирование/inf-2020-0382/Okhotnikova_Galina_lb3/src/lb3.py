class HouseScheme:
    def __init__(self, count_rooms, square, bathroom):
        if (count_rooms > 0) and (square > 0) and (type(bathroom) == bool):
            self.count_rooms = count_rooms
            self.square = square
            self.bathroom = bathroom
        else:
            raise ValueError('Invalid value')


class CountryHouse(HouseScheme): 
    def __init__(self, count_rooms, square, bathroom, count_floors, square2):
        super().__init__(count_rooms, square, bathroom)
        if count_floors > 0 and square2 > 0:
            self.count_floors = count_floors
            self.square2 = square2
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return 'Country House: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Количество этажей {}, Площадь участка {}.'.format(
            self.count_rooms, self.square, self.bathroom, self.count_floors, self.square2)

    def __eq__(self, other):
        if self.square == other.square and self.square2 == other.square2 and abs(
                self.count_floors - other.count_floors) <= 1:
            return True
        else:
            return False


class Apartment(HouseScheme):
    def __init__(self, count_rooms, square, bathroom, floor, window):
        super().__init__(count_rooms, square, bathroom)
        if floor >= 1 and floor <= 15 and window in ['N', 'S', 'W', 'E']:
            self.floor = floor
            self.window = window
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return 'Apartment: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Этаж {}, Окна выходят на {}.'.format(
        self.count_rooms, self.square, self.bathroom, self.floor, self.window)


class CountryHouseList(list): 
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if issubclass(type(p_object), CountryHouse):
            super().append(p_object)
        else:
            raise TypeError(f'Invalid type {type(p_object)}')

    def total_square(self):
        __total_area = 0
        for i in self:
            __total_area += i.square
        return __total_area


class ApartmentList(list):  
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        super().extend(filter(lambda x: type(x) == Apartment, iterable))


    def floor_view(self, floors, directions):
        checking = list(filter(lambda i: (i.window in directions) and (i.floor in list(range(floors[0], floors[1] + 1))), self))
        for i in checking:
            print('{}: {}'.format(i.window, i.floor))
