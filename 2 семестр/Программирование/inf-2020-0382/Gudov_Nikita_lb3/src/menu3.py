class HouseScheme:                                                                                                                                                                           
    def __init__(self, rooms, place, bath):                                                                                                                                            
        if type(bath) == bool and place >= 0:                                                                                                                                          
            self.rooms = rooms                                                                                                                                                               
            self.place = place                                                                                                                                                                 
            self.bath = bath                                                                                                                                                   
        else:                                                                                                                                                                                
            raise ValueError("Invalid value")                                                                                                                                                


class CountryHouse(HouseScheme):                                                                                                                                                             
    def __init__(self, rooms, place, bath, floors, square):                                                                                                                         
        if place > 0 and type(bath) == bool:
            super().__init__(rooms, place, bath)                                                                                                                                           
            self.floors = floors                                                                                                                                                                 
            self.square = square                                                                                                                                                           
        else:                                                                                                                                                                                
            raise ValueError("Invalid value")
    def __str__(self):                                                                                                                                                                       
        return "Country House: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Количество этажей {}, Площадь участка {}.".format(                                      
            self.rooms, self.place, self.bath, self.floors, self.square)                                                                                                            

    def __eq__(self, other):                                                                                                                                                                 
        if type(other) != CountryHouse: raise ValueError("Invalid value")                                                                                                                    
        return self.place == other.place and self.square == other.square and abs(self.floors - other.floors) <= 1                                                                        


class Apartment(HouseScheme):                                                                                                                                                                

    def __init__(self, rooms, place, bath, floor, side):                                                                                                                            
        super().__init__(rooms, place, bath)                                                                                                                                           
        if 1 <= floor <= 15 and side in ['N', 'S', 'W', 'E']:                                                                                                                               
            self.floor = floor                                                                                                                                                               
            self.side = side                                                                                                                                                           
        else:                                                                                                                                                                                
            raise ValueError("Invalid value")                                                                                                                                                

    def __str__(self):                                                                                                                                                                       
        return "Apartment: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Этаж {}, Окна выходят на {}.".format(                                                       
            self.rooms, self.place, self.bath, self.floor, self.side)                                                                                                               


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
        total_place = 0                                                                                                                                                                       
        for i in range(len(self)):                                                                                                                                                           
            total_place += self[i].place                                                                                                                                                       
        return total_place                                                                                                                                                                    


class ApartmentList(list):                                                                                                                                                                   
    def __init__(self, name):                                                                                                                                                                
        super().__init__()                                                                                                                                                                   
        self.name = name                                                                                                                                                                     

    def extend(self, iterable):
        for i in iterable:
            if isinstance(i, Apartment): super().append(i)                                                                                                                   

    def floor_view(self, floors, directions):                                                                                                                                                
        for s in filter(lambda art: art.side in directions and floors[0] <= art.floor <= floors[1], self):                                                                          
            print("{}: {}".format(s.side, s.floor)) 