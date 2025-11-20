section .data
    align 4
    kmh_to_ms: dd 0.27777778        ; constant

section .text
    global asm_compute_accel

; void asm_compute_accel(float *in, int *out, int rows)
; RCX = in pointer
; RDX = out pointer
; R8  = rows

asm_compute_accel:

    mov     r10, rcx          ; input
    mov     r11, rdx          ; output
    mov     r9,  r8           ; countre

    test    r9, r9
    jz      done

loop_start:

    ; load Vi, Vf, T
    movss   xmm0, [r10]           ; Vi_kmh
    movss   xmm1, [r10 + 4]       ; Vf_kmh
    movss   xmm2, [r10 + 8]       ; T

    ; load conversion
    movss   xmm3, [rel kmh_to_ms]

    ; convert both to m/s
    mulss   xmm0, xmm3            ; Vi_ms
    mulss   xmm1, xmm3            ; Vf_ms

    ; delta_v = Vf_ms - Vi_ms
    subss   xmm1, xmm0

    ; compute acceleration
    divss   xmm1, xmm2

    ; round to nearest integer
    roundss xmm1, xmm1, 0

    ; convert float
    cvtss2si eax, xmm1

    ; store result
    mov     [r11], eax

    ; advance pointers
    add     r10, 12               ; next input row
    add     r11, 4                ; next output int

    dec     r9
    jnz     loop_start

done:
    ret