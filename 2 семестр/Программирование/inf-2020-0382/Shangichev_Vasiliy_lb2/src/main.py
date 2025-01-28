class T_machine():
	def __init__(self, string, program, init_state='q0'):
		self.memory = string
		self.table = program
		self.state = init_state
		self.index = 0
		
	def start(self):
		while self.state != 'qt':
			st = self.table[self.state][self.memory[self.index]]
			self.memory[self.index] = st['write']
			self.index += st['direct']
			self.state = st['state']
		answer = self.get_answer()
		return answer
		
	def get_answer(self):
		answer = ''
		for i in range(len(self.memory)):
			answer += self.memory[i]
		return answer

q_0 = {
	'0': {'write': '0', 'direct': 1, 'state': 'q0'},
	'1': {'write': '1', 'direct': 1, 'state': 'q0'},
	'2': {'write': '2', 'direct': 1, 'state': 'q0'},
	'+': {'write': '+', 'direct': 1, 'state': 'q1'},
	'-': {'write': '-', 'direct': 1, 'state': 'q4'},
	' ': {'write': ' ', 'direct': 1, 'state': 'q0'},
}

q_1 = {
	'0': {'write': '0', 'direct': 0, 'state': 'qt'},
	'1': {'write': '1', 'direct': -1, 'state': 'q2'},
	'2': {'write': '2', 'direct': -1, 'state': 'q3'},
	'+': {},
	'-': {},
	' ': {},
}

q_2 = {
	'0': {'write': '1', 'direct': 0, 'state': 'qt'},
	'1': {'write': '2', 'direct': 0, 'state': 'qt'},
	'2': {'write': '0', 'direct': -1, 'state': 'q2'},
	'+': {'write': '+', 'direct': -1, 'state': 'q2'},
	'-': {},
	' ': {'write': '1', 'direct': 0, 'state': 'qt'},
}

q_3 = {
	'0': {'write': '2', 'direct': 0, 'state': 'qt'},
	'1': {'write': '0', 'direct': -1, 'state': 'q2'},
	'2': {'write': '1', 'direct': -1, 'state': 'q2'},
	'+': {'write': '+', 'direct': -1, 'state': 'q3'},
	'-': {},
	' ': {},
}

q_4 = {
	'0': {'write': '0', 'direct': 0, 'state': 'qt'},
	'1': {'write': '1', 'direct': -1, 'state': 'q5'},
	'2': {'write': '2', 'direct': -1, 'state': 'q6'},
	'+': {},
	'-': {},
	' ': {},
}

q_5 = {
	'0': {'write': '2', 'direct': -1, 'state': 'q5'},
	'1': {'write': '0', 'direct': 0, 'state': 'q9'},
	'2': {'write': '1', 'direct': 0, 'state': 'qt'},
	'+': {},
	'-': {'write': '-', 'direct': -1, 'state': 'q5'},
	' ': {},
}

q_6 = {
	'0': {'write': '1', 'direct': -1, 'state': 'q5'},
	'1': {'write': '2', 'direct': -1, 'state': 'q5'},
	'2': {'write': '0', 'direct': 0, 'state': 'q9'},
	'+': {},
	'-': {'write': '-', 'direct': -1, 'state': 'q6'},
	' ': {},
}

# стирает нули
q_7 = {
	'0': {'write': ' ', 'direct': 1, 'state': 'q7'},
	'1': {'write': '1', 'direct': 0, 'state': 'qt'},
	'2': {'write': '2', 'direct': 0, 'state': 'qt'},
	'+': {'write': '+', 'direct': -1, 'state': 'q8'},
	'-': {'write': '-', 'direct': -1, 'state': 'q8'},
	' ': {},
}

# ставит нуль в начале
q_8 = {
	'0': {'write': '0', 'direct': 0, 'state': 'qt'},
	'1': {'write': '1', 'direct': 0, 'state': 'qt'},
	'2': {'write': '2', 'direct': 0, 'state': 'qt'},
	'+': {'write': '+', 'direct': 0, 'state': 'qt'},
	'-': {'write': '-', 'direct': 0, 'state': 'qt'},
	' ': {'write': '0', 'direct': 0, 'state': 'qt'},
}

# переводит указатель в начало
q_9 = {
	'0': {'write': '0', 'direct': -1, 'state': 'q9'},
	'1': {'write': '1', 'direct': -1, 'state': 'q9'},
	'2': {'write': '2', 'direct': -1, 'state': 'q9'},
	'+': {},
	'-': {},
	' ': {'write': ' ', 'direct': 1, 'state': 'q7'},	
}

program = {
	'q0': q_0,
	'q1': q_1,
	'q2': q_2,
	'q3': q_3,
	'q4': q_4,
	'q5': q_5,
	'q6': q_6,
	'q7': q_7,
	'q8': q_8,
	'q9': q_9,
}

request = list(input())
machine = T_machine(request.copy(), program)
answer = machine.start()
print(answer)