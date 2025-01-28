class HouseScheme:

    def __init__(self, n_room, area_room, sanuzl):

        if area_room < 0: raise ValueError("Invalid value")
        if not isinstance(sanuzl, bool):  raise ValueError("Invalid value")

        self.n_room = n_room
        self.area_room = area_room
        self.sanuzl = sanuzl



class CountryHouse(HouseScheme):

    def __init__(self, n_room, area_room, sanuzl, n_level, area_home):
        super().__init__(n_room, area_room, sanuzl)

        self.n_level = n_level
        self.area_home = area_home

    def __str__(self):
        return "Country House: Количество жилых комнат " + str(self.n_room) + ', Жилая площадь ' + str(
            self.area_room) + ", Совмещенный санузел " + str(self.sanuzl) + ", Количество этажей " + str(
            self.n_level) + ", Площадь участка " + str(self.area_home) + '.'

    def __eq__(self, home1):

        if (self.area_room == home1.area_room) and (self.area_home == home1.area_home) and (
                abs(self.n_level - home1.n_level) <= 1):
            return True
        else:
            return False


class Apartment(HouseScheme):

    def __init__(self, n_room, area_room, sanuzl, level, window):
        super().__init__(n_room, area_room, sanuzl)
        if not isinstance(level, int): raise ValueError("Invalid value")
        if not (level >= 1 and level <= 15): raise ValueError("Invalid value")
        if (not window == 'N') and (not window == 'S') and (not window == 'W') and (
        not window == 'E'): raise ValueError("Invalid value")

        self.level = level
        self.window = window

    def __str__(self):

        return "Apartment: Количество жилых комнат " + str(self.n_room) + ', Жилая площадь ' + str(
            self.area_room) + ", Совмещенный санузел " + str(self.sanuzl) + ", Этаж " + str(
            self.level) + ", Окна выходят на " + str(self.window) + '.'


class CountryHouseList(list):

    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if isinstance(p_object, CountryHouse):
            super().append(p_object)
        else:
            raise TypeError("Invalid type " + str(type(p_object)))

    def total_square(self):
        sum_area_room = 0

        for i in self:
            sum_area_room += i.area_room

        return sum_area_room


class ApartmentList(list):

    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        # if isinstance(iterable, Apartment):
        #   super().extend(iterable)
        super().extend(filter(lambda x: type(x) == Apartment, iterable))

    def floor_view(self, floors, directions):
        list_room = list(
            filter(lambda room: (room.level >= floors[0]) and (room.level <= floors[1]) and (room.window in directions),
                   self))

        for i in list_room:
            print(str(i.window) + ': ' + str(i.level))
