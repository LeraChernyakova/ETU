# for github
# -*- coding: utf 8 -*-

from sys import argv

from icecream import ic


class Edge(object):
    def __init__(self, u, v, w):
        self.source = u
        self.sink = v
        self.capacity = w

    def __repr__(self):
        return "%s %s %s" % (self.source, self.sink, self.capacity)


class FlowNetwork(object):
    def __init__(self):
        self.adj = {}
        self.flow = {}

    def add_vertex(self, vertex):
        self.adj[vertex] = []

    def get_edges(self, v):
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
        ic(edge)

    def find_path(self, source, sink, path):
        if source == sink:
            return path
        for edge in self.get_edges(source):
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
        res = self.flow
        for i in res.keys():
            if res[i] >= 0:
                new_dict[i] = res[i]
        return new_dict


def main():
    g = FlowNetwork()
    vers = []
    with open(argv[1], 'r') as file:
        N = int(file.readline())
        v0 = file.readline()[:-1]
        vn = file.readline()[:-1]
        strlist = file.read().splitlines()
        ic(strlist)
        s = " ".join(strlist)
        ic(s)
        ver = "".join(c for c in s if c.isalpha())
        ver = set(ver)
        [g.add_vertex(v) for v in "".join(list(ver))]
        for i in strlist:
            vers.append(i[0])
            vers.append(i[2])
            g.add_edge(i.split(' ')[0], i.split(' ')[1], int(i.split(' ')[2]))

    print(g.max_flow(v0, vn))
    ic(g.flow)
    res = g.get_result()
    for i in res:
        print(i)


if __name__ == '__main__':
    main()
