#include <stdio.h>  // printf();

void main(void)
{
    // Set port 0 and 1 as output
    _asm mov dx,0B810h
    _asm mov eax,3;
    _asm db  066h
	_asm db  0EFh

    _asm xor ebx,ebx
start:

    // Write port 0
    _asm mov dx,0B800h
	_asm mov eax,ebx
    _asm not eax
    _asm db  066h
	_asm db  0EFh

    // Read port 2
    _asm mov dx,0B808h
	_asm db  066h
	_asm db  0EDh

    // With our test adaptor, it have to be the same
    _asm not eax
    _asm cmp eax,ebx
	_asm je short equal1

    _asm pusha
    printf("dismatch (0x%08lx)\n", _EBX);
    _asm popa
equal1:

    // Write port 1
    _asm mov dx,0B804h
	_asm mov eax,ebx
    _asm not eax
    _asm db  066h
	_asm db  0EFh

    // Read port 3
    _asm mov dx,0B80Ch
	_asm db  066h
	_asm db  0EDh

    // With our test adaptor, it have to be the same
    _asm not eax
    _asm cmp eax,ebx
	_asm je short equal2

    _asm pusha
    printf("dismatch (0x%08lx)\n", _EBX);
    _asm popa
equal2:

    // processing indication
	_asm test ebx,large 0000FFFFFh
	_asm jne short process
    _asm pusha
    printf("passing 0x%08lx\n", _EBX);
    _asm popa
process:

    _asm inc ebx
    _asm cmp ebx,000FFFFFFh
    _asm je  ende
    _asm jmp start
ende:
    printf("Last ebx 0x%08lx\n", _EBX);
}