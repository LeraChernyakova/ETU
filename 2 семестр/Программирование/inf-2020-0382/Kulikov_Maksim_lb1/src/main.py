import wikipedia


def is_page_valid(page):
    try:
        wikipedia.page(page)
    except Exception:
        return False
    return True


def set_lang(language):
    if language[-1] in wikipedia.languages():
        wikipedia.set_lang(language[-1])
        language.pop()
        return 0
    else:
        return 1



def max_words(inp):
    max_amount = 0
    page = ''
    for i in range(len(inp)):
        if len(wikipedia.page(inp[i]).summary.split()) > max_amount:
            max_amount = len(wikipedia.page(inp[i]).summary.split())
            page = wikipedia.page(inp[i]).title
    return max_amount, page


def chain_list(inp):
    chain = [inp[0]]
    for i in range(len(inp) - 1):
        links = wikipedia.page(inp[i]).links
        if inp[i + 1] in links:
            chain.append((inp[i + 1]))
        else:
            for j in range(len(links)):
                if is_page_valid(links[j]):
                    trans_links = wikipedia.page(links[j]).links
                    if inp[i + 1] in trans_links:
                        chain.append(links[j])
                        chain.append(inp[i + 1])
                        break
    return chain


inp = input().split(', ')
if set_lang(inp) == 0:
    arr = max_words(inp)
    print(arr[0], arr[1])
    print(chain_list(inp))
else:
    print('no results')

