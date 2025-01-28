#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

typedef struct File{                          
    char* fname;                              
    char* fpath;                              
}newFile;

typedef struct rewersed_arr{                   
    char** arr;                                
    int count;                                 
    int maxcount;                             
}Paths_arr;

void setName(newFile* ptrFile,const char* fname){
    ptrFile->fname=calloc(50,sizeof(char));
    strcpy(ptrFile->fname,fname);
}

void setPath(const char* pathDir,newFile* ptrFile){    
    char nextDir[300]={0};                    
    strcpy(nextDir,pathDir);
    strcat(nextDir,"/");
    DIR* dir=opendir(pathDir);                
    if(!dir)                                  
        return;
    struct dirent* de=readdir(dir);          
    while(de){                                
        if(de->d_type==DT_DIR&&strcmp(de->d_name,".")!=0&&strcmp(de->d_name,"..")!=0){
            int len=strlen(nextDir);
            strcat(nextDir,de->d_name);
            setPath(nextDir,ptrFile);
            nextDir[len]='\0';
        }
        if(de->d_type==DT_REG&&strcmp(de->d_name,ptrFile->fname)==0){
            strcat(nextDir,de->d_name);
            ptrFile->fpath=calloc(300,sizeof(char));
            strcpy(ptrFile->fpath,nextDir);
            closedir(dir);
            return;
        }
        de=readdir(dir);
    }
}

void push_answer(Paths_arr* ptrAnswer, char* path){
    if(ptrAnswer->count==ptrAnswer->maxcount){
        ptrAnswer->maxcount+=5;
        ptrAnswer->arr=realloc(ptrAnswer,ptrAnswer->maxcount*sizeof(char*));
    }
    ptrAnswer->arr[ptrAnswer->count]=calloc(strlen(path)+2,sizeof(char));
    strcpy(ptrAnswer->arr[ptrAnswer->count++],path);
}

int findMntr(const char* root,const char* fname,Paths_arr* ptrAnswer){
    newFile file;
    setName(&file,fname);
    setPath(root,&file);                 
    FILE* fFile=fopen(file.fpath,"r");   
    if(!fFile)                           
        return 0;
    char s[50];
    fscanf(fFile,"%s",s);
    if(strcmp(s, "Minotaur") == 0){
        push_answer(ptrAnswer,file.fpath);
        fclose(fFile);
        return 1;
    }
    else if(strcmp(s,"Deadlock")==0) {
        fclose(fFile);
        return 0;
    }
    else {
        char tmp[50],key[50];
        fseek(fFile,0,SEEK_SET);          
        while(fscanf(fFile,"%s%s",tmp,s)!=EOF){
            strcpy(key,s);
            if(findMntr(root,key,ptrAnswer)==1){
                push_answer(ptrAnswer,file.fpath);
                fclose(fFile);
                return 1;
            }
        }
    }
}

int main(){
    const char* root="./labyrinth";
    char* fname="file.txt";

    Paths_arr answer;
    answer.maxcount=10;
    answer.count=0;
    answer.arr=calloc(answer.maxcount,sizeof(char*));

    findMntr(root,fname,&answer);

    FILE* fRes=fopen("result.txt","w");
    int i;
    for(i=answer.count-1;i>=0;i--){
        fprintf(fRes,"%s\n",answer.arr[i]);
        free(answer.arr[i]);
    }
    free(answer.arr);
    fclose(fRes);
    return 0;
}