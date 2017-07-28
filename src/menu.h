//
// Created by gabriel on 27/07/17.
//

#ifndef MYTOWERDEFENCE_MENU_H
#define MYTOWERDEFENCE_MENU_H

typedef struct Menu Menu;
unsigned int getMenuSizeOf();
Menu* newMenu();
void deleteMenu(Menu *menu);
void initMenu(Menu* menu,char *const title);
char * const getMenuTitle(Menu *menu);
void setMenuTileInfo(Menu *menu, char *const info);
char *const getMenuTileInfo(Menu *menu);
#endif //MYTOWERDEFENCE_MENU_H
