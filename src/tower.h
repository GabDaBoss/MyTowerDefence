//
// Created by gabriel on 15/07/17.
//

#ifndef MYTOWERDEFENCE_TOWER_H
#define MYTOWERDEFENCE_TOWER_H

typedef struct Tower Tower;
typedef struct TowerArray TowerArray;

Tower *newTowers(unsigned int num);

Tower *towerNew();

unsigned int getTowerSizeof();

void deleteTower(Tower *tower);

void initTower(Tower *tower, int rng, int dmg, int rof, int pos, int target);

#endif //MYTOWERDEFENCE_TOWER_H
