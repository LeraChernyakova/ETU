.586 
.MODEL FLAT, C 
.CODE 

PUBLIC C second
second PROC C result1:dword, intervals: dword, result2: dword, x_max: dword, x_min: dword, n_int: dword 

push esi 
push edi 

mov esi, intervals 
mov edi, result2 
mov ecx, n_int 

PROCESSING: 
mov eax, [esi] ; ����� ������� ��������� 
mov ebx, [esi + 4] ; ������ ������� 

cmp eax, x_min ; ���� ����� ������� >= x_min 
jge LEFTGRMOREXMIN
cmp ebx, x_min; ������ ������� < ������������ ��������
;jl NEXTELEM ; 1) �������� �� jb NEXTELEM
jb NEXTELEM
mov eax, 0 ; �����, eax = 0, ������ ������� result1 
cmp ebx, x_max ; ���� ������ ������� > x_max
jg RIGHTGRMORE
sub ebx, x_min ; ���� ����� ��������� <= 0 
cmp ebx, 0;
jle NEXTELEM

RIGHTGRMORE:
mov ebx,x_max
sub ebx, eax ; ���������� ��������� � ��������� 
cmp ebx, 0 ; ���� ����� ��������� = 0 
jle NEXTELEM 

jmp PROCESSNOZEROINTERVAL;����� ������� � ��������� �� 0 ��������� 

LEFTGRMOREXMIN:
cmp eax, x_max ; ���� ����� ������� > x_max
jg NEXTELEM
cmp ebx, x_max ; ���� ������ ������� > x_max
jg RIGHTGRMOREXMAX
sub ebx, eax ; ���������� ��������� � ��������� 
cmp ebx, 0 ; ���� ����� ��������� = 0 
je NEXTELEM 
sub eax, x_min ; ������ ������� �������� �� �������� ��������� � ������� result1 
jmp PROCESSNOZEROINTERVAL

RIGHTGRMOREXMAX:
mov ebx,x_max
sub ebx, eax ; ���������� ��������� � ��������� 
add ebx, 1; ��������� �������, ����� ��������� � ��������� �������
cmp ebx, 0 ; ���� ����� ��������� = 0 
je NEXTELEM 
sub eax, x_min ; ������ ������� �������� �� �������� ��������� � ������� result1 
;sub eax, x_min ; 2)�������� �� add eax, x_min 
;add eax, x_min 

PROCESSNOZEROINTERVAL: 
push esi ;��������� �������� 
push ecx 

mov ecx, ebx ; ���������� ��������� �� result1 �� ������� ����� ������ 
mov esi, result1 ; ������ 
mov ebx, 0 ; ������� ����� ���������� ��������� 

SUMELEM: ; ����, ������� ����� ���������, �������� � �������� 
add ebx, [esi + 4*eax];� ebx ��������� ���������� ��������� � ��������� ��������� �������� 
;add ebx, [esi + 4*eax] ; 3) �������� �� add ebx, [esi + 2*eax]
;add ebx, [esi + 2*eax]
inc eax 
loop SUMELEM 

pop ecx;�������������� �������� 
;pop ecx; 4)������� ������� 


cmp ecx, 1 ; ���� ������������ �� ��������� �������, �� ���������� ����� � ������ ��������� 
jne RECORDING
;add ebx, [esi + 4*eax] ; ����� ��������� ��� ������� ��������� ������ ������ 

RECORDING: 
mov [edi], ebx ; ���������� ��������� 
pop esi;�������������� �������� 
jmp NEXTELEM 

NEXTELEM: 
add edi, 4 ; ��������� � ����. ��������� �������� 
add esi, 4 

loop PROCESSING 


pop edi
pop esi 

ret 
second ENDP 
END 
