import wikipedia
def is_page_valid(page):
    try:
        wikipedia.page(page)
    except Exception:
        return False
    return True

def setlang(mainstring):
    if mainstring[len(mainstring) - 1] in wikipedia.languages():
        wikipedia.set_lang(mainstring[-1])
        return True
    else:
        return False


def maximum(pagess):
    ttle = ''
    max = 0
    length = 0
    for i in pagess:
        length = 0
        strng = wikipedia.page(i)
        length = len(strng.summary.split())
        if length >= max:
            max = length
            ttle = strng.title
    return max, ttle

def chain(string1, string2):
    spage1 = wikipedia.page(string1)
    spage2 = wikipedia.page(string2)
    rez = []
    links1 = []
    links1 = spage1.links
    if string2 in links1:
        rez.append(string2)
    else:
        for i in links1:
            if is_page_valid(i):
                spage3 = wikipedia.page(i)
                links3 = spage3.links
                if string2 in links3:
                    rez.append(i)
                    rez.append(string2)
                    break
    return(rez)
    
mainstring = input().split(', ')
pages = mainstring[0:len(mainstring)-1]
if setlang(mainstring)==False:
	 print('no results')
else:
    print(maximum(pages)[0], maximum(pages)[1])

    result = []
    result.append(pages[0])

    for cycle in range(len(pages)-1):
        new = chain(pages[cycle], pages[cycle+1])
        if new == []:
            break
        else:
            for k in new:
                result.append(k)
    print(result)
