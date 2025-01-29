; HELLO2 - Учебная программа N2  лаб.раб.#1 по дисциплине "Архитектура компьютера"
;          Программа использует процедуру для печати строки
;
;      ТЕКСТ  ПРОГРАММЫ

EOFLine  EQU  '$'         ; Определение символьной константы
                          ;     "Конец строки"

; Стек  программы

AStack    SEGMENT  STACK
          DW 12 DUP(?)    ; Отводится 12 слов памяти
AStack    ENDS

; Данные программы

DATA      SEGMENT

;  Директивы описания данных

HELLO     DB 'Здравствуйте!', 0AH, 0DH,EOFLine
GREETING  DB 'Вас приветствует ст.гр.4350 - Иванов И.И.$'
DATA      ENDS

; Код программы

CODE      SEGMENT
          ASSUME CS:CODE, DS:DATA, SS:AStack

; Процедура печати строки
WriteMsg  PROC  NEAR
          mov   AH,9
          int   21h  ; Вызов функции DOS по прерыванию
          ret
WriteMsg  ENDP

; Головная процедура
Main      PROC  FAR
          push  DS       ;\  Сохранение адреса начала PSP в стеке
          sub   AX,AX    ; > для последующего восстановления по
          push  AX       ;/  команде ret, завершающей процедуру.
          mov   AX,DATA             ; Загрузка сегментного
          mov   DS,AX               ; регистра данных.
          mov   DX, OFFSET HELLO    ; Вывод на экран первой
          call  WriteMsg            ; строки приветствия.
          mov   DX, OFFSET GREETING ; Вывод на экран второй
          call  WriteMsg            ; строки приветствия.
          ret                       ; Выход в DOS по команде,
                                    ; находящейся в 1-ом слове PSP.
Main      ENDP
CODE      ENDS
          END Main
