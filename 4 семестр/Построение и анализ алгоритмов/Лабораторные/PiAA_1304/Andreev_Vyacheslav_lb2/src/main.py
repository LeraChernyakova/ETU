
import functools



INF_WEIGHT = 999999


'''
	Element of graph.
'''
class MapNode:
	def __init__(self) -> None:
		self.__PathsDict = dict[str, float]()
		self.__SortedNames = list[str]()

	'''
		Add link to other graph node.

		@param NodeName - Name of node to link.
		@param Weight - Weight of link between current node and target.
	'''
	def AddPath(self, NodeName: str, Weight: float) -> None:
		self.__PathsDict[NodeName] = Weight
	'''
		Sort links by its weight.
	'''
	def Sort(self) -> None:
		self.__SortedNames = list(map(lambda x: x[0], sorted(self.__PathsDict.items(), key = lambda x: x[1])))
	'''
		@return list of sorted nodes names by links weight. 
	'''
	def GetSortedNames(self) -> list[str]:
		return self.__SortedNames
	'''
		@return weight of link between current node and target.
	'''
	def GetWeightFor(self, NodeName: str) -> float:
		if not NodeName in self.__PathsDict:
			return INF_WEIGHT
		return self.__PathsDict[NodeName]

'''
	Graph of nodes.
'''
class MapGraph:
	def __init__(self) -> None:
		self.__PathDict = dict[str, MapNode]()
		self.__VisitedNodes = list[str]()

	'''
		Add link between nodes.

		@param NodeNameA - Name of first node.
		@param NodeNameB - Name of second nnode.
		@param Weight - Weight of link between first and second nodes.
	'''
	def AddPath(self, NodeNameA: str, NodeNameB: str, Weight: float) -> None:
		if not NodeNameA in self.__PathDict:
			self.__PathDict[NodeNameA] = MapNode()
		self.__PathDict[NodeNameA].AddPath(NodeNameB, Weight)
	'''
		Sort links by weight of all nodes in graph.
	'''
	def Sort(self):
		for LNode in self.__PathDict.keys():
			self.__PathDict[LNode].Sort()
	'''
		@return dict of graph nodes.
	'''
	def GetPathDict(self) -> dict[str, MapNode]:
		return self.__PathDict

	'''
		Greedy algorithm to find path between Start and End nodes.

		@param StartName - Name of start node.
		@param EndName - Name of end node.
		@return path as str.
	'''
	def FindPathGreedy_Process(self, StartName: str, EndName: str) -> str:
		LResult = StartName
		if StartName == EndName:
			return LResult
		for S in  self.__PathDict[StartName].GetSortedNames():
			if S == EndName:
				return LResult + S
			if (S in self.__VisitedNodes) or (not S in self.__PathDict):
				continue
			self.__VisitedNodes.append(S)
			LResult += self.FindPathGreedy_Process(S, EndName)
			break
		return LResult
	'''
		A* algorithm to find path between Start and End nodes.

		@param StartName - Name of start node.
		@param EndName - Name of end node.
		@return path as str.
	'''
	def FindPathAStar_Process(self, StartName: str, EndName: str) -> str:
		LPotentialNodes = [(StartName, 0.0, 0.0)]
		LNodesPath = {StartName : ""} # to - from

		while len(LPotentialNodes) != 0:
			LNodeName, LNodeWeight, LNodeEvristicWeight = LPotentialNodes[-1]
			LPotentialNodes.pop()
			self.__VisitedNodes.append(LNodeName)

			if LNodeName == EndName:
				break
			if not LNodeName in self.__PathDict:
				continue

			for LPotentialNodeName in self.__PathDict[LNodeName].GetSortedNames():
				if LPotentialNodeName in self.__VisitedNodes:
					continue

				LPotentialNodeWeight = LNodeWeight + self.__PathDict[LNodeName].GetWeightFor(LPotentialNodeName)
				LPotentialNodeEvristicWeight = ord(EndName) - ord(LPotentialNodeName)

				tmp = [x for x in LPotentialNodes if x[0] == LPotentialNodeName]
				if len(tmp) != 0:
					if tmp[0][1] + tmp[0][2] > LPotentialNodeWeight + LPotentialNodeEvristicWeight:
						LPotentialNodes.remove(tmp[0])
						LNodesPath[LPotentialNodeName] = LNodeName
						LPotentialNodes.append((LPotentialNodeName, LPotentialNodeWeight, LPotentialNodeEvristicWeight))
				else:
					LNodesPath[LPotentialNodeName] = LNodeName
					LPotentialNodes.append((LPotentialNodeName, LPotentialNodeWeight, LPotentialNodeEvristicWeight))

			def Compare(x, y) -> int:
				if x[1] + x[2] == y[1] + y[2]:
					return ord(x[0]) - ord(y[0])
				return (x[1] + x[2]) - (y[1] + y[2])
			LPotentialNodes.sort(key = functools.cmp_to_key(Compare), reverse = True)

		if not EndName in LNodesPath:
			return ""
		LNodeName = EndName
		LResult = LNodeName
		while LNodeName != StartName:
			LNodeName = LNodesPath[LNodeName]
			LResult += LNodeName
		return LResult[::-1]
			
	'''
		Main method to start greedy algorithm.

		@param StartName - Name of start node.
		@param EndName - Name of end node.
		@return path as str.
	'''
	def FindPathGreedy(self, StartName: str, EndName: str) -> str:
		self.Sort()
		self.__VisitedNodes.clear()
		return self.FindPathGreedy_Process(StartName, EndName)
	'''
		Main method to start A* algorithm.

		@param StartName - Name of start node.
		@param EndName - Name of end node.
		@return path as str.
	'''
	def FinPathAStar(self, StartName: str, EndName: str) -> str:
		self.Sort()
		self.__VisitedNodes.clear()
		return self.FindPathAStar_Process(StartName, EndName)




if __name__ == "__main__":
	Map = MapGraph()

	StartName, EndName = input().split()
	while True:
		try:
			N1, N2, W = input().split()
			Map.AddPath(N1, N2, float(W))
		except:
			break
	print(Map.FinPathAStar(StartName, EndName))