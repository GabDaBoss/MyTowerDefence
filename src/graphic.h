//
// Created by gabriel on 30/06/17.
//

#ifndef MYTOWERDEFENCE_GRAPHIC_H
#define MYTOWERDEFENCE_GRAPHIC_H

#include <SDL_ttf.h>

#define Rect struct SDL_Rect
typedef struct Graphic Graphic;

Graphic* newGraphic();
void deleteGraphic(Graphic *graphic);

int getGraphicWidth(Graphic *graphic);

void setGraphicWidth(Graphic *graphic, int width);

int getGraphicHeight(Graphic *graphic);

void setGraphicHeight(Graphic *graphic, int height);


void calcGraphicSize(Graphic *graphic);

void loadFont(Graphic *graphic, char const *name, int size);

void drawText(Graphic *graphic, char const *text, Rect dest);

int initGraphic(Graphic *graphic, int width, int height);

void setRenderingColor(Graphic *graphic, unsigned int rgba);

void clear(Graphic *graphic);

void drawRect(Graphic *graphic, Rect rect);

void fillRect(Graphic *graphic, Rect rect);

void renderPresent(Graphic *graphic);


#endif //MYTOWERDEFENCE_GRAPHIC_H
