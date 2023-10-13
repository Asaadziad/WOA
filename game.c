#include "game.h"
#include "stdlib.h"

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
            default: {}
        }
    }
}
