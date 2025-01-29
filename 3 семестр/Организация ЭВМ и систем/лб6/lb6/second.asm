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
mov eax, [esi] ; левая граница интервала 
mov ebx, [esi + 4] ; правая граница 

cmp eax, x_min ; если левая граница >= x_min 
jge LEFTGRMOREXMIN
cmp ebx, x_min; правая граница < минимального элемента
;jl NEXTELEM ; 1) заменить на jb NEXTELEM
jb NEXTELEM
mov eax, 0 ; иначе, eax = 0, начало массива result1 
cmp ebx, x_max ; если правая граница > x_max
jg RIGHTGRMORE
sub ebx, x_min ; если длина интервала <= 0 
cmp ebx, 0;
jle NEXTELEM

RIGHTGRMORE:
mov ebx,x_max
sub ebx, eax ; количество элементов в интервале 
cmp ebx, 0 ; если длина интервала = 0 
jle NEXTELEM 

jmp PROCESSNOZEROINTERVAL;иначе перейти к обработке не 0 интервала 

LEFTGRMOREXMIN:
cmp eax, x_max ; если левая граница > x_max
jg NEXTELEM
cmp ebx, x_max ; если правая граница > x_max
jg RIGHTGRMOREXMAX
sub ebx, eax ; количество элементов в интервале 
cmp ebx, 0 ; если длина интервала = 0 
je NEXTELEM 
sub eax, x_min ; индекс первого элемента из текущего интервала в массиве result1 
jmp PROCESSNOZEROINTERVAL

RIGHTGRMOREXMAX:
mov ebx,x_max
sub ebx, eax ; количество элементов в интервале 
add ebx, 1; Добавляем единицу, чтобы сосчитать и последний элемент
cmp ebx, 0 ; если длина интервала = 0 
je NEXTELEM 
sub eax, x_min ; индекс первого элемента из текущего интервала в массиве result1 
;sub eax, x_min ; 2)заменить на add eax, x_min 
;add eax, x_min 

PROCESSNOZEROINTERVAL: 
push esi ;сохраняем регистры 
push ecx 

mov ecx, ebx ; количество элементов из result1 по которым нужно пройти 
mov esi, result1 ; массив 
mov ebx, 0 ; считает сумму подходящих элементов 

SUMELEM: ; цикл, считает сумму элементов, входящих в интервал 
add ebx, [esi + 4*eax];к ebx добавляем количество попаданий в очередной еденичный интервал 
;add ebx, [esi + 4*eax] ; 3) заменить на add ebx, [esi + 2*eax]
;add ebx, [esi + 2*eax]
inc eax 
loop SUMELEM 

pop ecx;восстановление регистра 
;pop ecx; 4)удалить команду 


cmp ecx, 1 ; если обрабатывали не последний элемент, то записываем сумму в массив результат 
jne RECORDING
;add ebx, [esi + 4*eax] ; иначе добавляем еще элемент последней правой скобки 

RECORDING: 
mov [edi], ebx ; записываем результат 
pop esi;восстановление регистра 
jmp NEXTELEM 

NEXTELEM: 
add edi, 4 ; двигаемся к след. элементам массивов 
add esi, 4 

loop PROCESSING 


pop edi
pop esi 

ret 
second ENDP 
END 
