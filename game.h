#ifndef GAME_H
#define GAME_H

#include "texture.h"
#include "player.h"

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800

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
    SDL_Renderer* renderer;
} *Game;

Game initGame();
void handleEvent(SDL_Event* e,Game game);
void initEntities(Game game);
void renderEntities(Game game);

void quitGame(Game game);

#endif