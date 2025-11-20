#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void asm_compute_accel(float *in, int *out, int rows);

// C reference for checking
void c_compute_accel(float *in, int *out, int rows) {
    const float factor = 0.27777778f;
    for (int i = 0; i < rows; i++) {
        float Vi = in[3*i + 0] * factor;
        float Vf = in[3*i + 1] * factor;
        float T  = in[3*i + 2];
        float acc = (Vf - Vi) / T;
        int rounded = (int)(acc + (acc >= 0 ? 0.5f : -0.5f));
        out[i] = rounded;
    }
}

// get current time
unsigned long long now_ns() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (unsigned long long)ts.tv_sec * 1000000000ULL + ts.tv_nsec;
}

int main() {

    int n;
    scanf("%d", &n);

    float *matrix = malloc(sizeof(float) * 3 * n);
    int   *out_c  = malloc(sizeof(int) * n);
    int   *out_asm = malloc(sizeof(int) * n);

    // read input
    for (int i = 0; i < n; i++) {
        scanf("%f , %f , %f",
              &matrix[3*i+0],
              &matrix[3*i+1],
              &matrix[3*i+2]);
    }

    // c
    c_compute_accel(matrix, out_c, n);

    // asm
    asm_compute_accel(matrix, out_asm, n);

    printf("Correctness Check:\n");
    for (int i = 0; i < n; i++) {
        printf("Row %d: C = %d   ASM = %d %s\n",
            i,
            out_c[i],
            out_asm[i],
            (out_c[i] == out_asm[i] ? "OK" : "MISMATCH"));
    }

    // benchmark
    const int runs = 30;
    // unsigned long long total_c = 0;
    unsigned long long total_asm = 0;

    for (int r = 0; r < runs; r++) {
        unsigned long long t0, t1;

        // t0 = now_ns();
        // c_compute_accel(matrix, out_c, n);
        // t1 = now_ns();
        // total_c += (t1 - t0);

        t0 = now_ns();
        asm_compute_accel(matrix, out_asm, n);
        t1 = now_ns();
        total_asm += (t1 - t0);
    }

    printf("\nBenchmark Results over %d runs:\n", runs);
    // printf("C average:    %.3f microseconds\n", total_c / 1000.0 / runs);
    printf("ASM average:  %.3f microseconds\n", total_asm / 1000.0 / runs);

    free(matrix);
    free(out_c);
    free(out_asm);

    return 0;
}
