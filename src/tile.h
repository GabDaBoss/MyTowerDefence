//
// Created by gabriel on 15/07/17.
//

#ifndef MYTOWERDEFENCE_TILE_H
#define MYTOWERDEFENCE_TILE_H

typedef struct Tile Tile;
typedef enum tileType
{
    WALL, PATH, ENTRY, EXIT
} tileType;

unsigned long getTileSizeOf();

void deleteTile(Tile *tile);

Tile *newTile();

Tile *newTiles(int num);

tileType getTileType(Tile *tile);

char *const getTileTypeAsText(Tile *tile);

void setTileType(Tile *tile, tileType type);

void setTileAsPath(Tile *tile);

void setTileAsWall(Tile *tile);

void setTileAsEntry(Tile *tile);

void setTileAsExit(Tile *tile);
Tile * getTileFromArray(Tile *tiles, int pos);
#endif //MYTOWERDEFENCE_TILE_H
