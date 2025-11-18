#include <stdio.h>
#include <stdlib.h>
#include "acceleration.h"

int main() {
    int num_cars;
    
    // Read number of cars
    printf("Enter number of cars: ");
    if (scanf("%d", &num_cars) != 1 || num_cars <= 0) {
        fprintf(stderr, "Invalid number of cars\n");
        return 1;
    }
    
    // Allocate memory for input matrix (Y x 3)
    float *matrix = (float *)malloc(num_cars * 3 * sizeof(float));
    if (matrix == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Allocate memory for output (acceleration values)
    int *acceleration = (int *)malloc(num_cars * sizeof(int));
    if (acceleration == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(matrix);
        return 1;
    }
    
    // Read input matrix
    printf("Enter matrix data (Initial_Velocity, Final_Velocity, Time for each car):\n");
    for (int i = 0; i < num_cars; i++) {
        // Read three values per row with commas
        if (scanf("%f, %f, %f", &matrix[i*3], &matrix[i*3 + 1], &matrix[i*3 + 2]) != 3) {
            fprintf(stderr, "Invalid input format. Use: value1, value2, value3\n");
            free(matrix);
            free(acceleration);
            return 1;
        }
    }
    
    // Call assembly function to compute acceleration
    compute_acceleration(matrix, acceleration, num_cars);
    
    // Print results
    printf("\nOutput (Acceleration in m/s^2):\n");
    for (int i = 0; i < num_cars; i++) {
        printf("%d\n", acceleration[i]);
    }
    
    // Free allocated memory
    free(matrix);
    free(acceleration);
    
    return 0;
}