//
// Created by gabriel on 15/07/17.
//

#ifndef MYTOWERDEFENCE_TILE_H
#define MYTOWERDEFENCE_TILE_H

typedef struct Tile Tile;
typedef enum tileType{WALL, PATH, ENTRY, EXIT} tileType;

unsigned long getTileSizeof();
void deleteTile(Tile *tile);
Tile *newTile();
Tile *newTiles(int num);
tileType getTileType(Tile *tile);
void setTileType(Tile *tile, tileType type);
void setTileAsPath(Tile *tile);
void setTileAsWall(Tile *tile);
void setTileAsEntry(Tile *tile);
void setTileAsExit(Tile *tile);
Tile * getTileFromMap(Tile* tiles, int pos);
#endif //MYTOWERDEFENCE_TILE_H
