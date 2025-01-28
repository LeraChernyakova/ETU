import wikipedia


def is_page_valid(page):
    try:
        wikipedia.page(page)
    except Exception:
        return False
    return True


def makelist(pages):#3
    lst = [pages[0]]

    for i in range(len(pages) - 1):
        link = wikipedia.page(pages[i]).links

        if pages[i + 1] in link:
            lst.append((pages[i + 1]))

        else:
            for j in range(len(link)):

                if is_page_valid(link[j]):

                    slink = wikipedia.page(link[j]).links
                    if pages[i + 1] in slink:

                        lst.append(link[j])
                        lst.append(pages[i + 1])

                        break

    return lst


def maxsum(pages):#2
    words = -1
    mpage = ''
    for i in range(len(pages)):

        if len(wikipedia.page(pages[i]).summary.split()) >= words:

            words = len(wikipedia.page(pages[i]).summary.split())
            mpage = wikipedia.page(inf[i]).title

    return words, mpage


def setlang(lan):#1

    if lan in wikipedia.languages():
        wikipedia.set_lang(lan)
        return True

    else:
        return False


inf = input().split(', ')

if  setlang(inf[-1]):#1
    inf.pop(-1)
    print(maxsum(inf)[0], maxsum(inf)[1]) #2
    print(makelist(inf)) #3

else:

    print("no results")