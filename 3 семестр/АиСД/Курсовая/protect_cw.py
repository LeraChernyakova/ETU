# Задача на программирование: Удалите все числа из красно-черного дерева, которые лежат в диапазоне
# [min, max]. Min, max задаются пользовальским вводом.


BLACK = 'black'
RED = 'red'


class Node:
    def __init__(self, key):
        self.key = key
        self.parent = None
        self.left = None
        self.right = None
        self.color = RED


class RBTree:
    def __init__(self):
        self.NULL = Node(0)
        self.NULL.color = BLACK
        self.NULL.left = None
        self.NULL.right = None
        self.root = self.NULL

    def left_rotate(self, node):
        new_node = node.right
        node.right = new_node.left

        if new_node.left != self.NULL:
            new_node.left.parent = node

        new_node.parent = node.parent

        if node.parent is None:
            self.root = new_node
        elif node == node.parent.left:
            node.parent.left = new_node
        else:
            node.parent.right = new_node

        new_node.left = node
        node.parent = new_node

    def right_rotate(self, node):
        new_node = node.left
        node.left = new_node.right

        if new_node.right != self.NULL:
            new_node.right.parent = node

        new_node.parent = node.parent

        if node.parent is None:
            self.root = new_node
        elif node == node.parent.right:
            node.parent.right = new_node
        else:
            node.parent.left = new_node

        new_node.right = node
        node.parent = new_node

    def insert(self, key):
        node = Node(key)
        node.parent = None
        node.key = key
        node.left = self.NULL
        node.right = self.NULL
        node.color = RED

        parent = None
        current = self.root

        while current != self.NULL:
            parent = current
            if node.key < current.key:
                current = current.left
            else:
                current = current.right

        node.parent = parent

        if parent is None:
            self.root = node
        elif node.key < parent.key:
            parent.left = node
        else:
            parent.right = node

        if node.parent is None:
            node.color = BLACK
            return

        if node.parent.parent is None:
            return

        self.fix_insert(node)

    def fix_insert(self, node):
        while node.parent.color == RED:
            if node.parent == node.parent.parent.right:
                uncle = node.parent.parent.left
                if uncle.color == RED:
                    uncle.color = BLACK
                    node.parent.color = BLACK
                    node.parent.parent.color = RED
                    node = node.parent.parent
                else:
                    if node == node.parent.left:
                        node = node.parent
                        self.right_rotate(node)
                    node.parent.color = BLACK
                    node.parent.parent.color = RED
                    self.left_rotate(node.parent.parent)
            else:
                uncle = node.parent.parent.right
                if uncle.color == RED:
                    uncle.color = BLACK
                    node.parent.color = BLACK
                    node.parent.parent.color = RED
                    node = node.parent.parent
                else:
                    if node == node.parent.right:
                        node = node.parent
                        self.left_rotate(node)
                    node.parent.color = BLACK
                    node.parent.parent.color = RED
                    self.right_rotate(node.parent.parent)
            if node == self.root:
                break

        self.root.color = BLACK

    def search(self, key):
        current = self.root
        while current is not None:
            if key < current.key:
                current = current.left
            elif key > current.key:
                current = current.right
            elif key == current.key:
                return current
        return None

    def delete(self, key):
        self.delete_helper(self.root, key)

    def delete_helper(self, node, key):
        delete = self.NULL

        while node != self.NULL:
            if node.key == key:
                delete = node

            if node.key <= key:
                node = node.right
            else:
                node = node.left

        if delete == self.NULL:
            print("There is no such key in the tree! Deletion failed.")
            return

        n_change = delete
        change_original_color = n_change.color

        if delete.left == self.NULL:
            n_fix = delete.right
            self.change(delete, delete.right)
        elif delete.right == self.NULL:
            n_fix = delete.left
            self.change(delete, delete.left)
        else:
            n_change = self.minimum(delete.right)
            change_original_color = n_change.color
            n_fix = n_change.right
            if n_change.parent == delete:
                n_fix.parent = n_change
            else:
                self.change(n_change, n_change.right)
                n_change.right = delete.right
                n_change.right.parent = n_change

            self.change(delete, n_change)
            n_change.left = delete.left
            n_change.left.parent = n_change
            n_change.color = delete.color

        if change_original_color == BLACK:
            self.fix_delete(n_fix)

    def change(self, p, c):
        if p.parent is None:
            self.root = c
        elif p == p.parent.left:
            p.parent.left = c
        else:
            p.parent.right = c
        c.parent = p.parent

    def minimum(self, node):
        while node.left != self.NULL:
            node = node.left
        return node

    def fix_delete(self, node):
        while node != self.root and node.color == BLACK:
            if node == node.parent.left:
                brother = node.parent.right
                if brother.color == RED:
                    brother.color = BLACK
                    node.parent.color = RED
                    self.left_rotate(node.parent)
                    brother = node.parent.right
                if brother.left.color == BLACK and brother.right.color == BLACK:
                    brother.color = RED
                    node = node.parent
                else:
                    if brother.right.color == BLACK:
                        brother.left.color = BLACK
                        brother.color = RED
                        self.right_rotate(brother)
                        brother = node.parent.right

                    brother.color = node.parent.color
                    node.parent.color = BLACK
                    brother.right.color = BLACK
                    self.left_rotate(node.parent)
                    node = self.root
            else:
                brother = node.parent.left
                if brother.color == RED:
                    brother.color = BLACK
                    node.parent.color = RED
                    self.right_rotate(node.parent)
                    brother = node.parent.left
                if brother.right.color == BLACK and brother.right.color == BLACK:
                    brother.color = RED
                    node = node.parent
                else:
                    if brother.left.color == BLACK:
                        brother.right.color = BLACK
                        brother.color = RED
                        self.left_rotate(brother)
                        brother = node.parent.left

                    brother.color = node.parent.color
                    node.parent.color = BLACK
                    brother.left.color = BLACK
                    self.right_rotate(node.parent)
                    node = self.root

        node.color = BLACK

    def print_node(self, node, indent, last):
        if node != self.NULL:
            print(indent, end=' ')
            if last:
                print("R--->", end=' ')
                indent += "  "
            else:
                print("L--->", end=' ')
                indent += "|  "

            node_color = "RED" if node.color == RED else "BLACK"
            print(str(node.key) + "(" + node_color + ")")
            self.print_node(node.left, indent, False)
            self.print_node(node.right, indent, True)

    def print_tree(self):
        self.print_node(self.root, "", True)


def test1():
    tree1_list = [12, 2, 56, 8, 90, 1, 3, 7]
    return tree1_list


def test2():
    tree2_list = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    return tree2_list


def test3():
    tree3_list = [40, 34, 56, 12, 56, 78]
    return tree3_list


tree_list = test1()
tree = RBTree()


for i in range(len(tree_list)):
    tree.insert(tree_list[i])

tree.print_tree()
print()

tree.insert(9)
print()
tree.print_tree()

print('Введите отрезок min и max, чтобы удалить узлы дерева, находящиеся в данном диапозоне')
mini = int(input())
maxi = int(input())

if mini > maxi:
    print('Введенные некорректные значения! min > max. Попробуйте еще раз.')
    mini = int(input())
    maxi = int(input())

for i in range(len(tree_list)):
    tree.insert(tree_list[i])

print()
print('Дерево до удаления узлов:')
print()


print('Удаление узлов будет осуществляться из диапазона [', mini, ',', maxi, ']')
print()

for i in range(mini, maxi+1):
    print('Удаление числа ', i)
    tree.delete(i)
    print()
    tree.print_tree()
