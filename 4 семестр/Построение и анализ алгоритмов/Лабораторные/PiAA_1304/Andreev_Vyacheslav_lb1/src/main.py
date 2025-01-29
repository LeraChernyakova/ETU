
from copy import deepcopy


'''
	Map primitive. Provides simple functional for square manipulating. 
'''
class Square:
	def __init__(self, X: int, Y: int, R: int):
		self.X = X
		self.Y = Y
		self.R = R

	'''
		Check that this square is collide with other.

		@param S - other square.
		@return true if collide.
	'''
	def IsCollide(self, S) -> bool:
		return (S.X < self.X + self.R) and (S.Y < self.Y + self.R) and (S.X + S.R > self.X) and (S.Y + S.R > self.Y)
	'''
		@return square size.
	'''
	def GetSize(self) -> int:
		return self.R * self.R

	'''
		Print square data to stdout.
	'''
	def Print(self) -> None:
		print(self.X, self.Y, self.R)
	
'''
	Container of used squares. 
'''
class SquareMap:
	def __init__(self, N: int):
		self.N = N 
		self.__FreeSize = N * N
		self.__SquaresList = []
		self.__OnesSquareList = []

	'''
		Check that can add given square.

		@param S - square to check.
		@return true if given square can be added.
	'''
	def CanAddSquare(self, S: Square) -> bool:
		if (self.__FreeSize - S.GetSize() < 0) or (S.X + S.R > self.N + 1) or (S.Y + S.R > self.N + 1):
			return False
		for LS in self.__SquaresList:
			if LS.IsCollide(S):
				return False
		for LS in self.__OnesSquareList:
			if LS.IsCollide(S):
				return False
		return True
	'''
		Add given square without checking.
	'''
	def AddSquare(self, S: Square) -> None:
		self.__FreeSize -= S.GetSize()
		if S.R == 1:
			self.__OnesSquareList.append(S)
		else:
			self.__SquaresList.append(S)

	'''
		Remove last added square.
	'''
	def Pop(self) -> None:
		self.__FreeSize += self.__SquaresList[-1].GetSize()
		self.__SquaresList.pop()
	'''
		Remove all squares with size 1.
	'''
	def ClearOnes(self) -> None:
		self.__FreeSize += len(self.__OnesSquareList)
		self.__OnesSquareList.clear()

	'''
		Check that map is complete filled. 
	'''
	def IsFilled(self) -> bool:
		return self.__FreeSize <= 0
	'''
		@return count of squares in map.
	'''
	def GetCount(self) -> int:
		return len(self.__SquaresList) + len(self.__OnesSquareList)
	'''
		@return unused square size of map.
	'''
	def GetFreeSize(self) -> int:
		return self.__FreeSize

	'''
		Print all containing squares to stdout.
	'''
	def Print(self) -> None:
		for LS in self.__SquaresList:
			LS.Print()
		for LS in self.__OnesSquareList:
			LS.Print()


'''
	Result of search will be here.
'''
GSearchResult = None

'''
	Try to set new result of search if it is better than current.
'''
def TryToSetResult(Map: SquareMap) -> None:
	global GSearchResult
	if (GSearchResult is None) or (Map.GetCount() < GSearchResult.GetCount()):
		GSearchResult = deepcopy(Map)
'''
	Main backtracking function.
'''
def FindPositions(Map: SquareMap, InitR: int) -> bool:
	global GSearchResult

	if Map.IsFilled():
		TryToSetResult(Map)
		return True
	else:
		if Map.N <= 25:
			if Map.GetCount() >= 13:
				return False
		if (not GSearchResult is None) and (Map.GetCount() + 1 >= GSearchResult.GetCount()):
			return False
	
	for r in range(InitR, 0, -1):
		if r * r > Map.GetFreeSize():
			continue
		if r > 1:
			LSkipXY = False
			for x in range(1, Map.N - r + 2):
				for y in range(1, Map.N - r + 2):
					LSquare = Square(x, y, r)
					if not Map.CanAddSquare(LSquare):
						continue
					Map.AddSquare(LSquare)
					if not FindPositions(Map, InitR):	
						Map.Pop()
						return True
					else:
						Map.Pop()
						LSkipXY = True
						break
				if LSkipXY:
					break
		else:
			if Map.N <= 25:
				if Map.GetFreeSize() + Map.GetCount() > 13:
					return False
			if (not GSearchResult is None) and (Map.GetFreeSize() + Map.GetCount() >= GSearchResult.GetCount()):
				return False
			
			for x in range(1, Map.N + 1):
				for y in range(1, Map.N + 1):
					LSquare = Square(x, y, 1)
					if not Map.CanAddSquare(LSquare):
						continue
					Map.AddSquare(LSquare)
			TryToSetResult(Map)
			Map.ClearOnes()
			return True
	return False


if __name__ == "__main__":
	N = int(input())
	GSearchResult = None
	if N % 2 == 0:
		print(4)
		print(1, 1, N // 2) 
		print(N // 2 + 1, 1, N // 2)
		print(1, N // 2 + 1, N // 2)
		print(N // 2 + 1, N // 2 + 1, N // 2)
	elif N % 3 == 0:
		print(6)
		print(1, 1, N // 3 * 2) 
		print(1, N // 3 * 2 + 1, N // 3) 
		print(N // 3 + 1, N // 3 * 2 + 1, N // 3) 
		print(N // 3 * 2 + 1, 1, N // 3) 
		print(N // 3 * 2 + 1, N // 3 + 1, N // 3) 
		print(N // 3 * 2 + 1, N // 3 * 2 + 1, N // 3) 
	elif N in [5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59]:
		LMap = SquareMap(N)
		LMap.AddSquare(Square((N + 1) // 2, (N + 1) // 2, (N + 1) // 2))
		LMap.AddSquare(Square((N + 1) // 2 + 1, 1, (N + 1) // 2 - 1))
		LMap.AddSquare(Square(1, (N + 1) // 2 + 1, (N + 1) // 2 - 1))
		FindPositions(LMap, N // 4 + 1)
		print(GSearchResult.GetCount())
		GSearchResult.Print()
	else:
		FindPositions(SquareMap(N), N - 1)
		print(GSearchResult.GetCount())
		GSearchResult.Print()
