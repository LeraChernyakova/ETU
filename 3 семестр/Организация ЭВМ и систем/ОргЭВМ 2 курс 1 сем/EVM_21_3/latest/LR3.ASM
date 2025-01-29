
STACKSG SEGMENT  PARA STACK 'Stack'
        DW       32 DUP(?)
STACKSG	ENDS

DATASG  SEGMENT  PARA 'Data'				;SEG DATA
VARA	DW	1h
VARB	DW	1h
VARI	DW	1h
VARK	DW	1h
VARI1	DW	1h
VARI2	DW	1h
VARRES	DW	1h
DATASG	ENDS								;ENDS DATA

CODE      SEGMENT   						;SEG CODE
ASSUME  DS:DataSG, CS:Code
	
Main      PROC  FAR
   	mov  ax, DATASG                        ;ds setup
   	mov  ds, ax                        	
   
	jmp f1
f1_end:
	mov ax,VARI1
	pop VARI1
	
	jmp f2
f2_end:
	pop VARI2
	
	jmp f3
f3_end:
	pop VARRES
	
	mov  ah, 4ch								;exit
	int  21h  
   
  
f1: ;dw f1(VARA,VARB,VARI)
   mov 	ax,VARA			;ax = *si	(a)
   mov  si,VARB		;si = &b
   mov bx,VARI			;bx = i
	shl bx,1			;bx *= 2
   
   cmp	ax,si			;cmp ax,*si	(a,b)
   
   
   jg	f1_1			;if a>b

f1_2:					;else (6i-10)
	shl bx,1			;bx *= 2
	mov ax,VARI			;ax = i
	shl ax,1			;ax *= 2
	add ax,bx			;ax += bx	(ax = 6i)
	sub ax,10			;ax -= 10
	push ax				;ret ax
	jmp f1_c
	
f1_1:   				;then -(4i+3) = (-4i - 3)
	shl bx,1			;bx *= 2
	sub ax,ax			;ax = 0
	sub ax,bx			;ax = -bx	(-4i)
	sub ax,3			;ax -= 3  
	push ax				;ret ax
	jmp f1_c
	
f1_c:
	jmp f1_end
	
	
f2: ;dw f2(VARA,VARB,VARI)
   mov 	ax,VARA			;ax = *si	(a)
   cmp	ax,VARB			;cmp ax,*si	(a,b)
   jg	f2_1			;if a>b
   jmp	f2_2
f2_1:   				;then -(6i + 8) = (-6i - 8)
	mov bx,VARI			;bx = i
	shl bx,1			;bx *= 2
	shl bx,1			;bx *= 2
	mov ax,VARI			;ax = i
	shl ax,1			;ax *= 2
	add ax,bx			;ax += bx	(ax = 6i)
	sub bx,bx			;bx = 0
	sub bx,ax			;bx = -ax	(bx = -6i)
	sub bx,8			;bx -= 8
	push bx				;ret bx

	jmp f2_c
f2_2:					;else 9-3(i-1) = -3i + 12
	mov ax,VARI			;ax = i
	shl ax,1			;ax *= 2
	add ax,VARI		;ax += i	(ax = 3i)
	sub bx,bx			;bx = 0
	sub bx,ax			;bx = -ax	(bx = -3i)
	add bx,12			;bx += 12
	push bx				;ret bx
	jmp f2_c
f2_c:
	jmp f2_end
	

f3: ;dw f3(VARI1,VARI2,VARK)
   mov 	ax,VARK			;ax = *si	(k)
   cmp	ax,0			;cmp k,0
   je	f3_1			;if k=0
;   jmp	f3_2
f3_2:					;else min(i1,i2)
	mov ax,VARI1			;ax = i1
	cmp ax,VARI2		;cmp i1,i2
	jg f3_2_c			;unless quiri1 > i2
	push ax				;ret i2
	jmp f3_c
f3_2_c:					;else
	push VARI2			;ret i1
	jmp f3_c		
f3_1:   				;then abs(i1+i2)
	mov ax,VARI1			;ax = i1
	add ax,VARI2			;ax += i2 (ax = i1 + i2)
	cmp ax,0			;cmp i1+i2,0
	jnl	f3_1_c			;unless ax >= 0
	neg ax				;neg ax
f3_1_c:					;else dont			
	push ax				;ret ax
	jmp f3_c
		
f3_c:
	jmp f3_end
 
Main      ENDP
CODE      ENDS
END Main									;ENDS CODE	