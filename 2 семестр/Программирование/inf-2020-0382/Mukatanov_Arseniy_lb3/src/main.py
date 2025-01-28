class HouseScheme:
    def __init__(self, num_of_room, area, comb_b):
        if area < 0 or type(combwc)!=bool:
            raise ValueError("Invalid value")
        self.num_of_room = num_of_room
        self.area = area
        self.comb_b = comb_b


class CountryHouse(HouseScheme):
    def __init__(self, num_of_room, area, comb_b, num_of_floors, land_area):
        super().__init__(num_of_room, area, comb_b)
        self.num_of_floors = num_of_floors
        self.land_area = land_area


    def __str__(self):
        return "Country House: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Количество " \
               "этажей {}, Площадь участка {}.".format(self.num_of_room, self.area, self.comb_b,self.num_of_floors, self.land_area)

    def __eq__(self, other):
        return self.area == other.area and self.land_area == other.land_area and abs(self.num_of_floors - other.num_of_floors) <= 1

class Apartment(HouseScheme):
    window_directions = ['N', 'S', 'W', 'E']

    def __init__(self, num_of_room, area, comb_b, floor, side):
        super().__init__(num_of_room, area, comb_b)
        if (1 <= floor <= 15) and (side in Apartment.window_directions):
            self.floor = floor
            self.side = side
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return 'Apartment: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Этаж {}, ' \
               'Окна выходят на {}.'.format(self.num_of_room, self.area, self.comb_b, self.floor, self.side)


class CountryHouseList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, CountryHouse):
            super().append(p_object)
        else:
            raise TypeError("Invalid type {}".format(type(p_object)))

    def total_square(self):
        res = 0
        for house in self:
            res+=house.area
        return res


class ApartmentList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        for i in iterable:
            if isinstance(i, Apartment):
                self.append(i)

    def floor_view(self, floors, directions):
        for i in filter(lambda x: floors[0] <= x.floor <= floors[1] and x.side in directions, self):
            print('{}: {}'.format(i.side, i.floor))