s = input()
for i in range(int(input())):
    a, b, c = (int(j) for j in input().split())
    de, os = s[a: b + 1], s[: a] + s[b + 1:]
    if c == 0:
        s = de + os
    else:
        s = os[: c] + de + os[c:]
print(s)