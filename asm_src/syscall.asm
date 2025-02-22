section .note.GNU-stack

section .text
global read, write, open, mmap, fork, execve, exit, wait4, kill, getcwd, chdir, getuid, setuid

read:
	mov rax, 0
	syscall
	ret

write:
	mov rax, 1
	syscall
	ret

open:
	mov rax, 2
	syscall
	ret

mmap:
	mov rax, 9
	mov r10, rcx
	syscall
	ret

fork:
	mov rax, 57
	syscall
	ret

execve:
	mov rax, 59
	syscall
	ret

exit:
	mov rax, 60
	syscall
	ret

wait4:
	mov rax, 61
	xor r10, r10
	syscall
	ret

kill:
	mov rax, 62
	syscall
	ret

getcwd:
	mov rax, 79
	syscall
	ret

chdir:
	mov rax, 80
	syscall
	ret

getuid:
	mov rax, 102
	syscall
	ret

setuid:
	mov rax, 105
	syscall
	ret
