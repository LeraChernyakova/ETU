from RBTree import RBTree

def test1():
    tree1_list = [1, 2, 3, 45, 12, 34, 90, 12, 3]
    tree1 = RBTree()

    for i in range(len(tree1_list)):
        tree1.insert(tree1_list[i])

    for i in range(3):
        tree1.delete(i)
        tree1.print_tree(i)

test1()