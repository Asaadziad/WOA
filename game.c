#include "game.h"
#include "stdlib.h"

#include "logic.h"
#include "memory.h"
#include "rendering.h"

Game initGame(){
    Game new_g = (Game)malloc(sizeof(*new_g));
    if(!new_g) return NULL;
    
    new_g->current_texture = initTexture();
    new_g->state = RUNNING_STATE;

    
    return new_g;
}

void handleEvent(SDL_Event* e,Game game){
    while(SDL_PollEvent(e) != 0){
        switch(e->type){
            case SDL_QUIT:
                game->state = QUIT_STATE;
            break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&game->players[0]->walk_to_x,&game->players[0]->walk_to_y);
            break;
            default: {}
        }
    }
}

void initEntities(Game game){
    game->players = ALLOCATE(Player, PLAYERS_COUNT);
    Player asaad = initPlayer(50,50);
    game->players[0] = asaad;
}

void renderEntities(Game game){
    int p_x = game->players[0]->x;
    int p_y = game->players[0]->y;
    render_character(game->renderer,game,p_x,p_y);
}

void quitGame(Game game){
    FREE_ARRAY(Player,game->players,PLAYERS_COUNT);
    free(game);
}
