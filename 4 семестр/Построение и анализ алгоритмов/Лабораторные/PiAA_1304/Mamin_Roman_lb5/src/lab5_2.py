class TrieNode:
    def __init__(self, suffix_link=None):
        self.children = {}
        self.suffix_link = suffix_link
        self.patterns = []


class Trie:
    """
    Класс дерева три.
  Атрибуты:
  - root: корневой узел дерева
  Методы:
  - create_trie: создание дерева три для заданных паттернов
  - links: создание суффиксных ссылок для узлов дерева три
  """

    def __init__(self, patterns):
        """Конструктор класса"""
        self.create_trie(patterns)
        self.create_links()

    def create_trie(self, patterns):
        """
        Метод для создания дерева для заданных паттернов.
        :param patterns: 
        :return: 
        """
        self.root = TrieNode()
        for index, pattern in enumerate(patterns):
            node = self.root
            for symbol in pattern:
                node = node.children.setdefault(symbol, TrieNode(self.root))
            node.patterns.append(index)

    def create_links(self):
        """
        Метод для создания суффиксных ссылок для узлов дерева три.
        :return: 
        """
        queue = [child for child in self.root.children.values()]
        while queue:
            current_node = queue.pop(0)
            for symbol, child_node in current_node.children.items():
                queue.append(child_node)
                link = current_node.suffix_link
                while not (link is None or symbol in link.children):
                    link = link.suffix_link
                child_node.suffix_link = link.children[
                    symbol] if link else self.root
                child_node.patterns += child_node.suffix_link.patterns


def aho_corasick(text, patterns):
    """
    Функция для поиска всех вхождений паттернов в текст с помощью алгоритма Ахо-Корасика.
    Возвращает список кортежей, содержащих индекс начала найденного вхождения и номер паттерна.
    """
    trie = Trie(patterns)
    result = []
    node = trie.root
    for i in range(len(text)):
        while node is not None and text[i] not in node.children:
            node = node.suffix_link
        if node is None:
            node = trie.root
            continue
        node = node.children[text[i]]
        for pattern in node.patterns:
            result.append((i - len(patterns[pattern]) + 1, pattern))
    result = sorted(result)
    return result


def generate_patterns(pattern, wildcard):
    """
    Функция для генерации частей и стартовых индексов паттерна, разделенных символом подстановки.

    Аргументы:
    - pattern: строка, содержащая паттерн и символы подстановки.
    - wildcard: символ подстановки.

    Возвращает:
    - parts: список строк, содержащих части паттерна, разделенные символом подстановки.
    - start_indices: список индексов начала частей паттерна в строке pattern.
    """
    parts = list(filter(bool, pattern.split(wildcard)))
    start_indices = []
    flag = 1
    for i, c in enumerate(pattern):
        if c == wildcard:
            flag = 1
            continue
        if flag:
            start_indices.append(i)
            flag = 0
    return parts, start_indices


def solve(text, pattern, wildcard):
    """
    Функция для решения задачи поиска всех вхождений паттерна в текст с помощью алгоритма Ахо-Корасика.

    Аргументы:
    - text: строка, в которой производится поиск.
    - pattern: строка, содержащая паттерн и символы подстановки.
    - wildcard: символ подстановки.

    Возвращает:
    - res: список индексов начала найденных вхождений паттерна в строке text.
    """
    patterns, starts = generate_patterns(pattern, wildcard)
    indices = aho_corasick(text, patterns)
    c = [0] * len(text)
    for i, p_i in indices:
        index = i - starts[p_i]
        if 0 <= index < len(c):
            c[index] += 1

    res = []
    for i in range(len(c) - len(pattern) + 1):
        if c[i] == len(patterns):
            res.append(i + 1)
    return res


if __name__ == "__main__":
    text = input()
    pattern = input()
    wildcard = input()
    answer = solve(text, pattern, wildcard)
    print(*answer, sep="\n")