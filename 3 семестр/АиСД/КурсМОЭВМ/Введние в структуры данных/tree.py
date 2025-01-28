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
    def __init__(self, root):
        self.root = root

    def Height (self, current):
        res_height = 1
        for child in current.elements:
            res_height = max(self.Height(child) + 1, res_height)
        return res_height

def Tree_creator(data):
    tree = {i: [] for i in data}
    for i, elem in enumerate(data):
        tree[elem].append(i)
    return tree

tree = input()
data = list(map(int, tree.split()))
print(Tree_creator(data))


def height(self, current_root):
    res_height = 1
    for child in current_root.elements:
        if child in self.keys():
            height(self, child)
        else:

    return res_height


def Tree_creator(data):
    tree = {i: [] for i in data}
    for i, elem in enumerate(data):
        tree[elem].append(i)
    return tree


def tree_creator(data):
    tree = {i: [] for i in data}
    for i, elem in enumerate(data):
        tree[elem].append(i)


def height(tree, current):
    res_height = 1
    print('current: \n', current)
    for elem in tree[current]:
        print(elem)

    def Height(self, current):
        res_height = 1
        for child in current.elements:
            res_height = max(self.Height(child) + 1, res_height)
        return res_height