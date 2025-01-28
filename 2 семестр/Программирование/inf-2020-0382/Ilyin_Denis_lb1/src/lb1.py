import wikipedia

def Max(a):
    kol = 0
    rez = 0
    for i in a:
        t = wikipedia.page(i)
        if kol <= len(t.summary.split()):
            kol = len(t.summary.split())
            rez = wikipedia.page(i).title
    return kol, rez


def is_page_valid(page):
    try:
        wikipedia.page(page)
    except Exception:
        return False
    return True


def mass(a, kon, nach):
        #print(1)
        if nach < len(a) - 1:
            t = wikipedia.page(a[nach]).links
            kon.append(a[nach])
            if a[nach + 1] in t:
                #print(kon)
                mass(a, kon, nach + 1)
            else:
                for i in t:
                    #print(i)
                    if is_page_valid(i):
                        l = wikipedia.page(i).links
                        if a[nach + 1] in l:
                            kon.append(i)
                            #print(kon)
                            mass(a, kon, nach + 1)
                            break

        else:
            kon.append(a[nach])
            return kon

a = input().split(', ')
b = a[len(a) - 1]
a.pop(len(a) - 1)
kon = []

if b in wikipedia.languages():
    wikipedia.set_lang(b)
    print(Max(a)[0], Max(a)[1])
    print(mass(a, kon, 0))

else:
    print("no results")

