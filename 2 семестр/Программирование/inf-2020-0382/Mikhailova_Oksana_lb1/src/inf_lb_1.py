def is_page_valid(page):
    try:
        wikipedia.page(page)
    except Exception:
        return False
    return True

import wikipedia

def language(s):
    if s[-1] in wikipedia.languages():
        wikipedia.set_lang(s[-1])
        return True
    else:
        return False

def max_words(s):
    maximum = 0
    for i in range(len(s)-1):
        if len(wikipedia.page(s[i]).summary.split()) >= maximum:
            maximum = len(wikipedia.page(s[i]).summary.split())
            t = wikipedia.page(s[i]).title
    return maximum, t

def chain(s):
    L = [s[0]]
    for i in range(len(s) - 2):
        if s[i+1] in wikipedia.page(s[i]).links:
            L.append(s[i+1])
        else:
            for j in wikipedia.page(s[i]).links:
                if s[i+1] in wikipedia.page(j).links:
                    L.append(j)
                    L.append(s[i + 1])
                    break
    return L


s = input().split(', ')
if language(s):
    res = max_words(s)
    print(res[0], res[1])
    print(chain(s))
else:
    print('no results')
