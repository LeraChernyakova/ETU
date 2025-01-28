import wikipedia

def is_page_valid(page):
    try:
        wikipedia.page(page)
    except Exception:
        return False
    return True
    
def max_words(p):
    max_w = len(wikipedia.page(p[0]).summary.split())
    page = wikipedia.page(p[0]).title
    for i in range(len(p) - 1):
        if len(wikipedia.page(p[i]).summary.split()) > max_w:
            max_w = len(wikipedia.page(p[i]).summary.split())
            page = wikipedia.page(p[i]).title
    return max_w, page

def language_exist(language):
    if language in wikipedia.languages():
        wikipedia.set_lang(language)
        return 1
    else:
        return 0

def chain(p):
    a = [p[0]]
    for i in range(len(p)-2):
        links_first = wikipedia.page(p[i]).links
        if p[i+1] in links_first:
            a.append(p[i+1])
        else:
            for o in range(len(links_first)):
                if is_page_valid(links_first[o]):
                    if p[i+1] in wikipedia.page(links_first[o]).links:
                        a.append(links_first[o])
                        a.append(p[i+1])
                        break
    return a


p = input().split(", ")
k = language_exist(p[-1])
if k == 1:
    max_w, page = max_words(p)
    print(max_w, page)
    print(chain(p))
else:
    print("no results")
