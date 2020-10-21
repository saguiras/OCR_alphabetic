#include "neural_network_XOR.h"
#include "../treatment/treatment.c"
# include <stdlib.h>
# include <SDL/SDL.h>


void Train_NtWork(SDL_Surface *img, int attempted){
	static const int nb_inputs = 900 ; // nb de pixels dans l image
	static const int nb_outputs = 92; //ASCII 126 - 33 peut etre 93
	static const int nb_hid = 2; // nb de niveaux caches commence par 2

	double hidLayer[nb_hid];
	double outLayer[nb_outputs];               //biais entree et sortie entre deuxieme hiden et sortie

	double hidenLayerBiais[nb_hid];            //On a 4 niveau donc 3 nvx de biais de transition si on veut plus de hidden layers il faut ajouter des vars de biais
	double outBiais[nb_outputs];             // les biais d entree et de sorti entre les hidden

	double hidBiais[nb_inputs][nb_hid];
	double outWeights[nb_hid][nb_outputs];

	//On se base sur le reseau de neurone SGD

	static const int numTrainingSets = 4;
	double training_inputs[numTrainingSets][numInputs] = { {0.0f,0.0f},{1.0f,0.0f},{0.0f,1.0f},{1.0f,1.0f} }; // pas compris ca 
	double training_outputs[numTrainingSets][numOutputs] = { {0.0f},{1.0f},{1.0f},{0.0f} };


	//On va se servir de sigmoid ici

	for (int i = 0; i < nb_hid; ++i)
	{
		double activ = hidenLayerBiais[i];
		for (int i = 0; i < nb_inputs; ++i)
		{
			activ += trai
		}
	}




}