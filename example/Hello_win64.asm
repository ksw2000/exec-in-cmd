;-------------------------------------------------------------------
; Assemble by pressing f12 (Automatically)
; nasm -f win64 Hello_win64.asm -o out/Hello_win64.obj
;
; Link by gcc (Manually)
; cd out & gcc Hello_win64.obj -o Hello_win64.exe & Hello_win64.exe
;--------------------------------------------------------------------
    extern printf
    global main
section .data
    msg db  "Hello world!"
section .text
main:
    mov rcx, msg
    sub rsp, 32
    call printf
    add rsp, 32
    ret
