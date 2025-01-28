#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>

typedef struct Node{
    char* path;
    struct Node* next;
    struct Node* prev;
} Node;

Node* createNode(char* path){
	char* dir = malloc(500 * sizeof(char));
	strcpy(dir, path);
	Node* head = malloc(sizeof(Node));
	head->path = dir;
	head->next = NULL;
	head->prev = NULL;
	return head;
}

void push(Node* head, char* path){
	char* dir = malloc(500 * sizeof(char));
	strcpy(dir, path);
	Node* cur = malloc(sizeof(Node));
	cur->path = dir;
	cur->next = NULL;
	cur->prev = NULL;
	Node* n = head;
	while (n->next)
		n = n->next;
	cur->prev = n;
	n->next = cur;	
}

void write(Node* head){
	Node* cur = head;
	while (cur->next)
		cur = cur->next;
	FILE* f = fopen("result.txt", "w");
	while (cur){
		fprintf(f, "%s\n", cur->path);
		cur = cur->prev;
	}
	fclose(f);

}

void freeList(Node* head){
	Node* cur = head;
	while (cur->next){
		cur = cur->next;
		free(cur->prev);
	}
	free(cur);
}

int search(char *dir_name, char *file_name, Node** out_list){
	DIR *cur_dir = opendir(dir_name);
	struct dirent *cur_file;
	while (cur_file = readdir(cur_dir)){
		int last_end = strlen(dir_name);
		strcat(dir_name, "/");
		strcat(dir_name, cur_file->d_name);
		if (cur_file->d_type == DT_REG && !strcmp(cur_file->d_name, file_name)){
			FILE *f = fopen(dir_name, "r");
			char content[1000];
			while (fgets(content, 1000, f)){
				if (strstr(content,"\n") && content)
					*strstr(content, "\n") = '\0';
				if (!strcmp(content, "Minotaur")){
					*out_list = createNode(dir_name);
					closedir(cur_dir);
					fclose(f);
					return 1;
				}
				if (!strcmp(content, "Deadlock")){
					closedir(cur_dir);
					fclose(f);
					return 0;
				}
				char other_path[500];
				strcpy(other_path, "./labyrinth");
				int out = search(other_path, strstr(content, " ") + 1, out_list);
				if (out){
					push(*out_list, dir_name);
					closedir(cur_dir);
					fclose(f);
					return out;
				}
			}
		}
		if (cur_file->d_type == DT_DIR && strcmp(cur_file->d_name, ".") && strcmp(cur_file->d_name, "..")){
			int out = search(dir_name, file_name, out_list);
			if (out){
				closedir(cur_dir);
				return out;
			}
		}
		dir_name[last_end] = '\0';
	}
	closedir(cur_dir);
	return 0;
}

int main(){	
	Node* out_list;
	char dir_name[500];
	strcpy(dir_name, "./labyrinth");
	search(dir_name, "file.txt", &out_list);
	write(out_list);
	freeList(out_list);
	return 0;
} 