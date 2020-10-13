# ifndef TOOLS_H_
# define TOOLS_H_

# include <stdlib.h>
# include <SDL/SDL.h>

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);

void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);

# endif
