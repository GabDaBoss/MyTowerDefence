//
// Created by gabriel on 15/07/17.
//

#ifndef MYTOWERDEFENCE_GAMESTATE_H
#define MYTOWERDEFENCE_GAMESTATE_H
typedef struct GameState GameState;

GameState *newGameState();
void deleteGameState(GameState* state);

unsigned long getGameStateSizeOf();

#endif //MYTOWERDEFENCE_GAMESTATE_H
