void greyscale(SDL_Surface* img)
{
    /* Variables */
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int w = img->w;
    int h = img->h;

    /* Iterate on each pixels and greyscale */
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            /* Apply luminance on r g b */
            pixel = getpixel(img, i, j);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            pixel = SDL_MapRGB(img->format, r * 0.3f, g * 0.59f, b * 0.11f);
            putpixel(img, i, j, pixel);
        }
    }
}

void Convolute(SDL_Surface* img)
{

    float mask[3][3] = {
     {1 / 9, 1 / 9, 1 / 9},
     {1 / 9, 1 / 9, 1 / 9},
     {1 / 9, 1 / 9, 1 / 9}
    };

    int maskWidth = 3;
    int maskHeight = 3;

    int Width = img->w;
    int Height = img->h;
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;

    for (int i = 0; i < Width; i++)
    {
        for (int j = 0; j < Height; j++)
        {
            Uint8 R = 0;
            Uint8 G = 0;
            Uint8 B = 0;

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
                        pixel = getpixel(img, x, y);
                        SDL_GetRGB(pixel, img->format, &r, &g, &b);
                        
                        R += mask[i][j] * r;
                        G += mask[i][j] * g;
                        B += mask[i][j] * b;

                    }
                }
            }
            pixel = SDL_MapRGB(img->format, R , G , B );
            putpixel(img, i, j, pixel);
        }
    }
}

void Contrast(SDL_Surface* img, float factor)
{
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int w = img->w;
    int h = img->h;

    /* Iterate on each pixels and greyscale */
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            /* Apply luminance on r g b */
            pixel = getpixel(img, i, j);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            pixel = SDL_MapRGB(img->format, factor * (r - 128) + 128, factor * (g - 128) + 128, factor * (b - 128) + 128);
            putpixel(img, i, j, pixel);
        }
    }
}


void blacknwhite(SDL_Surface* img)
{
    /* Variables */
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int w = img->w;
    int h = img->h;

    //int med = mediumPixel(img);
   /* Iterate on each pixels and blacknwhite */
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            pixel = getpixel(img, i, j);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            if (r >= 127 && g >= 127 && b >= 127)
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
            putpixel(img, i, j, pixel);
        }
    }
}

