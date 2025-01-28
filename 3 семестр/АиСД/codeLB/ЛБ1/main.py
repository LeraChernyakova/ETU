def tree_creator(data):
    tree = list(int(parents) for parents in data)
    return tree

def height(tree, n):
    if n == 1:
        return n
    else:
        all_height = n*[0]
        for i in range(n):
            current = i
            while current != -1:
                parent = tree[current]
                current = parent
                all_height[i] += 1
                if all_height[parent]:
                    all_height[i] += all_height[parent]
                    break
        return max(all_height)

if __name__ == '__main__':
    n = int(input())
    parents = list(map(int, input().split()))
    print(height(tree_creator(parents), n))