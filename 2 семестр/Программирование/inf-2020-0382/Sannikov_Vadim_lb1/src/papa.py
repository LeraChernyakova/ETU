import wikipedia
def is_page_valid(page):
    try:
        wikipedia.page(page)
    except Exception:
        return False
    return True

def lang_here(lg):
    if lg in wikipedia.languages():
        wikipedia.set_lang(lg)
        return True
    else:
        return False

def max_st(st):
    max_str = '' 
    size = 0
    numb_max = 0
    for i in st:
        i_page = wikipedia.page(i)
        size = len((i_page.summary).split())
        if size >= numb_max:
            numb_max = size
            max_str = i_page.title
    return [numb_max, max_str]
    
def st_cep(st):
    ans = [st[0]]
    count = len(st)-1
    for i in range(count):
        thefirst = wikipedia.page(st[i]).links
        if st[i+1] in thefirst:
            ans.append(st[i+1])
        else:
            for j in thefirst:
                if is_page_valid(j):
                    thesecond=(wikipedia.page(j)).links
                    if st[i+1] in thesecond:
                        ans.append(j)
                        ans.append(st[i+1])
                        break
    return ans
    
a = input().split(', ')
if lang_here(a[len(a)-1]):
    result = max_st(a)
    print(result[0], result[1])
    print(st_cep(a))
else:
    print('no results') 
 
