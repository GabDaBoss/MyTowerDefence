//
// Created by gabriel on 15/07/17.
//

#ifndef MYTOWERDEFENCE_TOWER_H
#define MYTOWERDEFENCE_TOWER_H

typedef struct Tower Tower;
Tower *newTowers(unsigned int num);
Tower *newTower();
unsigned int getTowerSizeof();
void deleteTower(Tower *tower);
#endif //MYTOWERDEFENCE_TOWER_H
