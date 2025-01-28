from sys import argv, stdin

from icecream import ic


class Edge(object):
    def __init__(self, u, v, w):
        self.source = u
        self.sink = v
        self.capacity = w

    def __repr__(self):
        return "%s %s:%s" % (self.source, self.sink, self.capacity)


class FlowNetwork(object):
    def __init__(self):
        self.founded = []
        self.adj = {}
        self.flow = {}

    def add_vertex(self, vertex):
        self.adj[vertex] = []

    def get_edges(self, v):
        ic(v)
        return self.adj[v]

    def add_edge(self, u, v, w=0):
        if u == v:
            raise ValueError("u == v")
        edge = Edge(u, v, w)
        redge = Edge(v, u, 0)
        edge.redge = redge
        redge.redge = edge
        self.adj[u].append(edge)
        self.adj[v].append(redge)
        self.flow[edge] = 0
        self.flow[redge] = 0

    def find_path(self, source, sink, path):
        if source == sink:
            return path
        for edge in self.get_edges(source):
            ic(edge)
            residual = edge.capacity - self.flow[edge]
            if residual > 0 and edge not in path:
                result = self.find_path(edge.sink, sink, path + [edge])
                if result is not None:
                    return result

    def max_flow(self, source, sink):
        path = self.find_path(source, sink, [])
        while path is not None:
            residuals = [edge.capacity - self.flow[edge] for edge in path]
            flow = min(residuals)
            for edge in path:
                self.flow[edge] += flow
                self.flow[edge.redge] -= flow
            path = self.find_path(source, sink, [])
        return sum(self.flow[edge] for edge in self.get_edges(source))

    def get_result(self):
        new_dict = {}
        for i in self.flow:
            if self.flow[i] >= 0:
                name = i.__repr__().split(":")[0]
                value = self.flow[i]
                if (name in new_dict and value > new_dict[name]) or (name not in new_dict) and name in self.founded:
                    new_dict[name] = value

        res = []
        for i in new_dict.keys():
            res.append(f'{i} {new_dict[i]}')
        return sorted(res)


def main():
    g = FlowNetwork()
    vers = []
    N = int(input())
    v0 = input()
    vn = input()
    strlist = []
    [strlist.append(line) for line in stdin]
    s = "".join(strlist).splitlines()
    for i in s:
        vers.append(i[0])
        vers.append(i[2])
        g.founded.append("".join(i[0] + ' ' + i[2]))
    vers = list(set(vers))
    [g.add_vertex(v) for v in vers]
    for i in s:
        g.add_edge(i.split(' ')[0], i.split(' ')[1], int(i.split(' ')[2]))

    print(g.max_flow(v0, vn))
    res = g.get_result()
    for i in res:
        print(i)


if __name__ == '__main__':
    main()
