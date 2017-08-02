//
// Created by gabriel on 15/07/17.
//

#include "game.h"

#include "util.h"
#include "mapRenderer.h"
#include "menuRenderer.h"

#define MENU_WIDTH 200
static const int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;
static const char *const MAP_FILE = "map.csv";

typedef struct Game
{
    Graphic *graphic;
    GameState *state;
    Map *map;
    Menu *menu;
    MapRenderer *mapRenderer;
    MenuRenderer *menuRenderer;
} Game;

int initGame(Game *game)
{
    game->graphic = newGraphic();
    game->state = newGameState();
    game->map = newMap();
    game->menu = newMenu();
    game->mapRenderer = newMapRenderer();
    game->menuRenderer = newMenuRenderer();

    initMenu(game->menu, "TowerDefense");
    initMenuRenderer(game->menuRenderer, MENU_WIDTH, WINDOW_HEIGHT);


    return initGraphic(game->graphic, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void deleteGame(Game *game)
{

    deleteGraphic(game->graphic);
    deleteGameState(game->state);
    deleteMap(game->map);
    deleteMapRenderer(game->mapRenderer);
    deleteMenuRenderer(game->menuRenderer);
    deleteMenu(game->menu);
}


int game()
{
    Game game;

    if (initGame(&game))
    {
        // Now that we went through the initialization of SDL everything should be good and dandy.
        if (loadMap(game.map, MAP_FILE))
        {
            if (gameLoop(&game))
            {

            }
        }
    }

    return 0;
}


int gameLoop(Game *game)
{

    unsigned int lastTime, currentTime, deltaTime;
    lastTime = currentTime = SDL_GetTicks();
    int cursorX, cursorY;

    char quit = 0;
    SDL_Event event;
    while (!quit)
    {
        calcGraphicSize(game->graphic);
        setMapRendererHeight(game->mapRenderer, getGraphicHeight(game->graphic));
        setMapRendererWidth(game->mapRenderer, getGraphicWidth(game->graphic));
        calcTileSize(game->mapRenderer, game->map);
        setMapRendererWidth(game->mapRenderer, getGraphicWidth(game->graphic) - MENU_WIDTH);
        setMapRendererHeight(game->mapRenderer, getGraphicHeight(game->graphic));
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

            handlePlayFieldScrolling(game->mapRenderer, game->map, game->graphic, cursorX, cursorY, deltaTime);
        }


        setRenderingColor(game->graphic, 0xFFFFFFFF);

        clear(game->graphic);
        drawMap(game->mapRenderer, game->graphic, game->map);

        handleSelector(game->mapRenderer, game->map, game->graphic, cursorX, cursorY);

        setMenuTileInfo(game->menu, getTileTypeAsText(getTile(game->map, getTileIndexUnderPoint(game->mapRenderer, game->map, cursorX, cursorY))));

        drawMenu(game->menuRenderer, game->graphic, game->menu);

        setRenderingColor(game->graphic, 0xffffffff);
//        fillCircle(game->graphic, (Rect){0,0,100, 0});

        renderPresent(game->graphic);
    }


    return 1;
}



