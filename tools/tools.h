# ifndef TOOLS_H_
# define TOOLS_H_

# include <stdlib.h>
# include <SDL/SDL.h>

void update_surface(SDL_Surface* screen, SDL_Surface* image);

Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y);

void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);

# endif
