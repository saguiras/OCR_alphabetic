#ifndef NEURAL_TOOLS_H_
#define NEURAL_TOOLS_H_

# include "neural_network.h"
# include <stdio.h>
# include <stdlib.h>
# include <err.h>
# include "../CharDetection/CharDetection.h"

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

double Sigmoid(double x);

//The classical derivate of the sigmoid function
double Derivate_Sigmoid(double x);

//Return the position of the output with the greatest sigmoid result
int RetrievePos(struct Neural_Network *net);

//Calculates the Squared error
void SquaredError(struct Neural_Network *net);

//Retrive the position of the char in the goal tab
int PosGoal(double *goal);

//Retrive char from value val
char RetrieveChar(int val);

//Save data of the NN in 4 files:
//WeightIH - WeightHO - BiasH - BiasO
void SaveData(struct Neural_Network *net);

//Extract data previously saved in 4 files:
//WeightIH - WeightHO - BiasH - BiasO
struct Neural_Network* ExtractData ();
double *matrixFromFile(char *filename);
double *goalArray(char letter);
double **goalMatrix();
double **lettersMatrix(char x,char y);
int Learn_NN();
int launchOCR(SDL_Surface *img);
#endif
