AStack    SEGMENT  STACK
          DW 32 DUP(0)
AStack    ENDS
 
DATA      SEGMENT

DATA      SEGMENT
a	DW	0
b	DW	0
i	DW	0
k	DW	0
i1	DW	0	;f1
i2	DW	0	;f3
res	DW	0	;f2
DATA      ENDS

CODE SEGMENT

Main PROC FAR

push DS
sub AX,AX
push AX
mov AX, DATA
mov DS, AX

;вычисление f1 и f3
mov AX,a ; ax = a
mov CX,i ; cx = i
cmp AX,b	 ; сравнение двух операндов a и b
jg AGreaterB ; короткий переход, если первый операнд больше первого при выполнении операции cmp

;f1
sal CX,1 ; i<<1 = 2*i
add CX,i ; i*2+i = 3*i
mov i1,CX ; запись результата функции f1
add i1,4 ; 3*i+4

;f3
sal CX,1 ; i<<1 = 6*i
mov i2,8 ; запись числа 8 в результат работы функции f3 для дальнейших вычислений
sub i2,CX ; 8-6*i

jmp F2 ; выполнение безусловного перехода

AGreaterB:
;f1
sal CX,1 ; i<<1 = 2*i
mov i1,15 ; запись числа 15 в результат работы функции f1 для дальнейших вычислений
sub i1,CX ; 15-2*i

sal CX,1 ; i<<1 = 4*i
mov i2,7 ; запись числа 7 в результат работы функции f3 для дальнейших вычислений
sub i2,CX ; 7-4*i

;f2
F2:
cmp k,0 ; сравнение двух операндов k и 0
jl KLESSZERO ; короткий переход, если первый операнд меньше второго при выполнении операции cmp
;далее выполняется, если k >= 0
mov AX,i1 ; запись значения i1 для дальнейших вычислений
sub AX,i2 ; i1-i2
mov res,AX ; res = i1 - i2
cmp res,0 ; сравнение двух операндов res и 0
jl Module_is_negative ; короткий переход, если первый операнд меньше второго при выполнении операции cmp
jmp QUIT ; выполнение безусловного перехода

Module_is_negative:
;необходимо вывести модуль выражения i1-i2, знак которого "-" => смена знака
neg res ; изменение знака числа res
jmp QUIT ; выполнение безусловного перехода

KLESSZERO:
; выполняется, когда k < 0
mov AX,10 ; запись 10 для дальнейших вычислений
sub AX,i2 ; 10 - i2
cmp i1,AX ; сравнение i1 и 10 - i2
jg i1_GREATER_i2 ; короткий переход, если первый операнд больше первого при выполнении операции cmp
mov res,AX ; res = 10 -i2
jmp QUIT ; выполнение безусловного перехода

i1_GREATER_i2:
;при сравнении i1 и 10 - i2 первое оказалось больше
mov AX,i1 ; запись i1 для вывода результата
mov res,AX ; res = i1

QUIT:
    int 20 ; завершение программы

Main    ENDP
CODE    ENDS
        END Main