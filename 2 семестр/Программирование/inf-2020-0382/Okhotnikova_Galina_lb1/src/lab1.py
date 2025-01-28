import wikipedia
def is_page_valid(page):
    try:
        wikipedia.page(page)
    except Exception:
        return False
    return True
    
def lang(s):
    if s[-1] in wikipedia.languages():
        wikipedia.set_lang(s[-1])
        return True
    else:
        return False

def max_number_of_words(s):
    max = 0
    for i in range(len(s)-1):
        if len(wikipedia.page(s[i]).summary.split()) >= max:
            max = len(wikipedia.page(s[i]).summary.split())
            t = wikipedia.page(s[i]).title
    return max, t

def chain(s):
    l = [s[0]]
    for i in range(len(s) - 2):
        if s[i+1] in wikipedia.page(s[i]).links:
            l.append(s[i+1])
        else:
            for j in wikipedia.page(s[i]).links:
                if s[i+1] in wikipedia.page(j).links:
                    l.append(j)
                    l.append(s[i + 1])
                    break
    return l


s = input().split(', ')
if lang(s):
    res = max_number_of_words(s)
    print(res[0], res[1])
    print(chain(s))
else:
    print('no results')
