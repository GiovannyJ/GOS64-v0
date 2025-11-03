global long_mode_start
extern kernel_main
extern handle_keyboard_input

section .text
bits 64
long_mode_start:
    ; Load null into all data segment registers
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call initialize_keyboard
    call kernel_main
    hlt

keyboard_isr:
    ; Save all caller-saved registers that the C function might clobber
    push rax
    push rcx
    push rdx
    push rsi
    push rdi
    push r8
    push r9
    push r10
    push r11

    in al, 0x60                ; Read scan code from keyboard
    
    ; Move scan code (in AL) into RDI as the first C function argument
    ; We use movzx to zero-extend the 8-bit value into the 64-bit register
    movzx rdi, al              
    
    call handle_keyboard_input ; Call the C handler

    mov al, 0x20
    out 0x20, al               ; Send EOI to PIC

    ; Restore all saved registers
    pop r11
    pop r10
    pop r9
    pop r8
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rax

    iretq

initialize_keyboard:
    ; Remap PIC IRQ1 (keyboard) to interrupt vector 0x21
    mov al, 0x11        ; ICW1: Initialize PIC
    out 0x20, al        ; Send ICW1 to master PIC
    out 0xA0, al        ; Send ICW1 to slave PIC

    mov al, 0x20        ; ICW2: Master PIC offset (interrupt vector 0x20)
    out 0x21, al
    mov al, 0x28        ; ICW2: Slave PIC offset (interrupt vector 0x28)
    out 0xA1, al

    mov al, 0x04        ; ICW3: Tell master PIC about slave PIC at IRQ2
    out 0x21, al
    mov al, 0x02        ; ICW3: Tell slave PIC its cascade identity
    out 0xA1, al

    mov al, 0x01        ; ICW4: Set PIC to 8086 mode
    out 0x21, al
    out 0xA1, al
    
    ;Mask all interrupts on slave PIC
    mov al, 0xFF
    out 0xA1, al

    ;Enable only IRQ1 (keyboard) on master PIC
    mov al, 0xFD        ; 1111 1101 (unmask bit 1)
    out 0x21, al


    ; Set up the keyboard entry in the IDT
    call setup_keyboard_idt

    ; Load IDT
    lidt [idt_descriptor]

    ; Enable interrupts
    sti

    ret

setup_keyboard_idt:
    mov rax, keyboard_isr              ; ISR address

    ;Calc correct IDT entry address == idt_base + (vector * 16)
    mov rbx, keyboard_interrupt_vector ; rbx = 0x21
    shl rbx, 4                         ; <-- FIXED: Removed extra comma
    mov rcx, idt                       ; rcx = base of IDT
    add rcx, rbx                       ; rcx = address of IDT entry 0x21

    mov word [rcx], ax                 ; Low 16 bits of ISR address
    mov word [rcx + 2], 0x08           ; Code segment selector
    mov byte [rcx + 4], 0              ; Reserved
    mov byte [rcx + 5], 0x8E           ; Present, DPL=00, interrupt gate
    shr rax, 16
    mov word [rcx + 6], ax             ; Middle 16 bits
    shr rax, 16
    mov dword [rcx + 8], eax           ; Upper 32 bits

    ret

section .data
; IDT Descriptor
idt_descriptor:
    dw idt_end - idt - 1      ; Limit (size of IDT - 1)
    dq idt                    ; Base address of IDT


; Keyboard Interrupt Vector
keyboard_interrupt_vector equ 0x21

section .bss
    align 4096                ; align IDT w 4k page boundry

idt:
    times 256 dq 0, 0
idt_end:
