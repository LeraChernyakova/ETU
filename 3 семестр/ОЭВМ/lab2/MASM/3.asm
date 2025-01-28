Stk SEGMENT STACK
DB 1024 DUP(?)
Stk ENDS
DATA SEGMENT
KEEP_CS DW 0
KEEP_IP DW 0
Message2 db 'prerivanie',10,13,'$'
DATA ENDS

CODE SEGMENT 
ASSUME CS:CODE, DS:DATA, SS:Stk

subr_int proc far
push ax
push dx
mov ah, 9h
mov dx, offset message2
int 21h
pop dx
pop ax
mov al, 20h
out 20h,al
iret
subr_int endp

main proc far
push ds
sub ax,ax
push ax
mov ax,DATA
mov ds,ax
mov ah,35h
mov al, 08h
int 21h

mov keep_ip, bx
mov keep_cs, es
push ds
mov dx, offset subr_int
mov ax, seg subr_int
mov ds,ax
mov ah,25h
mov al, 08h
int 21h
pop ds
int 08h
mov cx, 0ffffh
m1:
loop m1
mov cx, 0ffffh
m2:
loop m2
mov cx, 0ffffh
m3:
loop m3

CLI
Push ds 
mov dx, keep_ip
mov ax, keep_cs
mov ds,ax
mov ah,25h
mov al, 08h
int 21h
pop ds
STI
ret
Main endp
code ends
end Main