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
#include "DialougeManager.h"
#include "TileManager.h"

#define IS_RUNNING(game) ((game)->state != QUIT_STATE)

typedef enum {
    RUNNING_STATE,
    QUIT_STATE,
    MENU_STATE,
    GAME_OVER_STATE,
    DIALOUGE_STATE,
} GameState;

struct game_managers {
    TaskManager task_manager;
    TextureManager texture_manager;
    ComponenetsManager components_manager;
    ObjectManager object_manager;
    NpcManager npc_manager;
    DialougeManager dialouge_manager;
    TileManger tile_manager;
};

struct game_window {
    TTF_Font* global_font;
    SDL_Renderer* renderer;
    SDL_Rect camera;
    int mouse_x;
    int mouse_y;
};

typedef struct game_t {
    Player* players;
    GameState state;
    struct game_managers* managers;
    struct game_window* window;
    Int8 handeled_event;
    int* map;
} *Game;


/*{
  Accept Resources() // from another  source/ Component - Data file/ Network (multiplayer thing) / ...
  Update& render()
}*/

Game initGame();
void handleEvents(SDL_Event* e,Game game);
void initEntities(Game game);

// Game get resources 
void loadTextures(Game game);

// loop once and do 2 operations
void gameUpdateAndRender(Game game);

// loop twice and do 2 operations
void initRendering(Game game);
void gameUpdate(Game game);


// window functions - window class or something
void clearScreen(Game game);
void updateScreen(Game game);
void quitGame(Game game);

#endif
