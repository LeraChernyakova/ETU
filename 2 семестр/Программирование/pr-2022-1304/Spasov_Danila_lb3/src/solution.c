#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>


#define OUTPUT_FILE_NAME "result.txt"
#define ROOT_DIRECTORY "."

#define PATH_BUFFER_SIZE 1024
#define MAX_FILES_COUNT 16384



struct FileInfo
{
    long int Number;
    char* Str;
};


struct FileInfo ParseString(char* str)
{
    struct FileInfo Result;
    Result.Number = 0;
    Result.Str = NULL;

    char* FirstSpace = strstr(str, " ");
    if( FirstSpace == NULL) return Result;

    Result.Number = atoi(str);
    Result.Str = (char*)malloc(sizeof(char) * (strlen(FirstSpace + 1) + 1));
    strcpy(Result.Str, FirstSpace + 1);

    return Result;
}


int CompareFileInfo(const void* A, const void* B)
{
    if( ((struct FileInfo*)A)->Number > ((struct FileInfo*)B)->Number ) return 1;
    if( ((struct FileInfo*)A)->Number < ((struct FileInfo*)B)->Number ) return -1;
    return 0;
}


void PrintFileInfoToFile(const struct FileInfo* FileInfo, FILE* File)
{
    if( FileInfo == NULL || File == NULL ) return;

    fprintf(File, "%ld %s\n", FileInfo->Number, FileInfo->Str);
}

void FreeFileInfo(struct FileInfo* FileInfo)
{
    if( FileInfo == NULL ) return;

    free(FileInfo->Str);
    FileInfo->Str = NULL;
    FileInfo->Number = 0;
}




int IterateDirectory(char* DirPath, struct FileInfo* FilesInfo)
{
    if( DirPath == NULL || FilesInfo == NULL ) return 0;

    DIR* CurrentDirectory = opendir(DirPath);
    if( CurrentDirectory == NULL ) return 0;


    int ElemsCount = 0;

    struct dirent* LSubDir = readdir(CurrentDirectory);
    while( LSubDir )
    {
        if( LSubDir->d_name[0] == '.') { LSubDir = readdir(CurrentDirectory); continue; }
        if( strcmp(LSubDir->d_name, OUTPUT_FILE_NAME) == 0 ) { LSubDir = readdir(CurrentDirectory); continue; }

        char LFilePath[PATH_BUFFER_SIZE];
        #ifdef _WIN32
            strcpy(LFilePath, CurrentDirectory->dd_name);
            LFilePath[strlen(LFilePath) - 1] = '\0';
            strcat(LFilePath, "\\");
            strcat(LFilePath, LSubDir->d_name);
        #else
            #ifdef __linux__
                strcpy(LFilePath, DirPath);
                strcat(LFilePath, "/");
                strcat(LFilePath, LSubDir->d_name);
            #endif // __linux__
        #endif // _WIN32

        if(strstr(LSubDir->d_name, ".txt") != NULL)
        {
            FILE* LFile = fopen(LFilePath, "r");
            if(LFile == NULL) { LSubDir = readdir(CurrentDirectory); continue; }

            char LStr[256];
            fgets(LStr, 256, LFile);
            FilesInfo[ElemsCount] = ParseString(LStr);
            fclose(LFile);

            ++ElemsCount;
        }
        else
        {
            ElemsCount += IterateDirectory(LFilePath, FilesInfo + ElemsCount);
        }


        LSubDir = readdir(CurrentDirectory);
    }

    closedir(CurrentDirectory);
    return ElemsCount;
}


int main()
{
    struct FileInfo FilesInfo[MAX_FILES_COUNT];

    int ElemsCount = IterateDirectory(ROOT_DIRECTORY, FilesInfo);
    qsort(FilesInfo, ElemsCount, sizeof(struct FileInfo), CompareFileInfo);


    FILE* OutputFile = fopen(OUTPUT_FILE_NAME, "w");
    if(OutputFile == NULL)
    {
        puts("Can't open output file!");
        return 0;
    }

    for(int i = 0; i < ElemsCount; ++i)
    {
        PrintFileInfoToFile(&FilesInfo[i], OutputFile);
        FreeFileInfo(&FilesInfo[i]);
    }
    fclose(OutputFile);


    return 0;
}
