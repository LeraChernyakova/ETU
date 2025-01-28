def qsort(arr):
    if len(arr) <= 1:
        return arr
    else:
        support = arr[len(arr)//2]
        more = list()
        less = list()
        same = list()
        for elem in arr:
            if elem < support:
                less.append(elem)
            if elem > support:
                more.append(elem)
            if elem == support:
                same.append(elem)
        '''        
        print('support: ', support)
        print('more: ', more)
        print('less: ', less)
        print('same: ', same)
        print()
        '''
        return qsort(less) + same + qsort(more)

arr = list(map(int, input().split(', ')))
print(qsort(arr))
