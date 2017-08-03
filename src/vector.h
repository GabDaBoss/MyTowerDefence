//
// Created by gabriel on 01/08/17.
//

#ifndef MYTOWERDEFENCE_VECTOR_H
#define MYTOWERDEFENCE_VECTOR_H

typedef struct Vector Vector;

void vectorInitDefault(Vector *vector);

Vector *vectorNew(unsigned int capacity, unsigned int sizeOfItem);

Vector *vectorNewDefault(unsigned int sizeOfItem);

void vectorDelete(Vector *vector);

void vectorInit(Vector *vector, int capacity);

int vectorTotal(Vector *vector);

static void vectorResize(Vector *vector, unsigned int capacity);

void vectorAddItem(Vector *vector, unsigned char *item);

void *vectorAddNew(Vector *vector);

void vectorAddItems(Vector *vector, unsigned char *items, int num);

void *vectorGetItems(Vector *vector, int index, int num);

void vectorSetItem(Vector *vector, int index, unsigned char *item);

void *vectorGetItem(Vector *vector, int index);

void vectorDeleteItem(Vector *vector, int index);

void vectorEmpty(Vector *vector);


#endif //MYTOWERDEFENCE_VECTOR_H
