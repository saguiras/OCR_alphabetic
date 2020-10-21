# ifndef CHARDETECTION_H_
# define CHARDETECTION_H_

# include <stdlib.h>
# include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
# include "../tools/tools.h"


void draw_ligne_H(SDL_Surface *img, int i);
void draw_ligne_W(SDL_Surface *img, int j);
void ligne_detect(SDL_Surface *img);
void ligne_coord(SDL_Surface* img);
void cut_ligne(SDL_Surface* img, int firstCut,int lastCut);
void char_coord(SDL_Surface* img);
void cut_char(SDL_Surface* img, int firstCut,int lastCut);
void char_Detect(SDL_Surface* timg, SDL_Surface* img,int f);


# endif
