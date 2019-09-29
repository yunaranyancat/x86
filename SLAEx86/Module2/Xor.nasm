; Name: Execve-Stack

global _start

section .text
_start:
	
	; PUSH NULL DWORD onto the stack
	xor eax, eax
	push eax

	; PUSH /bin//sh onto the stack (8 bytes)
	PUSH 0x68732f2f
	PUSH 0x6e69622f
	
	; Set up EBX to store address of bin/bash
	mov ebx,esp

	; Push NULL to the stack
	push eax

	mov edx, esp

	push ebx
	mov ecx, esp
	
	; SYSCALL

	mov al, 11
	int 0x80
