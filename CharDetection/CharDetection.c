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
	SDL_Surface* img2  = SDL_CreateRGBSurface( 0, 28, 28, 32, 0, 0, 0, 0); 
	int h = img -> h;
	int w = img ->w;
	float hmul = 28./h;
	float lmul = 28./w;
	int i = 0;
	int j = 0;
	int newh;
	int neww;

	//for each pixel, check if it is black and put it in the new image to its new 
	//place, using hmul and lmul.
	if (h>28){
	while (i<h)
	{
		j = 0;
		while (j<w)
		{
			Uint32 pixel = get_pixel(img, i, j);
			Uint8 r, g, b;
			SDL_GetRGB(pixel, img->format, &r, &g, &b);
			if (r == 255)
			{
				newh = (int) (i*hmul);
				neww = (int) (j*lmul);

				put_pixel(img2, newh, neww, pixel);
			}
			j +=1;

		
		}
		i +=1;
	}
	}
	else
	{
        while (i<28)
	{
		j = 0;
		while (j<28)
		{
			newh = (int) (i/hmul);
			neww = (int) (j/lmul);
                        Uint32 pixel = get_pixel(img, newh, neww);
			Uint8 r, g, b;
                        SDL_GetRGB(pixel, img->format, &r, &g, &b);
                        if (r == 255)
			{
				put_pixel(img2, i, j, pixel);
			}


			j +=1;

		
		}
		i +=1;
	}

	}

return img2;

}

int space_pixelcount(SDL_Surface* img, int i, int j)//lenght of a space caract
{
	int result = 0;
        Uint32 pixel;
	Uint8 r, g, b;
	int w = img -> w;
	int _bool = 1;
	while(_bool && j < w)
	{
                pixel = get_pixel(img, i, j);
                SDL_GetRGB(pixel, img->format, &r, &g, &b);
                if (r == 255 && g == 0 && r == 0)
		{
			_bool = 0;
		}
		result+=1;
		j+=1;

	}

	return result;
}

int notiscaract(SDL_Surface* img, int i, int j)
{
	int i2 = i;
	int i3 = i;
	int j2 = j;
	int j3 = j;
	int w = img -> w;
	int h = img -> h;
	int _bool = 1;
	int resultbool = 1;
        while(_bool && j3 < w)
	{
                pixel = get_pixel(img, i2, j3);
                SDL_GetRGB(pixel, img->format, &r, &g, &b);
                if (r == 255 && g == 0 && r == 0)
		{
			_bool = 0;
		}
		j3+=1;
	}
	_bool = 1;
	while(_bool && i3 < h)
	{
                pixel = get_pixel(img, i3, j2);
                SDL_GetRGB(pixel, img->format, &r, &g, &b);
                if (r == 255 && g == 0 && r == 0)
		{
			_bool = 0;
		}
		i3+=1;
	}

	while(i2<i3)
	{
		j2 = j;
		while(j2<j3)
		{
                    pixel = get_pixel(img, i2, j2);
                    SDL_GetRGB(pixel, img->format, &r, &g, &b);
                    if (r == 255 && g == 255 && r == 255)
		    {
			   resultbool = 0;

		    }
		    j2 +=1;
		}
		I2+=1;

	}
	return resultbool;

}


int space_nbpixels(SDL_Surface* img)//
{
	//variables
	int h = img -> h;
	int w = img -> w;
	int i = 0;
	int j = 0;
	int _bool = 1;
	Uint32 pixel;
	Uint8 r, g, b;
	int total_pixel;
	int divisor;
	int a;
	//get go the first line of caract
	//while(_bool)
	//{
	//	pixel = get_pixel(img, i, j);
        //      SDL_GetRGB(pixel, img->format, &r, &g, &b);
	//	if (r == 255 && g == 0 && r == 0)
	//	{
	//		_bool = 0;
	//	}
	//	i+=1;
        //
	//}
	//_bool = 1;
	//get to the first column of caract
	//while(_bool) 
	//{
        //        pixel = get_pixel(img, i, j);
        //        SDL_GetRGB(pixel, img->format, &r, &g, &b);
	//	if (r == 255 && g == 0 && r == 0)
	//	{
	//		_bool = 0;
	//	}
	//	j+=1;
	//}
	while(i<h)
	{
		j = 0;
                while(_bool)
	        {
		      if(i>=h)
		      {
		          break;
		      }
		      pixel = get_pixel(img, i, j);
                      SDL_GetRGB(pixel, img->format, &r, &g, &b);
		      if (r == 255 && g == 0 && r == 0)
		      {
		          _bool -= 1;
		      }
		      i+=1;

	        }
		if (i>=h)
		{
			break;
		}
	        _bool = 1;
                while(_bool) 
	        {
                    pixel = get_pixel(img, i, j);
                    SDL_GetRGB(pixel, img->format, &r, &g, &b);
		    if (r == 255 && g == 0 && r == 0)
		    {
			_bool = 0;
		    }
		    j+=1;

	        }
		_bool = 2;

		while(j<w)
		{
		    a = space_pixelcount(img, i, j);
		    b = notiscaract(img, i, j);
		    if(b)
		    {
			total_pixel += a;
			divisor += 1;
		    }
		    j +=a;

		}
		total_pixel-=a;
		divisor-=1;
	}
	return ((total_pixel/divisor)+1);


}
