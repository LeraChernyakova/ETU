import wikipedia
def is_page_valid(page):
	try:
		wikipedia.page(page)
	except Exception:
		return False
	return True
    
    
def is_language_valid(lang):
	if lang in wikipedia.languages():
		wikipedia.set_lang(lang)
		return True
	else:
		return False
		
		
def max_outline(pages_names):
	size_of_page_max = 0
	page_max_name = ''
	size_of_page = 0
	for i in pages_names:
		i_page = wikipedia.page(i)
		size_of_page = len((i_page.summary).split())
		if size_of_page >= size_of_page_max:
			size_of_page_max = size_of_page
			page_max_name = i_page.title
	return [size_of_page_max, page_max_name]
		
		
def list_chain(pages_names):
	chain = [pages_names[0]]
	quantity = len(pages_names)-1
	for i in range(quantity):
		first_links = wikipedia.page(pages_names[i]).links
		if pages_names[i+1] in first_links:
			chain.append(pages_names[i+1])
		else:
			for j in first_links:
				if is_page_valid(j):
					second_links = (wikipedia.page(j)).links
					if pages_names[i+1] in second_links:
						chain.append(j)
						chain.append(pages_names[i+1])
						break
	return chain
			
			
beg_str = input().split(',')
beg_str = [i.strip() for i in beg_str]
language = beg_str[len(beg_str)-1]
beg_str.pop()
if is_language_valid(language):
	res = max_outline(beg_str)
	print (res[0], res[1], sep = ' ')
	print (list_chain(beg_str))
else:
	print ("no results")
