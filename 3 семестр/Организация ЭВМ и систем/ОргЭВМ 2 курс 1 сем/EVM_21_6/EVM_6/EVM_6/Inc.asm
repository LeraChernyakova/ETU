.686
.MODEL FLAT, C
.STACK
.DATA
;-----------Local data------------------------------
.CODE
;-----------External usage--------------------------
;-----------Function definitions--------------------
MAS_FUNC PROC C n:dword, ni:dword, xmi:dword, xma:dword,nums:dword, bordArr:dword, inclArr:dword
mov ecx,0
mov ebx,[nums]
mov esi,[bordArr]
mov edi,[inclArr]
lp:
nop
mov eax,[ebx]

push ebx;

mov ebx,0;edge num
lp1:
mov edx,ebx;
shl edx,2;
;mov ebx,[esi+edx]
cmp eax,[esi+edx];more then next border
jg ink
jmp ent
ink:
inc ebx
jmp lp1
ent:

add edx,edi
mov eax,[edx]
inc eax
mov [edx],eax;element lies in edx section

pop ebx;

add ebx,4
inc ecx
cmp ecx,n
jl lp

ret
MAS_FUNC ENDP

END