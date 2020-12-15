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
#include "Graphic/graphic.h"
#include "neural_network/neural_network.h"

void help()
{
    printf("commands : \n");
    printf("   --help                   To picture commands\n");
    printf("   --xor                    To show the neural network for the XOR function with 50000 try\n");
    printf("   --xor (int)              To show the neural network for the XOR function with (int) try\n");
    printf("   --img display            To display image\n");
    printf("   --img greyscale          apply greysclae to image\n");
    printf("   --img blur               apply blur to image\n");
    printf("   --img blacknwhite        apply blacknwhite to image\n");
    printf("   --img rmligne            remove long ligne to image\n");
    printf("   --img chardetect         detect char in image\n");
    printf("   --img contrast (float)   apply contrast to image with (float) factor\n");
    printf("   --img brightness (float) apply brightness to image with (float) factor\n\n");
    printf("   --img treatment (float1) (float2)  \n");
    printf("                            apply all treatment to image with contrast (float1) factor and \n");
    printf("                            brightness (float2) factor \n\n");
    printf("   --learn                  learn the neural network\n");
    printf("   --graphic                enter graphic mode\n");

}

int main(int argc, char** argv)
{
  
    if(argc > 1)// at least one argument
    {
        SDL_Surface* img;
        SDL_Surface* screen_surface;


        if (argc == 2)
        {
           if (!strcmp(argv[1], "help"))
            {
                help();
                return 0;
            }
           if (!strcmp(argv[1], "xor"))
            {
                XOR(50001);
                return 0;
            }
           if (!strcmp(argv[1], "learn"))
            {
                Learn_NN();
                return 0;
            }
            if (!strcmp(argv[1],"graphic"))
            {
                launch_menu();
                return 0;
            }

        }
        if(argc == 3 && !strcmp(argv[1], "xor") && isNumber(argv[2]))
        {
            XOR((int)strtol(argv[2], (char **)NULL, 10)+1);
            return 0;
        }
        if(argc == 3 && !strcmp(argv[1], "char"))
        {
            init_sdl();
            img = load_image(argv[2]);
            screen_surface = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);

            img = resize_caract(img);
            display_image(img);

            wait_for_keypressed();
            SDL_FreeSurface(img);
            SDL_FreeSurface(screen_surface);

            return 0;
        }
        if(argc == 4)
        {   
            init_sdl();

            img = load_image(argv[1]);
            screen_surface = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);


            if (!strcmp(argv[2], "contrast"))
            {
                display_image(img);
                wait_for_keypressed();
                
                Contrast(img, (float)atof(argv[3]));
                
                display_image(img);
                wait_for_keypressed();
                
                SDL_SaveBMP(img, "out.jpg"); 
                SDL_FreeSurface(img);
                SDL_FreeSurface(screen_surface);

                return 0;
            }

            if (!strcmp(argv[2], "brightness"))
            {
                display_image(img);
                wait_for_keypressed();

                Brightness(img, (float)atof(argv[3]));

                display_image(img);
                wait_for_keypressed();

                SDL_SaveBMP(img, "out.jpg");
                SDL_FreeSurface(img);
                SDL_FreeSurface(screen_surface);

                return 0;
            }

            else
            {
                printf("Unknown command.\n");
                return 1;
            }
        }
        if (argc == 3)
        {
            init_sdl();

            img = load_image(argv[1]);
            screen_surface = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);


            if (!strcmp(argv[2], "greyscale"))
            {
                display_image(img);
                wait_for_keypressed();

                greyscale(img);

                display_image(img);
                wait_for_keypressed();

                SDL_SaveBMP(img, "out.jpg");
                SDL_FreeSurface(img);
                SDL_FreeSurface(screen_surface);

                return 0;
            }
            if (!strcmp(argv[2], "blur"))
            {
                display_image(img);
                wait_for_keypressed();

                blur(img);

                display_image(img);
                wait_for_keypressed();

                SDL_SaveBMP(img, "out.jpg");
                SDL_FreeSurface(img);
                SDL_FreeSurface(screen_surface);

                return 0;
            }
            if (!strcmp(argv[2], "blacknwhite"))
            {
                display_image(img);
                wait_for_keypressed();

                blacknwhite(img);

                display_image(img);
                wait_for_keypressed();

                SDL_SaveBMP(img, "out.jpg");
                SDL_FreeSurface(img);
                SDL_FreeSurface(screen_surface);

                return 0;
            }
            if (!strcmp(argv[2], "rmligne"))
            {
                display_image(img);
                wait_for_keypressed();

                noligne_H(img); 
                noligne_W(img);

                display_image(img);
                wait_for_keypressed();

                SDL_SaveBMP(img, "out.jpg");
                SDL_FreeSurface(img);
                SDL_FreeSurface(screen_surface);

                return 0;
            }
            if (!strcmp(argv[2], "chardetect"))
            {
                display_image(img);
                wait_for_keypressed();

                ligne_detect(img);
                ligne_coord(img);

                display_image(img);
                wait_for_keypressed();

                SDL_SaveBMP(img, "out.jpg");
                SDL_FreeSurface(img);
                SDL_FreeSurface(screen_surface);

                return 0;
            }
            if (!strcmp(argv[2], "display"))
            {
                display_image(img);
                wait_for_keypressed();

                SDL_FreeSurface(img);
                SDL_FreeSurface(screen_surface);

                return 0;
            }
            if (!strcmp(argv[2], "l"))
            {
                struct Neural_Network *net = ExtractData();
                SDL_Surface* char_ = increaseChar(img);
                double *letter = create_matrix(char_);
                char res = DetectText(net, letter);
                char str[2] = "\0";
                str[0] = res;
                printf("-> %s\n",str);



                display_image(img);
                wait_for_keypressed();

                SDL_FreeSurface(img);
                SDL_FreeSurface(screen_surface);

                return 0;
            }
            if (!strcmp(argv[2], "ocr"))
            {

                printf("%s",launchOCR(img));

                display_image(img);
                wait_for_keypressed();

                SDL_FreeSurface(img);
                SDL_FreeSurface(screen_surface);

                return 0;
            }




            printf("Unknown command.\n");
            return 1;
        }
        if (argc == 5)
        {
            init_sdl();

            img = load_image(argv[1]);
            screen_surface = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);


            if (!strcmp(argv[2], "treatment"))
            {
                display_image(img);
                wait_for_keypressed();

                greyscale(img);

                display_image(img);
                wait_for_keypressed();

                Contrast(img,(float)atof(argv[3]));

                display_image(img);
                wait_for_keypressed();

                blur(img);

                display_image(img);
                wait_for_keypressed();

                Brightness(img,(float)atof(argv[4]));

                display_image(img);
                wait_for_keypressed();

                blacknwhite(img);

                display_image(img);
                wait_for_keypressed();

                noligne_H(img);
                noligne_W(img);

                display_image(img);
                wait_for_keypressed();


                SDL_SaveBMP(img, "out.jpg");
                SDL_FreeSurface(img);
                SDL_FreeSurface(screen_surface);        

                return 0;
            }

            printf("Unknown command.\n");
            return 1;
        }

        printf("Unknown command.\n");
        return 1;
    
    }
    else
    {
         printf("'./main' needs at least one argument.\n");
         return 1;

    }
}
