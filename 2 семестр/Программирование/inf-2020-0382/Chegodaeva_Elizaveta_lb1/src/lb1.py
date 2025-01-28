import wikipedia
def is_page_valid(page):
    try:
        wikipedia.page(page)
    except Exception:
        return False
    return True
def one(a):
    if a[-1] not in wikipedia.languages().keys():
        return False
    else:
        return True
def maxlen(a):
    max=0
    maxt=''    
    for i in range(len(a)):
        p=(wikipedia.page(a[i]).summary.split())
        if len(p)>=max:
            max=len(p)
            maxt=wikipedia.page(a[i]).title
    return max, maxt
def ress(a):
    res=[]
    res.append(a[0])
    for i in range(len(a)-1):
        lin=wikipedia.page(a[i]).links
        if a[i+1] in lin:
            res.append(a[i+1])
        else:
            for j in range(len(lin)):
                if  is_page_valid(lin[j]):
                    linn=wikipedia.page(lin[j]).links
                    if a[i+1] in linn:
                        res.append(lin[j])
                        res.append(a[i+1])
                        break   
    return res
a=input().split(', ')
if one(a):
    wikipedia.set_lang(a[-1])
    a.pop(-1)
    print(maxlen(a)[0],maxlen(a)[1] )
    print(ress(a))
else:     
    print("no results")  
            

