	.386p
	ifndef	??version
?debug	macro
	endm
publicdll macro	name
	public	name
	endm
$comm	macro	name,dist,size,count
	comm	dist name:BYTE:count*size
	endm
	else
$comm	macro	name,dist,size,count
	comm	dist name[size]:BYTE:count
	endm
	endif
	?debug	V 300h
	?debug	S "dostest.c"
	?debug	C E9EB50532709646F73746573742E63
	?debug	C E94019CB1815473A5C42435C494E434C5544455C737464696F2E68
	?debug	C E94019CB1815473A5C42435C494E434C5544455C5F646566732E68
	?debug	C E94019CB1816473A5C42435C494E434C5544455C5F6E66696C652E+
	?debug	C 68
	?debug	C E94019CB1815473A5C42435C494E434C5544455C5F6E756C6C2E68
_TEXT	segment byte public use16 'CODE'
_TEXT	ends
DGROUP	group	_DATA,_BSS
	assume	cs:_TEXT,ds:DGROUP
_DATA	segment word public use16 'DATA'
d@	label	byte
d@w	label	word
_DATA	ends
_BSS	segment word public use16 'BSS'
b@	label	byte
b@w	label	word
_BSS	ends
_TEXT	segment byte public use16 'CODE'
   ;	
   ;	void main(void)
   ;	
	assume	cs:_TEXT
_main	proc	near
	push	bp
	mov	bp,sp
   ;	
   ;	{
   ;	    // Set port 0 and 1 as output
   ;	    _asm mov dx,0B810h
   ;	
 	mov	 dx,0B810h
   ;	
   ;	    _asm mov eax,3;
   ;	
 	mov	 eax,3
   ;	
   ;	    _asm db  066h
   ;	
 	db	  066h
   ;	
   ;		_asm db  0EFh
   ;	
 	db	  0EFh
   ;	
   ;	
   ;	    _asm xor ebx,ebx
   ;	
 	xor	 ebx,ebx
@1@170:
   ;	
   ;	start:
   ;	
   ;	    // Write port 0
   ;	    _asm mov dx,0B800h
   ;	
 	mov	 dx,0B800h
   ;	
   ;		_asm mov eax,ebx
   ;	
 	mov	 eax,ebx
   ;	
   ;	    _asm not eax
   ;	
 	not	 eax
   ;	
   ;	    _asm db  066h
   ;	
 	db	  066h
   ;	
   ;		_asm db  0EFh
   ;	
 	db	  0EFh
   ;	
   ;	
   ;	    // Read port 2
   ;	    _asm mov dx,0B808h
   ;	
 	mov	 dx,0B808h
   ;	
   ;		_asm db  066h
   ;	
 	db	  066h
   ;	
   ;		_asm db  0EDh
   ;	
 	db	  0EDh
   ;	
   ;	
   ;	    // With our test adaptor, it have to be the same
   ;	    _asm not eax
   ;	
 	not	 eax
   ;	
   ;	    _asm cmp eax,ebx
   ;	
 	cmp	 eax,ebx
   ;	
   ;		_asm je short equal1
   ;	
	je	short @1@562
   ;	
   ;	
   ;	    _asm pusha
   ;	
 	pusha	
   ;	
   ;	    printf("dismatch (0x%08lx)\n", _EBX);
   ;	
	push	ebx
	push	offset DGROUP:s@
	call	near ptr _printf
	add	sp,6
   ;	
   ;	    _asm popa
   ;	
 	popa	
@1@562:
   ;	
   ;	equal1:
   ;	
   ;	    // Write port 1
   ;	    _asm mov dx,0B804h
   ;	
 	mov	 dx,0B804h
   ;	
   ;		_asm mov eax,ebx
   ;	
 	mov	 eax,ebx
   ;	
   ;	    _asm not eax
   ;	
 	not	 eax
   ;	
   ;	    _asm db  066h
   ;	
 	db	  066h
   ;	
   ;		_asm db  0EFh
   ;	
 	db	  0EFh
   ;	
   ;	
   ;	    // Read port 3
   ;	    _asm mov dx,0B80Ch
   ;	
 	mov	 dx,0B80Ch
   ;	
   ;		_asm db  066h
   ;	
 	db	  066h
   ;	
   ;		_asm db  0EDh
   ;	
 	db	  0EDh
   ;	
   ;	
   ;	    // With our test adaptor, it have to be the same
   ;	    _asm not eax
   ;	
 	not	 eax
   ;	
   ;	    _asm cmp eax,ebx
   ;	
 	cmp	 eax,ebx
   ;	
   ;		_asm je short equal2
   ;	
	je	short @1@954
   ;	
   ;	
   ;	    _asm pusha
   ;	
 	pusha	
   ;	
   ;	    printf("dismatch (0x%08lx)\n", _EBX);
   ;	
	push	ebx
	push	offset DGROUP:s@+20
	call	near ptr _printf
	add	sp,6
   ;	
   ;	    _asm popa
   ;	
 	popa	
@1@954:
   ;	
   ;	equal2:
   ;	
   ;	    // processing indication
   ;		_asm test ebx,large 0000FFFFFh
   ;	
 	test	 ebx,large 0000FFFFFh
   ;	
   ;		_asm jne short process
   ;	
	jne	short @1@1094
   ;	
   ;	    _asm pusha
   ;	
 	pusha	
   ;	
   ;	    printf("passing 0x%08lx\n", _EBX);
   ;	
	push	ebx
	push	offset DGROUP:s@+40
	call	near ptr _printf
	add	sp,6
   ;	
   ;	    _asm popa
   ;	
 	popa	
@1@1094:
   ;	
   ;	process:
   ;	
   ;	    _asm inc ebx
   ;	
 	inc	 ebx
   ;	
   ;	    _asm cmp ebx,000FFFFFFh
   ;	
 	cmp	 ebx,000FFFFFFh
   ;	
   ;	    _asm je  ende
   ;	
	je	short @1@1206
   ;	
   ;	    _asm jmp start
   ;	
	jmp	@1@170
@1@1206:
   ;	
   ;	ende:
   ;	    printf("Last ebx 0x%08lx\n", _EBX);
   ;	
	push	ebx
	push	offset DGROUP:s@+57
	call	near ptr _printf
	add	sp,6
   ;	
   ;	}
   ;	
	pop	bp
	ret	
_main	endp
	?debug	C E9
	?debug	C FA00000000
_TEXT	ends
_DATA	segment word public use16 'DATA'
s@	label	byte
	db	'dismatch (0x%08lx)'
	db	10
	db	0
	db	'dismatch (0x%08lx)'
	db	10
	db	0
	db	'passing 0x%08lx'
	db	10
	db	0
	db	'Last ebx 0x%08lx'
	db	10
	db	0
_DATA	ends
_TEXT	segment byte public use16 'CODE'
_TEXT	ends
	public	_main
	extrn	_printf:near
_s@	equ	s@
	end
