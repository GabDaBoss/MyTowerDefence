//
// Created by gabriel on 15/07/17.
//

#include <malloc.h>
#include "creep.h"
typedef struct Creep
{
    int health;
    int speed;
    int pos;
} Creep;
Creep **newCreeps(int num)
{
    return calloc((size_t) num, getCreepSizeof());
}
Creep *newCreep()
{
    return newCreeps(1)[0];
}
void deleteCreep(Creep *creep)
{
    free(creep);
    creep = NULL;
}
unsigned long getCreepSizeof()
{
    return sizeof(Creep);
}
