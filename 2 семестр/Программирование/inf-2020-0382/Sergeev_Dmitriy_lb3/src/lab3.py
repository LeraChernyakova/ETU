class HouseScheme():
    def __init__(self,count,area,toi):
        if type(count)==int and count>=0 and (type(area)== float or type(area)==int) and (area>=0) and type(toi)==bool:
            self.count=count 
            self.area=area
            self.toi=toi
        else:
            raise ValueError('Invalid value')
        

class CountryHouse(HouseScheme):
    def __init__(self, count, area,toi,floor_count, sec_area):
        super().__init__(count,area,toi)
        if (floor_count>=0 and sec_area>=0):
            self.floor_count=floor_count
            self.sec_area=sec_area
        else:
            raise ValueError('Invalid value')
    def __str__(self):
        return 'Country House: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Количество этажей {}, Площадь участка {}.'.format(self.count,self.area,self.toi,self.floor_count,self.sec_area)
    def __eq__(self,other):
        if ((self.area==other.area) and (self.sec_area==other.sec_area) and (abs(self.floor_count-other.floor_count)<=1)):
            return True
        else:
            return False
            
class Apartment(HouseScheme):
    def __init__(self,count,area,toi,floor,window):
        super().__init__(count,area,toi)
        if (floor>=1 and floor<=15 and (window == 'N' or window=='S' or window=='E' or window=='W')):
            self.floor=floor
            self.window=window
        else:
            raise ValueError('Invalid value')
    def __str__(self):
        return 'Apartment: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Этаж {}, Окна выходят на {}.'.format(self.count,self.area,self.toi,self.floor,self.window)

class CountryHouseList(list): 
    def __init__(self,name):
        super().__init__()
        self.name=name
        
    def append(self, p_object):
        a=0
        if (type(p_object)==CountryHouse):
            super().append(p_object)
        else:
            raise TypeError('Invalid type {}'.format(type(p_object)))
            
    def total_square(self):
        sum=0
        for i in self:
            sum+=i.area
        return sum
        
class ApartmentList(list):
    def __init__(self,name):
        super().__init__()
        self.name=name

    def extend(self,iterable):
        ext=list(filter(lambda x: type(x)==Apartment,iterable))
        super().extend(ext)

    def floor_view(self,floors, directions):
        w_fl=list(filter(lambda x: (x.window in directions) and (x.floor>=floors[0]) and x.floor<=floors[1],self))
        for i in w_fl:
            print(i.window,i.floor,sep=': ')