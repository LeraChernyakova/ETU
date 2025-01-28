#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
void list_dir(char *s,char *dirPath,char *s2,FILE *f)
{
    DIR *dir = opendir(dirPath);
    if(dir) {
        struct  dirent *de = readdir(dir);
        while (de)
                {if (strstr(de->d_name,".txt"))
                        {if (s[0]==de->d_name[0] && strlen(de->d_name)==5)
                        {       s++;
                                char *s1=malloc(sizeof(char)*100);
                                strcpy(s1,dirPath);
                                strcat(s1,"/\0");
                                strcat(s1,de->d_name);
                                if (s)
                                        fprintf(f,"%s\n",s1);
                                else
                                        {fprintf(f,"%s",s1);
					 exit(1);}
                                //printf("%s\n",s2);
                                list_dir(s,s2,s2,f);
                                free(s1);
                        }
                        }
                        else
                                if (strcmp(de->d_name,".\0") && strcmp(de->d_name,"..\0"))
                                {       char *s1=malloc(sizeof(char)*100);
                                        strcpy(s1,dirPath);
                                        strcat(s1,"/\0");
                                        strcat(s1,de->d_name);
					  list_dir(s,s1,s2,f);
                                        free(s1);
                                }
                de=readdir(dir);
             }}
    closedir(dir);
}
int main(int argc,char **argv){
        char *s=malloc(sizeof(char)*50);
        char *s1=malloc(sizeof(char)*100);
        fgets(s,100,stdin);
         FILE *f=fopen("result.txt","w");
        s1[0]='.';
        s1[1]='/';
        s1[2]='t';
        s1[3]='m';
        s1[4]='p';
        s1[5]='\0';
        list_dir(s,s1,s1,f);
        fclose(f);
        return 0;
}
