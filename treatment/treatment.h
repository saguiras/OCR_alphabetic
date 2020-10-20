# ifndef TREATMENT_H_
# define TREATMENT_H_

# include <stdlib.h>
# include <SDL/SDL.h>
# include "SDL/SDL_image.h"
# include "../tools/tools.h"

void greyscale(SDL_Surface *img);
void Contrast(SDL_Surface *img, float factor);
void blacknwhite(SDL_Surface *img);

# endif
