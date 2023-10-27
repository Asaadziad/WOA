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

    //renderPlayerTiles(game,game->players[0]->tile_list);
}

void renderTile(Game game,Tile tile){
    if(!tile) return;
    SDL_Rect rect;
        rect.x = tile->current_position.x;
        rect.y = tile->current_position.y - 25;
        rect.w = 50;
        rect.h = 50;

    SDL_SetRenderDrawColor(game->renderer,255,0,0,255);
    SDL_RenderFillRect(game->renderer,&rect);
    
}

void renderLabel(Game game){
    SDL_Texture* label;

    SDL_Color black = {0,0,0,0};
    SDL_Surface* surface = TTF_RenderText_Solid(game->global_font,"hello world",black);
    if(!surface) return;

    label = SDL_CreateTextureFromSurface(game->renderer , surface );

    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = surface->w;
    src.h = surface->h;

    SDL_RenderCopy(game->renderer,label,NULL,&src);

    SDL_FreeSurface( surface );
}

void renderTexture(Game game,Texture texture,int x, int y){
    SDL_Rect dst;
    dst.x = texture->render_pos.x;
    dst.y = texture->render_pos.y;
    dst.h = texture->height;
    dst.w = texture->width;
    SDL_RenderCopy(game->renderer,texture->texture,NULL,&dst);
}