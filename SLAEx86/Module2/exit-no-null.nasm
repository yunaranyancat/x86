; Filename: exit.nasm
; Author : yunaranyancat

global _start

section .text
_start:

	xor eax, eax
	mov al, 1
	xor ebx, ebx
	; mov bl, 10 if we want to return 10 as exit but normally we will return 0
	int 0x80
