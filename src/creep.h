//
// Created by gabriel on 15/07/17.
//

#ifndef MYTOWERDEFENCE_CREEP_H
#define MYTOWERDEFENCE_CREEP_H

typedef struct Creep Creep;
Creep **newCreeps(int num);
Creep *newCreep();
unsigned long getCreepSizeof();
void deleteCreep(Creep *creep);
#endif //MYTOWERDEFENCE_CREEP_H
