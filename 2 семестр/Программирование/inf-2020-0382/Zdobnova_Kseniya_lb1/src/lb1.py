import wikipedia

def is_page_valid(page):
    try:
        wikipedia.page(page)
    except Exception:
        return False
    return True

def max_words_page(input_list):
    max_words = 0
    position = 0
    for i in range (len(input_list) - 1):
        if is_page_valid(input_list[i]):
            if len(wikipedia.page(input_list[i]).summary.split()) > max_words:
                max_words = len(wikipedia.page(input_list[i]).summary.split())
                position = i
    return wikipedia.page(input_list[position]).title

def make_chain(input_list):
    input_list.pop(len(input_list) - 1)
    length = len(input_list) - 1
    processed = 0
    for pos in range (length):
        if input_list[processed + 1] not in wikipedia.page(input_list[processed]).links:
            for j in range(len(wikipedia.page(input_list[processed]).links)):
                temp = wikipedia.page(wikipedia.page(input_list[processed]).links[j])
                if input_list[processed + 1] in temp.links:
                    input_list.insert(processed + 1, wikipedia.page(input_list[processed]).links[j])
                    processed += 1
                    break
        processed += 1
    return input_list

input_list = input().split(', ')
if input_list[len(input_list) - 1] not in wikipedia.languages().keys():
    print('no results')
else:
    wikipedia.set_lang(input_list[len(input_list) - 1])
    max_page = max_words_page(input_list)
    print(len(wikipedia.page(max_page).summary.split()), max_page)
    input_list = make_chain(input_list)
    print(input_list)
