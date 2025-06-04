; boot.asm - simple bootloader that prints "Hello, bootloader!" and loops forever

BITS 16                  ; 16-bit code for bootloader
ORG 0x7C00               ; BIOS loads boot sector at 0x7C00

start:
    mov si, message      ; Load message address into SI

print_loop:
    lodsb                ; Load byte at DS:SI into AL and increment SI
    cmp al, 0            ; Check for null terminator
    je hang              ; If zero, jump to hang

    mov ah, 0x0E         ; BIOS teletype function
    mov bh, 0x00         ; Page number
    mov bl, 0x07         ; Text attribute (light gray on black)
    int 0x10             ; Call BIOS video interrupt

    jmp print_loop       ; Repeat for next character

hang:
    cli                  ; Clear interrupts
    hlt                  ; Halt CPU
    jmp hang             ; Infinite loop

message:
    db "Hello, bootloader!", 0

times 510-($-$$) db 0    ; Pad with zeros to 510 bytes
dw 0xAA55                ; Boot sector signature (must be last two bytes)
