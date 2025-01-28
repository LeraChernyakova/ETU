class HouseScheme:
    def __init__(self, rooms, square, bathroom):
        if square > 0 and rooms > 0 and type(rooms) == int and type(bathroom) == bool:
            self.rooms = rooms
            self.square = square
            self.bathroom = bathroom
        else:
            raise ValueError("Invalid value")
    
class CountryHouse(HouseScheme): 
    def __init__(self, rooms, square, bathroom, floors, square_place):
        super().__init__(rooms, square, bathroom)
        if floors > 0 and type(floors) == int and square_place > 0:
            self.floors = floors
            self.square_place = square_place
        else:
            raise ValueError("Invalid value")

    def __str__(self):
        return ("Country House: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Количество этажей {}, Площадь участка {}.".format(self.rooms, self.square, self.bathroom, self.floors, self.square_place))
   
    def __eq__(self,others):
        return self.square == others.square and self.square_place == others.square_place and abs(self.floors - others.floors) <= 1 

class Apartment(HouseScheme): 
    def __init__(self, rooms, square, bathroom, floors, window):
        windows = ['N', 'S', 'W', 'E']
        super().__init__(rooms, square, bathroom)
        if 15>= floors > 0 and type(floors) == int and (window in windows):
            self.floors = floors
            self.window = window
        else:
            raise ValueError("Invalid value")
            
    def __str__(self):
        return ("Apartment: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Этаж {}, Окна выходят на {}.".format(self.rooms, self.square, self.bathroom, self.floors, self.window))
   
class CountryHouseList(list): 
    def __init__(self, name):
        super().__init__()
        self.name = name
    
    def append(self, p_object):
        if isinstance(p_object,CountryHouse):
            super().append(p_object)
        else:
            raise TypeError("Invalid type {}".format(type(p_object)))

    def total_square(self):
        square_total = 0
        for i in self:
            square_total += i.square
        return square_total
class ApartmentList(list): 
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        for i in iterable:
            if isinstance(i, Apartment):
                self.append(i)
    
    def floor_view(self, floors, directions):
        for i in filter(lambda x: floors[0] <= x.floors <= floors[1] and x.window in directions, self):
            print("{}: {}".format(i.window, i.floors))
