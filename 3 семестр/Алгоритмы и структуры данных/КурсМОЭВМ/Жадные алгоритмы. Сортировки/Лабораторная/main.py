def merge(arr, arr_result):
    if len(arr) == 1:
        return
    middle = len(arr) // 2
    left, right = arr[:middle], arr[middle:]
    merge(left, arr_result)
    merge(right, arr_result)
    index_left = index_right = index = 0
    result = [0] * (len(left) + len(right))
    merge_list = list()
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
        merge_list.append(arr[i][1])
    arr_result.append(merge_list)
    return arr_result

if __name__ == '__main__':
    n = int(input())
    summaDM = list()
    arr_result = list()
    for ind in range(n):
        summaD = 0
        mi = int(input())
        indForSum = 0
        for j in range(mi):
            line = list(map(int, input().split()))
            summaD += line[indForSum]
            indForSum += 1
        summaDM.append((summaD, ind))
    answer = merge(summaDM, arr_result)
    for ind in range(len(answer)):
        for j in answer[ind]:
            print(j, end=' ')
        print()
        if ind == len(answer) - 1:
            for j in answer[ind]:
                print(j, end=' ')
