class HouseScheme:
	def __init__(self, rooms, area, bath):
		if area >= 0 and type(bath) == bool:
			self.rooms = rooms
			self.area = area
			self.shared_bath = bath
		else:
			raise ValueError("Invalid value")
class CountryHouse(HouseScheme):
	def __init__(self, *CountryHouse_input):
		if len(CountryHouse_input) != 5 or CountryHouse_input[0] <= 0 or CountryHouse_input[1] <= 0 or isinstance(CountryHouse_input[2], bool) != True or CountryHouse_input[3] <= 0 or CountryHouse_input[4] < 0:
			raise ValueError('Invalid value')
		super().__init__(CountryHouse_input[0], CountryHouse_input[1], CountryHouse_input[2])
		self.floors = CountryHouse_input[3]
		self.land_area = CountryHouse_input[4]
                                                                                                                                                                                             
	def __str__(self):
		return "Country House: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Количество этажей {}, Площадь участка {}.".format(self.rooms, self.area, self.shared_bath, self.floors, self.land_area)

	def __eq__(self, second):
		if type(second) != CountryHouse:
		    raise ValueError("Invalid value")
		return self.area == second.area and self.land_area == second.land_area and abs(self.floors - second.floors) <= 1


class Apartment(HouseScheme):
	def __init__(self, *Apartment_input):
		if len(Apartment_input) != 5 or Apartment_input[0] <= 0 or Apartment_input[1] <= 0 or isinstance(Apartment_input[2], bool) != True or Apartment_input[3] <= 0 or Apartment_input[3] > 15 or (Apartment_input[4] in ['N', 'S', 'W', 'E']) != True:
			raise ValueError('Invalid value')
		super().__init__(Apartment_input[0], Apartment_input[1], Apartment_input[2])
		self.floor = Apartment_input[3]
		self.windows_of_Apartment = Apartment_input[4]

	def __str__(self):
		return "Apartment: Количество жилых комнат {}, Жилая площадь {}, Совмещенный санузел {}, Этаж {}, Окна выходят на {}.".format(self.rooms, self.area, self.shared_bath, self.floor, self.windows_of_Apartment)

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
		all_area = 0
		for i in range(len(self)):
			all_area += self[i].area
		return all_area


class ApartmentList(list):                                                                                                                                                                   
	def __init__(self, name):
		super().__init__()
		self.name = name
	def extend(self, iterable):
		super().extend(list(filter(lambda i: type(i) == Apartment, iterable)))
	def floor_view(self, floors, directions):
		for x in list(filter(lambda i: floors[0] <= i.floor <= floors[1] and i.windows_of_Apartment in directions, self)):
			print("{}: {}".format(x.windows_of_Apartment, x.floor))







