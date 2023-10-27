#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL_ttf.h"

#include "texture.h"
#include "player.h"
#include "DS/list.h"

#define SCREEN_HEIGHT 500
#define SCREEN_WIDTH 500
#define WORLD_WIDTH 1250
#define WORLD_HEIGHT 1165

#define PLAYERS_COUNT 1

#define IS_RUNNING(game) ((game)->state != QUIT_STATE)

typedef enum {
    RUNNING_STATE,
    QUIT_STATE,
    MENU_STATE
} GameState;

typedef struct game_t {
    Player* players;
    GameState state;
    List textures;
    TTF_Font* global_font;
    SDL_Renderer* renderer;
} *Game;

Game initGame();
void handleEvents(SDL_Event* e,Game game);
void initTextures(Game game);
void initEntities(Game game);
void initRendering(Game game);

void loadTextures(Game game);

void renderEntities(Game game);

void clearScreen(Game game);
void updateScreen(Game game);
void quitGame(Game game);

#endif