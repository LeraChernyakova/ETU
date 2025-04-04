#include <stdio.h>

int main(int argc, char* argv[]) {
	if (argc <= 1) { //Если не передано аргументов
		printf("%s: не передан входной параметр\n", argv[0]);
	} else {
		FILE* f; //Создаем указатель для работы с файлом
		f = fopen(argv[1], "r"); //Открываем файл для чтения
		if (f) { //Если открыт
			printf("%s: %s файл открыт\n", argv[0], argv[1]);
			char str[64]; //Создаем строку для содержимого файла
			while (fgets(str, sizeof(str), f)) { //Пока можем записывать 
							     //данные из файла в строку
				printf("%s", str); //Выводим строку с содержиммым файла
			}
			fclose(f); //Закрываем файл
		} else {
			printf("%s: %s файл не открыт\n", argv[0], argv[1]); //Иначе файл не открыт
		}
	}
	return 0;
}
