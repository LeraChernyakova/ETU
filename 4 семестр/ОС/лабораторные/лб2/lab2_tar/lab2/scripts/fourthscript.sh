#!/bin/bash

> new.txt #создаем новый файл для изменений
echo "Создан новый регулярный файл:\n" > result.txt #создаем файл результатов
od -tc new.txt >> result.txt #записываем анализ содержимого файла для изменений в файл для результатов

# далее изменияем файл для изменения, результаты его анализа записываем в результирующий файл
echo "abc\nABCD\ntesttset" >> new.txt
echo "Файл был изменён (добавлен текст):\n" >> result.txt
od -tc new.txt >> result.txt

echo "abc\nABCD" > new.txt
echo "Файл был изменён (удалена часть текста):\n" >> result.txt
od -tc new.txt >> result.txt
