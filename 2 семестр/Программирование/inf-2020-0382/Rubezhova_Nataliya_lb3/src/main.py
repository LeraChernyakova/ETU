class HouseScheme:
    def __init__(self,quant_rooms,area_in,san_uz):
        if quant_rooms>0 and area_in>0 and type(san_uz)==bool:
            self.quant_rooms=quant_rooms
            self.area_in=area_in
            self.san_uz=san_uz
        else:
            raise ValueError('Invalid value')

class CountryHouse(HouseScheme):
    def __init__(self,quant_rooms,area_in,san_uz,quant_floors,area_out):
        super().__init__(quant_rooms,area_in,san_uz)
        if isinstance(quant_floors,int) and isinstance(area_out,int):
            self.quant_floors=quant_floors
            self.area_out=area_out
        else:
            raise ValueError('Invalid value')

    def __str__(self):
        return 'Country House: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Количество этажей {}, Площадь участка {}.'.format(self.quant_rooms, self.area_in, self.san_uz, self.quant_floors, self.area_out)

    def __eq__(self,other):
       if self.area_in==other.area_in and self.area_out==other.area_out and abs(self.quant_floors-other.quant_floors)<=1:
           return True
       else:
           return False


class Apartment(HouseScheme):

    def __init__(self,quant_rooms,area_in,san_uz,floor,windows):
        super().__init__(quant_rooms,area_in,san_uz)
        if isinstance(floor,int) and floor<16 and floor>0 and windows in ['N','S','W','E']:
            self.floor=floor
            self.windows=windows
        else:
            raise ValueError('Invalid value')
            
    def __str__(self):
        return 'Apartment: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Этаж {}, Окна выходят на {}.'.format(self.quant_rooms, self.area_in, self.san_uz, self.floor, self.windows)


class CountryHouseList(list): 

    def __init__(self,name):
        super().__init__()
        self.name=name

    def append(self,p_object):
        if issubclass(type(p_object),CountryHouse):
            super().append(p_object)
        else:
            st='Invalid type '+str(type(p_object))
            raise TypeError(st)

    def total_square(self):
        total_sq=0
        for i in self:
            total_sq+=i.area_in
        return total_sq


class ApartmentList(list):

    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self,iterable):
        super().extend(filter(lambda apart: type(apart) == Apartment, iterable))

    def floor_view(self,floors, directions):
        filtered=list(filter(lambda apart: (apart.windows in directions) and (apart.floor in list(range(floors[0],floors[1]+1))),self))
        for i in filtered:
            print("{}: {}".format(i.windows,i.floor))
