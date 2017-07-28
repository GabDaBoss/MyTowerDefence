//
// Created by gabriel on 30/06/17.
//

#include <SDL.h>
#include "util.h"
#include "graphic.h"

typedef struct Graphic
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    int width, height;
    unsigned int color;
} Graphic;

Graphic* newGraphic()
{
    return calloc(1, sizeof(Graphic));
}

void deleteGraphic(Graphic *graphic)
{
    SDL_DestroyRenderer(graphic->renderer);
    SDL_DestroyWindow(graphic->window);

    TTF_CloseFont(graphic->font);
    TTF_Quit();
    SDL_Quit();

    free(graphic);
    graphic = NULL;
}

int getGraphicWidth(Graphic *graphic)
{
    return graphic->width;
}

void calcGraphicSize(Graphic *graphic)
{
    int w, h;
//    SDL_GetWindowSize(graphic->window, &w, &h);
    if(SDL_GetRendererOutputSize(graphic->renderer, &w, &h) == 0)
    {
        graphic->width = w;
        graphic->height = h;
    }
}

void setGraphicWidth(Graphic *graphic, int width)
{
    graphic->width = width;
}

int getGraphicHeight(Graphic *graphic)
{
    return graphic->height;
}

void setGraphicHeight(Graphic *graphic, int height)
{
    graphic->height = height;
}

int initSDL(Graphic *graphic, int width, int height);

int initGraphic(Graphic *graphic, int width, int height)
{
    int result = initSDL(graphic, width, height);
    TTF_Init();
    loadFont(graphic, "Roman_SD.ttf", 14);

    return result;
}

void loadFont(Graphic *graphic, char const *name, int size)
{
    graphic->font = TTF_OpenFont(name, size);
    if (!graphic->font)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }
}

void drawText(Graphic *graphic, char const *text, Rect dest)
{
    SDL_Color color = {255, 255, 255};

    SDL_Surface *textSurface = TTF_RenderText_Solid(graphic->font, text, color);

    SDL_Texture *msgTexture = SDL_CreateTextureFromSurface(graphic->renderer, textSurface);

    SDL_RenderCopy(graphic->renderer, msgTexture, NULL, &dest);

    SDL_DestroyTexture(msgTexture);
    SDL_FreeSurface(textSurface);
}

int initSDL(Graphic *graphic, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "SDL couldn't initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    } else
    {
        graphic->window = SDL_CreateWindow("MyTowerDefence", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
                                           height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

        if (graphic->window == NULL)
        {
            fprintf(stderr, "Window couldn't be created! SDL_Error: %s\n", SDL_GetError());
            return -1;
        } else
        {
            graphic->renderer = SDL_CreateRenderer(graphic->window, -1, SDL_RENDERER_ACCELERATED);

            if (graphic->renderer == NULL)
            {
                fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
                return -1;
            }
        }
    }
    return 1;
}



void setRenderingColor(Graphic *graphic, unsigned int rgba)
{
//    SDL_SetRenderDrawColor(graphic->renderer, (Uint8) ((24 << rgba) & 0xFF), (Uint8) ((16 << rgba) & 0xFF),
//                           (Uint8) ((8 << rgba) & 0xFF), (Uint8) (rgba & 0xFF));
    graphic->color = rgba;
    Uint8 *vp = (Uint8 *) &rgba;
    SDL_SetRenderDrawColor(graphic->renderer,
                           vp[3],
                           vp[2],
                           vp[1],
                           vp[0]);
}

void clear(Graphic *graphic)
{
    SDL_RenderClear(graphic->renderer);
}

void drawRect(Graphic *graphic, Rect rect)
{
    SDL_RenderDrawRect(graphic->renderer, &rect);
}

void fillRect(Graphic *graphic, Rect rect)
{
    SDL_RenderFillRect(graphic->renderer, &rect);
}

void renderPresent(Graphic *graphic)
{
    SDL_RenderPresent(graphic->renderer);
}

void fillCircle(Graphic *graphic, Rect rect)
{
    filledCircleColor(graphic->renderer, rect.x, rect.y, rect.w, graphic->color);
}


