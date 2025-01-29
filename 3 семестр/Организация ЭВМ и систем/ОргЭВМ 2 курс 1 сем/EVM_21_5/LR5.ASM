STACKSG SEGMENT  PARA STACK 'Stack'
        DW       512 DUP(?)
STACKSG	ENDS

DATASG  SEGMENT  PARA 'Data'				;SEG DATA
	KEEP_CS DW 0 ; для хранения сегмента
	KEEP_IP DW 0 ; и смещения вектора прерывания
	GREETING  DB '_Larin_Anton_8383_$'
	TIMER_CNT DW 0;
DATASG	ENDS								;ENDS DATA

CODE      SEGMENT   						;SEG CODE
ASSUME  DS:DataSG, CS:Code, SS:STACKSG

TMR_OVR  PROC FAR
	PUSH AX   ; сохранение изменяемых регистров
	;<действия по обработке прерывания>
	mov   AH,9
	int   21h
	dec TIMER_CNT;
	
	MOV  AL, 20H
	OUT  20H,AL
	POP  AX   ; восстановление регистров
	IRET
TMR_OVR  ENDP

	
	
Main      PROC  FAR
   	mov  ax, DATASG                        ;ds setup
   	mov  ds, ax   

	MOV  AH, 35H   ; функция получения вектора
	MOV  AL, 1CH   ; номер вектора
	INT  21H
	MOV  KEEP_IP, BX  ; запоминание смещения
	MOV  KEEP_CS, ES  ; и сегмента вектора прерывания

	PUSH DS
	MOV  DX, OFFSET TMR_OVR ; смещение для процедуры в DX
	MOV  AX, SEG TMR_OVR    ; сегмент процедуры
	MOV  DS, AX          ; помещаем в DS
	MOV  AH, 25H         ; функция установки вектора
	MOV  AL, 1CH         ; номер вектора
	INT  21H             ; меняем прерывание
	POP  DS
	
	
	mov   DX, OFFSET GREETING
	
	mov TIMER_CNT,5h;
lop:
	cmp TIMER_CNT,0;
	jnz lop;

	
	CLI
	PUSH DS
	MOV  DX, KEEP_IP
	MOV  AX, KEEP_CS
	MOV  DS, AX
	MOV  AH, 25H
	MOV  AL, 1CH
	INT  21H          ; восстанавливаем старый вектор прерывания
	POP  DS
	STI
	
	mov ah,4Ch;
	int 21h;
	
	
 
Main      ENDP
CODE      ENDS
END Main									;ENDS CODE	