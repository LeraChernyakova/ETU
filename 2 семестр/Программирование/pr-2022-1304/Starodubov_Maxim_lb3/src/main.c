#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

#define BASE_SIZE 300

struct Buffer
{
	char *content;
	int size;
};

int extendBuffer(struct Buffer *buffer)
{
	buffer->size += BASE_SIZE;
	char *tmp = realloc(buffer->content, buffer->size);
	if (tmp)
	{
		buffer->content = tmp;
		return 0;
	}
	return 1;
}

int searchingFolders(struct Buffer *directory_name_buffer, char *file_name)
{
	char *current_directory_name = directory_name_buffer->content;
	DIR *current_directory = opendir(current_directory_name);
	if (!current_directory) return 0;
	
	struct dirent *current_file;

	while (current_file = readdir(current_directory))
	{
		if (current_file->d_type == DT_REG && !strcmp(current_file->d_name, file_name))
		{
			if (strlen(current_directory_name)+strlen(current_file->d_name)+2 > directory_name_buffer->size && extendBuffer(directory_name_buffer))
			{
				closedir(current_directory);
				return 0;
			}

			strcat(current_directory_name, "/");
			strcat(current_directory_name, current_file->d_name);
			
			closedir(current_directory);
			return 1;
		}

		if (current_file->d_type == DT_DIR && strcmp(current_file->d_name, ".") && strcmp(current_file->d_name, ".."))
		{
			if (strlen(current_directory_name)+strlen(current_file->d_name)+2 > directory_name_buffer->size && extendBuffer(directory_name_buffer))
			{
				closedir(current_directory);
				return 0;
			}

			int dir_name_length = strlen(current_directory_name);
			
			strcat(current_directory_name, "/");
			strcat(current_directory_name, current_file->d_name);

			int out = searchingFolders(directory_name_buffer, file_name);
			
			if (out)
			{
				closedir(current_directory);
				return 1;
			}

			current_directory_name[dir_name_length] = '\0';
		}
	}

	closedir(current_directory);
	return 0;
}

int main()
{
	struct Buffer required_path_name;
	required_path_name.content = malloc(BASE_SIZE);
	if (!required_path_name.content) return 0;
	required_path_name.size = BASE_SIZE;

	char file_name[strlen("_.txt")+1];
	strcpy(file_name, "_.txt");

	FILE *result_file = fopen("./result.txt", "w");

	scanf("%c", &file_name[0]);
	while (file_name[0] != '\n')
	{
		strcpy(required_path_name.content, "./tmp");
		if (searchingFolders(&required_path_name, file_name))
		{
			fprintf(result_file, "%s\n", required_path_name.content);
			scanf("%c", &file_name[0]);
		} else
		{
			free(required_path_name.content);			
			fclose(result_file);
			return 0;
		}
	}

	free(required_path_name.content);
	fclose(result_file);
	return 0;
}
