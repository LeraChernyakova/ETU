def merge(arr):
    if len(arr) == 1:
        return
    middle = len(arr) // 2
    left, right = arr[:middle], arr[middle:]
    merge(left)
    merge(right)
    index_left = index_right = index = 0
    result = [0] * (len(left) + len(right))
    while index_left < len(left) and index_right < len(right):
        if left[index_left][0] <= right[index_right][0]:
            result[index] = left[index_left]
            index_left += 1
        else:
            result[index] = right[index_right]
            index_right += 1
        index += 1
    while index_left < len(left):
        result[index] = left[index_left]
        index_left += 1
        index += 1
    while index_right < len(right):
        result[index] = right[index_right]
        index_right += 1
        index += 1
    for i in range(len(arr)):
        arr[i] = result[i]
    for i in range(len(arr)):
        print(arr[i][1], end=" ")
    print()
    return arr

n = int(input())
summaDM = []
for i in range(n):
    summaD = 0
    mi = int(input())
    indForSum = 0
    for j in range(mi):
        line = list(map(int, input().split()))
        summaD += line[indForSum]
        indForSum += 1
    summaDM.append((summaD, i))
answer = merge(summaDM)
for i in range(len(answer)):
    print(answer[i][1], end=" ")
