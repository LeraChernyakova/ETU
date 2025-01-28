import wikipedia 

def is_page_valid(page):
    try:
        wikipedia.page(page)
    except Exception:
        return False
    return True
    
def find_max(pages):
    max_words = -1
    page_name = ''
    for i in range(len(pages)):
        page = wikipedia.page(pages[i])
        if len(page.summary.split()) >= max_words:
            page_name = page.title
            max_words = len(page.summary.split())
    return max_words, page_name
    
def get_chain(pages):
    chain = list()
    for i in range(0, len(pages)-1):
        page_from, page_to = wikipedia.page(pages[i]),                  wikipedia.page(pages[i+1])
        chain.append(pages[i])
        if pages[i+1] not in page_from.links:
            for k in range(len(page_from.links)):
                current_page = wikipedia.page(page_from.links[k])
                if pages[i+1] in current_page.links:
                    chain.append(page_from.links[k])
                    break
    chain.append(pages[-1])
    return chain
        
# ---начало---
request = [x.strip() for x in input().split(',')]
language = request.pop(-1)

# подзадача 1
if language in wikipedia.languages().keys():
    wikipedia.set_lang(language)
    
    # подзадача 2
    max_words, page_title = find_max(request)
    print(str(max_words), page_title)


    # подзадача 3
    chain = get_chain(request)
    print(chain)

else:
    print('no results')

