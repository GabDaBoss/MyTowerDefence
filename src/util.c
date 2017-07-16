//
// Created by gabriel on 30/06/17.
//

#include "util.h"
int min(int x, int y)
{
//    return y ^ ((x ^ y) & -(x < y));
    return x < y ? x : y;
}

int max(int x, int y)
{
//    return x ^ ((x ^ y) & -(x < y));
    return x < y ? y : x;
}
