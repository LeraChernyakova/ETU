class HouseScheme:
    def __init__(self, room_amount, area, comb_bath):
        if type(comb_bath) == bool and area >= 0:
            self.room_amount = room_amount
            self.area = area
            self.comb_bath = comb_bath
        else:
            raise ValueError('Invalid value')


class CountryHouse(HouseScheme):
    def __init__(self, room_amount, area, comb_bath, floors_amount, land_area):
        super().__init__(room_amount, area, comb_bath)
        self.floors_amount = floors_amount
        self.land_area = land_area


    def __str__(self):
        return "Country House: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Количество " \
               "этажей {}, Площадь участка {}.".format(self.room_amount, self.area, self.comb_bath,
                                                       self.floors_amount, self.land_area)

    def __eq__(self, other):
        return self.area == other.area and self.land_area == other.land_area and abs(self.floors_amount - other.floors_amount) <= 1


class Apartment(HouseScheme):
    window_directions = ['N', 'S', 'W', 'E']

    def __init__(self, room_amount, area, comb_bath, floor, win_dir):
        super().__init__(room_amount, area, comb_bath)
        if (1 <= floor <= 15) and (win_dir in Apartment.window_directions):
            self.floor = floor
            self.win_dir = win_dir
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return 'Apartment: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Этаж {}, ' \
               'Окна выходят на {}.'.format(self.room_amount, self.area, self.comb_bath, self.floor, self.win_dir)


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
        total_area = 0
        for i in self:
            total_area += i.area
        return total_area


class ApartmentList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        for i in iterable:
            if isinstance(i, Apartment):
                self.append(i)

    def floor_view(self, floors, directions):
        for i in filter(lambda x: floors[0] <= x.floor <= floors[1] and x.win_dir in directions, self):
            print('{}: {}'.format(i.win_dir, i.floor))

