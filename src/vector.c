//
// Created by gabriel on 01/08/17.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

#define VECTOR_INIT_CAPACITY 4
typedef struct Vector
{
//    void **items;
    unsigned char *items;
    unsigned int capacity, total, sizeOfItem;
} Vector;


Vector *vectorNew(unsigned int capacity, unsigned int sizeOfItem)
{
    Vector *vector = calloc(1, sizeof(Vector));
    vector->sizeOfItem = sizeOfItem;
    vector->capacity = capacity;
    vector->total = 0;
    vector->items = malloc(sizeOfItem * vector->capacity);
    return vector;
}

Vector *vectorNewDefault(unsigned int sizeOfItem)
{
    return vectorNew(VECTOR_INIT_CAPACITY, sizeOfItem);
}

void vectorDelete(Vector *vector)
{
    vectorEmpty(vector);
    free(vector);
}

void vectorInit(Vector *vector, int capacity)
{
}

void vectorInitDefault(Vector *vector)
{
    vectorInit(vector, VECTOR_INIT_CAPACITY);
}

int vectorTotal(Vector *vector)
{
    return vector->total;
}

static void vectorResize(Vector *vector, unsigned int capacity)
{
    unsigned char *items = realloc(vector->items, vector->sizeOfItem * capacity);
    if (items)
    {
        vector->items = items;
        vector->capacity = capacity;
    }
}

void vectorAddItem(Vector *vector, unsigned char *item)
{
    if (vector->capacity == vector->total)
    {
        vectorResize(vector, vector->capacity * 2);
    }
//    vector->items[vector->total*vector->sizeOfItem] = item;
    memcpy(&vector->items[vector->total++ * vector->sizeOfItem], item, vector->sizeOfItem);
}

void vectorSetItem(Vector *vector, int index, unsigned char *item)
{
    if (index >= 0 && index < vector->total)
//        vector->items[index] = item;
        memcpy(&vector->items[index * vector->sizeOfItem], item, vector->sizeOfItem);
}


void *vectorGetItem(Vector *vector, int index)
{
    if (index >= 0 && index < vector->total)
        return &vector->items[index * vector->sizeOfItem];
    return NULL;
}

void vectorDeleteItem(Vector *vector, int index)
{
    if (index < 0 || index >= vector->total)
        return;

    vector->items[index] = NULL;

    for (int i = index; i < vector->total - 1; i++)
    {
        vector->items[i] = vector->items[i + 1];
        vector->items[i + 1] = NULL;
    }
    vector->total--;

    if (vector->total > 0 && vector->total == vector->capacity / 4)
        vectorResize(vector, vector->capacity / 2);
}

void vectorEmpty(Vector *vector)
{
    free(vector->items);
}
