//
// Created by gabriel on 29/04/17.
//

#include <SDL.h>

static const int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600, MAX_MAP_SIZE = 1000, TILE_SIZE = 50, SCREEN_SCROLL_WIDTH = 50;
static const int SCREEN_SCROLL_SPEED = 1;
static const char *const MAP_FILE = "map.csv";

typedef struct Tower
{
    int rng; // Range.
    int dmg; // Damage.
    int rof; // Rate of fire.
    int pos; // Position on the map.
    int target; // Creep targeted.
} Tower;

typedef struct Creep
{
    int health;
    int speed;
    int pos;
} Creep;

typedef struct Tile
{
    char type;
    int occupied;
} Tile;

int min(int x, int y)
{
    return y ^ ((x ^ y) & -(x < y));
}

int max(int x, int y)
{
    return x ^ ((x ^ y) & -(x < y));
}

int initSDL(SDL_Window *window, SDL_Renderer **renderer);

int loadMap(
        Tile map[]
        , int *mapSize
        , int *mapWidth
        , int *numPaths
        , int *numWalls
        , int *entry
        , int *exit
        , const char *const filename
);

int game(
        Tile map[]
        , int *mapSize
        , int *mapWidth
        , int *numPaths
        , int *numWalls
        , int *entry
        , int *exit
        , SDL_Renderer *renderer
);

int main(int argc, char *argv[])
{
    char c = 127;
    fprintf(stderr, "%d", min(0, -10));
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    Tile map[MAX_MAP_SIZE];

    int mapSize = 0, mapWidth = 0, numPaths = 0, numWalls = 0, entry = 0, exit = 0;
    if (initSDL(window, &renderer))
    {
        // Now that we went through the initialization of SDL everything should be good and dandy.
        if (loadMap(map, &mapSize, &mapWidth, &numPaths, &numWalls, &entry, &exit, MAP_FILE))
        {
            if (game(map, &mapSize, &mapWidth, &numPaths, &numWalls, &entry, &exit, renderer))
            {

            }
        }
    }

    return 0;
}

int initSDL(SDL_Window *window, SDL_Renderer **renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "SDL couldn't initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    } else
    {
        window = SDL_CreateWindow("MyTowerDefence", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                                  WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

        if (window == NULL)
        {
            fprintf(stderr, "Window couldn't be created! SDL_Error: %s\n", SDL_GetError());
            return -1;
        } else
        {
            *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            if (*renderer == NULL)
            {
                fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
                return -1;
            }
        }
    }
    return 1;
}

int loadMap(
        Tile map[]
        , int *mapSize
        , int *mapWidth
        , int *numPaths
        , int *numWalls
        , int *entry
        , int *exit
        , const char *const filename
)
{
    FILE *file = fopen(filename, "r");
    int i = 0;
    if (file)
    {
        char c;
        while ((c = (char) getc(file)) != EOF && i < MAX_MAP_SIZE)
        {
            int valid = 1;
            switch (c)
            {
                case 'i':
                    *entry = i;
                    break;
                case 'o':
                    *exit = i;
                    break;
                case 'p':
                    (*numPaths)++;
                    break;
                case 'w':
                    (*numWalls)++;
                    break;
                case '\n':
                    if (!*mapWidth)
                        *mapWidth = i;
                case ',':
                default:
                    valid = 0;
                    break;
            }

            if (valid)
            {
                map[i].type = c;
                map[i].occupied = 0;
                i++;
            }
        }
        *mapSize = i;
    } else
    {
        fprintf(stderr, "Couldn't open map file: %s\n", filename);
        return -1;
    }
    return 1;
}

int game(
        Tile map[]
        , int *mapSize
        , int *mapWidth
        , int *numPaths
        , int *numWalls
        , int *entry
        , int *exit
        , SDL_Renderer *renderer
)
{
    double zoom =
            max(max(WINDOW_WIDTH / *mapWidth, TILE_SIZE), max(WINDOW_HEIGHT / (*mapSize / *mapWidth), TILE_SIZE)) /
            (double) TILE_SIZE;
    Tower towers[*numWalls];
    Creep creeps[*numPaths];
    int windowPosX = 0, windowPosY = 0;
    unsigned int lastTime, currentTime, deltaTime;
    lastTime = currentTime = SDL_GetTicks();
    int cursorX, cursorY;

    char quit = 0;
    while (!quit)
    {
        SDL_Event event;
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
        if (deltaTime > 2)
        {
            lastTime = SDL_GetTicks();
            windowPosX += (int) (deltaTime * SCREEN_SCROLL_SPEED) * ((min(0, cursorX - SCREEN_SCROLL_WIDTH)) |
                                                                     (max(0, cursorX - WINDOW_WIDTH -
                                                                             SCREEN_SCROLL_WIDTH))) /
                          SCREEN_SCROLL_WIDTH;
            windowPosX = min(max(0, windowPosX), (int) (*mapWidth * TILE_SIZE * zoom - WINDOW_WIDTH));

            windowPosY += (int) (deltaTime * SCREEN_SCROLL_SPEED) * ((min(0, cursorY - SCREEN_SCROLL_WIDTH)) |
                                                                     (max(0, cursorY - WINDOW_HEIGHT +
                                                                             SCREEN_SCROLL_WIDTH))) /
                          SCREEN_SCROLL_WIDTH;
            windowPosY = min(max(0, windowPosY),
                             (int) (((*mapSize / *mapWidth) * TILE_SIZE * zoom) - WINDOW_HEIGHT));
        }


        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < *mapSize; i++)
        {
            switch (map[i].type)
            {
                case 'w':
                    SDL_SetRenderDrawColor(renderer, 19, 132, 48, 255);
                    break;
                case 'p':
                    SDL_SetRenderDrawColor(renderer, 96, 67, 0, 255);
                    break;
                case 'i':
                    SDL_SetRenderDrawColor(renderer, 19, 132, 126, 255);
                    break;
                case 'o':
                    SDL_SetRenderDrawColor(renderer, 132, 19, 55, 255);
                    break;
                default:
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    break;
            }
            SDL_Rect rect = {(int) ((i % *mapWidth) * TILE_SIZE * zoom) - windowPosX,
                             (int) ((i / *mapWidth) * TILE_SIZE * zoom) - windowPosY,
                             (int) (TILE_SIZE * zoom), (int) (TILE_SIZE * zoom)};
            SDL_RenderFillRect(renderer, &rect);
        }


        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        int cursorTile = (int) (((int)((cursorY + windowPosY) / (TILE_SIZE * zoom)) * *mapWidth) +
                                ((cursorX + windowPosX) / (TILE_SIZE * zoom)));
        SDL_Rect rect = {(int) ((cursorTile % *mapWidth) * TILE_SIZE * zoom) - windowPosX,
                         (int) ((cursorTile / *mapWidth) * TILE_SIZE * zoom) - windowPosY,
                         (int) (TILE_SIZE * zoom), (int) (TILE_SIZE * zoom)};
        SDL_RenderDrawRect(renderer, &rect);

        SDL_RenderPresent(renderer);
    }


    return 1;
}
