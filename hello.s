BITS 64
org 0x401000

; All information about ELF file structure taken from
; https://en.wikipedia.org/wiki/Executable_and_Linkable_Format#File_header
elf_header:
	db 0x7f, "ELF"         ; header constant
	db 2                   ; 1 - 32-bit, 2 - 64-bit
	db 1                   ; 1 - little-endian, 2 - big-endian
	db 1                   ; version of ELF file, always has been 1
	db 0                   ; operating system ABI, 0 for Sytem V
	db 0                   ; further ABI information
	times 7 db 0           ; unused
	dw 2                   ; object file type: 2 - executable
	dw 0x3e                ; instruction set architecture: 0x3e for x86_64
	dd 1                   ; elf version
	dq _start              ; address of entry point
	dq program_header - $$ ; offset to program header
	dq 0                   ; seciton header offset
	dd 0                   ; flags dependent on architecture
	dw elf_header_size
	dw program_header_size
	dw 1                   ; program header table entries count
	dw 0                   ; size of section header entry
	dw 0                   ; number of entries in section header table
	dw 0                   ; index of section header table entry that contains section names

elf_header_size equ $ - elf_header

program_header:
	dd 1         ; program header type: 1 - loadable
	dd 5         ; flags
	dq 0         ; offset of segment in file
	dq $$        ; virtual address
	dq $$        ; phisical address
	dq file_size ; size of segment in file
	dq file_size ; size of segment in memory
	dq 0x1000    ; aligment

program_header_size equ $ - program_header

_start:
	; write(stdout, "hello, world\n", 14)
	mov rdi, 0
	mov rsi, hello
	mov rdx, 14
	mov rax, 1
	syscall

	; exit(0)
	mov rdi, 0
	mov rax, 60
	syscall

hello: db `hello, world!\n`

file_size equ $ - $$
