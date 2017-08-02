//
// Created by gabriel on 15/07/17.
//

#include <stdlib.h>
#include "tile.h"

#define TILE_SIZE 50
typedef struct Tile
{
    tileType type;
    int occupied;
} Tile;

Tile *newTile()
{
//    return calloc(1, getTileSizeof());
    return newTiles(1);
}

Tile *newTiles(int num)
{
    return calloc((size_t) num, getTileSizeof());
}

void deleteTile(Tile *tile)
{
    free(tile);
    tile = NULL;
}


size_t getTileSizeof()
{
    return sizeof(Tile);
}

tileType getTileType(Tile *tile)
{
    return tile->type;
}

char * const getTileTypeAsText(Tile *tile)
{
    if(!tile)
        return NULL;

    char * result;
    switch (getTileType(tile))
    {
        case WALL:
            result = "Wall";
            break;
        case PATH:
            result = "Path";
            break;
        case ENTRY:
            result = "Entry";
            break;
        case EXIT:
            result = "Exit";
            break;
        default:
            result = "Undefined";
            break;
    }
    return  result;
}

void setTileType(Tile *tile, tileType type)
{
    tile->type = type;
}

void setTileAsPath(Tile *tile)
{
    setTileType(tile, PATH);
}

void setTileAsWall(Tile *tile)
{
    setTileType(tile, WALL);
}

void setTileAsEntry(Tile *tile)
{
    setTileType(tile, ENTRY);
}

void setTileAsExit(Tile *tile)
{
    setTileType(tile, EXIT);
}

Tile * getTileFromArray(Tile *tiles, int pos)
{
    return &tiles[pos];
}
