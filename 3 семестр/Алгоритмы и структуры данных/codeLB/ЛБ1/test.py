from main import height
import pytest

@pytest.mark.parametrize("tree, n, expected_result", [([-1], 1, 1),
                                                      ([-1, 0, 0], 3, 2),
                                                      ([3, 4, 3, 4, -1], 5, 3),
                                                      ([4, 0, 8, -1, 3, 7, 2, 1, 5], 9, 9),
                                                      ([15, 2, 4, 2, 8, 6, 4, 6, -1, 10, 12, 10, 8, 14, 12, 14], 16, 5)])
def test(tree, n, expected_result):
    assert height(tree, n) == expected_result
