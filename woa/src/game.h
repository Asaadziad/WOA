#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL.h"

#define IS_RUNNING(game) ((game)->state != QUIT_STATE)


typedef SDL_Renderer* Renderer;
typedef SDL_Event* Event;
typedef struct game_managers* Managers;
typedef struct game_window* Window;
typedef struct game_t* Game;

typedef enum {
    RUNNING_STATE,
    QUIT_STATE,
    MENU_STATE,
    GAME_OVER_STATE,
    DIALOUGE_STATE,
} GameState;



Renderer getRenderer(Game game);

/*{
  Accept Resources() // from another  source/ Component - Data file/ Network (multiplayer thing) / ...
  Update& render()
}*/

Game initGame();
void handleEvents(Event e,Game game);
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