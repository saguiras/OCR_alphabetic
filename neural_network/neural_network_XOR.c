# include "neural_network_XOR.h"
# include <stdlib.h>
# include <SDL/SDL.h>
# include <math.h>
# include "neural_Tools.h"

struct NeuralNetwork
{
//size neural network
	int nbInputs;
	int nbHidden;
	int nbOutputs;
	
        struct Matrix matInputValues;
	//expected outputs
	struct Matrix matAim;
	//input/hidden
	struct Matrix matWeightsIH;
	//hidden/output
	struct Matrix matWeightsHO;
	//biases of hidden
	struct Matrix matBiasH;
	//output hidden (after sum))
	struct Matrix matOutputH;
	//sum of weights * inputs
	struct Matrix matSumIH;
	//error values
	struct Matrix matErrors;
	struct Matrix matDerivatives;
	struct Matrix matGradientsHO;
	struct Matrix matGradientsIH;
	struct Matrix matGradientsB;
	struct Matrix matPreviousWeightsIH;
	struct Matrix matPreviousWeightsHO;
	struct Matrix matPreviousBiasH;

	//gradient Bias Output
        struct Matrix GradientBiasOutput;
	//bias of output neuron
        struct Matrix BiasO;
	//sum of weights * outputs of hidden 
	struct Matrix SumHOutputs;
	struct Matrix FinalOutput;
	struct Matrix DerivativeO;
	double LearningRate;
	double ConstanteUpdate;
	struct Matrix PreviousBiasO;
};


struct NeuralNetwork InitializeNetwork()
{
	struct NeuralNetwork net;
	
	net.nbInputs = 2;
	net.nbHidden = 2;
	net.nbOutputs = 1;

//initialise input
	net.matInputValues = CreateMatrix(8, 1);
	ChangeMatrix(net.matInputValues, 0, 0, 0);
	ChangeMatrix(net.matInputValues, 1, 0, 0);
	ChangeMatrix(net.matInputValues, 2, 0, 0);
	ChangeMatrix(net.matInputValues, 3, 0, 1);
	ChangeMatrix(net.matInputValues, 4, 0, 1);
	ChangeMatrix(net.matInputValues, 5, 0, 0);
	ChangeMatrix(net.matInputValues, 6, 0, 1);
	ChangeMatrix(net.matInputValues, 7, 0, 1);
		
//initialise error
	net.matErrors = CreateMatrix(8, 1);
	ChangeMatrix(net.matErrors, 0, 0, 1);
	ChangeMatrix(net.matErrors, 2, 0, 1);
	ChangeMatrix(net.matErrors, 4, 0, 1);
	ChangeMatrix(net.matErrors, 6, 0, 1);

//initialise aim
	net.matAim = CreateMatrix(8, 1);
	ChangeMatrix(net.matAim, 0, 0, 0);
	ChangeMatrix(net.matAim, 2, 0, 1);
	ChangeMatrix(net.matAim, 4, 0, 1);
        ChangeMatrix(net.matAim, 6, 0, 0);


	net.matWeightsIH = CreateMatrix(net.nbHidden, net.nbInputs);
	net.matWeightsHO = CreateMatrix(net.nbOutputs, net.nbHidden);
	net.matOutputH = CreateMatrix(net.nbHidden, 1);
	net.matBiasH = CreateMatrix(net.nbHidden, 1);
	net.matSumIH = CreateMatrix(net.nbHidden, 1);
	net.matDerivatives = CreateMatrix(net.nbHidden, 1);
	net.matPreviousWeightsIH = CreateMatrix(net.nbHidden, net.nbInputs);
	net.matPreviousWeightsHO = CreateMatrix(net.nbOutputs, net.nbHidden);
	net.matPreviousBiasH = CreateMatrix(net.nbHidden, 1);
	net.matGradientsIH = CreateMatrix(net.nbHidden, net.nbInputs);
	net.matGradientsHO = CreateMatrix(net.nbOutputs, net.nbHidden);
	net.matGradientsB = CreateMatrix(net.nbHidden, 1);


	net.BiasO = CreateMatrix(1, 1);
        net.SumHOutputs = CreateMatrix(1, 1);
	net.PreviousBiasO = CreateMatrix(1, 1);
	net.GradientBiasOutput = CreateMatrix(1, 1);
	net.SumHOutputs = CreateMatrix(1, 1);
 	net.FinalOutput = CreateMatrix(1, 1);
        net.DerivativeO = CreateMatrix(1, 1);

	ChangeMatrix(net.BiasO, 0, 0, Random());
	InitMatrix(net.matWeightsIH);
	InitMatrix(net.matWeightsHO);
	InitMatrix(net.matBiasH);
	InitMatrixZero(net.matPreviousWeightsHO);
	InitMatrixZero(net.matPreviousWeightsIH);
        InitMatrixZero(net.matPreviousBiasH);
	ChangeMatrix(net.SumHOutputs, 0, 0, 0.0);
	net.LearningRate = 1.414213562;
	net.ConstanteUpdate =  0.25;
	ChangeMatrix(net.PreviousBiasO, 0, 0, 0.0);
	return net;
}

double Sigmoid(double Sum)
{
	 return (1.0/(1.0 + exp(-Sum)));
}

void ForwardPass(struct NeuralNetwork net, int inpValues, int epoch)
{
	//calcul output of a neurone
	for (int h = 0; h < net.nbHidden; h++)
	{
		double SumIH = 0;
		for (int i = 0; i < net.nbInputs; i++)
		{
			SumIH += NavMatrix(net.matWeightsIH, h, i) *
			   NavMatrix(net.matInputValues, inpValues + i, 0);
		}
		SumIH += NavMatrix(net.matBiasH, h, 0);
		ChangeMatrix(net.matSumIH, h, 0, SumIH);
		ChangeMatrix(net.matOutputH, h, 0, Sigmoid(SumIH));
		
	}
	
	//same for hidden/output
	double SumHO = 0;
        for (int i = 0; i < net.nbHidden; i++)
        {
        	SumHO += NavMatrix(net.matWeightsHO, 0, i) *
                	 NavMatrix(net.matOutputH, i, 0);
        }
        SumHO += NavMatrix(net.BiasO, 0, 0);
        ChangeMatrix(net.SumHOutputs, 0, 0, SumHO);
        ChangeMatrix(net.FinalOutput, 0, 0, Sigmoid(SumHO));
	ChangeMatrix(net.matErrors, inpValues, 0,
			    NavMatrix(net.FinalOutput, 0, 0) -
			    NavMatrix(net.matAim, inpValues, 0));

	//print results every 1000 epoch (easiest)
	if (epoch % 1000 == 0)
        {
		if (inpValues == 0)
        	printf("\n");
                printf("|            %d ⊕  %d -> %f             |\n",
                        (int)NavMatrix(net.matInputValues, inpValues, 0),
                        (int)NavMatrix(net.matInputValues, inpValues + 1, 0),
                        NavMatrix(net.FinalOutput, 0, 0));
	}

}

void CalculateDerivative(struct NeuralNetwork net, int pattern)
{
	//initialise the derivative of output 
    	ChangeMatrix(net.DerivativeO, 0, 0, -(NavMatrix(net.matErrors,
				       	pattern, 0)*
			  exp(NavMatrix(net.SumHOutputs, 0, 0))) /
		    (pow((1 + exp(NavMatrix(net.SumHOutputs, 0, 0))), 2)));
    	for (int i = 0; i < net.nbHidden; i++)
    	{
        	//calculate the derivate of each
        	ChangeMatrix(net.matDerivatives, i, 0,
				(exp(NavMatrix(net.matSumIH, i, 0)) /
			pow((1 + exp(NavMatrix(net.matSumIH, i, 0))), 2)) *
				NavMatrix(net.matWeightsHO, 0, i) *
				(NavMatrix(net.DerivativeO, 0, 0)));
    	}
}


void CalculateGradient(struct NeuralNetwork net, int pattern)
{
	//initialise the weights input/hidden
    	for (int i = 0; i < net.nbInputs; i++)
    	{
        	for (int h = 0; h < net.nbHidden; h++)
        	{
            		ChangeMatrix(net.matGradientsIH, h, i,
			      Sigmoid(NavMatrix(net.matInputValues,
					      pattern + i, 0))*
			      NavMatrix(net.matDerivatives, h, 0));
        	}
	}
	
	//initialise the bias hidden/neurones
    	for (int h = 0; h < net.nbHidden; h++)
    	{
        	ChangeMatrix(net.matGradientsB, h, 0, Sigmoid(1) *
		       		NavMatrix(net.matDerivatives, h, 0));
    	}

	ChangeMatrix(net.GradientBiasOutput, 0, 0, Sigmoid(1) *
		       	(NavMatrix(net.DerivativeO, 0, 0)));

    	//initialise the weights hidden/output
    	for (int h = 0; h < net.nbHidden; h++)
    	{
        	ChangeMatrix(net.matGradientsHO, 0, h,
			       	Sigmoid(NavMatrix(net.matOutputH, h, 0)) *
		       		NavMatrix(net.DerivativeO, 0, 0));
    	}
}

void UpdateWeights(struct NeuralNetwork net) //training function
{
	//update weights input/ hidden 
	for (int h = 0; h < net.nbHidden; h++)
	{
		for (int i = 0; i < net.nbInputs; i++)
		{
			ChangeMatrix(net.matPreviousWeightsIH, h, i,
			    (net.LearningRate *
			    NavMatrix(net.matGradientsIH, h, i)) +
			    (net.ConstanteUpdate *
			     NavMatrix(net.matPreviousWeightsIH, h, i)));
			
			ChangeMatrix(net.matWeightsIH, h, i,
				(NavMatrix(net.matWeightsIH, h, i) +
				 NavMatrix(net.matPreviousWeightsIH, h, i)));
		}
	}

	//update weights hidden/output
	for (int h = 0; h < net.nbHidden; h++)
        {
        	ChangeMatrix(net.matPreviousWeightsHO, 0, h,
                            (net.LearningRate *
                            NavMatrix(net.matGradientsHO, 0, h)) +
                            (net.ConstanteUpdate *
                             NavMatrix(net.matPreviousWeightsHO, 0, h)));
                        
                ChangeMatrix(net.matWeightsHO, 0, h,
                            (NavMatrix(net.matWeightsHO, 0, h) +
                            NavMatrix(net.matPreviousWeightsHO, 0, h)));
        } 

	//update the biases of hidden 
	for (int h = 0; h < net.nbHidden; h++)
        {
                ChangeMatrix(net.matPreviousBiasH, h, 0,
                            (net.LearningRate *
                            NavMatrix(net.matGradientsB, h, 0)) +
                            (net.ConstanteUpdate *
                             NavMatrix(net.matPreviousBiasH, h, 0)));

                ChangeMatrix(net.matBiasH, h, 0,
                            (NavMatrix(net.matBiasH, h, 0) +
                            NavMatrix(net.matPreviousBiasH, h, 0)));
        }
	
	//update the bias of output
	ChangeMatrix(net.PreviousBiasO, 0, 0,
		       	(net.LearningRate *
			 NavMatrix(net.GradientBiasOutput, 0, 0)) +
			    (net.ConstanteUpdate *
			     NavMatrix(net.PreviousBiasO, 0, 0)));
	ChangeMatrix(net.BiasO, 0, 0, NavMatrix(net.BiasO, 0, 0)
		       	+ NavMatrix(net.PreviousBiasO, 0, 0));
}


void BackPropagation(struct NeuralNetwork net, int pattern)
{
    CalculateDerivative(net, pattern);
    CalculateGradient(net, pattern);
    UpdateWeights(net);
}

//function to train the neural network
void XOR(int epoch_)
{
	struct NeuralNetwork nettest = InitializeNetwork();
	for(int epoch = 0; epoch < epoch_; epoch++)
	{
                if (epoch % 1000 == 0)
                {
                    printf("\n");
                    printf("================= %d =====================",epoch);
                }

		for (int i = 0; i < 7; i += 2)
		{
			ForwardPass(nettest, i, epoch);
			BackPropagation(nettest, i);
		}

        }
}
