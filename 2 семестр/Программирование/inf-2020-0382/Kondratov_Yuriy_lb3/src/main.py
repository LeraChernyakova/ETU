class HouseScheme:                                                                                                                                                                           
    def __init__(self, rooms, area, shared_bath):                                                                                                                                            
        if area >= 0 and type(shared_bath) == bool:                                                                                                                                          
            self.rooms = rooms                                                                                                                                                               
            self.area = area                                                                                                                                                                 
            self.shared_bath = shared_bath                                                                                                                                                   
        else:                                                                                                                                                                                
            raise ValueError("Invalid value")                                                                                                                                                
                                                                                                                                                                                             
                                                                                                                                                                                             
class CountryHouse(HouseScheme):                                                                                                                                                             
    def __init__(self, rooms, area, shared_bath, floors, land_area):                                                                                                                         
        super().__init__(rooms, area, shared_bath)                                                                                                                                           
        self.floors = floors                                                                                                                                                                 
        self.land_area = land_area                                                                                                                                                           
                                                                                                                                                                                             
    def __str__(self):                                                                                                                                                                       
        return "Country House: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Количество этажей {}, Площадь участка {}.".format(                                      
            self.rooms, self.area, self.shared_bath, self.floors, self.land_area)                                                                                                            
                                                                                                                                                                                             
    def __eq__(self, other):                                                                                                                                                                 
        if type(other) != CountryHouse: raise ValueError("Invalid value")                                                                                                                    
        return self.area == other.area and self.land_area == other.land_area and abs(self.floors - other.floors) <= 1                                                                        
                                                                                                                                                                                             
                                                                                                                                                                                             
class Apartment(HouseScheme):                                                                                                                                                                
    win_dirs = ["N", "S", "W", "E"]                                                                                                                                                          
                                                                                                                                                                                             
    def __init__(self, rooms, area, shared_bath, floor, win_dir):                                                                                                                            
        super().__init__(rooms, area, shared_bath)                                                                                                                                           
        if 1 <= floor <= 15 and win_dir in Apartment.win_dirs:                                                                                                                               
            self.floor = floor                                                                                                                                                               
            self.win_dir = win_dir                                                                                                                                                           
        else:                                                                                                                                                                                
            raise ValueError("Invalid value")                                                                                                                                                
                                                                                                                                                                                             
    def __str__(self):                                                                                                                                                                       
        return "Apartment: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Этаж {}, Окна выходят на {}.".format(                                                       
            self.rooms, self.area, self.shared_bath, self.floor, self.win_dir)                                                                                                               
                                                                                                                                                                                             
                                                                                                                                                                                             
class CountryHouseList(list):                                                                                                                                                                
    def __init__(self, name):                                                                                                                                                                
        super().__init__()                                                                                                                                                                   
        self.name = name                                                                                                                                                                     
                                                                                                                                                                                             
    def append(self, p_object):                                                                                                                                                              
        if type(p_object) == CountryHouse:                                                                                                                                                   
            super().append(p_object)                                                                                                                                                         
        else:                                                                                                                                                                                
            raise TypeError("Invalid type {}".format(type(p_object)))                                                                                                                        
                                                                                                                                                                                             
    def total_square(self):                                                                                                                                                                  
        total_area = 0                                                                                                                                                                       
        for i in range(len(self)):                                                                                                                                                           
            total_area += self[i].area                                                                                                                                                       
        return total_area                                                                                                                                                                    
                                                                                                                                                                                             
                                                                                                                                                                                             
class ApartmentList(list):                                                                                                                                                                   
    def __init__(self, name):                                                                                                                                                                
        super().__init__()                                                                                                                                                                   
        self.name = name                                                                                                                                                                     
                                                                                                                                                                                             
    def extend(self, lst):                                                                                                                                                                   
        super().extend(filter(lambda item: type(item) == Apartment, lst))                                                                                                                    
                                                                                                                                                                                             
    def floor_view(self, floors, directions):                                                                                                                                                
        for x in filter(lambda apart: floors[0] <= apart.floor <= floors[1] and apart.win_dir in directions, self):                                                                          
            print("{}: {}".format(x.win_dir, x.floor))                                                                                                       
           
