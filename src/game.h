//
// Created by gabriel on 15/07/17.
//

#ifndef MYTOWERDEFENCE_GAME_H
#define MYTOWERDEFENCE_GAME_H

#include "graphic.h"
#include "map.h"
#include "gamestate.h"
#include "mapRenderer.h"


int game();

int loadMap(Map *map, const char *const filename);

int gameLoop(Map *map, Graphic *graphic, GameState *state, MapRenderer *mapRenderer);

#endif //MYTOWERDEFENCE_GAME_H
