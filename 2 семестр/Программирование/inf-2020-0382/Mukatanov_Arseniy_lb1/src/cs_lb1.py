import wikipedia


def is_page_valid(page):
    try:
        wikipedia.page(page)
    except Exception:
        return False
    return True

def set_lang(language):
    if language in wikipedia.languages():
        wikipedia.set_lang(language)
        return True
    else:
        return False

def max_words(p):
    max = -1001
    ti = ''
    for i in range(len(p)):
        if len(wikipedia.page(p[i]).summary.split()) > max:
            max = len(wikipedia.page(p[i]).summary.split())
            ti = wikipedia.page(p[i]).title
    return max, ti

def chain_list(p):
    chain = [p[0]]
    for i in range(len(p) - 1):
        link = wikipedia.page(p[i]).links
        if p[i+1] in link:
            chain.append(p[i+1])
        else:
            for j in range(len(link)):
                if is_page_valid(link[j]):
                    link_2 = wikipedia.page(link[j]).links
                    if p[i + 1] in link_2:
                        chain.append(link[j])
                        chain.append(p[i+1])
                        break
    return chain

p = input().split(', ')
if not set_lang(p[-1]):
	print('no results')
else:
	print(*max_words(p[:-1]))
	print(chain_list(p[:-1]))

                    

    


