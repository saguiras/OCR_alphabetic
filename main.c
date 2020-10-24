#include <string.h>
#include <stdio.h>
#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "tools/tools.h"
#include "treatment/treatment.h"
#include "CharDetection/CharDetection.h"
#include "neural_network/neural_network_XOR.h" 
#include "tools/display_tools.h"


int main()
{
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;

    // Initialize the SDL
    init_sdl();
 
    image_surface = load_image("my_image.jpg");
    screen_surface = SDL_SetVideoMode(image_surface->w, image_surface->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);

    // Display the image.

    // Wait for a key to be pressed.
     display_image(image_surface);

    wait_for_keypressed();
 
    greyscale(image_surface);

     display_image(image_surface);

    wait_for_keypressed();
   



    Contrast(image_surface, 0.8f );



    blur(image_surface);

    display_image(image_surface);

    wait_for_keypressed();
    Brightness(image_surface, 1.1f);


 
     display_image(image_surface);

    wait_for_keypressed();



    blacknwhite(image_surface);

    display_image(image_surface);

    wait_for_keypressed();

    noligne_H(image_surface);
    noligne_W(image_surface);

    ligne_detect(image_surface);
   




    ligne_coord(image_surface);

    display_image(image_surface);

    wait_for_keypressed();
    
    XOR(50000);   
    // Free the image surface.
    SDL_FreeSurface(image_surface);

    // Free the screen surface.
    SDL_FreeSurface(screen_surface);



    return 0;
}

