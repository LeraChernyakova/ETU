class Node:
    def __init__(self, data, prev=None, next=None):
        self.__data = data
        self.__prev__ k= prev
        self.__next__ = next

    def get_data(self):
        return self.__data

    def __str__(self):
        next = None
        prev = None
        if self.__next__:
            next = self.__next__.get_data()
        if self.__prev__:
            prev = self.__prev__.get_data()
        return 'data: {}, prev: {}, next: {}'.format(self.__data, prev, next)

class LinkedList:
    def __init__(self, first=None, last=None):
        if first == None and last != None:
            self.__length = 0
            raise ValueError('invalid value for last')
        elif first != None and last == None:
            self.__length = 1
            self.__first__ = Node(first, None, None)
            self.__last__ = self.__fisrt__
        elif first != None and last != None:
            self.__length = 2
            self.__first__ = Node(first)
            self.__last__ = Node(last)
            self.__first__.__next__ = self.__last__
            self.__last__.__prev__ = self.__first__
        else:
            self.__length = 0
            self.__first__ = None
            self.__last__ = None


    def __len__(self):
        return self.__length


    def append(self, element):
        listlen = self.__length
        if listlen != 0:
            self.__length += 1
            self.__last__.__next__ = Node(element)
            self.__last__.__next__.__prev__ = self.__last__
            self.__last__ = self.__last__.__next__

        else:
            self.__length = 1
            self.__first__ = Node(element)
            self.__last__ = self.__first__


    def __str__(self):
        listlen = self.__length
        if listlen != 0:
            elem_now = self.__first__
            all_list = ''
            while elem_now != None:
                all_list += str(elem_now) + '; '
                elem_now = elem_now.__next__
            all_list = all_list[0 : len(all_list) - 2]
            return 'LinkedList[length = {}, [{}]]'.format(self.__length, all_list)
        else:
            return 'LinkedList[]'


    def pop(self):
        listlen = self.__length
        if listlen > 1:
            self.__last__ = self.__last__.__prev__
            self.__last__.__next__ = None
            self.__length -=1
        elif listlen == 1:
            self.clear()
        else:
            raise IndexError('LinkedList is empty!')


    def popitem(self, element):
        delete_element = 0
        listlen = self.__length
        if listlen > 1:
            now_elem = self.__first__
            while now_elem != None:
                if now_elem.get_data() == element:
                    if now_elem.__next__ == None:
                        if now_elem.__prev__ == None:
                            self.__last__ = None
                            self.__first__ = None
                        else:
                            now_elem.__prev__.__next__ = None
                            self.__last__ = now_elem.__prev__
                    else:
                        if now_elem.__prev__ == None:
                            now_elem.__next__.__prev__ = None
                            self.__first__ = now_elem.__next__
                        else:
                            now_elem.__next__.__prev__ = now_elem.__prev__
                            now_elem.__prev__.__next__ = now_elem.__next__
                    delete_element += 1
                    self.__length -= 1
                now_elem = now_elem.__next__
        elif listlen == 1:
            if element == self.__first__.get_data():
                self.__first__ = None
                delete_element += 1
                self.__length -= 1

        if delete_element == 0:
            raise KeyError("{} doesn't exist!".format(element))


    def clear(self):
        self.__length = 0
        self.__first__ = None
        self.__last__ = None



node = Node(1)
print(node) # data: 1, prev: None, next: None
node.__prev__ = Node(2, None, None)
print(node) # data: 1, prev: 2, next: None

linked_list = LinkedList()
print(linked_list) # LinkedList[]
print(len(linked_list)) # 0

linked_list.append(10)
print(linked_list) # LinkedList[length = 1, [data: 10, prev: None, next: None]]
print(len(linked_list)) # 1

linked_list.append(20)
print(linked_list)
# LinkedList[length = 2, [data: 10, prev: None, next: 20; data: 20, prev: 10, next: None]]
print(len(linked_list)) # 2

linked_list.append(30)
print(linked_list)

linked_list.pop()
print(linked_list)
print(linked_list) # LinkedList[length = 1, [data: 10, prev: None, next: None]]
print(len(linked_list)) # 1