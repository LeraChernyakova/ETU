class HouseScheme:
    def __init__(self, rooms, livingSpace, combinedBathroom):
        if not (isinstance(rooms, int) and isinstance(livingSpace, int) and livingSpace > 0 and isinstance(combinedBathroom, bool)):
            raise ValueError('Invalid value')
        else:
            self.rooms = rooms
            self.space = livingSpace
            self.comBath = combinedBathroom

        
class CountryHouse(HouseScheme):
    def __init__(self, rooms, livingSpace, combinedBathroom, floors, area):
        if not (isinstance(floors, int) and isinstance(area, int)):
            raise ValueError('Invalid value')
        else:
            super().__init__(rooms, livingSpace, combinedBathroom)
            self.floors = floors
            self.area = area

    def __str__(self):
        return 'Country House: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Количество этажей {}, Площадь участка {}.'.format(
            self.rooms, self.space, self.comBath, self.floors, self.area)

    def __eq__(self, other):
        if isinstance(other, CountryHouse):
            if self.space == other.space and self.area == other.area and abs(self.floors - other.floors) <= 1: return True
        return False

    
class Apartment(HouseScheme):
    def __init__(self, rooms, livingSpace, combinedBathroom, floor, side):
        if not (isinstance(floor, int) and (1 <= floor <= 15) and (side in ['N', 'S', 'W', 'E'])):
            raise ValueError('Invalid value')
        else:
            super().__init__(rooms, livingSpace, combinedBathroom)
            self.floor = floor
            self.side = side

    def __str__(self):
        return 'Apartment: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Этаж {}, Окна выходят на {}.'.format(
            self.rooms, self.space, self.comBath, self.floor, self.side)


class CountryHouseList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, obj):
        if isinstance(obj, CountryHouse): super().append(obj)
        else: raise TypeError(f"Invalid type {type(obj)}")

    def total_square(self):
        return sum(house.space for house in self)

        
class ApartmentList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        for apt in iterable:
            if isinstance(apt, Apartment): super().append(apt)

    def floor_view(self, floors, directions):
        apts = list(filter(lambda apt: apt.floor in range(floors[0], floors[1]+1) and apt.side in directions, self))
        for apt in apts: print(f"{apt.side}: {apt.floor}")
