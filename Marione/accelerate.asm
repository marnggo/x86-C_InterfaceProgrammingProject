section .data
kmh_to_ms REAL4 0.27777778        ; 1000/3600

section .code
; void asm_compute_accel(float *in, int *out, int rows)
;
;   RCX = in pointer
;   RDX = out pointer
;   R8  = rows

asm_compute_accel:

    mov     r10, rcx          ; input
    mov     r11, rdx          ; output
    mov     r9,  r8           ; countre

    test    r9, r9
    jz      done

loop_start:

    ; load floats Vi, Vf, T
    movss   xmm0, DWORD PTR [r10]        ; Vi_kmh
    movss   xmm1, DWORD PTR [r10+4]      ; Vf_kmh
    movss   xmm2, DWORD PTR [r10+8]      ; T

    ; load km/h → m/s
    movss   xmm3, DWORD PTR [kmh_to_ms]

    ; convert to m/s
    mulss   xmm0, xmm3                   ; Vi_ms
    mulss   xmm1, xmm3                   ; Vf_ms

    ; delta_v = Vf_ms – Vi_ms
    subss   xmm1, xmm0

    ; divide by T
    divss   xmm1, xmm2                   ; acceleration (float)

    ; round to nearest int
    roundss xmm1, xmm1, 0

    ; float to int
    cvtss2si eax, xmm1

    ; store result
    mov     DWORD PTR [r11], eax

    ; advance pointers
    add     r10, 12                      ; 3 floats = 12 bytes
    add     r11, 4                       ; 1 int = 4 bytes

    dec     r9
    jnz     loop_start

done:
    ret

asm_compute_accel ENDP

END
