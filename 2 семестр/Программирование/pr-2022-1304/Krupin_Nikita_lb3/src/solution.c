#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#define MAX_NAME 255 // max size of file name in Linux (bytes)

int find_letter(const char* dirPath, const char letter, FILE* file){
	DIR* dir; struct dirent* de; int len;
	char *newDirPath, wanted_name[] = " .txt";
	if (!(dir = opendir(dirPath))) return 1;
	// open directory or say "it's just a file"
	
	wanted_name[0] = letter;
	len = strlen(dirPath);
	newDirPath = (char*)malloc((len+2)*sizeof(char) + MAX_NAME);
	if (!newDirPath){
		closedir(dir);
		return 0; // error: memory can't be allocated
	}
	strcpy(newDirPath, dirPath);
	*(newDirPath + len++) = '/';
	*(newDirPath + len + MAX_NAME) = '\0';
	
	while (de = readdir(dir)){
		if (de->d_name[0] == '.') continue;
		strncpy(newDirPath+len, de->d_name, MAX_NAME);
		if (find_letter(newDirPath, letter, file))
			if (!strcmp(de->d_name, wanted_name)){
				fputs(newDirPath, file);
				fputs("\n", file);
				break;
			}
	}
	
	free(newDirPath);
	closedir(dir);
	return 0;
}

int main(){
	FILE* file = fopen("result.txt", "w");
	if (!file) return 0; // error: file can't be created
	char ch = fgetc(stdin);
	while (isalpha(ch)){
		find_letter("./tmp", ch, file);
		ch = fgetc(stdin);
	}
	fclose(file);
	return 0;
}
