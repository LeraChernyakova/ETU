from collections import Counter

class Node():
    def __init__(self,meaning=None,weight=None):
        self.weight=weight
        self.meaning=meaning
        self.code=''
        self.right=None
        self.left = None

    def __str__(self):
        return str(self.weight)

    def __repr__(self):
        return str(self.weight)

class Tree():
    def __init__(self, my_dict):
        self.tree = []
        for el in my_dict:
            self.tree.append(Node(el, my_dict[el]))
    def proccessing(self):
        while len(self.tree) > 1:
            min_1 = self.tree[0]

            for el in self.tree:
                if min_1.weight > el.weight:
                    min_1 = el

            self.tree.remove(min_1)

            min_2 = self.tree[0]
            for el in self.tree:
                if min_2.weight > el.weight:
                    min_2 = el
            if len(self.tree) == 1:
                min_2 = self.tree[0]

            self.tree.remove(min_2)

            min_1.code += '0'
            min_2.code += '1'
            newNode = Node(min_1.meaning + min_2.meaning, min_1.weight + min_2.weight)
            newNode.left = min_1
            newNode.right = min_2
            self.tree.append(newNode)


def m_print(current, ans):
    if not current:
        return
    for el in current.meaning:
        ans[el]+=current.code
    m_print(current.left, ans)
    m_print(current.right, ans)

