from queue import PriorityQueue


class State(object):
    def __init__(self, value, parent, start=0, goal=0):
        self.children = []
        self.parent = parent
        self.value = value
        self.dist = 0
        if parent:
            self.path = parent.path[:]
            self.path.append(value)
            self.start = parent.start
            self.goal = parent.goal
        else:
            self.path = [value]
            self.start = start
            self.goal = goal

    def getdist(self):
        pass

    def createchildren(self):
        pass


class StateString(State):
    def __init__(self, value, parent, start=0, goal=0):
        super(StateString, self).__init__(value, parent, start, goal)
        self.dist = self.getdist()

    def getdist(self):
        if self.value == self.goal:
            return 0
        dist = 0
        for i in range(len(str(self.goal))):
            letter = str(self.goal)[i]
            dist += abs(i - self.value.index(letter))
        return dist

    def createchildren(self):
        if not self.children:
            for i in range(len(str(self.goal)) - 1):
                val = self.value
                val = val[:i] + val[i + 1] + val[i] + val[i + 2:]
                child = StateString(val, self)
                self.children.append(child)


class AStarSolver:
    def __init__(self, start, goal):
        self.path = []
        self.visited_queue = []
        self.priority_queue = PriorityQueue()
        self.start = start
        self.goal = goal

    def solve(self):
        start_state = StateString(self.start, 0, self.start, self.goal)
        count = 0
        self.priority_queue.put((0, count, start_state))
        while not self.path and self.priority_queue.qsize():
            closest_child = self.priority_queue.get()[2]
            closest_child.createchildren()
            self.visited_queue.append(closest_child.value)
            for child in closest_child.children:
                if child.value not in self.visited_queue:
                    count += 1
                    if not child.dist:
                        self.path = child.path
                        break
                    self.priority_queue.put((child.dist, count, child))
        if not self.path:
            print(f'Goal of {self.goal} is not possible!')
        return self.path


if __name__ == '__main__':
    start1 = 'hma'
    goal1 = 'ham'
    print('Starting...')
    a = AStarSolver(start1, goal1)
    a.solve()
    for i in range(len(a.path)):
        print(f'{i}) {a.path[i]}')