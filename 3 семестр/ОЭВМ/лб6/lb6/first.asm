.586
.MODEL FLAT, C 
.CODE 

PUBLIC C first
first PROC C numbers: dword, n: dword, result1: dword, x_min: dword 

push esi;���������� ��������� 
push edi 

mov esi, numbers;����� 1 �������� ������� ��������� ����� 
mov edi, result1;����� 1 �������� ���������� 
mov ecx, n;����� ������� 


PROCESSING: 
mov eax, [esi];������ ���������� ����� 
sub eax, x_min;��������� ������� ��� ��������� ������� 
mov ebx, [edi+4*eax];��������� �������� ��������� ������� 
inc ebx;����� ������ � �� �������=>����������� ���������� �� ������� 
mov [edi+4*eax], ebx;������ � ���� ������  
add esi, 4;��������� � ���� �������� 
loop PROCESSING;������� ecx � ���� ecx=0 ��������� ���� 
pop edi;�������������� ��������� 
pop esi 

ret 
first endp 
end
