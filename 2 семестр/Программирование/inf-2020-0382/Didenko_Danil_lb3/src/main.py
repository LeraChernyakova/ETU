class HouseScheme:
    def __init__(self, count_bedroom, square, joined_bathroom):
        self.count_bedroom = count_bedroom
        if square < 0:
            raise ValueError('Invalid value')
        else:
            self.square = square
        if type(joined_bathroom) == bool or joined_bathroom == 'True' or joined_bathroom == 'False':
            self.joined_bathroom = joined_bathroom
        else:
            raise ValueError('Invalid value')


class CountryHouse(HouseScheme):
    def __init__(self, count_bedroom, square, joined_bathroom, count_floor, square_place):
        super().__init__(count_bedroom, square, joined_bathroom)
        self.count_floor = count_floor
        self.square_place = square_place

    def __str__(self):
        return 'Country House: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Количество этажей {}, Площадь участка {}.'.format(self.count_bedroom,self.square,self.joined_bathroom,self.count_floor,self.square_place)
    def __eq__(self,el):
        if self.square == el.square and self.square_place == el.square_place and abs(self.count_floor-el.count_floor) <= 1:
            return True
        else:
            return False

class Apartment(HouseScheme):
    def __init__(self,count_bedroom,square,joined_bathroom,floor,side_of_window):
        super().__init__(count_bedroom,square,joined_bathroom)
        if 1<=floor<=15:
            self.floor = floor
        else:
            raise ValueError('Invalid value')
        if side_of_window in ['N', 'S', 'W', 'E']:
            self.side_of_window = side_of_window
        else:
            raise ValueError('Invalid value')
    def __str__(self):
        return 'Apartment: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Этаж {}, Окна выходят на {}.'.format(self.count_bedroom,self.square,self.joined_bathroom,self.floor,self.side_of_window)


class CountryHouseList(list):
    def __init__(self,name):
        self.name = name
    def append(self,p_object):
        if type(p_object) == CountryHouse:
            super().append(p_object)
        else:
            raise TypeError ('Invalid type {}'.format(type(p_object)))
    def total_square(self):
        total_squre = 0
        for i in self:
            total_squre+=i.square
        return total_squre

class ApartmentList(list):
    def __init__(self,name):
        self.name = name
    def extend(self,iterable):
        iterable = list(filter(lambda x: type(x) == Apartment, iterable))
        super().extend(iterable)
    def floor_view(self,floors, directions):
        check_apart = list(filter(lambda x: x.floor in list(range(floors[0],floors[1]+1)) and x.side_of_window in directions,self))
        for i in check_apart:
            print('{}: {}'.format(i.side_of_window,i.floor))