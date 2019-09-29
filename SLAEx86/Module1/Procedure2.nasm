; Filename: Procedure.nasm
; Author: yunaranyancat

global _start

section .text

HelloWorldProc:
	
	push ebp
	mov ebp, esp

	; print hello world using write syscall

	mov eax, 0x4
	mov ebx, 1
	mov ecx, message
	mov edx, mlen
	int 0x80
	
	; mov esp, ebp
	; pop ebp

	leave
	ret	; signifies end of procedure


_start:

	mov ecx, 0x10


PrintHelloWorld:

	; preserve registers and flags
	pushad
	pushfd
	
	call HelloWorldProc
	
	; restore registers and stack
	
	popfd
	popad
	
	
	loop PrintHelloWorld

	mov eax, 1
	mov ebx, 10 ; sys_exit syscall
	int 0x80

section .data

	message:	db	"Hello World! "
	mlen	equ $-message
