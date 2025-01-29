#!/bin/bash 
types='- c d l s b p' #типы файлов
for i in $types #ищем файл для каждого типа
do  
    echo $i #пишем текущий ключ
    file_search=`ls -lR $1 | grep ^$i | head -1` #найдем файл
        if [[ -n $file_search ]] #если нашли, т.е. переменная не пуста
        then
        cmd=`ls -lR $1 | grep ^$i | head -1 | cut -b 53-1000` #запоминаем нужную информацию про файл
                echo "$file_search -- `pwd`/$cmd" #выводим информацию про файл с указанием полного пути
        else    
                echo "notfound" #иначе говорим что не нашли файл
        fi
done

