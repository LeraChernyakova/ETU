import heapq

# Define a Graph class
class Graph:
    # Constructor function to initialize the graph object
    def __init__(self):
        self.graph = {}             # Initialize the graph as an empty dictionary
        self.start_node = None      # Initialize the start and end nodes as None
        self.end_node = None
        self.correct_path = False   # Initialize a boolean to indicate whether the correct path has been found
        self.answer = ""            # Initialize a string to store the answer path

    # Function to read input and store it in the graph
    def input_to_graph(self):
        # Read the start and end nodes from input
        self.start_node, self.end_node = input().split()
        input_graph = {}

        # Read in the edges and their weights from input and store them in the input_graph dictionary
        while True:
            try:
                cur_node, next_node, distance = input().split()
                if not input_graph.get(cur_node):
                    input_graph[cur_node] = [(next_node, float(distance))]
                else:
                    input_graph[cur_node] += [(next_node, float(distance))]
            except:
                break
        self.graph = input_graph

    # Function to print the answer path to output
    def output(self):
        print(self.answer)

    # Heuristic function for A* algorithm
    def heuristic(self, cur_node: str):
        return abs(ord(self.end_node) - ord(cur_node))

    # A* algorithm function to find the shortest path
    def a_star_algorithm(self):
        queue = []                                      # Create a priority queue to hold the nodes to be explored
        heapq.heappush(queue, (0, self.start_node))     # Add the start node to the queue with a priority of 0

        # Initialize dictionaries to keep track of the path and cost of each node
        came_from = {self.start_node: None}
        weight = {self.start_node: 0}

        # Loop until the queue is empty or the end node is found
        while queue:
            # Get the node with the highest priority from the queue
            cur_node = heapq.heappop(queue)[1]
            # If the end node is found, exit the loop
            if cur_node == self.end_node:
                break
            # If the current node has neighbors, check their distances and add them to the queue if they are closer
            if cur_node in self.graph:
                for next_node, next_distance in self.graph[cur_node]:
                    new_cost = weight[cur_node] + next_distance
                    if next_node not in weight or new_cost < weight[next_node]:
                        weight[next_node] = new_cost
                        priority = new_cost + self.heuristic(next_node)
                        heapq.heappush(queue, (priority, next_node))
                        came_from[next_node] = cur_node

        # Trace back the path from the end node to the start node and store it in the answer variable
        cur_node = self.end_node
        self.answer = self.end_node
        while cur_node != self.start_node:
            cur_node = came_from[cur_node]
            self.answer += cur_node
        self.answer = self.answer[::-1]


    def greedy_algorithm(self, cur_node: str, cur_way: str):
     # Sort the neighbors of the current node by their distances in ascending order
     for node in self.graph:
         self.graph[node].sort(key=lambda x: x[1])

     # If the way has already been found, terminate the search
     if self.correct_path:
         return
     # If the current node is the end node, set the answer and terminate the search
     if cur_node == self.end_node:
         self.answer = cur_way
         self.correct_path = True
         return
     # Recursively explore the neighbors of the current node
     if cur_node in self.graph:
         for next_node, _ in self.graph[cur_node]:
             next_way = cur_way + next_node
             self.greedy_algorithm(next_node, next_way)

    # This function solves the problem using the A* algorithm
    def solve_a_star(self):
        graph.input_to_graph()
        self.a_star_algorithm()

    # This function solves the problem using the greedy algorithm
    def solve_greedy(self):
        graph.input_to_graph()
        self.greedy_algorithm(self.start_node, self.answer + f"{self.start_node}")

# Create a Graph object and solve the problem using the greedy algorithm
if __name__ == "__main__":
    graph = Graph()
    #graph.solve_greedy()  # solve problem using the greedy algorithm
    graph.solve_a_star()   # solve problem using the A* algorithm
    graph.output()         # output the result of the algorithm
