import wikipedia
def is_page_valid(page):
    try:
        wikipedia.page(page)
    except Exception:
        return False
    return True
    
def put_lang(lang):
    if lang in wikipedia.languages():
        wikipedia.set_lang(lang)
        return True
    else:
        return False    

def maxCW(nameTitle):#возвращает страницу с максимальным кол-вом слов в содержании
    maX = 0
    title_max = ''
    for i in nameTitle:
        if len(wikipedia.page(i).summary.split()) >= maX:
            maX = len(wikipedia.page(i).summary.split())
            title_max = wikipedia.page(i).title
    return maX,title_max


def get_chain(nameTitle):#возвращает цепочку элементов from first to last
    chain = [nameTitle[0]]
    sign = True
    for i in range(len(nameTitle)-1):
        sign = True
        if nameTitle[i+1] in wikipedia.page(nameTitle[i]).links:
            chain.append(nameTitle[i+1])
        else:
            for j in wikipedia.page(nameTitle[i]).links:
                if sign == True: 
                    #if is_page_valid(j) == True:
                    if nameTitle[i+1] in wikipedia.page(j).links:
                        chain.append(j)
                        chain.append(nameTitle[i+1])
                        sign = False 
    return chain

nameTitle_val = input().split(', ')
        
if put_lang(nameTitle_val[-1]):
    nameTitle_val.pop()
    print(maxCW(nameTitle_val)[0],maxCW(nameTitle_val)[1])
    print(get_chain(nameTitle_val))
else:
    print("no results")
