#include <err.h>
# include <stdlib.h>
# include <SDL/SDL.h>


static inline Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y)
{
    int bpp = surf -> format -> BytesPerPixel;
    return (Uint8*)surf -> pixels + y * surf -> pitch + x * bpp;
}

Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y)
{
    Uint8 *p = pixelref(surface, x, y);
    switch(surface -> format -> BytesPerPixel) {
    case 1:
        return *p;
    case 2:
        return *(Uint16 *)p;
    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
    case 4:
            return *(Uint32 *)p;
    }
    return 0;
}
    

void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel)
{
    Uint8 *p = pixelref(surface, x, y);
    switch(surface -> format -> BytesPerPixel) {
    case 1:
        *p = pixel;
        break;
    case 2:
        *(Uint16 *)p = pixel;
        break;
    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        }
        else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;
    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

void update_surface(SDL_Surface* screen, SDL_Surface* image)
{
    if (SDL_BlitSurface(image, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

    SDL_UpdateRect(screen, 0, 0, image->w, image->h);
}

void array_swap(int array[], size_t i, size_t j)
{
  int element1 = array[i];
  int element2 = array[j];
  array[i] = element2;
  array[j] = element1;
}

void array_select_sort(int array[], size_t len)
{
  size_t i = 0;
  size_t j;
  int min_index;
  while(i<len)
  {
    /* Find Min Index */
    j= i;
    min_index = j;
    while(j<len)
    {
        if(array[j]<array[min_index])
        {
            min_index = j;
        }
        j+=1;
    }
    array_swap(array,i,min_index);
    i++;
  }
}

int isNumber(char s[])
{
    for (int i = 0; s[i]!= '\0'; i++)
    {
        if (isdigit(s[i]) == 0) 
              return 0;
    }
    return 1;
}

char* concat(const char *s1, const char *s2)
{
    //+1 for the null-terminator
    char *result = malloc(strlen(s1) + strlen(s2) + 1);

    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

double *create_matrix(SDL_Surface *img)
{
  //Variables
  double *letterMatrix = malloc(sizeof(double) * 28 * 28);
  Uint8 r;
  Uint8 g;
  Uint8 b;

  for(int i = 0; i < img -> h; i++)
  {
      for(int j = 0; j < img -> w; j++)
      {
          Uint32 pixel = get_pixel(img, j, i);
          SDL_GetRGB(pixel, img -> format, &r, &g, &b);
          if(r == 0 && g == 0 && b == 0)
              letterMatrix[j + i * img -> w] = 1;
          else
              letterMatrix[j + i * img -> w] = 0;
      }
  }
  return letterMatrix;
}

