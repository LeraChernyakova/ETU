#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
void list_dir(const char* dirPath,const char* need, FILE* f)
{
        DIR* dir = opendir(dirPath);
        if (dir){
                struct dirent *de = readdir(dir);
                while (de){
                        if ((strcmp(de->d_name,".")!=0) && (strcmp(de->d_name,"..")!=0)){
                                char s[strlen(dirPath)+2+strlen(de->d_name)];
                                strcpy(s,dirPath);
                                strcat(s,"/");
                                strcat(s,de->d_name);
                                if(strcmp(de->d_name, need)==0){
                                        fprintf(f,"%s\n",s);
                                        return;
                                }
                                list_dir(s,need,f);
                                de = readdir(dir);
                        }
                        else{
                                de = readdir(dir);
                        }
                }
        }
        closedir(dir);
        return;
}
int main()
{
        char s[]="./tmp";
        char c='1';
        int k=0;
        char* need;
        need=malloc(sizeof(char));
        while(c!='\n'){
                scanf("%c",&c);
                k+=1;
                need=(char*)realloc(need,sizeof(char)*k);
                need[k-1]=c;
        }
        need[k]='\0';
        char temp[]="1.txt";
        FILE *file = fopen("result.txt","w");
        int i;
        for(i=0;i<strlen(need);i++){
                temp[0]=need[i];
                list_dir(s,temp,file);
        }
	free(need);
        fclose(file);
}
