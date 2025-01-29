from main import merge
import pytest

@pytest.mark.parametrize("arr, arr_result, expected_result",
[([(35, 0), (-282, 1), (83, 2)], [], [[1, 2], [1, 0, 2]]),
 ([(9, 0), (4, 1), (53, 2), (2, 3)], [], [[1, 0], [3, 2], [3, 1, 0, 2]]),
 ([(23, 0), (14, 1), (-2, 2)], [], [[2, 1], [2, 1, 0]]),
 ([(9, 0), (9, 1), (9, 2), (9, 3), (18, 4)], [], [[0, 1], [3, 4], [2, 3, 4], [0, 1, 2, 3, 4]]),
 ([(-26, 0), (-131, 1), (3, 2)], [], [[1, 2], [1, 0, 2]])
 ])

def test(arr, arr_result, expected_result):
    assert merge(arr, arr_result) == expected_result