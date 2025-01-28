import wikipedia

def setLang(lang):
    if wikipedia.languages().get(lang):
        wikipedia.set_lang(lang)
        return True
    else: return False

def maxSummary(arr):
    maxWords, maxWTitle = 0, ''
    for title in arr:
        page = wikipedia.page(title)
        count = len(page.summary.split())
        if count >= maxWords:
            maxWords, maxWTitle = count, page.title
    return str(maxWords), maxWTitle

def makeChain(arr):
    chain = [arr.pop(0)]
    for title in arr:
        page = wikipedia.page(chain[-1])
        if title in page.links: chain.append(title)
        else:
            for nextTitle in page.links:
                nextPage = tryPage(nextTitle)
                if not nextPage: continue
                if title in nextPage.links:
                    chain.extend([nextTitle, title])
                    break
    return chain

def tryPage(title):
    try:
        return wikipedia.page(title)
    except Exception:
        return None

arr = input().split(', ')
lang = arr.pop(-1)
if setLang(lang):
    print(' '.join(maxSummary(arr)))
    print(makeChain(arr))
else: print("no results")
