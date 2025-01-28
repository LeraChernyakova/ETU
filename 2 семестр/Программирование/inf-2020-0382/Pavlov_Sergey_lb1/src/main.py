import wikipedia

def is_page_valid(page):
	try:
		wikipedia.page(page)
	except Exception:
		return False
	return True

def max_words(pages):
    maximum = [0,"name"]
    for i in range(0,len(pages)):
        name = pages[i]
        page = wikipedia.page(name)
        count = len((page.summary).split())
        if maximum[0] <= count:
            maximum[0] = count
            maximum[1] = page.title
    return maximum

def links_chain(pages):
	ans = []
	ans.append(pages[0])
	for i in range(0,len(pages)-1):
		A = wikipedia.page(pages[i])
		B = pages[i+1]
		A_links = A.links
		#Если есть вторая сыллка из Pages уже входит в первую

		if (B in A_links):
			ans.append(pages[i+1])
		else:
			for link in A_links:
				if is_page_valid(link):
					tmp_page = wikipedia.page(link)
					tmp_links = tmp_page.links
					if (B in tmp_links):
						ans.append(A_links[A_links.index(link)])
						ans.append(pages[i+1])
						break
					else:
						continue
				else:
					continue
	return ans


n = input().split(', ')
pages = n.copy()
pages.pop()
lang = n[-1]

if (lang in wikipedia.languages()):
    wikipedia.set_lang(lang)
    print((max_words(pages))[0],(max_words(pages))[1])
    print(links_chain(pages))
else:
    print("no results")
