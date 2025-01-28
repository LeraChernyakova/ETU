import wikipedia
def is_page_valid(page):
    try:
        wikipedia.page(page)
    except Exception:
        return False
    return True

def set_language(lang):
    if lang in wikipedia.languages():
        wikipedia.set_lang(a[len(a)-1])
        return True
    else:
        return False

def max_word_title(list):
    max=0
    title_max=''
    for i in range (len(list)-1):
        if len(wikipedia.page(a[i]).summary.split())>max:
            max = len(wikipedia.page(a[i]).summary.split())
            title_max=wikipedia.page(a[i]).title
    return title_max,max

def shortest_chain(list):
    k = []
    key = 0
    k.append(list[0])
    for i in range(len(list) - 1):
        l1 = wikipedia.page(list[i])
        key = 0
        if i != len(list) - 1:
            if (list[i + 1] in l1.links):
                k.append(list[i + 1])
            else:
                for j in l1.links:
                    if (key == 1):
                        break
                    else:
                        if is_page_valid(j) == True:
                            l2 = wikipedia.page(j)
                            if list[i + 1] in l2.links:
                                k.append(j)
                                k.append(list[i + 1])
                                key = 1
                                continue
                        else:
                            break
    return k

a=input().split(', ')
if (set_language(a[-1])):
    print (max_word_title(a)[1],max_word_title(a)[0])
    print(shortest_chain(a))
else:
    print('no results')