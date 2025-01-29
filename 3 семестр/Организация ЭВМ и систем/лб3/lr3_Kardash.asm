;Вариант 10 - 2.5.6
;
;         /-(4*i+3), при  a>b         
;   f2 = <                      
;         \ 6*i-10 , при  a<=b 
;
;          / 20-4*i,  при  a>b   
;   f5 = <                      
;          \-(6*i-6), при  a<=b
;
;          / (|i1|-|i2|), при  k<0
;   f6 = <
;          \ max(7,|i2|), при  k>=0

AStack SEGMENT STACK
        DW 12 DUP(?)
AStack ENDS


DATA SEGMENT


a       DW -15
b       DW -10
i       DW -5
i1      DW 0
i2      DW 0
k       DW -1
res     DW 0

DATA        ENDS
CODE        SEGMENT
ASSUME      CS:CODE, DS:DATA, SS:AStack

Main        PROC FAR
            push DS
            sub ax,ax
            push ax
            mov ax,DATA
            mov ds,ax
                        ; запись в регистры i с побитовым сдвигом
            mov cx, i   ; cx = i
            neg cx      ; cx = -i
            mov bx, cx  ; bx = -i
            sal bx,1    ; bx = -2*i
            mov dx,bx   ; dx = -2*i
            sal dx,1    ; dx = -4*i

                        ; вычисление fn1 fn2
            mov ax,a    ; ax = a
            cmp ax,b    ;сравнение a и b 
            jg F1       ;if a>b   
                        ; else (a<=b)
            add dx,bx   ; dx = -6i
            mov bx,dx   ; bx = -6i
            add dx, 6   ; dx = -6i +6
            neg bx      ; bx = 6i
            add bx, -10 ; bx = 6i-10
            jmp F2

F1:                     ;a>b
            mov bx, dx  ;bx = -4i
            add bx, -3  ; bx = -4i -3
            add dx, 20  ; dx = 20 - 4i

F2:                     ; вычисление fn3
            mov i1, bx  ; i1 = fn1
            mov i2, dx  ; i2 = fn2
            cmp dx, 0   ;вычисляю модуль i2 (нужен для обоих вычислений fn3)
            jg N1       ;(if i2>0)
            neg dx      ;else (i2<0)
N1:
            mov ax,k    ; ax =k
            cmp ax,0    
            jl FT       ;if k<0
            cmp dx,7    ;else (k>=0)
            jge RT1     ;if |i2|>= 7
            mov res, 7  ;else (|i2|<=7) res = 7
            jmp E
RT1:                    ; |i2|>=7
            mov res,dx  ;res = |i2|
            jmp E 
                
FT:                     ;k<0
            cmp bx,0
            jg N2
            neg bx      ; bx = |i1|
N2:
            sub bx,dx   ; bx = |i1|-|i2|
            mov res,bx  ; res = |i1|-|i2|
E:         
            ret
Main        ENDP
CODE        ENDS
END         Main