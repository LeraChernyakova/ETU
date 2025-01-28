import wikipedia
def is_page_valid(page):
    try:
        wikipedia.page(page)
    except Exception:
        return False
    return True

def set_language(str):
    return str in wikipedia.languages()

def search_max(L):
    m,title=-1,''
    for i in L:
        if len(wikipedia.page(i).summary.split())>=m:
            m=len(wikipedia.page(i).summary.split())
            title=wikipedia.page(i).title
    res=[str(m),title]
    return res

def sequence(L):
    res=[]
    res.append(L[0])
    for i in range(len(L)-1):
        if L[i+1] in wikipedia.page(L[i]).links:
            res.append(L[i+1])
        else:
            for j in wikipedia.page(L[i]).links:
                if L[i+1] in wikipedia.page(j).links:
                    res.append(j)
                    res.append(L[i+1])
                    break
    return res

s=input().split(', ')
if set_language(s[-1]):
    wikipedia.set_lang(s[-1])
    names = s[:len(s) - 1]
    print(' '.join(search_max(names)))
    print(sequence(names))

else:
    print('no results')
