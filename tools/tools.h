# ifndef TOOLS_H_
# define TOOLS_H_

# include <stdlib.h>
# include <SDL/SDL.h>

void update_surface(SDL_Surface* screen, SDL_Surface* image);

Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y);

void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);

void array_swap(int array[], size_t i, size_t j);

void array_select_sort(int array[], size_t len);

int isNumber(char s[]);

# endif
