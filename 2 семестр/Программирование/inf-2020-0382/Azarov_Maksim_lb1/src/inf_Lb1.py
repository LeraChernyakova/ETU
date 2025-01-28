import wikipedia


def is_page_valid(page):
    try:
        wikipedia.page(page)
    except Exception:
        return False
    return True


def find_lang(lang):
    if lang in wikipedia.languages():
        return True
    else:
        return False


def max_word(names):
    maxw = 0
    for i in names:
        page = wikipedia.page(i)
        if maxw <= len(page.summary.split()):
            maxw = len(page.summary.split())
            tit = page.title
    return maxw, tit


def page_chain(names):
    cer_ch = [names[0]]
    for i in range(len(names)-1):
        page = wikipedia.page(names[i])
        if names[i+1] in page.links :
             cer_ch.append(names[i+1])
        else :
            for l in page.links:
                if is_page_valid(l) :
                    subpage = wikipedia.page(l)
                    if names[i+1] in subpage.links :
                        cer_ch.append(l)
                        cer_ch.append(names[i+1])
                        break
    return cer_ch

#Начало осн функции

*names, lang = input().split(', ')

if find_lang(lang):
    wikipedia.set_lang(lang)
    maxw, tit = max_word(names)
    print(maxw, tit)
    cur_ch = page_chain(names)
    print(cur_ch)

else:
    print("no results")
