from protect_cw import RBTree
from protect_cw import delete_elements_in_range

def test1():
    tree1_list = [1, 2, 3, 45, 12, 34, 90, 12, 3, 12, 23, 33]
    tree1 = RBTree()

    for i in range(len(tree1_list)):
        tree1.insert(tree1_list[i])

    delete_elements_in_range(tree1)

print('Тест 1:')
print()
test1()
print()