import heapq
from sys import stdin, argv

# from icecream import ic

ASCII = 97


class PriorityQueue:
    def __init__(self):
        self.elements = []

    def empty(self):
        return len(self.elements) == 0

    def put(self, item, priority):
        heapq.heappush(self.elements, (priority, item))

    def get(self):
        return heapq.heappop(self.elements)[1]


def heuristic(a, b):
    return abs(b - a)


class Graph:

    def __init__(self, st, en):
        self.start = st
        self.end = en
        self.graph = []

    def get_connections(self, node):
        return self.graph[node]

    def get_weight(self, v1, v2):
        con = self.get_connections(v1)
        # ic(con)
        for w in con:
            if w[0] == v2:
                return w[1]

    def check_monotone(self, res):
        # ic(res)
        evr_list = []
        for wt in self.graph:
            for j in wt:
                evr_list.append(j)
        # ic(evr_list)
        tops = []
        for name in list(res):
            name = ord(name) - ASCII
            tops.append(name)
        wt = []
        # ic(self.get_connections(tops[0]))
        for i in range(len(tops)):
            if i != 0:
                wt.append(self.get_weight(tops[i - 1], tops[i]))
            else:
                wt.append(0)

        heur = []
        for j in range(len(tops)):
            if j != 0:
                h1 = abs(tops[j] - self.end)
                h2 = abs(tops[j - 1] - self.end)
                heur.append(abs(h1 - h2))
            else:
                heur.append(0)

        for k in range(len(tops)):
            if heur[k] > wt[k]:
                return False

        if self.end != 0:
            return False

        return True

    def check_admissibility(self, res):
        evr_list = []
        # ic(self.graph)
        for wt in self.graph:
            for j in wt:
                evr_list.append(j)
        # ic(evr_list)
        tops = []
        for name in list(res):
            name = ord(name) - ASCII
            tops.append(name)
        wt = []
        # ic(self.get_connections(tops[0]))
        for i in range(len(tops)):
            if i != 0:
                wt.append(self.get_weight(tops[i - 1], tops[i]))
            else:
                wt.append(0)

        heur = []
        for j in range(len(tops)):
            if j != 0:
                h1 = abs(tops[j] - self.end)
                heur.append(h1)
            else:
                heur.append(0)

        path_w = []
        for k in range(len(tops)):
            if k != 0:
                path_w.append(sum(wt[k+1:]))
            else:
                path_w.append(sum(wt))

        for u in range(len(tops)):
            if heur[u] > path_w[u]:
                return False
        return True

    def a_star_search(self, start, end):
        frontier = PriorityQueue()
        frontier.put(start, 0)
        came_from = {}
        cost_so_far = {}
        came_from[start] = None
        cost_so_far[start] = 0

        while not frontier.empty():
            current = frontier.get()

            if current == end:
                break

            for next_ in self.graph[current]:
                new_cost = cost_so_far[current] + next_[-1]
                if next_[0] not in cost_so_far or new_cost < cost_so_far[next_[0]]:
                    cost_so_far[next_[0]] = new_cost
                    priority = new_cost + heuristic(end, next_[0])
                    frontier.put(next_[0], priority)
                    came_from[next_[0]] = current
        return came_from, cost_so_far

    def create_graph(self, file):
        self.graph = [[] for i in range(ord('a'), ord('z'))]
        for line in file:
            start, end, weight = line.split()
            begin = ord(start) - ASCII
            stop = ord(end) - ASCII
            self.graph[begin].append([stop, float(weight)])

    def show_res(self):
        x, y = self.a_star_search(self.start, self.end)
        ans = "" + chr(self.end + ASCII)
        cur = x[self.end]
        while cur is not None:
            ans += chr(cur + ASCII)
            cur = x[cur]
        return ans[::-1]


if __name__ == '__main__':
    with open(argv[1], 'r') as f:
        file = f.readlines()
    start_, end_ = file[0].lower().strip().split(' ')
    file.pop(0)
    gr = Graph(start_, end_)
    gr.create_graph(file)
    gr.start = ord(start_) - ASCII
    gr.end = ord(end_) - ASCII
    ans = gr.show_res()
    print(ans)
    if not gr.check_monotone(ans):
        print("Эвристическая функция не монотонна")
    else:
        print("Эвристическая функция монотонна")

    if not gr.check_admissibility(ans):
        print("Эвристическая функция не допустима")
    else:
        print("Эвристическая функция допустима")