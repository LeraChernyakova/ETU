vector     EQU 16h
get_vector EQU 3516h
set_vector EQU 2516h
endl       EQU '$'

INTC MACRO addr
LOCAL intc_end   
   XOR AX,AX
   PUSHF
   CALL addr
intc_end:
ENDM

DOSSEG
.MODEL SMALL
.STACK 400h
.DATA
   vector_ip DD 0
   initial_message DB 'The handler began fulfilling its very important job...',10,13,endl
   final_message DB 'The handler has finished its very important job.',9,13,endl
.CODE
   Main PROC FAR
      PUSH DS
      SUB  AX,AX
      PUSH AX

      MOV  AX,@data
      MOV  DS,AX

      MOV  AX,get_vector
      INT  21h
      MOV  word ptr [vector_ip],BX
      MOV  word ptr [vector_ip + 2],ES

      CLI
      MOV  AX,SEG Handler
      MOV  DS,AX
      MOV  DX,OFFSET Handler
      MOV  AX,set_vector
      INT  21h
      STI

      INT  16h
      
      CLI
      LDS  DX,dword ptr [vector_ip]
      MOV  AX,word ptr [vector_ip + 2]
      MOV  ES,AX
      MOV  BX,word ptr [vector_ip]
      MOV  AX,set_vector
      INT  21h
      STI

      RET
   Main ENDP

   Handler PROC FAR
      PUSH AX
      PUSH CX
      PUSH DX
      PUSH DS

      MOV  AX,@data
      MOV  DS,AX
      MOV  AH,9
      MOV  DX,OFFSET initial_message
      INT  21h

      INTC vector_ip
      XOR  CX,CX
      MOV  CL,AH
   handler_loop:
      INTC vector_ip
      CMP  AL,0
      JE   handler_loop
      MOV  DL,AL
      MOV  AH,2
      INT  21h
      LOOP handler_loop
      MOV  DL,10
      INT  21h
      MOV  DL,13
      INT  21h

      MOV  AH,9
      MOV  DX,OFFSET final_message
      INT  21h

      POP  DS
      POP  DX
      POP  CX
      POP  AX
      MOV  AL,20h
      OUT  20h,AL
      IRET
   Handler ENDP
END
