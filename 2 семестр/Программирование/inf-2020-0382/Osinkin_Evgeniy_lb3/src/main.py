class HouseScheme:
    def __init__(self, rooms, area, bathroom):
        if rooms >= 0 and area >= 0 and type(bathroom) == bool:
            self.rooms = rooms
            self.area = area
            self.bathroom = bathroom
        else:
            raise ValueError('Invalid value')


class CountryHouse(HouseScheme):
    def __init__(self, rooms, area, bathroom, storey, ter_area):
        super().__init__(rooms, area, bathroom)
        if storey >= 0 and ter_area >= 0:
            self.storey = storey
            self.ter_area = ter_area
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return "Country House: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, " \
               "Количество этажей " \
               "{}, Площадь участка {}.".\
            format(self.rooms, self.area, self.bathroom, self.storey, self.ter_area)

    def __eq__(self, new_house):
        return new_house.area == self.area and new_house.ter_area == self.ter_area and -1 <= \
               (new_house.storey-self.storey) <= 1


class Apartment(HouseScheme):
    def __init__(self, rooms, area, bathroom, storey, window):
        super().__init__(rooms, area, bathroom)
        if 1 <= storey <= 15 and (window in ['N', 'S', 'W', 'E']):
            self.storey = storey
            self.window = window
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return 'Apartment: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Этаж {}, ' \
               'Окна выходят на {}.'.\
            format(self.rooms, self.area, self.bathroom, self.storey, self.window)


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
        square = 0
        for item in self:
            square = square + item.area
        return square


class ApartmentList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, lst):
        super().extend(filter(lambda x: type(x) == Apartment, lst))

    def floor_view(self, floors, directions):
        result = list(filter(lambda x: (x.window in directions) and floors[0] <= x.storey <= floors[1], self))
        for item in result:
            print('{}: {}'.format(item.window, item.storey))
