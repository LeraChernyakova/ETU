#!/bin/sh

filename=$1 #запоминаем имя файла, переданное через параметр
ls -lRa /home/ubstudy | grep $filename | grep ^l > symlinks.txt #рекурсивно в каталоге ищем символьные
								#ссылки на файл, записываем в выходной файл

echo -n "total " >> symlinks.txt #дописываем в файл строчку total
wc -l symlinks.txt | cut -c 1 >> symlinks.txt #дописываем количество ссылок

com=`cat symlinks.txt` #запоминаем команду вывода содержимого выходного файла

echo $com #вызываем команду

