//
// Created by gabriel on 15/07/17.
//

#include <stdlib.h>
#include <stdio.h>
#include "map.h"
#include "vector.h"

typedef struct Map
{
    Vector *tileVec;
    int width;
} Map;

Map *newMap()
{
    return calloc(1, getMapSizeof());
}


int loadMap(Map *map, const char *const filename)
{
    FILE *file = fopen(filename, "r");
    int i = 0;
    if (file)
    {
        char c;
        map->tileVec = vectorNewDefault(sizeof(void *));
        Tile *tile;

        // First Read just to get the map size, and other data.
        while ((c = (char) getc(file)) != EOF)
        {
            switch (c)
            {
                case 'i':
//                    map->numPaths++;
//                    tile = newTile();
                    tile = vectorAddNew(map->tileVec);
                    setTileAsEntry(tile);
//                    vectorAddItem(map->tileVec, (unsigned char *) tile);
//                    map->size++;
                    break;
                case 'o':
//                    (map->numPaths)++;
//                    tile = newTile();
                    tile = vectorAddNew(map->tileVec);
                    setTileAsExit(tile);
//                    vectorAddItem(map->tileVec, (unsigned char *) tile);
//                    map->size++;
                    break;
                case 'p':
//                    (map->numPaths)++;
//                    tile = newTile();
                    tile = vectorAddNew(map->tileVec);
                    setTileAsPath(tile);
//                    vectorAddItem(map->tileVec, (unsigned char *) tile);
//                    map->size++;
                    break;
                case 'w':
//                    (map->numWalls)++;
//                    map->size++;
//                    tile = newTile();
                    tile = vectorAddNew(map->tileVec);
                    setTileAsWall(tile);
//                    vectorAddItem(map->tileVec, (unsigned char *) tile);
                    break;
                case '\n':
                    if (!map->width)
                        map->width = vectorTotal(map->tileVec);
                default:
                    break;
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
//    for (int i = vectorTotal(map->tileVec); i-- > 0;)
//    {
//        free(vectorGetItem(map->tileVec, i));
//    }
    vectorDelete(map->tileVec);
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
    return getMapSize(map) / getMapWidth(map);
//    return map->size / map->width;
}

int getMapSize(Map *map)
{
    return vectorTotal(map->tileVec);
//    return map->size;
}

Tile *getTile(Map *map, int i)
{
//    return &map->tileArray[i];
    return vectorGetItem(map->tileVec, i);
//    return getTileFromArray(map->tileArray, i);
}
