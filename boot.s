section .multiboot
align 4
    dd 0x1BADB002                           ; Multiboot magic
    dd 0x00000003                           ; Flags: page-align + memory map
    dd -(0x1BADB002 + 0x00000003)           ; Checksum

section .text
global _start
extern kmain

_start:
    mov esp, stack_top
    push 0
    popf                    ; Clear EFLAGS
    push ebx                ; Multiboot info struct pointer
    push eax                ; Multiboot magic number
    call kmain
    cli
.hang:
    hlt
    jmp .hang
