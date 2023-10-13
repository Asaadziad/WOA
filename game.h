#ifndef GAME_H
#define GAME_H

#include "common.h"
#include "texture.h"

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800

#define IS_RUNNING(game) ((game)->state == RUNNING_STATE)

typedef enum {
    RUNNING_STATE,
    QUIT_STATE
} GameState;

typedef struct game_t {
    Texture* current_texture;
    GameState state;
} *Game;

Game initGame();

#endif