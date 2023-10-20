#include "rendering.h"
#include "texture.h"
#include "movementHandler.h"


void renderPlayer(Game game,Player p){
    SDL_Rect rect;
        rect.x = p->position.x;
        rect.y = p->position.y;
        rect.w = p->width;
        rect.h = p->height;

    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(game->renderer,&rect);

    handleMovement(PLAYER_TYPE,game->players[0]);

    int x = 0;

}

void renderTile(Game game,int x){
    SDL_Rect rect;
        rect.x = 600 + x;
        rect.y = 300;
        rect.w = 50;
        rect.h = 50;

    SDL_SetRenderDrawColor(game->renderer,255,0,0,255);
    SDL_RenderFillRect(game->renderer,&rect);
    
}