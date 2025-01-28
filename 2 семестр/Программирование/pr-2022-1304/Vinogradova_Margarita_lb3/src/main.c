#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <regex.h>
struct Pair{
    char first[100];
    char sec[100];
};

void listDir(char *startDir, char * need,int num_ans,char answer[100][3000]);

int isValid(char *filename){
   //char *regexp = "^test-[[:digit:]]{4}\\.txt$";
    char *regexp = "\\.txt$";
    regex_t regexComp;

    if(regcomp(&regexComp, regexp, REG_EXTENDED)){
        return 0;
    }

    return regexec(&regexComp, filename, 0, NULL, 0) == 0;
}

void readFile(char * file,int num_ans,char answer[50][3000]){
    //puts("i read");

    struct Pair mas[10];
    FILE *fp=fopen(file,"r");
    FILE *f_wr=fopen("result.txt","w");
    char s[100];
    //char answer[50][300];
    //int num_ans=0;
    int kol=0;
    char arr_sent[100][100];
    if(fp==NULL)return;



    while(fgets(s,100,fp)){

        strcpy(arr_sent[kol],s);

        kol++;
    }


    char *istr;
    istr = strtok (arr_sent[0]," \n");
    strcpy(mas[0].first,istr);
    //printf("'%s'\n",mas[0].first);

    strcpy(answer[num_ans],file);
    //printf("---->%d %s\n",num_ans, answer[num_ans]);
    num_ans++;

    if(kol==1&&(strcmp(istr,"Deadlock")==0 || strcmp(istr,"Minotaur")==0)){
        //char*try=strtok(arr_sent[0]," \n\0");
        //printf("'%s'",try);
        if(strcmp(istr,"Deadlock")==0) {
            //printf("end\n");
            num_ans--;
        }
        if(strcmp(istr,"Minotaur")==0){
            //printf("find\n");

            int q;
            //printf("num=%d\n",num_ans);
            for(q=0;q<num_ans;q++){

                if(q<num_ans-1)fprintf(f_wr,"%s\n",answer[q]);
                else fprintf(f_wr,"%s",answer[q]);
                //printf("--->%s\n",answer[q]);
            }

        }
        fclose(fp);
        return;
    }


    istr = strtok(NULL, " \n");
    strcpy(mas[0].sec, istr);
    int i=0;
    for(i=1;i<kol;i++){

        istr = strtok (arr_sent[i]," \n");
        strcpy(mas[i].first,istr);
        istr = strtok(NULL, " \n");
        strcpy(mas[i].sec, istr);

    }


    for( i=0;i<kol;i++){
        //printf("%s %s\n",mas[i].first,mas[i].sec);
        char dir_name[500];

        strcpy(dir_name,"./labyrinth");
        listDir(dir_name,mas[i].sec,num_ans,answer);

    }
    fclose(fp);

}
void listDir(char *startDir, char * need,int num_ans,char answer[100][3000]){
    char nextDir[200]={0};
    strcpy(nextDir, startDir);
    DIR *dir = opendir(startDir);
    if(!dir)
        return;
    struct dirent *de = readdir(dir);
    while(de){
        if(strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0){
            int len = strlen(nextDir);
            strcat(nextDir, "/");
            strcat(nextDir,de->d_name);
            if(strcmp(de->d_name,need)==0){
                readFile(nextDir,num_ans,answer);

                return;
            }
            listDir(nextDir, need,num_ans,answer);
            nextDir[len] = '\0';
        }
        if(/*de->d_type == DT_REG &&*/ isValid(de->d_name)){
            int len = strlen(nextDir);
            strcat(nextDir, "/");
            strcat(nextDir,de->d_name);

            nextDir[len] = '\0';
        }
        de = readdir(dir);
    }
    closedir(dir);

}

int main(){

        char dir_name[500];
        strcpy(dir_name,"./labyrinth");
        int num_ans=0;
        char answer[100][3000];
    listDir(dir_name,"file.txt",num_ans,answer);


    return 0;
}