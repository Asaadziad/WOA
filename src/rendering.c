#include "rendering.h"
#include "texture.h"
#include "movementHandler.h"
#define PLAYER_VEL 1

void renderPlayer(Game game,Player p){
    SDL_Rect rect;
        rect.x = p->x;
        rect.y = p->y;
        rect.w = p->width;
        rect.h = p->height;

    SDL_RenderFillRect(game->renderer,&rect);
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);

    handleMovement(PLAYER_TYPE,game->players[0]);
//    SDL_Rect src = {};
//    SDL_Rect dst = {};
//    SDL_RenderCopy(game->renderer,game->current_texture->texture,&src,&dst);
}