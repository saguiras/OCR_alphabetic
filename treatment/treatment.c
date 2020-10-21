# include <stdlib.h>
# include <SDL/SDL.h>
# include "SDL/SDL_image.h"
# include "../tools/tools.h"

void greyscale(SDL_Surface *img)
{
   /* Variables */
   Uint32 pixel;
   Uint8 r;
   Uint8 g;
   Uint8 b;
   int w = img -> w;
   int h = img -> h;
  
  /* Iterate on each pixels and greyscale */
  for(int i = 0; i < w; i++)
  {
    for(int j = 0; j < h; j++)
    {
      /* Apply luminance on r g b */
      pixel = get_pixel(img, i, j);
      SDL_GetRGB(pixel, img->format, &r, &g, &b);
      Uint8 average = 0.3*r + 0.59*g + 0.11*b;
      pixel = SDL_MapRGB(img->format,average, average, average);
      put_pixel(img,i,j,pixel);
    }
  }
}

/*
void Convolute(SDL_Surface* img, float[,] mask)
{
    Color color;
    Bitmap img = new Bitmap(image);

    int maskWidth = mask.GetLength(0);
    int maskHeight = mask.GetLength(1);

    int Width = img->w;
    int Height = img->h;

    for (int i = 0; i < Width; i++)
    {
        for (int j = 0; j < Height; j++)
        {
            int r = 0;
            int g = 0;
            int b = 0;

            int maxWidth = (maskWidth / 2);
            int maxHeight = (maskHeight / 2);
            for (int v = 0; i < maskWidth; i++)
            {
                for (int w = 0; j < maskHeight; j++)
                {
                    int x = v + i - maxWidth;
                    int y = w + j - maxHeight;
                    if (x >= 0 && y >= 0 && x < Width && y < Height)
                    {
                        r += Restrict256(mask[i, j] * getpixel(img, x, y).R);
                        g += Restrict256(mask[i, j] * getpixel(img, x, y).G);
                        b += Restrict256(mask[i, j] * getpixel(img, x, y).B);

                    }
                }
            }

            color = ColorExtension.FromHexa(Convert.ToString(r) + Convert.ToString(g) + Convert.ToString(b));
            img.SetPixel(i, j, color);
        }
    }
}
*/

void Contrast(SDL_Surface *img, float factor)
{
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int w = img -> w;
    int h = img -> h;
    for(int i = 0; i < w; i++)
    {
        for(int j = 0; j < h; j++)
        {
            pixel = get_pixel(img,i,j);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
             r = (factor * (r - 128 )+ 128);
             g = (factor * (g - 128 )+ 128);
             b = (factor * (b - 128 )+ 128);
            pixel = SDL_MapRGB(img->format,r, g, b);
            put_pixel(img,i,j,pixel);
        }
    }
}

void blacknwhite(SDL_Surface *img)
{
  /* Variables */
  Uint32 pixel;
  Uint8 r;
  Uint8 g;
  Uint8 b;
  int w = img -> w;
  int h = img -> h;

  //int med = mediumPixel(img);
 /* Iterate on each pixels and blacknwhite */
 for(int i = 0; i < w; i++)
 {
   for(int j = 0; j < h; j++)
   {
     pixel = get_pixel(img,i,j);
     SDL_GetRGB(pixel, img->format, &r, &g, &b);
     if(r >= 175 && g >= 175 && b >= 175)
     {
      r = 255;
      g = 255;
      b = 255;
     }
     else
     {
      r = 0;
      g = 0;
      b = 0;
     }
     pixel = SDL_MapRGB(img->format, r, g, b);
     put_pixel(img, i, j, pixel);
   }
 }
}
