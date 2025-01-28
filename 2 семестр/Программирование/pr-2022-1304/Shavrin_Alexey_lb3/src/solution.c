#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>


#define ROOT_DIRECTORY "."
#define OUTPUT_FILE_NAME "result.txt"
#define SEARCHING_FILE_TYPE ".txt"
#define PATH_SIZE 1024
#define MAX_COUNT_FILES 16384
#define CONTENT_LINE_LENGTH 256


typedef struct FileContent{
	long int number;
	char *string;
} FileContent;


int CompareFileContent(const void *a, const void *b){
	//type casting
	FileContent *f = (FileContent *)a;
	FileContent *s = (FileContent *)b;

	//compare
	if (f -> number > s -> number)
		return 1;
	if (f -> number < s -> number)
		return -1;
	else
		return 0;
}


FileContent CreateFileContent(char *content){
	//create element
	FileContent elem;
	elem.number = 0;
	elem.string = NULL;
	
	//get space position
	char *posSpace = strstr(content, " ");

	//check if the string is correct
	if (!posSpace)
		return elem;
	
	//initialize element
	elem.number = atoi(content);
	elem.string = (char*)malloc(strlen(posSpace)*sizeof(char));
	strcpy(elem.string, posSpace + 1);

	return elem;
}


int ReadFile(FileContent *FilesArray, char *file_path, int count_elem){
	FILE *file = fopen(file_path, "r");
	
	if (file != NULL){

		//read information from a file	
		char *content = malloc(CONTENT_LINE_LENGTH*sizeof(char));
		fgets(content, CONTENT_LINE_LENGTH, file);
	
		//create file content and add him into FilesArray
		FilesArray[count_elem] = CreateFileContent(content);
	
		//cleaning
		free(content);

		fclose(file);
		return 1;
	}
	return 0;
}


int DirectoryRecursion(char *DirectoryPath, FileContent *FilesArray){

	//error checking
	if (DirectoryPath == NULL || FilesArray == NULL)
		return 0;
	
	DIR *current_directory = opendir(DirectoryPath);
	//error checking
	if (current_directory == NULL)
		return 0;
	
	//count elem in the files array
	int count_elem = 0;

	//get first directory element
	struct dirent *dp = readdir(current_directory);
	
	//itarate over all elem of a directory
	while (dp){
		
		//checking for start directory or exit
		if (dp -> d_type == DT_DIR && (strcmp(dp -> d_name, ".") == 0 || strcmp(dp -> d_name, "..") == 0)){
			dp = readdir(current_directory);
			continue;
		}

		//checking for output file
		if (dp -> d_type == DT_REG && (!strcmp(dp -> d_name, OUTPUT_FILE_NAME) || strstr(dp->d_name, SEARCHING_FILE_TYPE) == NULL)){
			dp = readdir(current_directory);
			continue;
		}
		
		//create path to the file or directory
		char path[PATH_SIZE];
		strcpy(path, DirectoryPath);
		strcat(path, "/");
		strcat(path, dp -> d_name);

		//file type checking
		if (dp -> d_type == DT_REG && strstr(dp->d_name, SEARCHING_FILE_TYPE) != NULL){
			count_elem += ReadFile(FilesArray, path, count_elem);
		}else{
			if (dp -> d_type == DT_DIR){
				count_elem += DirectoryRecursion(path, FilesArray + count_elem);
			}
		}

		//get new directory element
		dp = readdir(current_directory);
	}

	closedir(current_directory);
	return count_elem;
}


void FreeFileContent(FileContent *elem){
	if (elem != NULL){
		free(elem -> string);
		elem -> string = NULL;
		elem -> number = 0;
	}
}


void PrintFilesArrayToFile(FileContent *FilesArray, int count_elem, char* output_file_name){
	FILE* output_file = fopen(output_file_name, "w");
	//error checking
	if (output_file == NULL){
		printf("I can't open outpute file\n");
		return;
	}
	
	//error checkin
	if (FilesArray == NULL)
		return;
		
	for (int i = 0; i < count_elem; i++){
		if (FilesArray[i].string == NULL){continue;}
		fprintf(output_file, "%ld %s\n", FilesArray[i].number, FilesArray[i].string);
		FreeFileContent(FilesArray + i);
	}
	fclose(output_file);
}


int main(){
	//create files array
	FileContent *FilesArray = malloc(MAX_COUNT_FILES*sizeof(FileContent));

	//get info and count files in array
	int count_elem = DirectoryRecursion(ROOT_DIRECTORY, FilesArray);
	
	//sort array
	qsort(FilesArray, count_elem, sizeof(FileContent), CompareFileContent);
	
	//print result
	PrintFilesArrayToFile(FilesArray, count_elem, OUTPUT_FILE_NAME);
	
	//free array
	free(FilesArray);
	FilesArray = NULL;

	return 0;
}
