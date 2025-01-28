class HouseScheme:
    def __init__(self, rooms_number, square, bathroom):

        if square < 0 or type(bathroom) != bool:
            raise ValueError("Invalid value")
        else:
            self.rooms_number = rooms_number
            self.square = square
            self.bathroom = bathroom

class CountryHouse(HouseScheme): 
    def __init__(self, rooms_number, square, bathroom, floors_number, land_area):
        
        super().__init__(rooms_number, square, bathroom)
        
        if (land_area < 0) or (floors_number < 0):
            raise ValueError('Invalid value')
        
        else:
            self.floors_number = floors_number
            self.land_area = land_area

    def __str__(self):
        return 'Country House: Количество жилых комнат {0}, Жилая площадь {1}, Совмещенный санузел {2}, Количество этажей {3}, Площадь участка {4}.'.format(self.rooms_number, self.square, self.bathroom, self.floors_number, self.land_area) 


    def __eq__(self, obj):
        summary = abs(self.floors_number - obj.floors_number)
        if ((self.square == obj.square) and (self.land_area == obj.land_area) and (summary < 2)):
            return True
        return False

class Apartment(HouseScheme):
    def __init__(self, rooms_number, square, bathroom, floor_number, windows_direct):

        super().__init__(rooms_number, square, bathroom)

        #Условие
        if (floor_number < 1) or (floor_number > 16) or (windows_direct not in ('N', 'S', 'W', 'E')):
            raise ValueError('Invalid value')
        else:
            self.floor_number = floor_number
            self.windows_direct = windows_direct

    def __str__(self):
        return 'Apartment: Количество жилых комнат {0}, Жилая площадь {1}, Совмещенный санузел {2}, Этаж {3}, Окна выходят на {4}.'.format(self.rooms_number, self.square, self.bathroom, self.floor_number, self.windows_direct) 


class CountryHouseList(list): 
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if (isinstance(p_object, CountryHouse)==0):
            raise TypeError('Invalid type {}'.format(type(p_object)))
        
        else:
            super().append(p_object)

    def total_square(self):
        summary = 0
        for i in self:
            summary += i.square
        return summary

class ApartmentList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        for i in iterable:
            if isinstance(i, Apartment):
                self.append(i)

    def floor_view(self, r, directs):
        apartments = list(filter(lambda x: x.floor_number in range(r[0], r[1] + 1) and x.windows_direct in directs, self.__iter__()))
        print('\n'.join(list(map(lambda x: x.windows_direct + ': ' + str(x.floor_number), apartments))))

