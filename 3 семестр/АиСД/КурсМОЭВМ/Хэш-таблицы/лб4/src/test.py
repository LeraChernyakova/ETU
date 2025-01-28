from main import algorithm_rabin_karp
import pytest


def test1():
    Pattern = 'aba'
    Text = 'abacaba'
    assert algorithm_rabin_karp(Pattern, Text) == [0, 4]


def test2():
    Pattern = 'cde'
    Text = 'aacdecdecdepppcde'
    assert algorithm_rabin_karp(Pattern, Text) == [2, 5, 8, 14]


def test3():
    Pattern = 'пти'
    Text = 'На ферме большой птичий двор. На дворе гуляют гуси и гусята, утки и утята, куры и цыплята. Птиц кормит птичница бабушка Настя. Ей помогают Таня и Катя. Они кормят гусят, утят и цыплят.'
    assert algorithm_rabin_karp(Pattern, Text) == [17, 103]


def test4():
    Pattern = 'cdb'
    Text = 'opoaserdjsnc'
    assert algorithm_rabin_karp(Pattern, Text) == []


def test5():
    Pattern = 'hello'
    Text = 'hi'
    assert algorithm_rabin_karp(Pattern, Text) == -1
