from sys import stdin, argv


def sorting(dictator):
    keys = []
    list_d = list(dictator.items())
    list_d.sort(key=lambda k: k[1])
    for i in list_d:
        keys.append(i[0])
    return keys


class Graph:
    def __init__(self, st, en):
        self.start = st
        self.end = en
        self.graph = dict()
        self.path = [st]

    def greedy(self, key):
        seen = False
        tmp_keys = sorting(self.graph[key])
        for item in tmp_keys:
            if item in self.path:
                continue
            if item in self.graph.keys():
                self.path.append(item)
                seen = self.greedy(item)
            if seen or item == self.end:
                seen = True
                if self.end not in self.path:
                    self.path.append(self.end)
                break
        return seen

    def create_graph(self, file):
        self.graph = dict()
        for line in file:
            st, en, leng = line.split(" ")
            leng = leng.strip()
            if st in self.graph.keys():
                self.graph[st][en] = float(leng)
            else:
                self.graph[st] = dict({en: float(leng)})


if __name__ == "__main__":
    with open(argv[1], 'r') as f:
        file = f.readlines()
    start, end = file[0].lower().strip().split(' ')
    file.pop(0)
    graph = Graph(start, end)
    graph.create_graph(file)
    graph.greedy(start)
    print(''.join(graph.path))
