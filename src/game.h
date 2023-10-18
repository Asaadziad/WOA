#ifndef GAME_H
#define GAME_H

#include "texture.h"
#include "player.h"

#define SCREEN_HEIGHT 500
#define SCREEN_WIDTH 500
#define WORLD_WIDTH 1250
#define WORLD_HEIGHT 1165

#define PLAYERS_COUNT 1

#define IS_RUNNING(game) ((game)->state == RUNNING_STATE)

typedef enum {
    RUNNING_STATE,
    QUIT_STATE
} GameState;

typedef struct game_t {
    Player* players;
    GameState state;
    Texture* current_texture;
    Texture* world_texture;
    SDL_Renderer* renderer;
} *Game;

Game initGame();
void handleEvents(SDL_Event* e,Game game);
void initEntities(Game game);
void renderEntities(Game game);
void renderWorld(Game game);

void clearScreen(Game game);
void updateScreen(Game game);
void quitGame(Game game);

#endif