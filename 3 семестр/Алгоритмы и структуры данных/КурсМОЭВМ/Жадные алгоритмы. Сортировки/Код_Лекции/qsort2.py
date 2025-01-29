def qsort(arr, start, end):
    if start >= end:
        return
    else:
        support = arr[(end-start)//2]
        i = start
        j = end
        while i <= j:
            while arr[i] < support:
                i += 1
            while arr[j] > support:
                j -= 1
            if i <= j:
                arr[i], arr[j] = arr[j], arr[i]
                i += 1
                j -= 1
                qsort(arr, start, j)
                qsort(arr, i, end)

arr = list(map(int, input().split(', ')))
qsort(arr, 0, len(arr)-1)
print(arr)
