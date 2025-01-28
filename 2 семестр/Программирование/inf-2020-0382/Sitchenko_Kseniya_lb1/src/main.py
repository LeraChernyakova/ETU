import wikipedia

def is_page_valid(page):
  try:
    wikipedia.page(page)
  except Exception:
    return False
  return True
    
def set_lang(lang):
  if lang in wikipedia.languages():
    wikipedia.set_lang(lang)
    return True
  else:
    return False
   
def max_words_on_page(pages):
  max_page = ''
  max_words = 0
  for i in range(len(pages)):
    if is_page_valid(pages[i]) == True:
      page = wikipedia.page(pages[i])
      if len((page.summary).split()) >= max_words:
        max_words = len((page.summary).split())
        max_page = page.title
  return max_words, max_page
  
def min_chain(pages):
  arr = []
  arr.append(pages[0])
  for i in range(len(pages)-1):
    if pages[i+1] in wikipedia.page(pages[i]).links:
      arr.append(pages[i+1])
    else:
      for j in wikipedia.page(pages[i]).links:
        if pages[i+1] in wikipedia.page(j).links:
          arr.append(j)
          arr.append(pages[i+1])
          break
  return arr

st = input().split(', ')
if set_lang(st[-1]):
  inp_pages = st[:len(st) - 1]
  print(max_words_on_page(inp_pages)[0], max_words_on_page(inp_pages)[1])
  print(min_chain(inp_pages))
else:
  print("no results")
