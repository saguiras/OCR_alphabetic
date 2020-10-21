# ifndef NEURAL_NETWORK_XOR_H_
# define NEURAL_NETWORK_XOR_H_
 
# include <SDL/SDL.h>
# include <err.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <math.h>


void XOR();
double sigmoid(double x);
double dSigmoid(double x);
double init_weight_biais();

# endif
