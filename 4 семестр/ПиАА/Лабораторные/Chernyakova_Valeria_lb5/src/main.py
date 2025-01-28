# Класс, описывающий узлы для построения дерева ключевых слов(узлы бора)
# Поля класса: leaves указывает, в какие узлы переходить
# plenty_patterns множество шаблонов, обнаруживающиеся при переходе по символу
# node_if_fail узел для перехода при просмотре неподходящего символа
class NodePatternTree:
    # Метод, инициализирующий поля класса
    def __init__(self):
        self.leaves = {}
        self.plenty_patterns = []
        self.node_if_fail = None

# Функция, создающая бор - дерево паттернов
# Принимает на вход набор шаблонов
# Возвращает корень дерева паттернов - бора
def create_pattern_tree_aho(patterns):
    root = NodePatternTree()
    for index, string in enumerate(patterns):
        node = root
        for symbol in string:
            node = node.leaves.setdefault(symbol, NodePatternTree())
        node.plenty_patterns += [index]
    return root

# Функция, реализующая автомат Ахо-Корасик, а именно
# создается дерево паттернов и инициализируются
# узлы для перехода при просмотре неподходящих символов
# Принимает на вход набор шаблонов
# Возвращает корень дерева паттернов - бора
def create_aho_statemachine(patterns):
    root = create_pattern_tree_aho(patterns)
    nodes_queue = []
    for node in root.leaves.values():
        nodes_queue += [node]
        node.node_if_fail = root
    while len(nodes_queue) > 0:
        current_node = nodes_queue.pop(0)
        for symbol, leaf in zip(current_node.leaves.keys(), current_node.leaves.values()):
            nodes_queue += [leaf]
            fail_node = current_node.node_if_fail
            while fail_node is not None and symbol not in fail_node.leaves:
                fail_node = fail_node.node_if_fail
            leaf.node_if_fail = fail_node.leaves[symbol] if fail_node else root
            leaf.plenty_patterns += leaf.node_if_fail.plenty_patterns
    return root

# Функция, находящая все возможные вхождения шаблонов в текст(1 задание)
# Принимает на вход текст, корень бора и набор шаблонов
# Возвращает список, содержащий шаблоны с их индексами вхождения в текст
def find_all_substrings_aho_first(text, root, patterns):
    current_node = root
    substrings_in_text = []
    for i in range(len(text)):
        while current_node is not None and text[i] not in current_node.leaves:
            current_node = current_node.node_if_fail
        if current_node is None:
            current_node = root
            continue
        current_node = current_node.leaves[text[i]]
        for pattern in current_node.plenty_patterns:
            substrings_in_text += [[i - len(patterns[pattern]) + 2, pattern + 1]]
    return substrings_in_text

# Функция, находящая все возможные вхождения шаблонов в текст(2 задание)
# Принимает на вход текст, корень бора и набор шаблонов
# Возвращает список, содержащий шаблоны с их индексами вхождения в текст
def find_all_substrings_aho_second(text, root, patterns):
    current_node = root
    substrings_in_text = []
    for i in range(len(text)):
        while current_node is not None and text[i] not in current_node.leaves:
            current_node = current_node.node_if_fail
        if current_node is None:
            current_node = root
            continue
        current_node = current_node.leaves[text[i]]
        for pattern in current_node.plenty_patterns:
            substrings_in_text += [[i - len(patterns[pattern]) + 1, pattern]]
    return substrings_in_text

# Функция, создающая наборы шаблонов для задания с символом джокером
# Принимает на вход единый шаблон и символ джокер
# Возвращает набор шаблонов и соответствующие им стартовые индексы в едином шаблоне
def create_all_patterns(pattern, joker_symbol):
    patterns = list(filter(None, pattern.split(joker_symbol)))
    start_indices_in_pattern = []
    start_index = 0
    for string in patterns:
        current_section = pattern[start_index:]
        current_index = current_section.index(string)
        start_indices_in_pattern += [current_index + (len(pattern)-len(current_section))]
        start_index = current_index + len(string) + (len(pattern)-len(current_section))
    return patterns, start_indices_in_pattern

# Функция, считающая количество безмасочных подстрок, встретившихся в тексте
# Принимает на вход текст, стартовые индексы шаблонов в едином шаблоне,
# список, хранящий шаблоны и их индексы вхождения в тексте
# Возвращает список, хранящий по индексу количество встретившихся подстрок
def calculate_substrings(text, start_indices_in_pattern, substrings_in_text):
    count_substring_without_mask = [0]*len(text)
    for index_in_text, pattern in substrings_in_text:
        current_index = index_in_text - start_indices_in_pattern[pattern]
        if current_index >= 0 and current_index < len(count_substring_without_mask):
            count_substring_without_mask[current_index] += 1
    return count_substring_without_mask

# Функция, выводящая ответ на первое задание
# Принимает на вход список, содержащий 
# шаблоны с их индексами вхождения в текст
def print_first_answer(patterns_in_text):
    patterns_in_text.sort(key=lambda value:(value[0], value[1]))
    for i in range(len(patterns_in_text)):
        print(*patterns_in_text[i], sep = ' ')   

# Функция, выводящая ответ на второе задание
# Принимает на вход список, хранящий по индексу 
# количество встретившихся подстрок
def print_second_answer(count_substrings_by_index, pattern, all_patterns):
    for i in range(len(count_substrings_by_index)-len(pattern)+1):
        if count_substrings_by_index[i] == len(all_patterns):
            print(i+1)

# Функция, запускающая решение первого задания
def solve_first_task():
    text = input()
    count_pattern = int(input())
    patterns = []
    for _ in range(count_pattern):
        patterns += [input()]
    root_pattern_tree = create_aho_statemachine(patterns)
    patterns_in_text = sorted(find_all_substrings_aho_first(text, root_pattern_tree, patterns))
    print_first_answer(patterns_in_text)

# Функция, запускающая решение второго задания
def solve_second_task():
    text = input()
    pattern = input()
    joker_symbol = input()
    all_patterns, start_indices_in_pattern = create_all_patterns(pattern, joker_symbol)
    root_pattern_tree = create_aho_statemachine(all_patterns)
    substrings_in_text = sorted(find_all_substrings_aho_second(text, root_pattern_tree, all_patterns))
    count_substrings_without_mask = calculate_substrings(text, start_indices_in_pattern, substrings_in_text)
    print_second_answer(count_substrings_without_mask, pattern, all_patterns)
    
# Условие для запуска программы
if __name__ == "__main__":
    solve_first_task()
    solve_second_task()