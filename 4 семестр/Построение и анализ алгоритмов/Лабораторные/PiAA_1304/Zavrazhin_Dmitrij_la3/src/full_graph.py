#!/usr/bin/python3
from sys import argv
from random import randint

# The script has four parameters:
# (1) The size of a matrix to be generated;
# (2) What to generate:
#  .  A hollow matrix
#  M  A regular matrix
#  U  An upper triangular matrix
#  L  A lower triangular matrix
# (3) The weight for non-diagonal elements. It can be:
#  -- A number - all weights are the same
#  -- A '\*" - all weights are random, some vertices being disconnected
#  -- A '." - all weights are random, no vertices being disconnected
# (4) If applicable, max possible weight

cardinality = int(argv[1])
mode = argv[2]
weight = argv[3]

condition = lambda i, j: i != j
if mode == 'M':
    condition = lambda i, j: True
elif mode == 'U':
    condition = lambda i, j: i <= j
elif mode == 'L':
    condition = lambda i, j: i >= j

generate_weight = lambda: weight
if weight == '.':
    generate_weight = lambda: randint(1, int(argv[4])) 
elif weight == '*':
    generate_weight = lambda: randint(0, int(argv[4])) 

print(cardinality)
for i in range(cardinality):
    for j in range(cardinality):
        print(generate_weight() if condition(i, j) else 0, end=" ")
    print()

