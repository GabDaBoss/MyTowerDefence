//
// Created by gabriel on 27/07/17.
//

#include "menuRenderer.h"

typedef struct MenuRenderer
{
    int width, height;
} MenuRenderer;

void initMenuRenderer(MenuRenderer *renderer, int width, int height)
{
    renderer->width = width;
    renderer->height = height;
}

void drawMenu(MenuRenderer *renderer, Graphic *graphic, Menu *menu)
{

    setRenderingColor(graphic, 0x000000FF);
    fillRect(graphic,
             (Rect) {getGraphicWidth(graphic) - renderer->width, 0, renderer->width, getGraphicHeight(graphic)});
    drawText(graphic, getMenuTitle(menu), (Rect) {getGraphicWidth(graphic) - renderer->width, 0, renderer->width, 14});
    drawText(graphic, getMenuTileInfo(menu), (Rect) {getGraphicWidth(graphic) - renderer->width, 16, renderer->width, 14});
}

unsigned int getMenuRendererSizeOf()
{
    return sizeof(MenuRenderer);
}

MenuRenderer *newMenuRenderer()
{
    return calloc(1, getMenuRendererSizeOf());
}

void deleteMenuRenderer(MenuRenderer *renderer)
{
    free(renderer);
}
