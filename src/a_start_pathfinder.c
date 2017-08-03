//
// Created by gabriel on 02/08/17.
//

#include "a_start_pathfinder.h"
#include "vector.h"
#include "map.h"
#include <stdlib.h>

typedef struct AStarPathfinder
{
    Vector *openVec;
    Vector *closeVec;
} AStarPathfinder;

typedef struct _AStarNode
{
    int heuristic;
    int cost;
    int pos;
    AStarNode *parent;
} AStarNode;


void initAStarPathfinder(AStarPathfinder *pathfinder)
{
    pathfinder->openVec = vectorNewDefault(sizeof(AStarNode));
    pathfinder->closeVec = vectorNewDefault(sizeof(AStarNode));
}

Vector *findPath(AStarPathfinder *pathfinder, Map *map, int start, int end)
{
    int width = getMapWidth(map);
    AStarNode startNode = {0};
    AStarNode endNode = {0};
    AStarNode currentNode = {0};

    Vector *pathVec = vectorNewDefault(sizeof(int));
    int i;



    return pathVec;
}
