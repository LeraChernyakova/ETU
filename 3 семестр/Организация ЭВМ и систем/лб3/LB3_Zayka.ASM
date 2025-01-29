; Вариант 9 - 2.4.7
; Входные данные - a, b, i, k размером 1 слово (16 бит)
;         /-(4*i+3), при  a>b
;   f2 = <                      
;         \ 6*i-10 , при  a<=b 
;
;         /-(6*i-4), при  a>b   
;   f4 = <                      
;         \ 3*(i+2), при  a<=b 
;
;         / (|i1|+|i2|), при  k<0
;   f7 = <
;         \ max(6,|i1|), при  k>=0 
;   Перед ветвлением запишем i, 2*i, 4*i
;
;
;
;
;
;
;
;
;


AStack SEGMENT STACK 
    DW 12 DUP(?)
AStack ENDS

DATA SEGMENT
    a   DW -15
    b   DW -10
    i   DW -5
    i1  DW 0
    i2  DW 0
    k   DW 1
    res DW 0
DATA ENDS

CODE SEGMENT 
    ASSUME CS:CODE, DS:DATA, SS:AStack

Main    PROC FAR
    push DS
    sub AX, AX
    push AX
    mov AX, DATA
    mov DS, AX

    mov CX, i ; i
    mov DX, CX 
    sal DX, 1 ; 2*i
    mov BX, DX
    sal BX, 1 ; 4*i
    
    mov AX, a
    cmp AX, b ; сравниваем a и b
    jg T1 ; переход при a > b
    add BX, DX ; 2*i+4*i 
    sub BX, 10 ; 6*i - 10
    add DX, CX ; 3*i
    add DX, 6 ; 3*i + 6  
    jmp F1
T1:
    add BX, 3 ; 4*i + 3
    neg BX ; -(4*i + 3)
    sub DX, BX ; 2*i+4*i-3
    sub DX, 1 ; 6*i-4
    neg DX ; -(6*i-4)
    
F1:
    mov i1, BX
    cmp BX, 0
    jg A1
    neg BX
A1:    
    mov i2, DX
    cmp DX, 0
    jg A2
    neg DX
A2:
    mov AX, k
    cmp AX, 0
    jl T3 ; k < 0

F3:
    cmp BX, 6
    jge T2
    mov res, 6
    jmp F2

T2:
    mov res, BX
    jmp F2

T3:
    mov AX, BX
    add AX, DX
    mov res, AX
    jmp F2
F2:
    ret

Main ENDP
CODE ENDS
    END MAIN

