# include <stdlib.h>
# include <SDL/SDL.h>
# include "SDL/SDL_image.h"
# include "../tools/tools.h"

void greyscale(SDL_Surface *img)
{
   Uint32 pixel;
   Uint8 r;
   Uint8 g;
   Uint8 b;
   int w = img -> w;
   int h = img -> h;
  
  /* Iterate on each pixels */
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
void blur(SDL_Surface *img)
{
  int w;
  int h;
  w = img -> w;
  h = img -> h;
  int pixelTable[4];

 for(int i = 0; i < w; i++)
 {
   for(int j = 0; j < h; j++)
   {
     for(int k = j; k <= j + 4; k++)
     {
       //Borders of picture
       if(i == 0)
       {
         if(k == 0)
         {
            pixelTable[0] = get_pixel(img, i, k);
            pixelTable[1] = get_pixel(img, i, k);
            pixelTable[2] = get_pixel(img, i, k);
            pixelTable[3] = get_pixel(img, i, k + 1);
            pixelTable[4] = get_pixel(img, i + 1, k);
            break;
         }
         if(k == h)
         {
            pixelTable[0] = get_pixel(img, i, k);
            pixelTable[1] = get_pixel(img, i, k - 1);
            pixelTable[2] = get_pixel(img, i, k);
            pixelTable[3] = get_pixel(img, i, k);
            pixelTable[4] = get_pixel(img, i + 1, k);
            break;
         }
         else
         {
          pixelTable[0] = get_pixel(img, i, k);
          pixelTable[1] = get_pixel(img, i, k - 1);
          pixelTable[2] = get_pixel(img, i, k);
          pixelTable[3] = get_pixel(img, i, k + 1);
          pixelTable[4] = get_pixel(img, i + 1, k);
          break;
         }
       }
       if(i == w)
       {
          if(k == 0)
          {
            pixelTable[0] = get_pixel(img, i, k);
            pixelTable[1] = get_pixel(img, i, k);
            pixelTable[2] = get_pixel(img, i - 1, k);
            pixelTable[3] = get_pixel(img, i, k + 1);
            pixelTable[4] = get_pixel(img, i, k);
            break;
          }
          if(k == h)
          {
            pixelTable[0] = get_pixel(img, i, k);
            pixelTable[1] = get_pixel(img, i, k - 1);
            pixelTable[2] = get_pixel(img, i - 1, k);
            pixelTable[3] = get_pixel(img, i, k);
            pixelTable[4] = get_pixel(img, i, k);
            break;
          }
          else
          {
            pixelTable[0] = get_pixel(img, i, k);
            pixelTable[1] = get_pixel(img, i, k - 1);
            pixelTable[2] = get_pixel(img, i - 1, k);
            pixelTable[3] = get_pixel(img, i, k + 1);
            pixelTable[4] = get_pixel(img, i, k);
            break;
          }
       }
       if(k == 0)
       {
          pixelTable[0] = get_pixel(img, i, k);
          pixelTable[1] = get_pixel(img, i, k);
          pixelTable[2] = get_pixel(img, i - 1, k);
          pixelTable[3] = get_pixel(img, i, k + 1);
          pixelTable[4] = get_pixel(img, i + 1, k);
          break;
       }
       if(k == h)
       {
        pixelTable[0] = get_pixel(img, i, k);
        pixelTable[1] = get_pixel(img, i, k - 1);
        pixelTable[2] = get_pixel(img, i - 1, k);
        pixelTable[3] = get_pixel(img, i, k);
        pixelTable[4] = get_pixel(img, i + 1, k);
        break;
       }
       else
       {
        pixelTable[0] = get_pixel(img, i, k);
        pixelTable[1] = get_pixel(img, i, k - 1);
        pixelTable[2] = get_pixel(img, i - 1, k);
        pixelTable[3] = get_pixel(img, i, k + 1);
        pixelTable[4] = get_pixel(img, i + 1, k);
        break;
       }
     }
      array_select_sort(pixelTable, 5);
      int med = pixelTable[2];
      put_pixel(img, i, j, med);
   }
 }
}
*/

void blur(SDL_Surface *img)
{
  
  int w;
  int h;
  w = img -> w;
  h = img -> h;
  int pixelTable[4];
  int x;

 for(int i = 0; i < w; i++)
 {
   for(int j = 0; j < h; j++)
   {
    
    
        // 
        x = 0;
        for (int li = i-1; li<=i+1; li+=2)
        {
            if (li >= 0 && li < h )
                pixelTable[x] = get_pixel(img, li, j);
            else
                pixelTable[x] = get_pixel(img, i, j);
            x += 1;

        }
        for(int col = j-1; col<= j+1; col+=2)
        {
            if (col >= 0 && col < w)
                pixelTable[x] = get_pixel(img, i, col);
            else
                pixelTable[x] = get_pixel(img, i, j);
            x += 1;
        }

      pixelTable[x] = get_pixel(img, i, j);   
      array_select_sort(pixelTable, 5);
      int med = pixelTable[2];
      put_pixel(img, i, j, med);
   }
 }
}


/*
void blur(SDL_Surface *img)
{
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;

    int w = img -> w;
    int h = img -> h;


    double average_red = 0, average_green = 0, average_blue = 0;
    int count_number = 0;
    int box = 1; // 1 for 3x3 box

    for (int i = 0; i < h; ++i)
    {
        for(int j = 0; j < w;++j)
        {
            average_red = 0;
            average_blue = 0;
            average_red = 0;
            count_number =0;

        
            
            for (int li = i-box; li<=i+box; ++li )
            {
                for(int col = j-box; col<= j+box; col++)
                {
                    
                    if ((li >= 0 && li < h ) && (col >= 0 && col < w))
                    { 
                        

                        count_number++;

                        pixel = get_pixel(img, col, li);
                        SDL_GetRGB(pixel, img->format, &r, &g, &b);


                        average_red += (int)r;
                        average_green += (int)g;
                        average_blue += (int)b;
                    }

                }

            }
            
            pixel = SDL_MapRGB(img->format, (Uint8) (average_red/count_number),(Uint8) (average_green/count_number) , (Uint8)(average_blue/count_number));
            put_pixel(img,j,i,pixel);

        }
    }
}
 
//Covolute c# of Alicetp
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

void Brightness(SDL_Surface *img, float factor)
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
             r = factor * r;
             g = factor * g;
             b = factor * b;
            pixel = SDL_MapRGB(img->format,r, g, b);
            put_pixel(img,i,j,pixel);
        }
    }
}


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

void draw_whit_W(SDL_Surface *img,int x,int y, int j)
{
    Uint32 pixel;

    for (int i = x;i < y;i++)
    {
        pixel = SDL_MapRGB(img->format,255, 255, 255);
        put_pixel(img,i,j,pixel);
    }
}

void draw_whit_H(SDL_Surface *img, int x,int y,int i)
{
    Uint32 pixel;

    for (int j = x; j < y ;j++)
    {
        pixel = SDL_MapRGB(img->format,255,255,255);
        put_pixel(img,i,j,pixel);
    }
}



void noligne_H(SDL_Surface *img)
{
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int w = img -> w;
    int h = img -> h;
    int count = 0;
    int last = 0;
    int max_count = 0;
    int a = 0;
    int x = 0;
    int y = 0;
    int j;


    for(int i = 0; i < w; i++)
    {
        x = 0;
        y = 0;
        last = 0;
        j = 0;
        max_count = 0; 
        for(j = 0; j < h; j++)
        {
            pixel = get_pixel(img,i,j);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            Uint32 average = (r + g + b) / 3;
            if(average < 127 && last)
            {

                count += 1;
            }
            else if (average < 127)
            {
                a = j;
                last = 1;
                count += 1;
            }
            else
            {
                if (max_count < count)
                {
                    max_count = count;
                    y = j;
                    x = a;
                }
                count = 0;
                last = 0;
            }

        }

        if (max_count < count)
        {
            y = j;
            x = a;
        }
    

        if (y-x > h/3)
        {          
            draw_whit_H(img,x,y,i);
            i -= 1;
        }
    }


}

void noligne_W(SDL_Surface *img)
{
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int w = img -> w;
    int h = img -> h;
    int count = 0;
    int last = 0;
    int max_count = 0;
    int a = 0;
    int x = 0;
    int y = 0;
    int j;

    for(int i = 0; i < h; i++)
    {
        x = 0;
        y = 0;
        last = 0;
        j = 0;
        max_count = 0;
        for(j = 0; j < w; j++)
        {
            pixel = get_pixel(img,j,i);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            Uint32 average = (r + g + b) / 3;
            if(average < 127 && last)
            {
                count += 1;
            }
            else if (average < 127)
            {
                a = j;
                last = 1;
                count += 1;
            }
            else
            {
                if (max_count < count)
                {
                    max_count = count;
                    y = j;
                    x = a;
                }
                count = 0;
                last = 0;
            }

        }

        if (max_count < count)
        {
            y = j;
            x = a;
        }

        if (y-x > h/3)
        {
            draw_whit_W(img,x,y,i);
            i -=1 ;
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
      Uint32 average = (r + g + b) / 3;
     if(average > 150)
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
