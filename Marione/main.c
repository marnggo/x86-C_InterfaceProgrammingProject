#include <stdio.h>
#include <stdlib.h>

extern void asm_compute_accel(float *in, int *out, int rows);

int main(void) {
    int n;

    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid number of rows.\n");
        return 1;
    }

    // memory allocation
    float *matrix = (float *)malloc(sizeof(float) * 3 * n);
    int   *outbuf = (int   *)malloc(sizeof(int)   * n);

    if (!matrix || !outbuf) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(matrix);
        free(outbuf);
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        float vi, vf, t;
        // read comma or space separated values
        if (scanf(" %f , %f , %f", &vi, &vf, &t) != 3) {
            if (scanf(" %f %f %f", &vi, &vf, &t) != 3) {
                fprintf(stderr, "Error reading row %d.\n", i + 1);
                free(matrix);
                free(outbuf);
                return 1;
            }
        }
        matrix[3*i + 0] = vi;
        matrix[3*i + 1] = vf;
        matrix[3*i + 2] = t;
    }

    // call func
    asm_compute_accel(matrix, outbuf, n);

    for (int i = 0; i < n; ++i) {
        printf("%d\n", outbuf[i]);
    }

    free(matrix);
    free(outbuf);
    return 0;
}
