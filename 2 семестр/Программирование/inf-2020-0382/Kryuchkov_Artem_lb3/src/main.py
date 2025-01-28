class HouseScheme:
    def __init__(self, number_of_living_rooms, area, combwc):
        if area < 0 or type(combwc)!=bool:
            raise ValueError("Invalid value")
        self.number_of_living_rooms = number_of_living_rooms
        self.area = area
        self.combwc = combwc
class CountryHouse(HouseScheme):
    def __init__(self, number_of_living_rooms, area, combwc, number_of_floors, land_area):
        super().__init__(number_of_living_rooms, area, combwc)
        self.number_of_floors = number_of_floors
        self.land_area = land_area
    def __str__(self):
        return "Country House: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Количество этажей {}, Площадь участка {}.".format(self.number_of_living_rooms, self.area, self.combwc, self.number_of_floors, self.land_area)
    def __eq__(self, another_house):
        return self.area==another_house.area and self.land_area == another_house.land_area and abs(self.number_of_floors-another_house.number_of_floors)<=1
class Apartment(HouseScheme):
    def __init__(self, number_of_living_rooms, area, combwc, floor, side):
        super().__init__(number_of_living_rooms, area, combwc)
        if 1<= floor <= 15 and side in ['N', 'S', 'W', 'E']:
            self.floor = floor
            self.side = side
        else:
            raise ValueError('Invalid value')
    def __str__(self):
        return "Apartment: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Этаж {}, Окна выходят на {}.".format(self.number_of_living_rooms, self.area, self.combwc, self.floor, self.side)
class CountryHouseList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name
    def append(self, p_object):
        if CountryHouse != type(p_object):
            raise TypeError("Invalid type {}".format(type(p_object)))
        super().append(p_object)
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
        super().extend(list(filter(lambda item: type(item) == Apartment, iterable)))
    def floor_view(self, floors, directions):
        for side_floor in list(filter(lambda apart: floors[0] <= apart.floor <= floors[1]  and apart.side in directions, self)):
            print('{}: {}'.format(side_floor.side, side_floor.floor))
