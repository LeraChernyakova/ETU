#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

#define answer "Minotaur"
#define end "Deadlock"

typedef struct File{
    char* filename;
    char* path;
}File;

typedef struct Maze{

    char** links;
    int count;
    int maxcount;
    
}Maze;

void setPath(const char* pathDir, File* path_file){
    char nextDir[300]={0};                    
    strcpy(nextDir,pathDir);
    strcat(nextDir,"/");
    DIR* dir=opendir(pathDir);                
    if(!dir)                                  
        return;
    
    struct dirent* current;
    current = readdir(dir);
    while(current){

        if((current->d_type == 4)&&(strcmp(current->d_name, ".") != 0)&&(strcmp(current->d_name, "..") != 0)){
                int len;
                len = strlen(nextDir);                                    
                strcat(nextDir,current->d_name);
                setPath(nextDir, path_file);
                nextDir[len] = '\0';
        }
        
        if((current->d_type ==  8) && (strcmp(current->d_name, path_file->filename) == 0)){
            strcat(nextDir,current->d_name);
            path_file->path = malloc(300 * sizeof(char));
            strcpy(path_file->path,nextDir);
            closedir(dir);
            return;
        }
        
        current = readdir(dir);    	
    }
    
}  

void push_answer(Maze* arr, char* path){
    if(arr->count == arr-> maxcount){
        arr->maxcount += 10;
        arr->links = realloc(arr, arr->maxcount * sizeof(char*));
    }

    arr->links[arr->count] = malloc((strlen(path)+2)*sizeof(char*));
    strcpy(arr->links[arr->count++], path);
}


int findMinotaur(const char* startDir, char* filename, Maze* arr){
    File new_file;
    new_file.filename = malloc(50 * sizeof(char));
    strcpy(new_file.filename, filename);

    setPath(startDir, &new_file);

    FILE* f = fopen(new_file.path,"r");
    if(!f)
        return 0;
    
    char s[100];
    fscanf(f,"%s",s);

    if(strcmp(s, answer) == 0){
        push_answer(arr, new_file.path);
        fclose(f);
        return 1;
    }
    else{
        if(strcmp(s, end) == 0){
            fclose(f);
            return 0;
        }
        else{
           
            char t[20];
            char file[100];
            
            fscanf(f,"%s",s);
            if(findMinotaur(startDir, s, arr) == 1){
                    push_answer(arr, new_file.path);
                    fclose(f);
                    return 1;
                }


            while(fscanf(f,"%s%s",t,s)!= EOF){
                strcpy(file,s);
                if(findMinotaur(startDir, file, arr) == 1){
                    push_answer(arr, new_file.path);
                    fclose(f);
                    return 1;
                }
            }
        }
    }
}

void free_memory(char** elem, int count){
    for(int i  = 0; i < count; i++){
        free(elem[i]);
    }
}

int main(){
    const char* startDir  = "./labyrinth";
    char* filename = "file.txt";

    Maze path;
    path.maxcount = 10;
    path.count = 0;
    path.links = malloc(path.maxcount * sizeof(char*));

    findMinotaur(startDir, filename, &path);

    FILE* res_file = fopen("result.txt", "w");
    for(int i  = path.count - 1; i >= 0; i--){
        fprintf(res_file,"%s\n",path.links[i]);
    }

    fclose(res_file);
    free_memory(path.links, path.count);
    free(path.links);
    return 0;
}