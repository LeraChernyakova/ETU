STACKSG SEGMENT  PARA STACK 'Stack'
        DW       512 DUP(?)
STACKSG	ENDS

DATASG  SEGMENT  PARA 'Data'				;SEG DATA
	KEEP_CS DW 0 ;
	TPL DB '-0123456789abcdef0123456789abcdefG$'
DATASG	ENDS								;ENDS DATA


CODE      SEGMENT   						;SEG CODE
ASSUME  DS:DataSG, CS:Code, SS:STACKSG


DTOB PROC NEAR; DX:AX - Number; DX - Final binary string
	jmp dtob_start
	BASE DW 1;Keep track of registers order
dtob_start:	
	mov BASE,1;
	mov DI,0h
	mov TPL[DI],'+'
	cmp DX,0
	mov BX,8000h;bit mask
	jge posit
;negative
	mov TPL[DI],'-'
	add DI,1
	;neg
	not DX;
	not AX;
	add AX,1;
	jnc no_carry
	add DX,1;
no_carry:	
	jmp scan
reg_skip:;skept register
	cmp BASE,1
	jne ZERO_OR_OVERFLOW
	mov SI,AX
	sub BASE,1
	mov BX,8000h
	jmp kostyl;Like not_yet but no initial bit skip
;positive
posit:
	mov TPL[0],'+'
	add DI,1
	;DX
	;WHILE FIRST NON-ZERO DIGIT NOT FOUND
scan:
	mov SI,DX
not_yet:
	shr BX,1
kostyl:;Like not_yet but no initial bit skip
	cmp BX,0
	je reg_skip
	mov CX,BX;CX <- mask
	and CX,SI;CX <- digit of SI
	cmp CX,0
	je not_yet;LOOP DIGIT SKIP
	;CX - first left nonzero digit
digit_loop:;SI - REGISTER TO PROCESS
	mov CX,BX; CX <- mask
	and CX,SI; CX <- digit of SI
	cmp CX,0; if zero digit
	je zero_digit
;non-zero digit
	mov TPL[DI],'1'
	inc DI;
	jmp digit_fi
zero_digit:
	mov TPL[DI],'0'
	inc DI;
	jmp digit_fi
digit_fi:;endif
	shr BX,1
	cmp BX,0
	jne digit_loop
	;some register processed
	cmp BASE,1
	jne loop_end;AX register processed, we're done
	mov SI,AX;AX not processed
	sub BASE,1
	mov bx,8000h;
	jmp digit_loop
loop_end:
	mov TPL[DI],'$'
	jmp dtob_end
ZERO_OR_OVERFLOW:
	mov SI,0
	cmp TPL[SI],'-'
	jne EZERO
;OVERFLOW
	inc SI
	mov TPL[SI],'1'
	mov CX,32
OF_LOOP:
	mov SI,CX;
	add SI,1;
	mov TPL[SI],'0'
	loop OF_LOOP
	mov SI,33
	mov TPL[SI],'$'
EZERO:
	mov TPL[SI],'0'
	inc SI
	mov TPL[SI],'$'
	
dtob_end:
	mov DX,offset TPL
	
	ret
DTOB ENDP	

BTOD PROC FAR;TPL - string to process; DX:AX - result number
	jmp btod_start
	NEGT DB 0
	REGN DB 1; REg number: 1, then 0
	
btod_start:
	mov AX,0
	mov DX,0
	mov SI,0;Si-index in str
	cmp TPL[SI],'-'
	jne positive;
;negative
	mov NEGT,1
	inc SI;
positive:
	;cld
	sub ax,ax;
	mov SI,0
	sub SI,1
len_loop:
	add SI,1
	cmp TPL[SI],'$'
	jne len_loop

;start parsing	
	mov REGN,1
	cmp SI,22h;Max len => -(2^32)
	je max_d
	cmp SI,1;Min len
	je zero_d
	mov DI,AX ;DI - active register
	mov BX,1;BX - bit mask
	
parse_loop:
	dec SI
	cmp SI,0
	jle parse_fi
	
parse_cont:
;parse_if
	cmp TPL[SI],'1'
	jne parse_zero
;parse_one
	or DI,BX;set one by mask BX
	jmp parse_fi
parse_zero:
	not BX;set zero by inverted mask BX
	and DI,BX;
	not BX;
parse_fi:
	shl BX,1
	cmp BX,0
	je parse_overflow
	;;BX == 0 - overflow
	cmp BX,8000h
	jb parse_loop
;BX 8000 or more (or overflow)
parse_overflow:

	cmp REGN,0;
	je parse_pool;;EXIT CONDITION HERE
;regn 1
;check 8000h as well
	cmp BX,8000h
	je parse_loop

	mov AX,DI;Set processed register
	mov DI,0;Reset active register
	mov REGN,0;Set 0 register number(DX)
	mov BX,1;Reset bit mask
	jmp parse_loop
parse_pool:
	mov DX,DI;Set processed register
	jmp btod_check_neg
	
max_d:;max negative number
	mov AX,0
	mov DX,8000h;
	jmp btod_end
zero_d:;Zero number
	mov AX,0;
	mov DX,0;
	jmp btod_end
	
btod_check_neg:
	cmp NEGT,0
	je btod_end
;btod_neg
	not DX;
	not AX;
	add AX,1;
	jnc btod_end;no carry
	add DX,1;	
;no carry
;btod_pos
btod_end:

	ret
BTOD ENDP

	
Main      PROC  FAR
   	mov  ax, DATASG                        ;ds setup
   	mov  ds, ax   
;51080821_16 1359480865_10 1010001000010000000100000100001_2
;D1080821_16 3506964513_10 11010001000010000000100000100001_2 -101110111101111111011111011111
	
	mov DX,0000h
	mov AX,0821h
	call DTOB
	
	mov ah,09h;
	int 21h;
	
	mov ax,0
	mov dx,0
	call BTOD;
	
	
	
 
Main      ENDP
CODE      ENDS
END Main									;ENDS CODE	