#include "game.h"
#include "stdlib.h"

#include "logic.h"
#include "memory.h"
#include "rendering.h"
#include "movementHandler.h"
#include "tile.h"

Game initGame(){
    Game new_g = (Game)malloc(sizeof(*new_g));
    if(!new_g) return NULL;
    
    new_g->current_texture = initTexture();
    new_g->world_texture = initTexture();
    new_g->state = RUNNING_STATE;

    
    return new_g;
}

static void handleKey(Game game,SDL_Keycode code){
    Player asaad = game->players[0];
    switch(code){
        case SDLK_LEFT:
        handlePlayerMovement(asaad,MOVE_LEFT);
        break;
        case SDLK_RIGHT:
        handlePlayerMovement(asaad,MOVE_RIGHT);
        break;
        case SDLK_UP:
        handlePlayerMovement(asaad,MOVE_UP);
        break;
        case SDLK_DOWN:
        handlePlayerMovement(asaad,MOVE_DOWN);
        break;
        case SDLK_SPACE:
        shootTile(game->players[0]);

        break;
        default:
        break;
    }
}

void handleEvents(SDL_Event* e,Game game){
    while(SDL_PollEvent(e) != 0){
        switch(e->type){
            case SDL_QUIT:
                game->state = QUIT_STATE;
            break;
            case SDL_KEYDOWN:
                handleKey(game,e->key.keysym.sym);
            break;
            case SDL_MOUSEBUTTONDOWN:
                game->players[0]->isMoving = true;
            break;
            default: {}
        }
    }
}

void initEntities(Game game){
    game->players = ALLOCATE(Player, PLAYERS_COUNT);
    Player asaad = initPlayer(50,50,200,200);
    game->players[0] = asaad;
}



void renderEntities(Game game){
    renderPlayer(game,game->players[0]);
    
}


void clearScreen(Game game){
    SDL_SetRenderDrawColor(game->renderer,0xff,0xff,0xff,0xff);
    SDL_RenderClear(game->renderer);
}
void updateScreen(Game game){
    SDL_RenderPresent(game->renderer);
}


void quitGame(Game game){
    FREE_ARRAY(Player,game->players,PLAYERS_COUNT);
    free(game);
}
