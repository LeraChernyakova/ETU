import wikipedia
def is_page_valid(page):
	try:
		wikipedia.page(page)
	except Exception:
		return False
	return True
    
    
def is_lang_valid(lang):
	if lang in wikipedia.languages():
		wikipedia.set_lang(lang)
		return True
	else:
		return False
		
		
def max_sum(pages):
    summ = 0
    title = ''
    for i in range(len(pages)):
        if len(wikipedia.page(pages[i]).summary.split()) >= summ:
            summ = len(wikipedia.page(pages[i]).summary.split())
            title = wikipedia.page(pages[i]).title
    return summ, title
		
		
def list_chain(ss):
    way = [ss[0]]
    for i in range(len(ss) - 1):
        links = wikipedia.page(ss[i]).links
        if ss[i + 1] in links:
            way.append((ss[i + 1]))
        else:
            for j in range(len(links)):
                if is_page_valid(links[j]):
                    sub_links = wikipedia.page(links[j]).links
                    if ss[i + 1] in sub_links:
                        way.append(links[j])
                        way.append(ss[i + 1])
                        break
    return way
			
			
s = list(input().split(','))
s = [i.strip() for i in s]
lang = s[len(s)-1]
s.pop()

if is_lang_valid(lang):
	x = max_sum(s)
	print (x[0], x[1], sep = ' ')
	print (list_chain(s))
else:
	print ("no results")