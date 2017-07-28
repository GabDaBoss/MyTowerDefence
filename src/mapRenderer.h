//
// Created by gabriel on 15/07/17.
//

#ifndef MYTOWERDEFENCE_MAPRENDERER_H
#define MYTOWERDEFENCE_MAPRENDERER_H

#include "map.h"
#include "graphic.h"

typedef struct MapRenderer MapRenderer;
//typedef struct MapRenderer
//{
//    int minTileSize;
//    int maxTileSize;
//    int tileSize;
//    int viewPosX;
//    int viewPosY;
//    int width;
//    int height;
//} MapRenderer;

void calcTileSize(MapRenderer *renderer, Map *map);

void setMinTileSize(MapRenderer *renderer, int min);

void setMaxTileSize(MapRenderer *renderer, int max);

int getTileSize(MapRenderer *renderer);

MapRenderer *newMapRenderer();

void deleteMapRenderer(MapRenderer *mapRenderer);

void drawMap(MapRenderer *renderer, Graphic *graphic, Map *map);

void setMapRendererWidth(MapRenderer *renderer, int width);

void setMapRendererHeight(MapRenderer *renderer, int height);

void
handlePlayFieldScrolling(MapRenderer *renderer, Map *map, Graphic *graphic, int cursorX, int cursorY, int deltaTime);

void handleSelector(MapRenderer *renderer, Map *map, Graphic *graphic, int cursorX, int cursorY);

int getTileIndexUnderPoint(MapRenderer *renderer, Map *map, int x, int y);

#endif //MYTOWERDEFENCE_MAPRENDERER_H
