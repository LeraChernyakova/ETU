class HouseScheme:
    def __init__(self, amout_of_rooms, square, combined_bathroom):
      if square > 0 and type(combined_bathroom) == bool:
        self.amout_of_rooms = amout_of_rooms
        self.square = square
        self.combined_bathroom = combined_bathroom
      else:
        raise ValueError("Invalid value")


class CountryHouse(HouseScheme):
  def __init__(self, amout_of_rooms, square, combined_bathroom, amount_of_floors, plottage):
    super().__init__(amout_of_rooms, square, combined_bathroom)
    self.amount_of_floors = amount_of_floors
    self.plottage = plottage

  def __str__(self):
    return "Country House: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Количество этажей {}, Площадь участка {}.".format(self.amout_of_rooms, self.square, self.combined_bathroom, self.amount_of_floors, self.plottage)                                      

  def __eq__(self, another):
    if type(another) != CountryHouse: raise ValueError("Invalid value")
    return self.square == another.square and self.plottage == another.plottage and abs(self.amount_of_floors - another.amount_of_floors) <= 1 


class Apartment(HouseScheme):
  def __init__(self, amout_of_rooms, square, combined_bathroom, floor, windows_direction):
    super().__init__(amout_of_rooms, square, combined_bathroom)
    if (1 <= floor <= 15) and (windows_direction in ['N', 'S', 'W', 'E']):
      self.floor = floor
      self.windows_direction = windows_direction
    else:
        raise ValueError("Invalid value")

  def __str__(self):
    return "Apartment: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Этаж {}, Окна выходят на {}.".format(self.amout_of_rooms, self.square, self.combined_bathroom, self.floor, self.windows_direction)


class CountryHouseList(list):
  def __init__(self, name):
      self.name = name                                                                                  
  
  def append(self, p_object):
    if type(p_object) == CountryHouse:
      super().append(p_object)
    else:
      raise TypeError("Invalid type {}".format(type(p_object)))

  
  def total_square(self):
    total_square = 0
    for item in self:
      total_square += item.square
    return total_square


class ApartmentList(list):
  def __init__(self, name):
      self.name = name 

  def extend(self, iterable):
    super().extend(filter(lambda element: type(element) == Apartment, iterable))

  def floor_view(self, floors, windows_directions):
    apartment_verification = list(filter(lambda element: floors[0] <= element.floor <= floors[1] and element.windows_direction in windows_directions, self))
    for item in apartment_verification:
      print('{}: {}'.format(item.windows_direction,item.floor))
