class Node:
    def __init__(self, data, next_element=None):
        self.data = data
        self.next_element = next_element

class LinkedList:
    def __init__(self, root, tail):
        self.root = root
        self.tail = tail
        self.root.next_element = tail


