//
// Created by gabriel on 15/07/17.
//

#include "game.h"

#include "util.h"
#include "mapRenderer.h"

#define MENU_WIDTH 200
static const int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;
static const char *const MAP_FILE = "map.csv";


int game()
{
    Graphic *graphic = newGraphic();
    GameState *state = newGameState();
    MapRenderer *mapRenderer = newMapRenderer();
    Map *map = newMap();
    if (initGraphic(graphic, WINDOW_WIDTH, WINDOW_HEIGHT))
    {
        // Now that we went through the initialization of SDL everything should be good and dandy.
        if (loadMap(map, MAP_FILE))
        {
            if (gameLoop(map, graphic, state, mapRenderer))
            {

            }
        }
    }

    deleteGraphic(graphic);
    deleteGameState(state);
    deleteMap(map);
    deleteMapRenderer(mapRenderer);

    return 0;
}

void drawMenu(Graphic *graphic)
{
    setRenderingColor(graphic, 0x000000FF);
    fillRect(graphic, (Rect) {getGraphicWidth(graphic) - MENU_WIDTH, 0, MENU_WIDTH, getGraphicHeight(graphic)});
    drawText(graphic, "Tower Defense", (Rect) {getGraphicWidth(graphic) - MENU_WIDTH, 0, MENU_WIDTH, 14});
}

int gameLoop(Map *map, Graphic *graphic, GameState *state, MapRenderer *mapRenderer)
{

    unsigned int lastTime, currentTime, deltaTime;
    lastTime = currentTime = SDL_GetTicks();
    int cursorX, cursorY;

    char quit = 0;
    SDL_Event event;
    while (!quit)
    {
        calcGraphicSize(graphic);
        setMapRendererHeight(mapRenderer, getGraphicHeight(graphic));
        setMapRendererWidth(mapRenderer, getGraphicWidth(graphic));
        calcTileSize(mapRenderer, map);
        setMapRendererWidth(mapRenderer, getGraphicWidth(graphic) - MENU_WIDTH);
        setMapRendererHeight(mapRenderer, getGraphicHeight(graphic));
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    quit = 1;
                    break;
            }
        }

        currentTime = SDL_GetTicks();
//        deltaTime = (unsigned int) max(currentTime - lastTime - 20, 0 );
//        lastTime += ((deltaTime > 0) * 20) + deltaTime;
        deltaTime = currentTime - lastTime;

        SDL_GetMouseState(&cursorX, &cursorY);
        if (deltaTime > 1)
        {
            lastTime = SDL_GetTicks();

            handlePlayFieldScrolling(mapRenderer,map, graphic, cursorX, cursorY, deltaTime);
        }


        setRenderingColor(graphic, 0xFFFFFFFF);

        clear(graphic);
        drawMap(mapRenderer,graphic, map);

        handleSelector(mapRenderer, map, graphic, cursorX, cursorY);

        drawMenu(graphic);

        renderPresent(graphic);
    }


    return 1;
}



