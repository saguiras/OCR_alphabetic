# ifndef TREATMENT_H_
# define TREATMENT_H_

# include <stdlib.h>
# include <SDL/SDL.h>
# include "SDL/SDL_image.h"
# include "../tools/tools.h"

void greyscale(SDL_Surface *img);
void blur(SDL_Surface *img);
void Brightness(SDL_Surface *img, float factor);
void Contrast(SDL_Surface *img, float factor);
void draw_Whit_W(SDL_Surface *img,int x,int y, int j);
void draw_whit_H(SDL_Surface *img, int x,int y,int i);
void noligne_H(SDL_Surface *img);
void noligne_W(SDL_Surface *img);

void blacknwhite(SDL_Surface *img);

# endif
