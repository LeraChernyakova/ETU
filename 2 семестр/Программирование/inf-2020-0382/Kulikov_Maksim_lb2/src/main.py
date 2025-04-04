memory = list(input())
index = 0
state = 'q1'
table = {'q1': {'1': ['1', 1, 'q2'],
                '2': ['2', 1, 'q2'],
                ' ': [' ', 1, 'q1']},

         'q2': {'0': ['0', 1, 'q2'],
                '1': ['1', 1, 'q2'],
                '2': ['2', 1, 'q2'],
                ' ': [' ', -1, 'q3'],
                '+': ['+', 1, 'q2'],
                '-': ['-', 1, 'q2']},

         'q3': {'0': ['0', 0, 'qT'],
                '1': ['1', -1, 'q4'],
                '2': ['2', -1, 'q5'], },

         'q4': {'+': ['+', -1, 'q6'],
                '-': ['-', -1, 'q7']},

         'q5': {'+': ['+', -1, 'q8'],
                '-': ['-', -1, 'q9']},

         'q6': {'0': ['1', 0, 'qT'],
                '1': ['2', 0, 'qT'],
                '2': ['0', -1, 'q10']},

         'q7': {'0': ['2', -1, 'q11'],
                '1': ['0', 0, 'qT'],
                '2': ['1', 0, 'qT']},

         'q8': {'0': ['2', 0, 'qT'],
                '1': ['0', -1, 'q10'],
                '2': ['1', -1, 'q10']},

         'q9': {'0': ['1', -1, 'q11'],
                '1': ['2', -1, 'q11'],
                '2': ['0', 0, 'qT']},

         'q10': {'0': ['1', 0, 'qT'],
                 '1': ['2', 0, 'qT'],
                 '2': ['0', -1, 'q10'],
                 ' ': ['1', 0, 'qT']},

         'q11': {'0': ['2', -1, 'q11'],
                 '1': ['0', -1, 'q12'],
                 '2': ['1', 0, 'q12']},

         'q12': {'0': [' ', 1, 'q12'],
                 '1': ['1', 0, 'qT'],
                 '2': ['2', 0, 'qT'],
                 '+': ['+', -1, 'q13'],
                 '-': ['-', -1, 'q13'],
                 ' ': [' ', 1, 'q12']},
         'q13': {' ': ['0', 0, 'qT']}

         }
while state != 'qT':
    sym, delta, state = table[state][memory[index]]
    memory[index] = sym
    index += delta
print(''.join(memory))
