import wikipedia

def is_page_valid(page):
    try:
        wikipedia.page(page)
    except Exception:
        return False
    return True

def lang(s):
  d=list((wikipedia.languages()).keys())
  for i in d:
    if s==i:
      return s
  return 'no results'

def max__quantity_of_words(List):
  quantity = 0
  name = ''
  for i in range(len(List)):
    if is_page_valid(List[i]) == True:
      page=wikipedia.page(List[i])
      if len((page.summary).split()) >= quantity:
        quantity = len((page.summary).split())
        name = page.title
  res = [quantity, name]
  return res

def list_res(list):
  res = []
  k = 0
  while is_page_valid(list[k]) == False:
    k += 1
  res.append(list[k])
  for k in range(len(list)-1):
    flag = 0
    if is_page_valid(list[k + 1]) == True:
      pages_links = (wikipedia.page(list[k])).links
      if list[k + 1] in pages_links:
        res.append(list[k + 1])
        flag = 1
      if flag == 0:
        for j in range(len(pages_links)):
          if flag == 0:
            pages2_links = (wikipedia.page(pages_links[j])).links
            for i in range(len(pages2_links)):
              if list[k + 1] == pages2_links[i]:
                res.append(pages_links[j])
                res.append(list[k + 1])
                flag = 1
    else:
      k += 1
  return res

L = input().split(', ')

res = lang(L[len(L)-1])
if res == 'no results':
  print(res)
else:
  wikipedia.set_lang(res)
  print(max__quantity_of_words(L[0:len(L) - 1:])[0], max__quantity_of_words(L[0:len(L) - 1:])[1])
  print(list_res(L[0:len(L) - 1:]))
