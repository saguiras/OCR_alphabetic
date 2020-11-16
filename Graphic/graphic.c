#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

void window(){
	SDL_INIT(SDL_INIT_VIDEO);

	SDL_Window *window = NULL;
	window = SDL_CreateWindow("Optical Character Recognition (Graphic)",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,0);

	SDL_Renderer *renderer = NULL;
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_SOFTWARE);

	SDL_bool launched = SDL_True;

	while(launched){
		SDL_Event event;

		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
				     launched = SDL_False;
				     break;
				default:
				     break;
			}
		}
	}

	SDL_RenderPresent(renderer);
	

	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_QUIT();

}