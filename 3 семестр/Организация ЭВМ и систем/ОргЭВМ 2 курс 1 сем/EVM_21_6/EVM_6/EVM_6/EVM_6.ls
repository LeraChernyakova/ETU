Microsoft (R) Macro Assembler Version 14.16.27030.1	    10/17/19 02:13:38
Inc.asm							     Page 1 - 1


				.686
				.MODEL FLAT, C
				.STACK
 00000000			.DATA
				;-----------Local data------------------------------
 00000000			.CODE
				;-----------External usage--------------------------
				;-----------Function definitions--------------------
 00000000			MAS_FUNC PROC C n:dword, ni:dword, xmi:dword, xma:dword,nums:dword, bordArr:dword, inclArr:dword
 00000003  B9 00000000		mov ecx,0
 00000008  8B 5D 18		mov ebx,[nums]
 0000000B  8B 75 1C		mov esi,[bordArr]
 0000000E  8B 7D 20		mov edi,[inclArr]
 00000011			lp:
 00000011  90			nop
 00000012  8B 03		mov eax,[ebx]

 00000014  53			push ebx;

 00000015  BB 00000000		mov ebx,0;edge num
 0000001A			lp1:
 0000001A  8B D3		mov edx,ebx;
 0000001C  C1 E2 02		shl edx,2;
				;mov ebx,[esi+edx]
 0000001F  3B 04 16		cmp eax,[esi+edx];more then next border
 00000022  7F 02		jg ink
 00000024  EB 03		jmp ent
 00000026			ink:
 00000026  43			inc ebx
 00000027  EB F1		jmp lp1
 00000029			ent:

 00000029  03 D7		add edx,edi
 0000002B  8B 02		mov eax,[edx]
 0000002D  40			inc eax
 0000002E  89 02		mov [edx],eax;element lies in edx section

 00000030  5B			pop ebx;

 00000031  83 C3 04		add ebx,4
 00000034  41			inc ecx
 00000035  3B 4D 08		cmp ecx,n
 00000038  7C D7		jl lp

				ret
 0000003C			MAS_FUNC ENDP
Inc.asm(46) : warning A6004:procedure argument or local not referenced : ni
Inc.asm(46) : warning A6004:procedure argument or local not referenced : xmi
Inc.asm(46) : warning A6004:procedure argument or local not referenced : xma

				END
Microsoft (R) Macro Assembler Version 14.16.27030.1	    10/17/19 02:13:38
Inc.asm							     Symbols 2 - 1




Segments and Groups:

                N a m e                 Size     Length   Align   Combine Class

FLAT . . . . . . . . . . . . . .	GROUP
STACK  . . . . . . . . . . . . .	32 Bit	 00000400 Para	  Stack	  'STACK'	 
_DATA  . . . . . . . . . . . . .	32 Bit	 00000000 Para	  Public  'DATA'	
_TEXT  . . . . . . . . . . . . .	32 Bit	 0000003C Para	  Public  'CODE'	


Procedures, parameters, and locals:

                N a m e                 Type     Value    Attr

MAS_FUNC . . . . . . . . . . . .	P Near	 00000000 _TEXT	Length= 0000003C Public C
  n  . . . . . . . . . . . . . .	DWord	 bp + 00000008
  ni . . . . . . . . . . . . . .	DWord	 bp + 0000000C
  xmi  . . . . . . . . . . . . .	DWord	 bp + 00000010
  xma  . . . . . . . . . . . . .	DWord	 bp + 00000014
  nums . . . . . . . . . . . . .	DWord	 bp + 00000018
  bordArr  . . . . . . . . . . .	DWord	 bp + 0000001C
  inclArr  . . . . . . . . . . .	DWord	 bp + 00000020
  lp . . . . . . . . . . . . . .	L Near	 00000011 _TEXT	
  lp1  . . . . . . . . . . . . .	L Near	 0000001A _TEXT	
  ink  . . . . . . . . . . . . .	L Near	 00000026 _TEXT	
  ent  . . . . . . . . . . . . .	L Near	 00000029 _TEXT	


Symbols:

                N a m e                 Type     Value    Attr

@CodeSize  . . . . . . . . . . .	Number	 00000000h   
@DataSize  . . . . . . . . . . .	Number	 00000000h   
@Interface . . . . . . . . . . .	Number	 00000001h   
@Model . . . . . . . . . . . . .	Number	 00000007h   
@code  . . . . . . . . . . . . .	Text   	 _TEXT
@data  . . . . . . . . . . . . .	Text   	 FLAT
@fardata?  . . . . . . . . . . .	Text   	 FLAT
@fardata . . . . . . . . . . . .	Text   	 FLAT
@stack . . . . . . . . . . . . .	Text   	 FLAT

	   3 Warnings
	   0 Errors
