import unittest

def binary_search(array, elem, start, end):
    array.sorted()

    if start > end:
        return -1

    mid = (start + end) // 2

    if elem == array[mid]:
        return mid
    elif elem < array[mid]:
        return binary_search(array, elem, mid+1, end)
    else:
        return binary_search(array, elem, start, mid-1)
