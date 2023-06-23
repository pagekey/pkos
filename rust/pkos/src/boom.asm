BITS 32

global _start

section .text

_start:
    ; Set up the stack
    mov esp, stack_end

    ; Call the Rust entrypoint function
    call rust_entrypoint

    ; Loop to prevent the program from exiting
kernel_loop:
    jmp kernel_loop

section .bss

stack_start:
    resb 16384 ; 16KB stack
stack_end:
