from abc import ABC, abstractmethod
from queue import PriorityQueue


class IReader(ABC):
    
    def __init__(self):
        self.graph = {}
        self.startNode, self.endNode = "", "" 

    @abstractmethod
    def ReadGraph(self):
        """ In that case, graph is a dictionary, which keys are parent nodes
        and his value is a 2D list, each interior list has only two items :
        child node and arc length

        Input stream:
        First string image: <Start Node> <End Node>
        All string below image: <Parent> <Child> <Arc Length>"""
        pass


class TerminalReader(IReader):
    
    def ReadGraph(self):
        """Implementation of the method for reading graph data from the
        terminal. Reads data from standard input and returns a start node,
        an end node, and a dictionary representing the graph."""
        self.startNode, self.endNode = input().split()

        while True:
            try:

                for item in input().split('\n'):
                    item = item.split()
                    parent, child, value = item[0], item[1], item[2]

                    if parent in self.graph.keys():
                        self.graph[parent].append([child, float(value)])
                        self.graph[parent] = sorted(self.graph[parent], 
                                                    key=lambda item : item[1])

                    else:
                        self.graph.update({parent: [[child, float(value)]]})
            except:
                break
        return self.startNode, self.endNode, self.graph
        

class FileReader(IReader):
    
    def ReadGraph(self):
        """Implementation of the method for reading graph data from a file. 
        Reads data from the input.txt file and returns the start node, 
        end node, and a dictionary representing the graph."""
        with open("input.txt", 'r') as inputFile:

            for i, line in enumerate(inputFile):

                if i == 0:
                    self.startNode, self.endNode = line.split()

                else:
                    parent, child, value = line.split()

                    if parent in self.graph.keys():
                        self.graph[parent].append([child, float(value)])
                        self.graph[parent] = sorted(self.graph[parent], 
                                                    key=lambda item : item[1])

                    else:
                        self.graph.update({parent: [[child, float(value)]]})

        return self.startNode, self.endNode, self.graph


class IAlgorithm(ABC):
    
    def __init__(self, startNode, endNode, graph):
        """A class constructor that takes a start node, an end node, 
        and a dictionary representing the graph."""
        self.startNode = startNode
        self.endNode = endNode
        self.graph = graph
        self.finalPath = None
    
    @abstractmethod
    def GetPath(self) -> str:
        """An abstract interface method that returns a string representing
        the found path between the start and end nodes of the graph."""
        pass        


class GreedAlgorithm(IAlgorithm):
    
    def GetPath(self):
        """Implementation of the method of finding a path between the start 
        and end nodes of the graph using a greedy algorithm. 
        Returns a string representing the found path between the start and 
        end nodes of the graph."""
        try:
            self.__SearchPath(self.startNode, "")
        except:
            return self.finalPath

    def __SearchPath(self, parent, currentPath) -> None:
        """An algorithm consisting in making locally optimal decisions
        at each stage, assuming that the final solution will also be optimal.
        When the path is found - raise an exception to end algorithm"""
        currentPath += parent

        if parent == self.endNode:
            self.finalPath = currentPath
            raise Exception()

        if self.graph.get(parent) is None:
            return

        else:

            for item in self.graph[parent]:

                if currentPath.count(item[0]) > 0 and len(self.graph[parent]) != 1:
                    continue
                self.__SearchPath(item[0], currentPath)


class AStar(IAlgorithm):

    def GetPath(self):
        """Implementation of the method for finding a path between the start 
        and end nodes of the graph using algorithm A*. 
        Returns a string representing the found path between the start and
        end nodes of the graph."""
        table = self.__GetTable()
        self.finalPath = currentNode = self.endNode
        
        while table[currentNode] is not None:
            self.finalPath += table[currentNode]
            currentNode = table[currentNode]
        self.finalPath = self.finalPath[::-1] 
        return self.finalPath
    
    def __Heuristic(self, currentNode):
        """A heuristic function that calculates an estimate of the distance 
        between the current node and the end node of the graph."""
        return abs(ord(self.endNode) - ord(currentNode))

    def __GetTable(self):
        """An accessory method that is used to build the cameFrom and costSoFar 
        table needed to execute Algorithm A*."""
        frontier = PriorityQueue()
        frontier.put((0, self.startNode))
        cameFrom = {}
        costSoFar = {}
        cameFrom[self.startNode] = None
        costSoFar[self.startNode] = 0

        while not frontier.empty():
            currentNode = frontier.get()[1]

            if currentNode == self.endNode:
                break
            
            if self.graph.get(currentNode) is not None:

                for node, value in self.graph.get(currentNode):
                    newValue = float(costSoFar[currentNode]) + value

                    if node not in costSoFar or newValue < costSoFar[node]:
                        costSoFar[node] = newValue
                        priority = newValue + self.__Heuristic(node)
                        frontier.put((priority, node))
                        cameFrom[node] = currentNode
            
        return cameFrom

if __name__ == "__main__":
    reader = TerminalReader()
    start, end, graph = reader.ReadGraph()
    algorithm = AStar(start, end, graph)
    print(algorithm.GetPath())
