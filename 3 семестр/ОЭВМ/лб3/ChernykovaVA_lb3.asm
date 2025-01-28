ASSUME CS:CODE, SS:AStack, DS:DATA

AStack    SEGMENT  STACK
          DW 32 DUP(0)
AStack    ENDS

DATA      SEGMENT

i	DW	?
a 	DW 	?
b	DW	?
k	DW	?

i1	DW	?		;f1
i2	DW	?		;f4
res	DW	?		;f3

DATA      ENDS

CODE SEGMENT

Main      PROC  FAR
	mov   AX,DATA
	mov   DS,AX

;Вычисление f1 и f2
	mov ax,a	;заносим значение а в ах
	mov cx,i	;заносим i в cx
	cmp ax,b	;Сравнение значений a и b	
	jg A1		;если a>b то на A1

				;если a<=b
	sal cx,1	;умножение i на 2 cx = i*2
	add cx,i	;cx = 2*i + i = 3*i	
	mov ax,4	;ax = 4
	add cx,ax	;cx = 3*i + 4
	mov i1,cx	;сохранение результата в f1
	
	add cx,ax	;cx = 3*i + 4 + 2 = 3(i + 2)
	mov i2,cx	;сохраняем рез-т в f2
	jmp A2		;Пропускаем следующие шаги

A1:				;если a>b
	mov cx,i	;восстановление значения i в cx	
	sal cx,1	;cx = i*2
	mov ax,15	;ax = 15
	sub ax,cx	;ax = ax - cx
	mov i1,ax	;сохраняем результат в i1

	mov ax,cx	;ax = 2*i
	sal cx,1	;cx:=2*i*2
	add cx,ax	;cx = 4*i + 2*i = 6*i
	mov ax,4	;ax = 4
	sub ax,cx	;ax = ax - cx = 4 - 6*i 
	mov i2,ax	;сохраняем результат в f2
	
;Вычисление f3
A2:
	mov ax,k
	
	cmp ax,0	;сравниваем k и 0
	JNe B1		;если k не равно 0 то перйти на B1
	
				;решение при к = 0
	mov dx,i1	;dx = i1
	add dx,i2	;dx = i1 + i2
	cmp dx,0
	JGe C1		;если i1+ i2 >= 0 то перейти на C1
	
	neg dx		;если i1 + i2 < 0 то меняем знак на противоположный
	mov res,dx	;res = dx
	jmp B2
	
C1:
	mov res,dx
	jmp B2
	
B1:
				;если k не равно 0
	mov ax,i1
	mov bx,i2
	cmp ax,bx
	JGe C2 		;если i1 >= i2 то перейти на C2
	
	mov res,ax
	jmp B2
	
C2:
	mov res,bx	;если i1 >= i2
	
B2:
	int 20h
		  
Main      ENDP
CODE      ENDS
          END Main
