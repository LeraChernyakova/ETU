class Heap:
    def __init__(self):
        self.MAX_SIZE = 10**5
        self.heap = [None] * self.MAX_SIZE
        self.size = 0

    @staticmethod
    def get_parent(index):
        return (index - 1) // 2

    @staticmethod
    def get_left_child(index):
        return 2 * index + 1

    @staticmethod
    def get_right_child(index):
        return 2 * index + 2

    def insert(self, element):
        if self.size == self.MAX_SIZE:
            return -1
        self.heap[self.size] = element
        self.sift_up(self.size)
        self.size += 1

    def extract_max(self):
        max_element = self.heap[0]
        self.heap[0], self.heap[self.size-1] = self.heap[self.size-1], None
        self.size -= 1
        self.sift_down(0)
        return max_element

    def sift_up(self, index):
        parent = self.get_parent(index)
        while index > 0 and self.heap[parent] < self.heap[index]:
            self.heap[parent], self.heap[index] = self.heap[index], self.heap[parent]
            index = parent
            parent = self.get_parent(index)

    def sift_down(self, index):
        left = self.get_left_child(index)
        right = self.get_right_child(index)
        if left >= self.size and right >= self.size:
            return
        if right >= self.size:
            min_index = left if self.heap[left] < self.heap[index] else index
        else:
            min_index = left if self.heap[left] < self.heap[right] else right
            min_index = min_index if self.heap[min_index] < self.heap[index] else index
        if min_index != index:
            self.heap[min_index], self.heap[index] = self.heap[index], self.heap[min_index]
            self.sift_down(min_index)

    def parallel_process(self, times):
        answer = list()
        for elem in times:
            answer.append([self.heap[0][1], self.heap[0][0]])
            self.heap[0][0] += elem
            self.sift_down(0)
        return answer

if __name__ == '__main__':
    n, m = map(int, input().split())
    arr = input().split()
    time = [int(i) for i in arr]
    heap = Heap(n)
    result = heap.parallel_process(time)
    for answ in result:
        print(*answ)
