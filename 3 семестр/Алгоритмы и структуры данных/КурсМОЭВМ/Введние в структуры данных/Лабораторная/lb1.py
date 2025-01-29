class Node:
    def __init__(self, data):
        self.data = data
        self.elements = []

    def append_child(self, child):
        self.elements.extend(child)

    def __str__(self):
        next_elems = []
        if self.elements:
            for elem in self.elements:
                next_elems.append(elem.data)
        return 'data: {}, next_element: {}\n'.format(self.data, next_elems)

class Tree:
    def __init__(self, parent):
        self.parent = parent

    def tree_creator(self):
        tree = {i: [] for i in self.parent}
        for i, elem in enumerate(self.parent):
            tree[elem].append(i)
            if elem == -1 or i == elem:
                self.root = i
        return tree

    def height(self):
        result_height = 1
        for child in self.root.elements:
            if child in tree.keys():
                self.root.height(child)
            else:
                result_height = max(result_height, 1+self.height(child))
        return result_height

n = input()
parents = list(map(int, input().split()))
data = Tree(parents)
print(data.tree_creator())