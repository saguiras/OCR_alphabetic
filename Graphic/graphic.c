#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

void main(){
	SDL_INIT(SDL_INIT_VIDEO);

	SDL_Window *window = NULL;
	window = SDL_CreateWindow("Optical Character Recognition (Graphic)",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,0);

	SDL_DELAY(5000);
	SDL_QUIT();

}