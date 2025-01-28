import sys


def output_result(pos, pattern):
    print(pos, pattern)


class AhoNode:
    def __init__(self):
        self.destination = {}
        self.out = []
        self.fail = None


class AhoCorasik:
    def __init__(self):
        self.T = None
        self.P = []
        self.N = 0
        self.pattern_indices = {}
        self.alphabet = ['A', 'C', 'T', 'G', 'N']
        self.result = []

    def reading(self, path):
        if not path:
            self.T = input()
            self.N = int(input())
            for i in range(self.N):
                line = input()
                self.P.append(line)
                self.pattern_indices[self.P[-1]] = len(self.P)
        else:
            with open("".join(path), 'r') as file:
                file = file.read().splitlines()
                self.T = file[0].strip()
                self.N = int(file[1])
                for i in range(2, self.N + 2):
                    line = file[i]
                    self.P.append(line)
                    self.pattern_indices[self.P[-1]] = len(self.P)

    def aho_create_forest(self):
        root = AhoNode()
        for path in self.P:
            node = root
            for character in path:
                node = node.destination.setdefault(character, AhoNode())
            node.out.append(path)
        return root

    def aho_create_statemachine(self):
        bohr = self.aho_create_forest()
        queue = []
        for node in bohr.destination.values():
            queue.append(node)
            node.fail = bohr

        while len(queue) > 0:
            cur_node = queue.pop(0)
            # print('Current node in BFS: ', cur_node.destination, cur_node.out)
            for key, next_node in iter(cur_node.destination.items()):
                queue.append(next_node)
                fail_node = cur_node.fail

                while fail_node is not None and key not in fail_node.destination:
                    fail_node = fail_node.fail

                next_node.fail = fail_node.destination[key] if fail_node else bohr
                next_node.out.extend(next_node.fail.out)
        return bohr

    def aho_find(self):
        root = self.aho_create_statemachine()
        node = root

        for i in range(len(self.T)):
            while node is not None and self.T[i] not in node.destination:
                node = node.fail
            if node is None:
                node = root
                continue
            node = node.destination[self.T[i]]
            for pattern in node.out:
                self.result.append([i - len(pattern) + 2, self.pattern_indices[pattern]])

        self.result.sort()
        for value in self.result:
            output_result(value[0], value[1])


if __name__ == '__main__':
    result = AhoCorasik()
    result.reading(sys.argv[1:])
    result.aho_find()