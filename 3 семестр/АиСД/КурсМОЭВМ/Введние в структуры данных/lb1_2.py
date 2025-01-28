import sys
sys.setrecursionlimit(1000000000)

def tree_creator(data):
    tree = {i: [] for i in data}
    for i, elem in enumerate(data):
        tree[elem].append(i)
    return tree

def height(tree, current_root):
    res_height = 1
    for child in tree[current_root]:
        if child in tree.keys():
            res_height = max(res_height, 1 + height(tree, child))
    return res_height

n = input()
parents = list(map(int, input().split()))
print(height(tree_creator(parents), -1))
