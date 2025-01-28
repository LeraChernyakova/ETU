#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>

void file_path(char *path, int i, char *str, FILE *file){
	char *next = malloc(200*sizeof(char));
	strcpy(next, path);
	strcat(next, "/");
	DIR *dir = opendir(path);
	if (!dir){
		return;
	}
	struct dirent* de = readdir(dir);
	while(de){
		if (de->d_type == DT_REG){
			if (str[i] == de->d_name[0] && de->d_name[1] == '.'){
				fprintf(file, "%s/%s\n", path, de->d_name);
			}
		}
		if (de->d_type == DT_DIR && strcmp(de->d_name, ".")!=0 && strcmp(de->d_name, "..")!=0){
			int len = strlen(next);
			strcat(next, de->d_name);
			file_path(next, i, str, file);
			next[len] = '\0';
		}
		de = readdir(dir);
	}
	closedir(dir);

}


int main(){
	char* name = "./tmp";
	char str[200];
	fgets(str, 200, stdin);
	FILE *result = fopen("result.txt", "w");
	int i;
	for (i=0; i<strlen(str); i++){
		file_path(name, i, str, result);
	}
	fclose(result);
	return 0;
}
