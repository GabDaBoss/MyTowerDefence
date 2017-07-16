//
// Created by gabriel on 15/07/17.
//

#include <stdlib.h>
#include <stdio.h>
#include "map.h"
#include "tile.h"
#include "creep.h"
#include "tower.h"

typedef struct Map
{
    Tile *tileMap;
    Creep **creepMap;
    Tower **towerMap;
    int size, width, numPaths, numWalls, entry, exit, tileSize, viewPosX, viewPosY;
    double zoom;
} Map;

Map *newMap()
{
    Map *map = calloc(1, getMapSizeof());
    return map;
}


int loadMap(Map *map, const char *const filename)
{
    FILE *file = fopen(filename, "r");
    int i = 0;
    if (file)
    {
        char c;

        // First Read just to get the map size, and other data.
        while ((c = (char) getc(file)) != EOF)
        {
            switch (c)
            {
                case 'i':
                    (map->numPaths)++;
                    map->size++;
                    break;
                case 'o':
                    (map->numPaths)++;
                    map->size++;
                    break;
                case 'p':
                    (map->numPaths)++;
                    map->size++;
                    break;
                case 'w':
                    (map->numWalls)++;
                    map->size++;
                    break;
                case '\n':
                    if (!map->width)
                        map->width = map->size;
                default:break;
            }
        }

        // create the map tiles.
        map->tileMap = newTiles(map->size);

        // Second read to load the data of the tiles;
        rewind(file);
        while ((c = (char) getc(file)) != EOF)
        {
            switch (c)
            {
                case 'i':
                    map->entry = i;
//                    setTileAsPath(&(map->tileMap[i]));
                    setTileAsEntry(getTileFromMap(map->tileMap, i));
                    i++;
                    break;
                case 'o':
                    map->exit = i;
//                    setTileAsPath(&map->tileMap[i]);
                    setTileAsEntry(getTileFromMap(map->tileMap, i));
                    i++;
                    break;
                case 'p':
//                    setTileAsPath(&map->tileMap[i]);
                    setTileAsPath(getTileFromMap(map->tileMap, i));
                    i++;
                    break;
                case 'w':
//                    setTileAsWall(&map->tileMap[i]);
                    setTileAsWall(getTileFromMap(map->tileMap, i));
                    i++;
                    break;
                default:break;
            }
        }
        fclose(file);
    } else
    {
        fprintf(stderr, "Couldn't open map file: %s\n", filename);
        return -1;
    }
    return 1;
}

void deleteMap(Map *map)
{
    free(map);
    map = NULL;
}


size_t getMapSizeof()
{
    return sizeof(Map);
}

int getMapWidth(Map *map)
{
    return map->width;
}
int getMapHeight(Map *map)
{
    return map->size / map->width;
}
int getMapSize(Map *map)
{
    return map->size;
}
Tile* getTile(Map* map, int i)
{
//    return map->tileMap[i];
    return getTileFromMap(map->tileMap, i);
}
