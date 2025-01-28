import wikipedia


def is_page_valid(page_name):
    try:
        wikipedia.page(page_name)
    except Exception:
        return False
    return True

def is_language_available(language):
    dict_of_languages = wikipedia.languages()
    if dict_of_languages.get(language, "not found")=="not found":
        return False
    else:
        wikipedia.set_lang(language)
        return True

def get_max_words_in_summary(pages_name):
    max_words_found = -1
    page_name_with_max_words = ""
    for page_name in pages_name:
        page = wikipedia.page(page_name)
        if max_words_found <= len(page.summary.split()): #len(page.summary.split()) - количество слов в кратком содержании страницы
            max_words_found = len(page.summary.split())
            page_name_with_max_words = page.title
    return max_words_found, page_name_with_max_words

def get_page_chain(pages_name):
    number_of_pages = len(pages_name)
    if number_of_pages == 0: return []
    chain = [pages_name[0]] 
    for page_number in range (number_of_pages-1): 
        page_found = False 
        links_current_page = wikipedia.page(pages_name[page_number]).links
        page_target_name = pages_name[page_number+1]
        for link_of_current_page in links_current_page: #Кратчайший путь
            if link_of_current_page == page_target_name:
                chain.append(page_target_name)
                page_found = True
                break
        if page_found: continue #Если короткий путь уже найден, то путь через одну страницу не ищется        
        for link_of_current_page in links_current_page: #Путь через одну страницу
            if not is_page_valid(link_of_current_page): continue          #Если страницы с такой ссылкой нет, то проверяем следуюущую ссылку           
            links_inter_page = wikipedia.page(link_of_current_page).links
            for link_from_inter_page in links_inter_page:
                if link_from_inter_page == page_target_name:
                    chain.append(link_of_current_page)
                    chain.append(page_target_name)
                    page_found = True
                    break
            if page_found: break                    
    return chain

if __name__ == "__main__":
    inlet = input().split(", ") 
    if not is_language_available(inlet[-1]):
        print("no results")
    else:
        print(*get_max_words_in_summary(inlet[:-1]))
        print(get_page_chain(inlet[:-1]))