//
// Created by gabriel on 27/07/17.
//

#ifndef MYTOWERDEFENCE_MENURENDERER_H
#define MYTOWERDEFENCE_MENURENDERER_H

#include "menu.h"
#include "graphic.h"

typedef struct MenuRenderer MenuRenderer;

void drawMenu(MenuRenderer *renderer, Graphic *graphic, Menu *menu);

unsigned int getMenuRendererSizeOf();

MenuRenderer* newMenuRenderer();
void deleteMenuRenderer(MenuRenderer* renderer);
void initMenuRenderer(MenuRenderer *renderer, int width, int height);

#endif //MYTOWERDEFENCE_MENURENDERER_H
