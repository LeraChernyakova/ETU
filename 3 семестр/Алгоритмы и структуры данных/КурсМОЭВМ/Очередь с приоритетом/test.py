from main import Heap
import pytest

def test1():
    heap = Heap(2)
    time = [1, 2, 3, 4, 5]
    assert heap.parallel_process(time) == [[0, 0], [1, 0], [0, 1], [1, 2], [0, 4]]

def test2():
    heap = Heap(4)
    time = [10, 10, 10, 10, 10, 10, 10]
    assert heap.parallel_process(time) == [[0, 0], [1, 0], [2, 0], [3, 0], [0, 10], [1, 10], [2, 10]]

def test3():
    heap = Heap(1)
    time = [12, 3, 6]
    assert heap.parallel_process(time) == [[0, 0], [0, 12], [0, 15]]

def test4():
    heap = Heap(4)
    time = [100, 9, 1, 23, 45]
    assert heap.parallel_process(time) == [[0, 0], [1, 0], [2, 0], [3, 0], [2, 1]]

def test5():
    heap = Heap(3)
    time = [23, 3]
    assert heap.parallel_process(time) == [[0, 0], [1, 0]]
