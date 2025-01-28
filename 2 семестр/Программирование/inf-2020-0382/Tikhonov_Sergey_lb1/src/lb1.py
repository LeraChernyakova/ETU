import wikipedia


def is_page_valid(page):
    try:
        wikipedia.page(page)
    except Exception:
        return False
    return True


def set_lang(lg):
    if lg in wikipedia.languages():
        wikipedia.set_lang(lg)
        return True
    else:
        return False


def max_summary(pages):
    max_words = 0
    longest_page = ''
    for i in range(len(pages)):
        if len(wikipedia.page(pages[i]).summary.split()) >= max_words:
            max_words = len(wikipedia.page(pages[i]).summary.split())
            longest_page = wikipedia.page(inp[i]).title
    return max_words, longest_page


def make_chain(pages):
    ans = [pages[0]]
    for i in range(len(pages) - 1):
        links = wikipedia.page(pages[i]).links
        if pages[i + 1] in links:
            ans.append((pages[i + 1]))
        else:
            for j in range(len(links)):
                if is_page_valid(links[j]):
                    sub_links = wikipedia.page(links[j]).links
                    if pages[i + 1] in sub_links:
                        ans.append(links[j])
                        ans.append(pages[i + 1])
                        break
    return ans


inp = input().split(', ')
if not set_lang(inp[-1]):
    print("no results")
else:
    inp.pop(-1)
    print(max_summary(inp)[0], max_summary(inp)[1])
    print(make_chain(inp))
