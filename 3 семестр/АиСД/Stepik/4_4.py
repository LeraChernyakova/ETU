import sys


class Node:
    def __init__(self, key, left=None, right=None, parent=None):
        self.key = key
        self.left = left
        self.right = right
        self.parent = parent
        self.summa = key


class SplayTree:
    def __init__(self):
        self.root = None
        self.sum = 0

    def __hash(self, x):
        return (x + self.sum) % 1000000001

    def __keep_parent(self, node):
        if node.left is not None:
            node.left.parent = node
        if node.right is not None:
            node.right.parent = node

    def __count_sum(self, node):
        node.summa = node.key
        if node.left is not None:
            node.summa += node.left.summa
        if node.right is not None:
            node.summa += node.right.summa

    def __rotate(self, parent, child):
        gparent = parent.parent
        if gparent is not None:
            if gparent.left == parent:
                gparent.left = child
            else:
                gparent.right = child
        if parent.left == child:
            parent.left, child.right = child.right, parent
        else:
            parent.right, child.left = child.left, parent
        self.__keep_parent(parent)
        self.__keep_parent(child)
        child.parent = gparent
        self.__count_sum(parent)
        self.__count_sum(child)

    def __splay(self, node):
        while node.parent is not None:
            parent = node.parent
            gparent = parent.parent
            if gparent is None:
                self.__rotate(parent, node)
                self.root = node
                return node
            else:
                zigzig = (gparent.left == parent) == (parent.left == node)
                if zigzig:
                    self.__rotate(gparent, parent)
                    self.__rotate(parent, node)
                else:
                    self.__rotate(parent, node)
                    self.__rotate(gparent, node)
        self.root = node
        return node

    def __find(self, node, key):
        if node is None:
            return None
        if node.key == key:
            return self.__splay(node)
        while node.key != key:
            if (key < node.key) and (node.left is not None):
                node = node.left
            elif (key > node.key) and (node.right is not None):
                node = node.right
            else:
                break
        return self.__splay(node)

    def __split(self, node, key):
        if node.key < key:
            right, node.right = node.right, None
            if right is not None:
                right.parent = None
            self.__count_sum(node)
            return node, right
        else:
            left, node.left = node.left, None
            if left is not None:
                left.parent = None
            self.__count_sum(node)
            return left, node

    def __merge(self, left, right):
        if right is None:
            return left
        if left is None:
            return right
        right = self.__find(right, left.key)
        right.left, left.parent = left, right
        return right

    def insert(self, indat):
        key = self.__hash(indat)
        node = self.root
        node = self.__find(node, key)
        if node is None:
            self.root = Node(key, None, None)
            return self.root
        else:
            if node.key != key:
                left, right = self.__split(node, key)
                self.root = Node(key, left, right)
                self.__keep_parent(self.root)
                self.__count_sum(self.root)
                return self.root

    def remove(self, indat):
        key = self.__hash(indat)
        node = self.root
        node = self.__find(node, key)
        if (node is not None) and (node.key == key):
            if node.left is not None:
                node.left.parent = None
            if node.right is not None:
                node.right.parent = None
            self.root = self.__merge(node.left, node.right)
            return self.root

    def search(self, indat):
        key = self.__hash(indat)
        node = self.root
        node = self.__find(node, key)
        if (node is not None) and (node.key == key):
            print('Found')
        else:
            print('Not found')

    def count_sum(self, l, r):
        l_lim = self.__hash(l)
        r_lim = self.__hash(r)
        self.sum = 0
        node = self.root
        if node is not None:
            node = self.__find(node, l_lim)
            sum = node.summa
            if node.left is not None:
                sum -= node.left.summa
            if node.key < l_lim:
                sum -= node.key
            node = self.__find(node, r_lim)
            if node.right is not None:
                sum -= node.right.summa
            if node.key > r_lim:
                sum -= node.key
            if sum > 0:
                self.sum = sum
        print(self.sum)


tree = SplayTree()
if __name__ == "__main__":
    n = int(sys.stdin.readline().rstrip())
    while n:
        cmd = sys.stdin.readline().split()
        if cmd[0] == '+':
            tree.insert(int(cmd[1]))
        if cmd[0] == '-':
            tree.remove(int(cmd[1]))
        if cmd[0] == '?':
            tree.search(int(cmd[1]))
        if cmd[0] == 's':
            tree.count_sum(int(cmd[1]), int(cmd[2]))
        n -= 1
        