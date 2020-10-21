#include "neural_network_XOR.h"
#include "../treatment/treatment.c"
# include <stdlib.h>
# include <SDL/SDL.h>
# include <math.h>

double sigmoid(double x){                 //tools functions
	return (1/(1 + (exp(-x))));
}

double dSigmoid(double x){
	return x*(1-x);
}

double init_weight_biais(){
	return ((double) rand())/((double) RAND_MAX);
}

void XOR(){
	int epochs = 10000;
	static const int numTrainingSets = 4;

	static const int numInputs = 2 ; // nb of pixels in the image (16*16)
	static const int numHiddenNodes = 2; //ASCII 
	static const int numOutputs = 1; // nb of hiddens level

	double hiddenLayer[numHiddenNodes];
	double outputLayer[numOutputs];        //biais entree et sortie entre deuxieme hiden et sortie

	double hidenLayerBias[numHiddenNodes];            //On a 4 niveau donc 3 nvx de biais de transition si on veut plus de hidden layers il faut ajouter des vars de biais
	double outLayerBias[numOutputs];            // les biais d entree et de sorti entre les hidden

	double hiddenWeights[numInputs][numHiddenNodes];
	double outputWeights[numHiddenNodes][numOutputs];

	//On se base sur le reseau de neurone SGD

	double training_inputs[numTrainingSets][numInputs] = { {0.0f,0.0f},{1.0f,0.0f},{0.0f,1.0f},{1.0f,1.0f} }; // pas compris ca 
	double training_outputs[numTrainingSets][numOutputs] = { {0.0f},{1.0f},{1.0f},{0.0f} };


	//On va se servir de sigmoid ici

	for (int n=0; n< epochs ; n++)
	{
		int trainingSetOrder[] = {0,1,2,3};
		shuffle(trainingSetOrder, numTrainingSets);

		for ( int x=0; x<numTrainingSets; x++){
			int i = trainingSetOrder[x];
			for (int j=0; j<numHiddenNodes; j++){
				double activation=hidenLayerBias[j];
				for (int k=0; k<numInputs; k++){
					activation+=training_inputs[i][k]*hiddenWeights[k][j];
				}
				hiddenLayer[j] = sigmoid(activation);
			}
			for (int j=0; j<numOutputs; j++) {
				double activation=outputLayersBias[j];
				for (int k=0; k<numHiddenNodes; k++){
					activation+=hiddenLayer[k]*outputWeights[k][j];
				}
				outputLayer[j] = sigmoid(activation);
			}
			double deltaOutput[numOutputs];
			for (int j=0; j<numOutputs; j++){
				double dError = (training_outputs[i][j]-outputLayer[j]);
				deltaOutput[j] = dError*dSigmoid(outputLayer[j]);
			}
			double deltaHidden[numHiddenNodes];
			for (int j=0; j<numHiddenNodes; j++){
				double dError = 0.0f;
				for(int k=0; k<numOutputs; k++){
					dError+=deltaOutput[k]*outputWeights[j][k];
				}
				deltaHidden[j] = dError*dSigmoid(hiddenLayer[j]);
			}
			for(int j =0; j<numOutputs; j++){
				outputLayerBias[j] += deltaOutput[j]*lr;
				for (int k=0; k<numHiddenNodes; k++){
					outputWeights[k][j]+=hiddenLayer[k]*deltaOutput[j]*lr;
				}
			}
			for (int j=0; j<numHiddenNodes; j++){
				hiddenLayerBias[j] += deltaHidden[j]*lr;
				for(int k=0; k<numInputs; k++){
					hiddenWeights[k][j]+=training_inputs[i][k]*deltaHidden[j]*lr;
				}
			}
		}
	}
}
		
