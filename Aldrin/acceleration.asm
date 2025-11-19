section .data
    align 4
    const_1000: dd 1000.0    ; For KM/H to M/H conversion
    const_3600: dd 3600.0    ; For M/H to M/S conversion

section .text
    global compute_acceleration

; Function: compute_acceleration
; Parameters (Microsoft x64 calling convention for Windows):
;   rcx: float *matrix (pointer to input matrix)
;   rdx: int *acceleration (pointer to output array)
;   r8:  int num_cars (number of cars)
;
; Formula: acceleration = (Vf - Vi) / T
; Where velocities need to be converted from KM/H to M/S:
; M/S = (KM/H * 1000) / 3600

compute_acceleration:
    push rbp
    mov rbp, rsp
    push rbx
    sub rsp, 32                 ; Shadow space for Windows x64
    
    ; Check if num_cars is 0
    test r8, r8
    jz .done
    
    mov r9, r8                  ; r9 = counter (num_cars)
    xor rbx, rbx                ; rbx = index for matrix (will increment by 12 bytes)
    xor r10, r10                ; r10 = index for output (will increment by 4 bytes)
    
    ; Load constants
    movss xmm6, [rel const_1000]
    movss xmm7, [rel const_3600]
    
.loop:
    ; Load Vi (initial velocity) at matrix[rbx]
    movss xmm0, [rcx + rbx]
    
    ; Load Vf (final velocity) at matrix[rbx + 4]
    movss xmm1, [rcx + rbx + 4]
    
    ; Load T (time) at matrix[rbx + 8]
    movss xmm2, [rcx + rbx + 8]
    
    ; Convert Vi from KM/H to M/S: Vi_ms = Vi / 3.6
    ; (KM/H * 1000m/km) / (3600s/h) = KM/H / 3.6
    movss xmm3, xmm0            ; Copy Vi
    mulss xmm3, xmm6            ; Vi * 1000
    divss xmm3, xmm7            ; (Vi * 1000) / 3600 = Vi_ms
    
    ; Convert Vf from KM/H to M/S: Vf_ms = Vf / 3.6
    movss xmm4, xmm1            ; Copy Vf
    mulss xmm4, xmm6            ; Vf * 1000
    divss xmm4, xmm7            ; (Vf * 1000) / 3600 = Vf_ms
    
    ; Calculate acceleration = (Vf_ms - Vi_ms) / T
    subss xmm4, xmm3            ; Vf_ms - Vi_ms
    divss xmm4, xmm2            ; (Vf_ms - Vi_ms) / T
    
    ; Convert float to integer (rounds towards zero/truncates)
    cvtss2si eax, xmm4          ; Convert to integer
    
    ; Store result
    mov [rdx + r10], eax
    
    ; Increment indices
    add rbx, 12                 ; Move to next row (3 floats * 4 bytes)
    add r10, 4                  ; Move to next output position (1 int * 4 bytes)
    
    ; Decrement counter and loop
    dec r9
    jnz .loop
    
.done:
    add rsp, 32
    pop rbx
    pop rbp
    ret