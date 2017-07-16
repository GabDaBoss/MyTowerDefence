//
// Created by gabriel on 15/07/17.
//

#include "tile.h"

#ifndef MYTOWERDEFENCE_MAP_H
#define MYTOWERDEFENCE_MAP_H

typedef struct Map Map;

unsigned long getMapSizeof();
Map *newMap();
void deleteMap(Map *map);
int loadMap(Map *map, const char *const filename);
int getMapWidth(Map *map);
int getMapHeight(Map *map);
int getMapSize(Map *map);
Tile* getTile(Map* map, int i);
#endif //MYTOWERDEFENCE_MAP_H
