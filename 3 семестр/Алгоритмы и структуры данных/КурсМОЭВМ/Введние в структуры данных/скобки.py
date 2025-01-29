class Stack:
    def __init__(self):
        self.stack = []
    def push(self, item):
        self.stack.append(item)
    def pop(self):
        if len(self.stack) == 0:
            return None
        removed = self.stack.pop()
        return removed

def staples(string):
    i = 0
    right = 'Success'
    index = Stack()
    for char in string:
        i+=1
        if char in '(){}[]':
            if char in '([{':
                index.push(i)
            else:
                top = index.pop()
                if top == None:
                    return i
                elif (string[top-1] == '(' and string[i-1] != ')') or (string[top-1] == '{' and string[i-1] != '}') or (string[top-1] == '[' and string[i-1] != ']'):
                    return i
    top = index.pop()
    if top == None:
        return right
    else:
        while top!=None:
            answer = top
            top = index.pop()
        return answer
                    
s = input()
print (staples(s))
