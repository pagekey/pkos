global _memcpy_asm

_memcpy_asm:
    mov edi, [esp+0x4] ; arg1: esp+0x4 dest
    mov esi, [esp+0x8] ; arg2: esp+0x8 src
    mov ecx, [esp+0xc] ; arg3: esp+0xc size
    rep movsb
    ret