; Учебная программа  генерации звука по дисциплине "Архитектура компьютера"
; перед вызывом процедуры Sound загрузить: в регистр di частоту тона (21-65535 гц)
; в регистр bx - длительность звучания (в сотых долях сек.)

EOFLine  EQU  '$'         ; Определение символьной константы
                          ;     "Конец строки"

; Стек  программы

AStack    SEGMENT  STACK
          DW 100 DUP(?)    ; Отводится 100 слов памяти
AStack    ENDS

; Данные программы

DATA      SEGMENT

;  Директивы описания данных

HELLO     DB 'Hello from Sound!', 0AH, 0DH,EOFLine
DATA      ENDS

; Код программы

CODE      SEGMENT
          ASSUME CS:CODE, DS:DATA, SS:AStack

; Процедура печати строки
WriteMsg  PROC  NEAR
          mov   AH,9
          int   21h  ; Вызов функции печати строки
          ret
WriteMsg  ENDP

Sound     PROC  NEAR   ; процедура генерации звука
          Push AX
          Push BX
          Push CX
          Push DX
 	  Push DI
	  mov  al, 	0B6h  ; режим: канал 2,режим 3 (мл.байт и ст.байт;;)  
	  Out  43h,     al
          mov  dx,	14h   ; dx:ax - 1 331 000 
	  mov  ax, 	4F38h ; делится на  
	  div di              ; треб.частоту
          Out  42h,     al    ; Зап.мл байта 
          mov  al, ah 
          Out  42h,     al    ; Зап.ст.байта
          In   al,	61h   ; тек. установку порта 61 - в al 
 	  mov  ah, al         ; и сохранить в ah
	  or   al, 3
	  Out  61h,     al    ; запуск динамика и включение звука
Pause:	  mov  cx, 2801       ; пауза в
Delay:    loop Delay          ; 10 мсек
          dec  bx             ; длител-ть исчерпана?
	  Jnz  Pause           ; нет - звучать
	  mov  al,  ah        ; да - вернуть установку порта 61
	  Out  61h,	al		
          Pop  DI
	  Pop  DX
	  Pop  CX
	  Pop  BX
	  Pop  AX
          
          ret 		      ; возврат 

Sound     ENDP



; Головная процедура
Main      PROC  FAR
          push  DS       ;\  Сохранение адреса начала PSP в стеке
          sub   AX,AX    ; > для последующего восстановления по
          push  AX       ;/  команде ret, завершающей процедуру.
          mov   AX,DATA             ; Загрузка сегментного
          mov   DS,AX               ; регистра данных.
          mov   DX, OFFSET HELLO    ; Вывод на экран первой
          call  WriteMsg            ; строки приветствия.
          mov	DI,  300
	  mov   BX,  600 
	  call  Sound               ; Вызов процедуры генерации звука
          ret                       ; Выход в DOS по команде,
                                    ; находящейся в 1-ом слове PSP.
Main      ENDP
CODE      ENDS
          END Main
