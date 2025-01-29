from queue import PriorityQueue
# Вариант очереди, который извлекает открытые записи в порядке приоритета (сначала самый низкий).
from sys import stdin
# Cтандартный ввод используется для всего интерактивного ввода


# Класс решения
class Solution:
    def __init__(self):
        """
        Инициализирует поля класса, необходимые для решения
        """
        self.graph = {}
        self.start_node = None
        self.end_node = None
        self.answer = ""
        self.way_found = False

    def __create_graph_from_input(self) -> None:
        """
        Создает граф в виде словаря из ввода пользователя
        """
        self.start_node, self.end_node = input().split()
        process_graph = {}

        for line in stdin:
            cur_node, next_node, distance = line.split()
            if not process_graph.get(cur_node):
                process_graph[cur_node] = [(next_node, float(distance))]
            else:
                process_graph[cur_node] += [(next_node, float(distance))]
        self.graph = process_graph

    def __sort_graph_by_length(self) -> None:
        """
        Сортирует узлы у каждого узла в графе по весу ребра
        """
        for node in self.graph:
            self.graph.update({node: sorted(self.graph[node], key=lambda n: n[1])})

    def __solve_by_greedy_algorythm(self, cur_node: str, cur_way: str) -> None:
        """
        Решает задачу методом жадного алогритма
        :param cur_node: текущий узел
        :param cur_way: текущий построенный путь
        """
        if self.way_found:
            return
        if cur_node == self.end_node:
            self.answer = cur_way
            self.way_found = True
            return
        if self.graph.get(cur_node):
            for nodes in self.graph[cur_node]:
                next_node = nodes[0]
                next_way = cur_way + f"{next_node}"
                self.__solve_by_greedy_algorythm(next_node, next_way)

    def __compute_heuristic(self, cur_node: str) -> int:
        """
        Считает значении функции эвристики
        :param cur_node: текуший узел
        :return: значение функции эвристики
        """
        return abs(ord(self.end_node) - ord(cur_node))

    def __solve_by_a_star_algorythm(self) -> None:
        """
        Решает задачу методом алгоритма А*
        """
        frontier = PriorityQueue()
        frontier.put((0, self.start_node))
        came_from = {}
        cost_so_far = {}

        came_from[self.start_node] = None
        cost_so_far[self.start_node] = 0
        while not frontier.empty():
            cur_node = frontier.get()[1]
            if cur_node == self.end_node:
                break
            if self.graph.get(cur_node):
                for next_node, next_distance in self.graph.get(cur_node):
                    new_cost = cost_so_far[cur_node] + next_distance
                    if next_node not in cost_so_far or new_cost < cost_so_far[next_node]:
                        cost_so_far[next_node] = new_cost
                        priority = new_cost + self.__compute_heuristic(next_node)
                        frontier.put((priority, next_node))
                        came_from[next_node] = cur_node

        cur_node = self.end_node
        self.answer = f"{self.end_node}"
        while cur_node != self.start_node:
            cur_node = came_from[cur_node]
            self.answer += cur_node
        self.answer = self.answer[::-1]

    def get_solution_by_greedy(self) -> None:
        """
        Задает последовательность действий для
        решения задачи методом жадного алгоритма
        """
        solver.__create_graph_from_input()
        solver.__sort_graph_by_length()
        self.__solve_by_greedy_algorythm(self.start_node, self.answer + f"{self.start_node}")

    def get_solution_by_a_star(self) -> None:
        """
        Задает последовательность действий для
        решения задачи методом алгоримта A*
        """
        solver.__create_graph_from_input()
        self.__solve_by_a_star_algorythm()

    def print_answer(self) -> None:
        """
        Печатает ответ на задачу в консоль
        """
        print(self.answer)


if __name__ == "__main__":
    solver = Solution()
    # solver.get_solution_by_greedy()
    solver.get_solution_by_a_star()
    solver.print_answer()
