#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>

typedef struct Node{
    char* way;
    struct Node* next;
    struct Node* prev;

}Node;
void printN(Node* head){
	Node* cur=head;
	while(cur){
		printf("%s\n",cur->way);
		cur=cur->next;
		}
}
Node* CreateNode(char* way){
	char* dir= malloc(500*sizeof(char));
	strcpy(dir,way);
	Node* head=malloc(sizeof(Node));
	head->way=dir;
	head->next=NULL;
	head->prev=NULL;
	return head;
}
void PushNode(Node* head,char* way){
	char* dir= malloc(500*sizeof(char));
	strcpy(dir,way);
	Node* cur = malloc(sizeof(Node));
	cur->way=dir;
	cur->next=NULL;
	cur->prev=NULL;
	Node* n=head;
	while(n->next){
		n= n->next;
	}
	cur->prev=n;
	n->next=cur;	
}
void InFile(Node* head){
	Node* cur=head;
	while(cur->next){
		cur=cur->next;
	}
	
	FILE* f=fopen("result.txt","w");
	Node* reserv;
	while(cur){
		//printN(head);
		fprintf(f,"%s\n",cur->way);
		cur=cur->prev;
		}
	fclose(f);

}
void FreeList(Node* head){
	Node* cur=head;
	while(cur->next){
	cur=cur->next;
	free(cur->prev);
	}
	free(cur);
}

int recSearch(char *dir_name, char *file_name,Node** out_list)
{
	DIR *cur_dir = opendir(dir_name);

	struct dirent *cur_file;
	
	while (cur_file = readdir(cur_dir))
	{

		int last_end = strlen(dir_name);
		strcat(dir_name, "/");
		strcat(dir_name, cur_file->d_name);

		if (cur_file->d_type == DT_REG && !strcmp(cur_file->d_name, file_name))
		{
			FILE *f = fopen(dir_name, "r");
			char content[1000];
			while (fgets(content, 1000, f))
			{
				if(strstr(content,"\n")&&content)
					*strstr(content, "\n") = '\0';
				if (!strcmp(content, "Minotaur"))
				{
					//printf("%s\n", dir_name);
					*out_list=CreateNode(dir_name);
					//puts(out_list->way);
					closedir(cur_dir);
					fclose(f);
					return 1;
				}
				if (!strcmp(content, "Deadlock"))
				{
					closedir(cur_dir);
					fclose(f);
					return 0;
				}
				char other_path[500];
				strcpy(other_path, "./labyrinth");
				int out = recSearch(other_path, strstr(content, " ")+1,out_list);
				if (out)
				{
					//printf("%s\n", dir_name);
					PushNode(*out_list,dir_name);
					closedir(cur_dir);
					fclose(f);
					return out;
				}
			}
		}
		if (cur_file->d_type == DT_DIR && strcmp(cur_file->d_name, ".") && strcmp(cur_file->d_name, ".."))
		{
			int out = recSearch(dir_name, file_name,out_list);
			if (out) 
			{
				closedir(cur_dir);
				return out;
			}
		}
		dir_name[last_end] = '\0';
	}
	closedir(cur_dir);
	return 0;
}

int main()
{	Node* out_list;
	char dir_name[500];
	strcpy(dir_name, "./labyrinth");
	//printf("%d\n", recSearch(dir_name, "file.txt",out_list));
	recSearch(dir_name, "file.txt",&out_list);
	InFile(out_list);
	//printN(out_list);
	FreeList(out_list);
	return 0;
}
