
STACKSG SEGMENT  PARA STACK 'Stack'
        DW       32 DUP(?)
STACKSG	ENDS

DATASG  SEGMENT  PARA 'Data'				;SEG DATA
VARA	DW	1h
VARB	DW	2h
VARI	DW	2h
VARK	DW	3h
VARI1	DW	4h
VARI2	DW	5h
VARRES	DW	6h
DATASG	ENDS								;ENDS DATA

CODE      SEGMENT   						;SEG CODE
ASSUME CS:Code

	
Main      PROC  FAR
   	mov  ax, DATASG                        ;ds setup
   	mov  ds, ax                        	
   
	jmp f1
f1_end:
	mov di,offset VARI1
	pop [di]
	
	jmp f2
f2_end:
	mov di,offset VARI2
	pop [di]
	
	jmp f3
f3_end:
	mov di,offset VARRES
	pop [di]
	
	mov  ah, 4ch								;exit
	int  21h  
   
  
f1: ;dw f1(VARA,VARB,VARI)
   mov  si,OFFSET VARA	;si = &a
   mov 	ax,[si]			;ax = *si	(a)
   mov  si,OFFSET VARB	;si = &b
   cmp	ax,[si]			;cmp ax,*si	(a,b)
   jg	f1_1			;if a>b
   jmp	f1_2
f1_1:   				;then -(4i+3) = (-4i - 3)
	mov si,offset VARI
	mov bx,[si]			;bx = i
	shl bx,1			;bx *= 2
	shl bx,1			;bx *= 2
	sub ax,ax			;ax = 0
	sub ax,bx			;ax = -bx	(-4i)
	sub ax,3			;ax -= 3  
	push ax				;ret ax
	jmp f1_c
f1_2:					;else (6i-10)
	mov si,offset VARI
	mov bx,[si]			;bx = i
	shl bx,1			;bx *= 2
	shl bx,1			;bx *= 2
	mov ax,[si]			;ax = i
	shl ax,1			;ax *= 2
	add ax,bx			;ax += bx	(ax = 6i)
	sub ax,10			;ax -= 10
	push ax				;ret ax
	jmp f1_c
f1_c:
	jmp f1_end
	
	
f2: ;dw f2(VARA,VARB,VARI)
   mov  si,OFFSET VARA	;si = &a
   mov 	ax,[si]			;ax = *si	(a)
   mov  si,OFFSET VARB	;si = &b
   cmp	ax,[si]			;cmp ax,*si	(a,b)
   jg	f2_1			;if a>b
   jmp	f2_2
f2_1:   				;then -(6i + 8) = (-6i - 8)
	mov si,offset VARI
	mov bx,[si]			;bx = i
	shl bx,1			;bx *= 2
	shl bx,1			;bx *= 2
	mov ax,[si]			;ax = i
	shl ax,1			;ax *= 2
	add ax,bx			;ax += bx	(ax = 6i)
	sub bx,bx			;bx = 0
	sub bx,ax			;bx = -ax	(bx = -6i)
	sub bx,8			;bx -= 8
	push bx				;ret bx

	jmp f2_c
f2_2:					;else 9-3(i-1) = -3i + 12
	mov si,offset VARI
	mov ax,[si]			;ax = i
	shl ax,1			;ax *= 2
	add ax,[si]			;ax += i	(ax = 3i)
	sub bx,bx			;bx = 0
	sub bx,ax			;bx = -ax	(bx = -3i)
	add bx,12			;bx += 12
	push bx				;ret bx
	jmp f2_c
f2_c:
	jmp f2_end
	

f3: ;dw f3(VARI1,VARI2,VARK)
   mov  si,OFFSET VARK	;si = &k
   mov 	ax,[si]			;ax = *si	(k)
   cmp	ax,0			;cmp k,0
   je	f3_1			;if k=0
   jmp	f3_2
f3_1:   				;then abs(i1+i2)
	mov si,offset VARI1
	mov ax,[si]			;ax = i1
	mov si,offset VARI2
	add ax,[si]			;ax += i2 (ax = i1 + i2)
	cmp ax,0			;cmp i1+i2,0
	jnl	f3_1_c			;unless ax >= 0
	neg ax				;neg ax
f3_1_c:					;else dont			
	push ax				;ret ax
	jmp f3_c
f3_2:					;else min(i1,i2)
	mov si,offset VARI1
	mov ax,[si]			;ax = i1
	mov si,offset VARI2
	cmp ax,[si]			;cmp i1,i2
	jg f3_2_c			;unless i1 > i2
	push ax				;ret i2
	jmp f3_c
f3_2_c:					;else
	push [si]			;ret i1
	jmp f3_c				
f3_c:
	jmp f3_end
 
Main      ENDP
CODE      ENDS
END Main									;ENDS CODE	