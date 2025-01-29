#!/bin/sh

if [ $# -lt 1 ] #если входных параметров не задано
then
	echo $0: error: File not specified #то говорим что файл не задан
else
	filename=$1 #запоминаем имя файла
	inode=`ls -i $filename | cut -d ' ' -f 1 | tr -d " "` #получаем жесткую ссылку на файл
	tmp=`ls -lRi /home/ubstudy | grep $inode` #рекурсивно просматриваем каталог, ищем жесткую ссылку
fi

echo $tmp #выводим жесткую ссылку на файл
