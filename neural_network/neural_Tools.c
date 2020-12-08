#include "neural_Tools.h"

int CheckCoord(struct Matrix matrix, int x, int y);

// Create a matrix; return the matrix
struct Matrix CreateMatrix(int rows, int columns)
{
	struct Matrix matrix;
       	
	matrix.rows = rows;
	matrix.columns = columns;

	matrix.mat = malloc(sizeof(double)*columns*rows);

	return matrix;
}

// Testing if given coordinates are correct
int CheckCoord(struct Matrix matrix, int x, int y)
{
	return (x < matrix.rows &&  y < matrix.columns); 
}


// Function to navigate in the matrix; return matrix(x, y)
double NavMatrix(struct Matrix matrix, int x, int y)
{
	if (!CheckCoord(matrix, x, y))
	{
		printf("====================\n");
		printf("Error in coordinates\n");
		printf("====================\n");
	}
	int index = x * matrix.columns + y;
	return *(matrix.mat + index);
}

// Function to change a value in a matrix
void ChangeMatrix(struct Matrix matrix, int x, int y, float val)
{
	if (!CheckCoord(matrix, x, y))
	{
		printf("====================\n");
                printf("Error in coordinates\n");
                printf("====================\n");
	}
        *(matrix.mat + x * matrix.columns + y) = val;
}

// Print the matrix
void PrintMatrix(struct Matrix matrix)
{
	for (int i = 0; i < matrix.rows; i++)
	{
		for(int j = 0; j < matrix.columns; j++)
		{
			printf("%f ", NavMatrix(matrix, i, j));
		}
		printf("\n");
	}
}

// Initialize the matrix with zeros
void InitMatrix(struct Matrix matrix)
{
	for (int i = 0; i < matrix.rows; i++)
        {
                for(int j = 0; j < matrix.columns; j++)
                {
                        ChangeMatrix(matrix, i, j, Random());
                }
        }    
}

void InitMatrixZero(struct Matrix matrix)
{
	for (int i = 0; i < matrix.rows; i++)
        {
                for(int j = 0; j < matrix.columns; j++)
                {
                        ChangeMatrix(matrix, i, j, 0);
                }
        }

}




/*double Random()
{
        return (double)rand()/(double)RAND_MAX;
} */

double Random()
{
    return ((double)rand()) / ((double)RAND_MAX / 2) - 1;
}

//The classical sigmoid function
double Sigmoid(double x)
{
  return(1.0 / (1.0 + exp(-x)));
}

//The classical derivate of the sigmoid function
double Derivate_Sigmoid(double x)
{
  return x * (1.0 - x);
}

//Return the position of the output with the greatest sigmoid result
int RetrievePos(struct Neural_Network *net)
{
  double max = 0;
  int posMax = 0;

  for (int o = 0; o < net -> nbOutput; o++)
  {
    if (max < net -> OutputO[o])
    {
      posMax = o;
      max = net -> OutputO[o];
    }
  }
  return posMax;
}

//Calculates the Squared error
void SquaredError(struct Neural_Network *net)
{
  double max = 0;
  double sum = 0;

  for (int o = 0; o < net -> nbOutput; o++)
  {
    if (max < net -> OutputO[o])
    {
      max = net -> OutputO[o];
    }
    sum += (net -> Goal[o] - net -> OutputO[o]) *
                      (net -> Goal[o] - net -> OutputO[o]);
  }
  net -> ErrorRate += 0.5 * sum;
}


//Retrive the position of the char in the goal tab
int PosGoal(double *goal)
{
  int count = 0;

  while(goal[count] != 1.0)
    count++;

  return count;
}

//Retrive char from value val
char RetrieveChar(int val)
{
  char c;

  if(val <= 25)
  {
    c = val + 65;
  }
  else if(val > 25 && val <= 51)
  {
    c = (val + 97 - 26);
  }
  else if(val > 51 && val <= 61)
  {
    c = val + 48 - 52;
  }
  else
  {
    switch(val)
    {
      case 62:
        c = ';';
        break;
      case 63:
        c = '\'';
        break;
      case 64:
        c = ':';
        break;
      case 65:
        c = '-';
        break;
      case 66:
        c = '.';
        break;
      case 67:
        c = '!';
        break;
      case 68:
        c = '?';
        break;
      case 69:
        c = '(';
        break;
      case 70:
        c = '\"';
        break;
      case 71:
        c = ')';
        break;
      default:
        exit(1);
        break;
    }
  }
  return c;
}

//Save data of the NN in 4 files:
//WeightIH - WeightHO - BiasH - BiasO
void SaveData(struct Neural_Network *net)
{
  FILE* weightIH = fopen("neural_network/save/weightIH.w", "w");
  for(int i = 0; i < net -> nbInput; ++i)
  {
    for(int h = 0; h < net -> nbHidden; ++h)
    {
      fprintf(weightIH, "%f\n", net -> WeightIH[i][h]);
    }
  }
  fclose(weightIH);

  FILE* weightHO = fopen("neural_network/save/weightHO.w", "w");
  for(int h = 0; h < net -> nbHidden; ++h)
  {
    for(int o = 0; o < net -> nbOutput; ++o)
    {
        fprintf(weightHO, "%f\n", net -> WeightHO[h][o]);
    }
  }
  fclose(weightHO);

  FILE* biasH = fopen("neural_network/save/biasH.b", "w");
  for(int h = 0; h < net -> nbHidden; ++h)
  {
    fprintf(biasH, "%f\n", net -> BiasH[h]);
  }
  fclose(biasH);

  FILE* biasO = fopen("neural_network/save/biasO.b", "w");
  for (int o = 0; o < net -> nbOutput; ++o)
  {
    fprintf(biasO, "%f\n", net -> BiasO[o]);
  }
  fclose(biasO);
}

//Extract data previously saved in 4 files:
//WeightIH - WeightHO - BiasH - BiasO
struct Neural_Network* ExtractData ()
{
  //CREATE NN
  struct Neural_Network *net = malloc(sizeof(struct Neural_Network));
  net -> nbInput = 28*28; //size of imgs
  net -> nbHidden = 20;
  net -> nbOutput = 52; //26*2 letters
  net -> str = malloc(sizeof(char)*1200);
  net -> str = "\0";

  int sizeMax = 15;
  char *line = calloc(15, sizeof(char));

  //WeightIH
  FILE* weightIH = fopen("neural_network/save/weightIH.w", "r");
  for(int i = 0; i < net -> nbInput; ++i)
  {
    for(int h = 0; h < net -> nbHidden; ++h)
    {
      fgets(line, sizeMax, weightIH);
      strtok(line, "\n");
      net -> WeightIH[i][h] = atof(line);
    }
  }
  fclose(weightIH);

  //Weight HO
  FILE* weightHO = fopen("neural_network/save/weightHO.w", "r");
  for(int h = 0; h < net -> nbHidden; ++h)
  {
    for(int o = 0; o < net -> nbOutput; ++o)
    {
        fgets(line, sizeMax, weightHO);
        strtok(line, "\n");
        net -> WeightHO[h][o] = atof(line);
    }
  }
  fclose(weightHO);

  //BiasH
  FILE* biasH = fopen("neural_network/save/biasH.b", "r");
  for(int h = 0; h < net -> nbHidden; ++h)
  {
    fgets(line, sizeMax, biasH);
    strtok(line, "\n");
    net -> BiasH[h] = atof(line);
  }
  fclose(biasH);

  //BiasO
  FILE* biasO = fopen("neural_network/save/biasO.b", "r");
  for (int o = 0; o < net -> nbOutput; ++o)
  {
    fgets(line, sizeMax, biasO);
    strtok(line, "\n");
    net -> BiasO[o] = atof(line);
  }
  fclose(biasO);

  return net;
}

double *matrixFromFile(char *filename)
{
  double *matrix = malloc(sizeof(double) * 28 * 28);
  FILE *file = fopen(filename,"r");

  if(file == NULL)
    printf("File is NULL \n");
  for(int i = 0; i <= 28; i++)
  {
    for(int j = 0; j <= 28; j++)
    {
      int c = fgetc(file);
      if(c == 49)
        matrix[j+i*28] = 1;
      if(c == 48)
        matrix[j+i*28] = 0;
    }
  }
  fclose(file);
  return matrix;
}

//Create & return the double* goals pixels values from filename
double *goalArray(char letter)
{
  double *goal = calloc(52, sizeof(double));

  if(letter >= 'A' && letter <= 'Z')
    goal[(int)(letter) - 65] = 1;

  else if(letter >= 'a' && letter <= 'z')
    goal[((int)(letter) - 97) + 26] = 1;

  return goal;
}

double **goalMatrix()
{
  double **goalMatrix = malloc(sizeof(double*) * 52);
  char maj = 'A';
  char min = 'a';
  for(int i = 0; i < 52; i++)
  {
    if(i < 26)
    {
      goalMatrix[i] = goalArray(maj);
      maj++;
    }
    else
    {
      goalMatrix[i] = goalArray(min);
      min++;
    }
  }
  return goalMatrix;
}

double **lettersMatrix()
{
  //Variables
  char majs_path[14] = "majs/0/00.txt\0";
  char mins_path[14] = "mins/0/00.txt\0";
  double **lettersMatrix = malloc(sizeof(double *) * 52);
  char maj = 'A';
  char min = 'a';
  char count = '4';

  for(int i = 0; i < 52; i++)
  {

    if(i < 26 * 1)
    {
      majs_path[5] = maj;
      majs_path[7] = maj;
      majs_path[8] = count;
      //printf("%s\n",majs_path);
      lettersMatrix[i] = matrixFromFile(majs_path);
      maj++;

    }
    else if(i >= 26*1)
    {
      count = '3';
      mins_path[5] = min;
      mins_path[7] = min;
      mins_path[8] = count;
      //printf("%s\n",mins_path);
      lettersMatrix[i] = matrixFromFile(mins_path);
      min++;

    }
  }
  return lettersMatrix;
}

//Colors for print
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KWHT  "\x1B[37m"


int Learn()
{
	//Variables
	int nbEpoch = 5000;
	int nbLetters = 26 * 1 + 26 * 1; //5 fonts for uppers & 4 for lowers
	int currentChar = 0;
	//int count = 0;
	srand(time(NULL));

	//Intialize network
	struct Neural_Network *net = InitializeNetwork();

	//Initialize all goals & letters
	double **goal = goalMatrix();
	double **letters = lettersMatrix();

	for (int epoch = 0; epoch < nbEpoch; epoch++)
	{
			currentChar = 0;
			for (int l = 0; l < nbLetters; l++)
			{

					Neural_Network_OCR(net, letters[l], goal[currentChar]);
          currentChar++;

                                        
					if (epoch % 100 == 0)
					{
                                             if (l == 0)
                                        {
                                            printf(" Found  | Expected \n");
                                        }

							PrintState(net);
					}
					//count++;
			}
			//== PRINT ERROR EVERY 100 EPOCHs ==//
			if (epoch % 100 == 0)
			{
					if(net -> MaxErrorRate > 0.005)
							printf("Epoch %-5d | MaxErrorRate = %s %f \n",
                    epoch,KRED,net->MaxErrorRate);
					else
					{
							printf("Epoch %-5d | MaxErrorRate = %s %f \n",
                      epoch,KGRN,net->MaxErrorRate);
							// canSave = 1;
					}
					printf("%s",KWHT);
			}
      if(net->MaxErrorRate<0.0005 && net->MaxErrorRate != 0.0)
      {
         break;
      }
			net -> MaxErrorRate = 0.0;
	}
  printf("Save data...\n");
	SaveData(net);
  printf("Learn finish\n");
	return EXIT_SUCCESS;
}
