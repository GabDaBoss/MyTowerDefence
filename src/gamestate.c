//
// Created by gabriel on 15/07/17.
//

#include <malloc.h>
#include "gamestate.h"

typedef struct GameState
{

} GameState;
GameState *newGameState()
{
    return calloc(1, getGameStateSizeOf());
}
void deleteGameState(GameState* state)
{
    free(state);
}
unsigned long getGameStateSizeOf()
{
    return sizeof(GameState);
}
