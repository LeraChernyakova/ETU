.586
.MODEL FLAT, C 
.CODE 

PUBLIC C first
first PROC C numbers: dword, n: dword, result1: dword, x_min: dword 

push esi;сохранение регистров 
push edi 

mov esi, numbers;адрес 1 элемента массива случайных чисел 
mov edi, result1;адрес 1 элемента результата 
mov ecx, n;длина массива 


PROCESSING: 
mov eax, [esi];запись случайного числа 
sub eax, x_min;получение индекса для итогового массива 
mov ebx, [edi+4*eax];получение элемента итогового массива 
inc ebx;число попало в ед отрезок=>увеличиваем количесвто на единицу 
mov [edi+4*eax], ebx;запись в соот ячейку  
add esi, 4;переходим к след элементу 
loop PROCESSING;вычесть ecx и если ecx=0 завершить цикл 
pop edi;восстановление регистров 
pop esi 

ret 
first endp 
end
