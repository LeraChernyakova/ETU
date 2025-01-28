class HouseScheme():
    def __init__(self,rooms,area,restroom):
        if rooms>=0 and area>=0 and type(restroom)==bool:
            self.rooms = rooms
            self.area = area
            self.restroom = restroom
        else:
            raise ValueError('Invalid value')
        
class CountryHouse(HouseScheme):
    def __init__(self,rooms,area,restroom,storey,ter_area):
        super().__init__(rooms,area,restroom)
        if storey>=0 and ter_area>=0:
            self.storey = storey
            self.ter_area = ter_area 
        else:
            raise ValueError('Invalid value')      
    def __str__(self):
        return "Country House: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Количество этажей {}, Площадь участка {}.".\
            format(self.rooms,self.area,self.restroom,self.storey,self.ter_area)
    def __eq__(self, new_house):
        return new_house.area==self.area and new_house.ter_area==self.ter_area and -1<=(new_house.storey-self.storey)<=1 
    
class Apartment(HouseScheme):
    def __init__(self,rooms,area,restroom,storey,window):
        super().__init__(rooms,area,restroom)
        if 1<=storey<= 15 and (window in ['N','S','W','E']):
            self.storey = storey
            self.window = window
        else:
            raise ValueError('Invalid value')
    def __str__(self):
        return 'Apartment: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Этаж {}, Окна выходят на {}.'.\
            format(self.rooms,self.area,self.restroom,self.storey,self.window)    
    
class CountryHouseList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name
    def append(self, p_object):
        if type(p_object)==CountryHouse:
            super().append(p_object)
        else:
            raise TypeError('Invalid type {}'.format(type(p_object)))
    def total_square(self):                                                                                                                                                    
        S = 0                                                                                                                                                                
        for item in self:                                                                                                                                                           
            S = S+item.area                                                                                                                                                       
        return S 
        
class ApartmentList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name
    def extend(self,iterable):
        super().extend(filter(lambda x: type(x)==Apartment,iterable))  
    def floor_view(self,floors,directions):
        result = list(filter(lambda x: (x.window in directions) and floors[0]<=x.storey<=floors[1], self))
        for item in result:
            print('{}: {}'.format(item.window,item.storey)) 
