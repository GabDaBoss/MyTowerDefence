//
// Created by gabriel on 15/07/17.
//

#ifndef MYTOWERDEFENCE_GAME_H
#define MYTOWERDEFENCE_GAME_H

#include "graphic.h"
#include "map.h"
#include "gamestate.h"
#include "mapRenderer.h"

typedef struct Game Game;

int game();

int loadMap(Map *map, const char *const filename);

int gameLoop(Game *game);

#endif //MYTOWERDEFENCE_GAME_H
