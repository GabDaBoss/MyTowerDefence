//
// Created by gabriel on 27/07/17.
//

#include <malloc.h>
#include "menu.h"

typedef struct Menu
{
    char *title;
    char *tileInfo;
} Menu;

void initMenu(Menu *menu, char *const title)
{
    menu->title = title;
}

unsigned int getMenuSizeOf()
{
    return sizeof(Menu);
}

Menu *newMenu()
{
    return calloc(1, getMenuSizeOf());
};

void deleteMenu(Menu *menu)
{
    free(menu);
}

char *const getMenuTitle(Menu *menu)
{
    return menu->title;
}

void setMenuTileInfo(Menu *menu, char *const info)
{
    menu->tileInfo = info;
}

char *const getMenuTileInfo(Menu *menu)
{
    return menu->tileInfo;
}

