class HouseScheme():
    def __init__(self, living_rooms, territory, bathroom_unit):
        if (territory >= 0) and (type(bathroom_unit) == bool) and (living_rooms >= 0):
            self.territory = territory
            self.bathroom_unit = bathroom_unit
            self.living_rooms = living_rooms
        else:
            raise ValueError('Invalid value')


class CountryHouse(HouseScheme):  
    def __init__(self, living_rooms, territory, bathroom_unit, floors, place):
        super().__init__(living_rooms, territory, bathroom_unit)
        if (place >= 0) and (floors >= 0):
            self.place = place
            self.floors = floors

    def __str__(self):
        return 'Country House: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Количество этажей {}, Площадь участка {}.'.format(
            self.living_rooms, self.territory, self.bathroom_unit, self.floors, self.place)

    def __eq__(self, object2):
        return (self.territory == object2.territory) and (self.place == object2.place) and (
                    (self.floors - object2.floors) ** 2 <= 1)


class Apartment(HouseScheme):  
    def __init__(self, living_rooms, territory, bathroom_unit, floor, window_view):
        super().__init__(living_rooms, territory, bathroom_unit)
        if (floor >= 1) and (floor <= 15) and ((window_view == 'N') or (window_view == 'S') or (window_view == 'W') or (window_view == 'E')):
            self.window_view = window_view
            self.floor = floor
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return 'Apartment: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Этаж {}, Окна выходят на {}.'.format(self.living_rooms, self.territory, self.bathroom_unit, self.floor, self.window_view)


class CountryHouseList(list): 
    def __init__(self, name):
        self.name = name

    def append(self, p_object):
        if type(p_object) == CountryHouse:
            super().append(p_object)
        else:
            raise TypeError('Invalid type {}'.format(type(p_object)))

    def total_square(self):
        sqr = 0
        for i in self:
            sqr += i.territory
        return sqr


class ApartmentList(list):  
    def __init__(self, name):
        self.name = name

    def extend(self, iterable):
        super().extend(filter(lambda i: type(i) == Apartment, iterable))

    def floor_view(self, floors, directions):
        suitable = list(filter(lambda i: (i.window_view in directions)and(i.floor in list(range(floors[0], floors[1] + 1))), self))
        for i in suitable:
            print('{}: {}'.format(i.window_view, i.floor))
