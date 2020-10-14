void ligne_decect(SDL_Surface* img)
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
                pixel = getpixel(img, j, i);
                SDL_GetRGB(pixel, img->format, &r, &g, &b);

                if (!r && !g && !b)
                {
                    if (i == 0) 
                    {
                        draw_ligne_H(img, i);
                    }
                    else
                    {
                        draw_ligne_H(img, i - 1);
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
                pixel = getpixel(img, j, i);
                SDL_GetRGB(pixel, img->format, &r, &g, &b);

                if (!r && !g && !b)
                {
                    break;
                }
            }
            if (j < w - 1)
            {
                inligne = 0;
                draw_ligne(img, i);
            }
        }
    }

}

void lign_coord(SDL_Surface* img)
{
    /* Variables */
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int h = img->h;
    int w = img->w;
    int i = 0;
    int firstligne;
    int lastligne;

    while (i < h)
    {
        pixel = getpixel(img, 0, i);
        SDL_GetRGB(pixel, img->format, &r, &g, &b);

        //If there is a red line start cut
        if (r == 255 && b == 0 && g == 0)
        {
            firstligne = i;
            r = 0;

            while (r != 255 && b != 0 && g != 0)
            {
                pixel = getpixel(img, 0, i);
                SDL_GetRGB(pixel, img->format, &r, &g, &b);

                //Detect the second line
                if (r == 255 && b == 0 && g == 0)
                {
                    lastligne = i;

                    //Isolate into a surface the linecut
                    cutligne(img, firstligne, lastligne);
                }

                i++;
            }
        }

        i++;
    }
}

void cutligne(SDL_Surface* img, int firstCut,
    int lastCut) {}


void char_detect(SDL_Surface* img)
{
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int h = img->h;
    int w = img->w;
    int inchar = 0;

    for (int i = 0; i < w; i++)
    {
        if (!inchar)
        {
            for (int j = 0; j < h; j++)
            {
                pixel = getpixel(img, j, i);
                SDL_GetRGB(pixel, img->format, &r, &g, &b);

                if (!r && !g && !b)
                {
                    if (i == 0)
                    {
                        draw_ligne_V(img, i);
                    }
                    else
                    {
                        draw_ligne_V(img, i - 1);
                        inchar = 1;
                    }
                }

            }
        }
        if (inchar)
        {
            int j = 0;
            for (j = 0; j < h; j++)
            {
                pixel = getpixel(img, j, i);
                SDL_GetRGB(pixel, img->format, &r, &g, &b);

                if (!r && !g && !b)
                {
                    break;
                }
            }
            if (j < w - 1)
            {
                inchar = 0;
                draw_ligne_V(img, i);
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
    int h = img->h;
    int w = img->w;
    int i = 0;
    int firstLchar;
    int lastLchar;

    while (i < w)
    {
        pixel = getpixel(img, i, 0);
        SDL_GetRGB(pixel, img->format, &r, &g, &b);

        //If there is a red line start cut
        if (r == 255 && b == 0 && g == 0)
        {
            firstLchar = i;
            r = 0;

            while (r != 255 && b != 0 && g != 0)
            {
                pixel = getpixel(img, i, 0);
                SDL_GetRGB(pixel, img->format, &r, &g, &b);

                //Detect the second line
                if (r == 255 && b == 0 && g == 0)
                {
                    lastLchar = i;

                    //Isolate into a surface the linecut
                    cutchar(img, firstLchar, lastLchar);
                }

                i++;
            }
        }

        i++;
    }
}
