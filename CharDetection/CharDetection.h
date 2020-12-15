# ifndef CHARDETECTION_H_
# define CHARDETECTION_H_

# include <stdlib.h>
# include <stdio.h>
# include "SDL/SDL.h"
# include "SDL/SDL_image.h"
# include "../tools/tools.h"
# include "../neural_network/neural_network_char.h" 

void Initialisation_Data ();
void draw_ligne_H(SDL_Surface *img, int j,int f,int l);
void draw_ligne_W(SDL_Surface *img, int i);
void char_Detect(SDL_Surface* img,int f,int l);
SDL_Surface* increaseChar(SDL_Surface *img);
void ligne_detect(SDL_Surface *img);
void ligne_coord(SDL_Surface* img);
char* print_str();
SDL_Surface* resize_caract(SDL_Surface* img);



# endif
