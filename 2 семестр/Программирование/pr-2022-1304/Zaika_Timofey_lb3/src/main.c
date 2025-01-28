#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void writeWayToFile(char* way, char* outfilename){
	FILE *f_out = fopen(outfilename, "a");
	fprintf(f_out, "%s\n", way);
	fclose(f_out);
}

void dirtravel(char* dirname, char* filename){
	DIR *dir = opendir(dirname); // dir != NULL
	if(!dir) return;
	struct dirent *cur;
	while(cur = readdir(dir)){
		if(cur->d_type == DT_DIR){
			if(strcmp(cur->d_name, ".") && strcmp(cur->d_name, "..")){
				int slen = strlen(dirname);
				strcat(dirname, "/");
				strcat(dirname, cur->d_name);
				dirtravel(dirname, filename);
				dirname[slen] = '\0';
			}
		}
		if(cur->d_type == DT_REG){
			if(strcmp(cur->d_name, filename) == 0){
				char* curfilename = dirname;
				strcat(curfilename, "/");
				strcat(curfilename, cur->d_name);
				writeWayToFile(curfilename, "result.txt");
				break;
			}
		}
	}
	closedir(dir);
}


int main(){
	FILE *f_out = fopen("result.txt", "w");
	fclose(f_out);

	char input_line[100];
	scanf("%s", input_line);

	char path[300] = "./tmp";

	char cur_file[6] = "_.txt";
	for(int i=0; i<strlen(input_line); i++){
		cur_file[0] = input_line[i];
		dirtravel(path, cur_file);
	}

	return 0;
}