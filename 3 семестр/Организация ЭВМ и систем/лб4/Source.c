#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <Windows.h>



#define INP_STR_SIZE 100

char input_string[INP_STR_SIZE];     //������ ��� ������� ������
char output_string[INP_STR_SIZE * 4];//������ ��� �������� ������
char map[][2];                       //���������� ������� ������������ (����������� � ����� ����)

void printGreeting();

int main() {
    SetConsoleCP(1251); 
    SetConsoleOutputCP(1251); 
    printGreeting();
    fgets(input_string, INP_STR_SIZE, stdin);
    __asm {
        push ds
        pop es
        mov esi, offset input_string
        mov edi, offset output_string
        head :
            lodsb                    //��������� � al ������
            cmp al, '�'
            je jumpIfYoCharCapital   //��������� ������� ������ (� - "�� �� �������" � �������)
            cmp al, '�'
            je jumpIfYoChar       
            cmp al, '�'
            je jumpIfShchCharCapital //��������� ������� ������ (� - ������������ �������� 4 ������� ����� ��������������)
            cmp al, '�'
            je jumpIfShchChar
            cmp al, 192
            jge compareForRusChar
            stosb                   //����� ������ ������������ � output ������
            jmp final
            compareForRusChar:      //�������� ����� 192 � 255 => ������ ������� � ��� �� ���������
            cmp al, 255
            jle rusChar
            stosb                   //����� ������ ������������ � output ������
            jmp final
            rusChar :
            lea ebx, map            //��������� ������ �����. ��� ������ � xlatb
            sub al, 192             //�������� �� ���������� lotsb ������� 192, (�.�. � = 0....�=31....�=32...�=63) 
            sal al, 1               //�������� ������ �� 2 � ���� ������� ������� ������������
            mov ah, al
            add ah, 1               //���������� ��������� ������
            xlatb
            cmp al, ' '             //���������� �������
            je jumpIfSpace
            stosb                   //��������� ��� ������� � output
      //      mov al, ah
            xlatb
            cmp al, ' '             //���������� �������
            je jumpIfSpace
            stosb
            jmp final
            jumpIfShchCharCapital:  // ������������ ������� ������ �������
                mov al, 'S'
                stosb
                mov al, 'h'
                stosb
                mov al, 'c'
                stosb
                mov al, 'h'
                stosb
                jmp final
            jumpIfYoCharCapital:    // ������������ ������� ������ �������
                mov al, 'Y'
                stosb
                mov al, 'o'
                stosb
                jmp final
                jumpIfYoChar :
                mov al, 'y'
                stosb
                mov al, 'o'
                stosb
                jmp final
            jumpIfShchChar :        // ������������ ������� ������ �������
                mov al, 's'
                stosb
                mov al, 'h'
                stosb
                mov al, 'c'
                stosb
                mov al, 'h'
                stosb
                jmp final
            jumpIfSpace:            //���������� ������� ��� ��������� ������� ��������
            final:
                mov ecx, '\0'       //��������� �� ����� ������ (�����������, ���� ����� �� \0)
                cmp ecx, [esi]
                je ENDPROG
                jmp head
        ENDPROG:
    };
    output_string[strlen(output_string)] = '\0';
    printf("%s", output_string);
    

    FILE* fptr;
    fopen_s(&fptr,"processed_str.txt", "w");
    if (fptr != NULL)
    {
        fprintf(fptr, "%s", output_string);
    }
    puts("������� ENTER ��� ���������� ���������");
    getchar();
    return 0;
}

void printGreeting()
{
    printf("���������� ������� | ������ 1304 | ������� - 13\n");
    printf("�������������� ��������� �� ������� ������ ������� ���� � ��������� �\n");
    printf("������������ � ��������� ��������������, ��������� ������� ������� ������\n");
    printf("���������� � �������� ������ ���������������.\n");
    printf("������� ������ ��� ���������:\n");
}

char map[][2] = { 'A',' ','B',' ', 'V',' ', 'G',' ', 'D',' ', 'Y', 'e', 'Z','h','Z',' ',
'I',' ','Y',' ', 'K',' ', 'L',' ','M',' ','N',' ', 'O',' ', 'P',' ', 'R',' ', 'S',' ', 'T',' ',
'U',' ', 'F',' ', 'K','h', 'T','s', 'C','h', 'S','h', ' ',' ', (char)34, ' ', 'y',' ', (char)39,' ',
'E',' ', 'Y','u', 'Y','a',
'a',' ','b',' ', 'v',' ', 'g',' ', 'd',' ', 'y', 'e', 'z','h','z',' ',
'i',' ','y',' ', 'k',' ', 'l',' ','m',' ','n',' ', 'o',' ', 'p',' ', 'r',' ', 's',' ', 't',' ',
'u',' ', 'f',' ', 'k','h', 't','s', 'c','h', 's','h', ' ',' ', (char)34, ' ', 'y',' ', (char)39,' ',
'e',' ', 'y','u', 'y','a' };