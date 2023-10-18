#include "game.h"
#include "stdlib.h"

#include "logic.h"
#include "memory.h"
#include "rendering.h"
#include "movementHandler.h"

Game initGame(){
    Game new_g = (Game)malloc(sizeof(*new_g));
    if(!new_g) return NULL;
    
    new_g->current_texture = initTexture();
    new_g->world_texture = initTexture();
    new_g->state = RUNNING_STATE;

    
    return new_g;
}

void handleEvents(SDL_Event* e,Game game){
    while(SDL_PollEvent(e) != 0){
        switch(e->type){
            case SDL_QUIT:
                game->state = QUIT_STATE;
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
    SDL_RenderClear(game->renderer);
    SDL_SetRenderDrawColor(game->renderer,0xff,0xff,0xff,0xff);
}
void updateScreen(Game game){
    SDL_RenderPresent(game->renderer);
}


void quitGame(Game game){
    FREE_ARRAY(Player,game->players,PLAYERS_COUNT);
    free(game);
}
