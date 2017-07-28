//
// Created by gabriel on 15/07/17.
//

#include "mapRenderer.h"
#include "util.h"
#include "tile.h"

#define MIN_TILE_SIZE 20
#define MAX_TILE_SIZE 400
#define SCREEN_SCROLL_WIDTH 50
#define SCREEN_SCROLL_SPEED 1

typedef struct MapRenderer
{
    int minTileSize;
    int maxTileSize;
    int tileSize;
    int viewPosX;
    int viewPosY;
    int width;
    int height;
} MapRenderer;

int getTileIndexUnderPoint(MapRenderer *renderer, Map *map, int x, int y)
{
    return (((y + renderer->viewPosY) / (renderer->tileSize)) * getMapWidth(map)) +
            ((x + renderer->viewPosX) / (renderer->tileSize));
}

MapRenderer *newMapRenderer()
{
    MapRenderer *renderer = calloc(1, sizeof(MapRenderer));

    renderer->minTileSize = MIN_TILE_SIZE;
    renderer->maxTileSize = MAX_TILE_SIZE;
    renderer->tileSize = MIN_TILE_SIZE;

    return renderer;
}

void deleteMapRenderer(MapRenderer *mapRenderer)
{
    free(mapRenderer);
    mapRenderer = NULL;
}

void calcTileSize(MapRenderer *renderer, Map *map)
{
    renderer->tileSize =
            min(
                    max(
                            max(renderer->width / getMapWidth(map), renderer->minTileSize),
                            max(renderer->height / getMapHeight(map), renderer->minTileSize)
                    ), renderer->maxTileSize);
}

int getTileSize(MapRenderer *renderer)
{
    return renderer->tileSize;
}

void setMinTileSize(MapRenderer *renderer, int min)
{
    renderer->minTileSize = min;
}

void setMaxTileSize(MapRenderer *renderer, int max)
{
    renderer->maxTileSize = max;
}

void drawMap(MapRenderer *renderer, Graphic *graphic, Map *map)
{
    Tile *tile;
    for (int i = 0; i < getMapSize(map); i++)
    {
        tile = getTile(map, i);
        switch (getTileType(tile))
        {
            case WALL:
                setRenderingColor(graphic, 0x138430FF);
                break;
            case PATH:
                setRenderingColor(graphic, 0x604300FF);
                break;
            case ENTRY:
                setRenderingColor(graphic, 0x13847EFF);
                break;
            case EXIT:
                setRenderingColor(graphic, 0x841337FF);
                break;
            default:
                setRenderingColor(graphic, 0x000000FF);
                break;
        }
        fillRect(graphic, (SDL_Rect) {((i % getMapWidth(map)) * renderer->tileSize) - renderer->viewPosX,
                                      ((i / getMapWidth(map)) * renderer->tileSize) - renderer->viewPosY,
                                      renderer->tileSize,
                                      renderer->tileSize});
    }
}

void setMapRendererWidth(MapRenderer *renderer, int width)
{
    renderer->width = width;
}

void setMapRendererHeight(MapRenderer *renderer, int height)
{
    renderer->height = height;
}

void
handlePlayFieldScrolling(MapRenderer *renderer, Map *map, Graphic *graphic, int cursorX, int cursorY, int deltaTime)
{
//    int newPosX = map->viewPosX;
//    int newPosY = map->viewPosY;

//    if (cursorX - SCREEN_SCROLL_WIDTH < 0)
//        newPosX += (deltaTime * SCREEN_SCROLL_SPEED) * (cursorX - SCREEN_SCROLL_WIDTH) / SCREEN_SCROLL_WIDTH;
//    else if (cursorX - getGraphicWidth(graphic) + SCREEN_SCROLL_WIDTH > 0)
//        newPosX += (deltaTime * SCREEN_SCROLL_SPEED) * (cursorX - getGraphicWidth(graphic) + SCREEN_SCROLL_WIDTH) /
//                   SCREEN_SCROLL_WIDTH;

    renderer->viewPosX += (int) (deltaTime * SCREEN_SCROLL_SPEED)
                          * (
                                  (min(0, cursorX - SCREEN_SCROLL_WIDTH)) |
                                  (max(0, cursorX - renderer->width + SCREEN_SCROLL_WIDTH))
                          ) / SCREEN_SCROLL_WIDTH;

//    if (newPosX >= 0 && newPosX <= (map->width * map->tileSize * getZoom(graphic) - getGraphicWidth(graphic)))
//        map->viewPosX = newPosX;

    renderer->viewPosX = min(max(0, renderer->viewPosX),
                             (int) (getMapWidth(map) * renderer->tileSize - renderer->width));

//    if (cursorY - SCREEN_SCROLL_WIDTH < 0)
//        newPosY += (deltaTime * SCREEN_SCROLL_SPEED) * (cursorY - SCREEN_SCROLL_WIDTH) / SCREEN_SCROLL_WIDTH;
//    else if (cursorY - getGraphicHeight(graphic) + SCREEN_SCROLL_WIDTH > 0)
//        newPosY += (deltaTime * SCREEN_SCROLL_SPEED) * (cursorY - getGraphicHeight(graphic) + SCREEN_SCROLL_WIDTH) /
//                   SCREEN_SCROLL_WIDTH;

    renderer->viewPosY += (int) (deltaTime * SCREEN_SCROLL_SPEED) * ((min(0, cursorY - SCREEN_SCROLL_WIDTH)) |
                                                                     (max(0, cursorY - renderer->height +
                                                                             SCREEN_SCROLL_WIDTH))) /
                          SCREEN_SCROLL_WIDTH;

//    if (newPosY >= 0 && newPosY <= (map->size / map->width) * map->tileSize * getZoom(graphic) -
//                                   getGraphicHeight(graphic))
//        map->viewPosY = newPosY;
    renderer->viewPosY = min(max(0, renderer->viewPosY),
                             (int) (((getMapHeight(map)) * renderer->tileSize) - renderer->height));
}

void handleSelector(MapRenderer *renderer, Map *map, Graphic *graphic, int cursorX, int cursorY)
{
    setRenderingColor(graphic, 0xFFFFFFFF);
//    int cursorTileRow = (int) ((cursorY + map->viewPosY) / (map->tileSize * graphic->zoom));
//    int cursorTileCol = (int) ((cursorX + map->viewPosX) / (map->tileSize * graphic->zoom));
//    int cursorTile = cursorTileRow * map->width + cursorTileCol;

    int cursorTile = getTileIndexUnderPoint(renderer, map, cursorX, cursorY);
    
    drawRect(graphic, (SDL_Rect) {(int) ((cursorTile % renderer->width) * renderer->tileSize) - renderer->viewPosX,
                                  (int) ((cursorTile / renderer->width) * renderer->tileSize) - renderer->viewPosY,
                                  (int) (renderer->tileSize), (int) (renderer->tileSize)});
}

