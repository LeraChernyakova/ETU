class TrieNode:
    """
    Класс узла префиксного дерева
    """
    
    def __init__(self, suffix_link=None):
        """
        Инициализирует узел в префиксном дереве.
        
        :param suffix_link: суффиксная ссылка узла (по умолчанию None).
        """
        self.children = {}
        self.suffix_link = suffix_link
        self.patterns = []

class Trie:
    """Класс префиксного дерева."""
    
    def __init__(self, patterns):
        """
        Инициализирует префиксное дерево и создает суффиксные ссылки.
        
        :param patterns: список строк-образцов для поиска.
        """
        self.create_trie(patterns)
        self.create_links()

    def create_trie(self, patterns):
        """
        Создает префиксное дерево на основе списка строк-образцов.
        
        :param patterns: список строк-образцов для поиска.
        """
        self.root = TrieNode()
        for index, pattern in enumerate(patterns):
            node = self.root
            for symbol in pattern:
                node = node.children.setdefault(symbol, TrieNode(self.root))
            node.patterns.append(index)

    def create_links(self):
        """Создает суффиксные ссылки для всех узлов префиксного дерева."""
        queue = [child for child in self.root.children.values()]
        while queue:
            current_node = queue.pop(0)
            for symbol, child_node in current_node.children.items():
                queue.append(child_node)
                link = current_node.suffix_link
                while not (link is None or symbol in link.children):
                    link = link.suffix_link
                child_node.suffix_link = link.children[symbol] if link else self.root
                child_node.patterns += child_node.suffix_link.patterns

def aho_corasick(text, patterns):
    """
    Ищет все вхождения строк-образцов в заданный текст, используя алгоритм Ахо-Корасик.
    
    :param text: текст для поиска.
    :param patterns: список строк-образцов для поиска.
    :return: список кортежей, содержащих индекс начала вхождения образца в тексте и его порядковый номер в списке       patterns.
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
            result.append((i - len(patterns[pattern]) + 2, pattern + 1))
    result = sorted(result)
    return result


if __name__ == "__main__":
    input_text = input()
    num_patterns = int(input())
    patterns = []
    for i in range(num_patterns):
        patterns.append(input())

    matching_results = aho_corasick(input_text, patterns)
    for match in matching_results:
        print(match[0], match[1])