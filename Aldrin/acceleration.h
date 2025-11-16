#ifndef ACCELERATION_H
#define ACCELERATION_H

// Function prototype for assembly function
// Computes acceleration for multiple cars
// Parameters:
//   matrix: pointer to float array (Y x 3 matrix: Vi, Vf, T for each car)
//   acceleration: pointer to int array for output
//   num_cars: number of cars (Y)
extern void compute_acceleration(float *matrix, int *acceleration, int num_cars);

#endif // ACCELERATION_H