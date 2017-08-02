//
// Created by gabriel on 15/07/17.
//

#include <malloc.h>
#include "tower.h"
typedef struct Tower
{
    int rng; // Range.
    int dmg; // Damage.
    int rof; // Rate of fire.
    int pos; // Position on the map.
    int target; // Creep targeted.
} Tower;

unsigned int getTowerSizeof()
{
    return sizeof(Tower);
}

Tower *towerNew()
{
//    return calloc(1, getTileSizeof());
    return newTowers(1);
}

Tower *newTowers(unsigned int num)
{
    return calloc(num, getTowerSizeof());
}

void deleteTower(Tower *tower)
{
    free(tower);
}

void initTower(Tower *tower, int rng, int dmg, int rof, int pos, int target)
{
    tower->rng = rng;
    tower->dmg = dmg;
    tower->rof = rof;
    tower->pos =pos;
    tower->target;
}