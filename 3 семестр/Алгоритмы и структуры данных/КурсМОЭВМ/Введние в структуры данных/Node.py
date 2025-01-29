class Node:
    def __init__(self, __data, prev=None, next=None):
        self.__data = __data
        self.__prev__ = prev
        self.__next__ = next

    def get_data(self):
        return self.__data

    def __str__(self):
        next = None
        prev = None
        if self.__next__:
            next = self.__next__.__data
        if self.__prev__:
            prev = self.__prev__.__data
        return 'data: {}, prev: {}, next: {}\n'.format(self.__data, prev, next)

