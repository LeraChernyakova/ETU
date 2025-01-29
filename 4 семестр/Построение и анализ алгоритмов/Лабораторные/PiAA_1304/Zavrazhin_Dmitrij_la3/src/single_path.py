#!/usr/bin/python3
from sys import argv, stderr
from random import randint, sample

# The script has four parameters:
# (1) The size of a matrix to be generated;
# (2) The number of path to generate;
# (3) The weight for non-diagonal elements. It can be:
#  -- A number - all weights are the same
#  -- A '." - all weights are random, no vertices being disconnected
# (4) If applicable, max possible weight

cardinality = int(argv[1])
n_paths = int(argv[2])
weight = argv[3]

generate_weight = lambda: int(weight)
if weight == '.':
    generate_weight = lambda: randint(1, int(argv[4])) 

matrix = [0] * (cardinality * cardinality)

for i in range(n_paths):

    path = [0] + sample(list(range(1, cardinality)), cardinality - 1) + [0]
    for i in range(cardinality):
        if matrix[path[i] * cardinality + path[i + 1]] == 0:
            matrix[path[i] * cardinality + path[i + 1]] = generate_weight()
    weight = sum([matrix[path[i] * cardinality + path[i + 1]] for i in range(cardinality)])
    print(str([p + 1 for p in path]) + ',', weight, file=stderr)

print(cardinality)
for i in range(cardinality):
    for j in range(cardinality):
        print(matrix[i * cardinality + j], end=" ")
    print()

