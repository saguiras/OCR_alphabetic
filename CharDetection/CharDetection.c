# include <stdlib.h>
# include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
# include "../tools/tools.h"



void draw_ligne_W(SDL_Surface *img, int i)
{
    int w = img -> w;
    Uint32 pixel;

    for (int j = 0;j < w;j++)
    {
        pixel = SDL_MapRGB(img->format,255, 0, 0);
        put_pixel(img,j,i,pixel);
    }
}

void draw_ligne_H(SDL_Surface *img, int j,int f,int l)
{
    int h = img -> h;
    Uint32 pixel;

    for (int i = f; i < l ;i++)
    {
        pixel = SDL_MapRGB(img->format,255, 0, 0);
        put_pixel(img,j,i,pixel);
    }
}


void ligne_detect(SDL_Surface* img)
{
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int h = img->h;
    int w = img->w;
    int inligne = 0;

    for (int i = 0; i < h; i++)
    {
        if (!inligne)
        {
            for (int j = 0; j < w; j++)
            {
                pixel = get_pixel(img, j, i);
                SDL_GetRGB(pixel, img->format, &r, &g, &b);

                if (!r && !g && !b)
                {
                    if (i == 0) 
                    {
                        draw_ligne_W(img, i);
                    }
                    else
                    {
                        draw_ligne_W(img, i - 1);
                        inligne = 1;
                    }
                }

            }
        }
        if (inligne)
        {
            int j = 0;
            for (j = 0; j < w; j++)
            {
                pixel = get_pixel(img, j, i);
                SDL_GetRGB(pixel, img->format, &r, &g, &b);

                if (!r && !g && !b)
                {
                    break;
                }
            }
            if (j > w - 1)
            {
                inligne = 0;
                draw_ligne_W(img, i);
            }
        }
    }

}

void ligne_coord(SDL_Surface* img)
{
    /* Variables */
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int h = img->h;
    int i = 0;
    int firstligne;
    int lastligne;

    while (i < h)
    {
        pixel = get_pixel(img, 0, i);
        SDL_GetRGB(pixel, img->format, &r, &g, &b);

        //If there is a red line start cut
        if (r == 255 && b == 0 && g == 0)
        {
            firstligne = i+1;
            
             
            while (i < h-1)
            {
                pixel = get_pixel(img, 0, i+1);
                SDL_GetRGB(pixel, img->format, &r, &g, &b);

                
                if (r == 255 && b == 0 && g == 0)
                {
                    lastligne = i+1; 
                    cut_ligne(img, firstligne, lastligne);
                    break;
                }
                i++;
            }
            i++;
            
        }

        i++;
    }
}

void cut_ligne(SDL_Surface* img, int firstCut,int lastCut) 
{
    Uint32 pixel;
    /*SDL_Surface* copy = NULL;
    int w = img -> w;
    copy = SDL_CreateRGBSurface(SDL_HWSURFACE,
                              w,
                              lastCut - firstCut,
                              img -> format -> BitsPerPixel, 0, 0, 0, 0);
    for(int i = firstCut; i < lastCut ; i++)
    {
        for(int j = 0; j < w; j++)
        {
            pixel = get_pixel(img, j, i);
            put_pixel(copy, j, i, pixel);
        }
    }
  */
  char_Detect(img,firstCut,lastCut);
  //isolateChar(copy, net);
  //net -> str = concat(net -> str, "\n");
}


void char_Detect(SDL_Surface* img,int f,int l)
{
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int w = img->w;
    int inchar = 0; 
    
    for (int i = 0; i < w; i++)
    {
        if (!inchar)
        {   

            for (int j = f; j < l; j++)
            {
                pixel = get_pixel(img, i, j);
                SDL_GetRGB(pixel, img->format, &r, &g, &b);



                if (!r && !g && !b)
                {
                    
                    if (i == 0)
                    {
                        draw_ligne_H(img, i, f, l);
                        inchar = 1;
                    }
                    else
                    {
                        draw_ligne_H(img, i - 1, f, l);
                        inchar = 1;
                    }
                }
            }
        }
        if (inchar)
        {
            int j = f;
            for (j = f; j < l; j++)
            {
                pixel = get_pixel(img, i, j);
                SDL_GetRGB(pixel, img->format, &r, &g, &b);

                if (!r && !g && !b)
                {
                    break;
                }
            }
            if (j > l - 1)
            {
                inchar = 0;
                draw_ligne_H(img, i, f, l);
            }
            
        }
    }
}

void char_coord(SDL_Surface* img)
{
    /* Variables */
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int w = img->w;
    int i = 0;
    int firstLchar;
    int lastLchar;

    while (i < w)
    {
        pixel = get_pixel(img, i, 0);
        SDL_GetRGB(pixel, img->format, &r, &g, &b);

        //If there is a red line start cut
        if (r == 255 && b == 0 && g == 0)
        {
            firstLchar = i;
            r = 0;

            draw_ligne_H(img, i,i,i);
            while (r != 255 && b != 0 && g != 0)
            {
                
                pixel = get_pixel(img, i, 0);
                SDL_GetRGB(pixel, img->format, &r, &g, &b);

                //Detect the second line
                if (r == 255 && b == 0 && g == 0)
                {
                    lastLchar = i;

                    //Isolate into a surface the linecut
                    cut_char(img, firstLchar, lastLchar);
                }

                i++;
            }
        }

        i++;
    }
}

void cut_char(SDL_Surface* img, int firstCut,
    int lastCut)
{
    return;
}

