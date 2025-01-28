import wikipedia


def is_page_valid(page):
    try:
        wikipedia.page(page)
    except Exception:
        return False
    return True


def is_lang_valid(lang):
    if lang in wikipedia.languages():
        wikipedia.set_lang(names[-1])
        return True
    else:
        return False


def highest_word_count(names):
    max_length = 0
    page_name = ""
    for i in range(len(names) - 1):
        if len(wikipedia.page(names[i]).summary.split()) >= max_length:
            max_length = len(wikipedia.page(names[i]).summary.split())
            page_name = wikipedia.page(names[i]).title
    return max_length, page_name


def chain_list(names):
    chain = [names[0]]
    for i in range(len(names) - 1):
        link = wikipedia.page(names[i]).links
        if names[i + 1] in link:
            chain.append((names[i + 1]))
        else:
            for k in range(len(link)):
                if is_page_valid(link[k]):
                    between_link = wikipedia.page(link[k]).links
                    if names[i + 1] in between_link:
                        chain.append(link[k])
                        chain.append(names[i + 1])
                        break
    return chain


names = input().split(", ")
if is_lang_valid(names[-1]):
    names.pop(-1)
    print(highest_word_count(names)[0], highest_word_count(names)[1])
    print(chain_list(names))
else:
    print("no results")