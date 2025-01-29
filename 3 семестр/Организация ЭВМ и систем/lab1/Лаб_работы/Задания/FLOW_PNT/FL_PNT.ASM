;   Учебная программа  цикла лаб.раб. по дисциплине
;        "Организация и функционирование ЭВМ"
;        Тема: Использование М_Сопр.80Х87
;
;      ТЕКСТ  ПРОГРАММЫ

EOFLine  EQU  '$'      ; Определение символьной константы
                       ;     "Конец строки"

; Стек  программы

AStack    SEGMENT  STACK
          DW 12 DUP(?)     ; Отводится 12 слов памяти
AStack    ENDS

; Данные программы

DATA      SEGMENT

;  Директивы описания данных

A         DQ   1.6E+1
B         DQ   0.8e+1
Res       DQ    ?
DATA      ENDS

; Код программы

CODE      SEGMENT
          ASSUME CS:CODE, DS:DATA, SS:AStack

; Процедура печати строки - м.б. пригодится
WriteMsg  PROC  NEAR
          mov   AH,9
          int   21h  
          ret
WriteMsg  ENDP

;---------------------------------------------------
;          PUBLIC  Feccent

;  ФУНКЦИЯ
Feccent   PROC  NEAR
          fld   A         ; Загр. а  в FP-стек 
          Fmul  A         ; a*a  в  FP -стек
          fld   B         ; b  в  FP -стек
          fmul  B         ; b*b  в  FP -стек
          fsubp ST(1),ST  ; a*a-b*b  в  FP -стек и освобождение ST(1)
          fsqrt           ; sqrt(ST(0))
          fdiv  A         ; (a*a-b*b)/a в FP-стек 
          fst   res       ;  сохр. рез-т в res
          ret
Feccent   ENDP
;-------------------------------

; Головная процедура
Main      PROC  FAR
          push  DS          ;Сохранение адреса начала PSP в стеке
          sub   AX,AX       ;для последующего восстановления по
          push  AX          ;команде ret, завершающей процедуру.
          mov   AX,DATA             ; Загрузка сегментного
          mov   DS,AX               ; регистра данных.
          xor   ax,ax
          call  Feccent             ; Вычисление эксцентриситета
;         mov   DX,SI
;         call  WriteMsg                 ;  Вывод на экран
                                         ;  
          ret                            ; Выход в DOS по команде,
                                         ; нах-ся в 1-ом слове PSP.
Main      ENDP
CODE      ENDS
          END Main
