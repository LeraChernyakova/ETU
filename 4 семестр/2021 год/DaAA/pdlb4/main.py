def KnuthMorrisPratt(text, pattern):
    pattern = list(pattern)

    shifts = [1] * (len(pattern) + 1)
    shift = 1
    for pos in range(len(pattern)):
        while shift <= pos and pattern[pos] != pattern[pos - shift]:
            shift += shifts[pos - shift]
        shifts[pos + 1] = shift

    startPos = 0
    matchLen = 0
    for c in text:
        while matchLen == len(pattern) or \
                matchLen >= 0 and pattern[matchLen] != c:
            startPos += shifts[matchLen]
            matchLen -= shifts[matchLen]
        matchLen += 1
        if matchLen == len(pattern):
            yield str(startPos)


a = input()
b = input()
if ",".join(KnuthMorrisPratt(b, a)) == "":
    print(-1)
else:
    print(",".join(KnuthMorrisPratt(b, a)))
