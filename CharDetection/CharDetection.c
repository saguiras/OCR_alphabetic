# include <stdlib.h>
# include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
# include "../tools/tools.h"



void draw_ligne_W(SDL_Surface *img, int i)      //function witch draws a horizontal line on the line i
{
    int w = img -> w;
    Uint32 pixel;

    for (int j = 0;j < w;j++)
    {
        pixel = SDL_MapRGB(img->format,255, 0, 0);
        put_pixel(img,j,i,pixel);
    }
}

void draw_ligne_H(SDL_Surface *img, int j,int f,int l) //function withc draws a vertical line from the pixel (j,f) to (j,l)
{
    Uint32 pixel;

    for (int i = f; i < l ;i++)
    {
        pixel = SDL_MapRGB(img->format,255, 0, 0);
        put_pixel(img,j,i,pixel);
    }
}


void ligne_detect(SDL_Surface* img) //line detection function
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

                if (!r && !g && !b) //if the pixel is black
                {
                    if (i == 0)  //if this is the first line we draw a horizontal line
                    {
                        draw_ligne_W(img, i);
                    }
                    else
                    {
                        draw_ligne_W(img, i - 1);//we draw a line over it
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

                if (!r && !g && !b) //if a pixel is black on the line we cut the process for this line
                {
                    break;
                }
            }

            if (j > w - 1)
            {
                draw_ligne_W(img, i);
                
                int disection = 0;

                if (i+1 < h)
                {
                    for (int x = 0; x < w; x++)
                    {            
                        pixel = get_pixel(img, x, i+1);
                        SDL_GetRGB(pixel, img->format, &r, &g, &b);

                        if (!r && !g && !b)
                        {
                            disection = 1;
                            break;
                        }
                    }

                }
                
                if (disection)//if a pixel is black on this and this is the lowest one we draw a horizontal line under it
                {
                    draw_ligne_W(img, i+1);
                    i += 1;
                }
                else
                { 
                    inligne = 0;
                }                
            }
        }
    }

}


void Char_Detect(SDL_Surface* img,int f,int l) //character recognition function
{
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int w = img->w;
    int inchar = 0; //variable to detect if ta line has been drawn before 
    
    for (int i = 0; i < w; i++)
    {
        int f_array[l-f-1];
        int l_array[l-f-1];
        if (!inchar) 
        {   

            for (int j = f; j < l; j++)
            {
                pixel = get_pixel(img, i, j);
                SDL_GetRGB(pixel, img->format, &r, &g, &b);


                if (!r && !g && !b) // if the pixel is black
                {
                    
                    if (i == 0) //we draw a vertical line in right before any text
                    {
                        draw_ligne_H(img, i, f, l);
                        inchar = 1;//the vertical line detector is redefined to True
                        for(int j = 0; j < l-f ;j++)
                        {
                            f_array[j] = 1;
                            l_array[j] = 0;
                        }
                        i++;

                    }
                    else
                    {
                        draw_ligne_H(img, i - 1, f, l);//we draw a vertical line right before any black pixel
                        inchar = 1;
                        for(int j = 0; j < l-f;j++)
                        {
                            f_array[j] = 1;
                            l_array[j] = 0;
                        }

                    }
                }
            }
        }

        if (inchar)//if a line has been drawn
        {
            int h = 0;
            int two_char = 1;


            for (int j = f; j < l;j++)
            {
                pixel = get_pixel(img, i, j);
                SDL_GetRGB(pixel, img->format, &r, &g, &b);
                h = j - f;
                if (!r && !g && !b)//if the pixel is black
                {
                    l_array[h] = 1;
                }
                else 
                {
                    l_array[h] = 0;
                }


            }
            for (int j = f; j < l; j++)
            {
                pixel = get_pixel(img, i, j);
                SDL_GetRGB(pixel, img->format, &r, &g, &b);
                h = j - f;

                

                if (!r && !g && !b)//part where we try to figure out if there is a double char
                {
                    

                    
                    if ( (h == 0 && h == l - f) &&
                            f_array[h] == 1 )
                    {
                            two_char = 0;
                    }
                    else if ( h == 0  &&
                            ( f_array[h] == 1 ||
                              f_array[h+1] == 1 ))
                    {
                           two_char = 0;
                    }
                    else if ( h == l-f  &&
                            ( f_array[h] == 1 ||
                              f_array[h-1] == 1 ))
                    {
                          two_char = 0;
                    }
                    else if (f_array[h] == 1 ||
                              f_array[h-1] == 1 ||
                              f_array[h+1] == 1 )
                    {
                            two_char = 0;
                    }

                }

            }
            if (two_char)//if the two chars are distincts char we draw a vertical break line
            {


                inchar =0;
                draw_ligne_H(img, i, f, l);
            }

            for (int j = 0;j <= h;j++)
            {
                f_array[j] = l_array[j];

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
                    Char_Detect(img, firstligne, lastligne);
                    break;
                }
                i++;
            }
            i++;

        }

        i++;
    }
}

SDL_Surface* resize_caract(SDL_Surface* img)
{
	// the first line creates a surface , others are variables
	SDL_Surface* img2  = SDL_Surface( 0, 16, 16, 32, 0, 0, 0, 0); 
	int hight = img -> h;
	int lenght = img ->w;
	float hmul = 16./h;
	float lmul = 16./w;
	int i = 0;
	int j = 0;
	int newh;
	int neww;

	//for each pixel, check if it is black and put it in the new image to its new 
	//place, using hmul and lmul.
	while (i<h)
	{
		j = 0;
		while (j<w)
		{
			Uint32 pixel = get_pixel(img, i, j);
			Uint8 r, g, b;
			SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
			if (*r == 255)
			{
				newh = (int) (i*hmul);
				neww = (int) (j*lmul);

				put_pixel(img2, newh, neww, pixel);
			}
			j +=1;

		
		}
		i +=1;
	}

return img2;

}
