section .note.GNU-stack

section .text
global _start
extern init

_start:
	mov rdi, [rsp]
	lea rsi, [rsp+8]
	call init

	mov rax, 60
	mov rdi, 0
	syscall
