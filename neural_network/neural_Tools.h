#ifndef NEURAL_TOOLS_H_
#define NEURAL_TOOLS_H_

#include <stdio.h>
#include <stdlib.h>

// Matrix object declaration
struct Matrix
{
        // Size of the matrix
        int rows;
        int columns;

        // Pointer to the matrix
        double *mat;
};


void ChangeMatrix(struct Matrix matrix, int x, int y, float val);
double NavMatrix(struct Matrix matrix, int x, int y);
void InitMatrix(struct Matrix matrix);
void InitMatrixZero(struct Matrix matrix);
struct Matrix CreateMatrix(int rows, int colums);
void PrintMatrix(struct Matrix matrix);

double Random();

#endif
