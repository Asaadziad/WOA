#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL_ttf.h"

#include "texture.h"
#include "player.h"
#include "DS/list.h"
#include "taskManager.h"
#include "TextureManager.h"
#include "ComponentsManager.h"
#include "ObjectManager.h"
#include "npcManager.h"
#include "common.h"

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
    List objects;
    TaskManager task_manager;
    TextureManager texture_manager;
    ComponenetsManager components_manager;
    ObjectManager object_manager;
    NpcManager npc_manager;
    TTF_Font* global_font;
    SDL_Renderer* renderer;
    SDL_Rect camera;
    int mouse_x;
    int mouse_y;
    uint8_t handeled_event;
    int* map;

} *Game;

Game initGame();
void handleEvents(SDL_Event* e,Game game);
void initEntities(Game game);
void initRendering(Game game);
void gameUpdate(Game game);

void loadTextures(Game game);

void clearScreen(Game game);
void updateScreen(Game game);
void quitGame(Game game);

#endif