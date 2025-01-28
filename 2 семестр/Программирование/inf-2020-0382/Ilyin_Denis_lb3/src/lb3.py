class HouseScheme:
    def __init__(self, new_room, new_size, new_san):
        if ((new_size >= 0) and (type(new_san) == bool)):
            self.room = new_room
            self.size = new_size
            self.san = new_san
        else:
            raise ValueError('Invalid value')

class CountryHouse(HouseScheme):
    def __init__(self, new_room, new_size, new_san, new_height, new_space):
        super().__init__(new_room, new_size, new_san)
        self.height = new_height
        self.space = new_space

    def __str__(self):
        return f'Country House: Количество жилых комнат {self.room}, Жилая площадь {self.size}, Совмещенный санузел {self.san}, Количество этажей {self.height}, Площадь участка {self.space}.'

    def __eq__(self, other):
        if (self.size == other.size) and (self.height -1 <= other.height <= self.height +1):
            return True
        else:
            return False

class Apartment(HouseScheme):
    def __init__(self, new_room, new_size, new_san, new_floor, new_side):
        if ((1 <= new_floor <= 15) and (new_side in ['N', 'S', 'W', 'E'])):
            super().__init__(new_room, new_size, new_san)
            self.floor = new_floor
            self.side = new_side
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return f"Apartment: Количество жилых комнат {self.room}, Жилая площадь {self.size}, Совмещенный санузел {self.san}, Этаж {self.floor}, Окна выходят на {self.side}."

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
        __a = 0
        for i in self:
            __a += i.size
        return __a

class ApartmentList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        super().extend(filter(lambda x: type(x) == Apartment, iterable))

    def floor_view(self, floors, directions):
        norm_hight = lambda x: True if (floors[0] <= x.floor) and (x.floor <= floors[1]) else False
        norm_side = lambda x: True if x.side in directions else False
        norm_Apartment = list(set(filter(norm_hight, self)) & set(filter(norm_side, self)))
        endstr = []
        for i in norm_Apartment:
            endstr.append(f'{i.side}: {i.floor}')
        print('\n'.join(endstr))
