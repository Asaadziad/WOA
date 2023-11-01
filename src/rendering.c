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

void renderTexture(Game game,Texture texture){
    
    SDL_Rect dst;
    dst.x = texture->render_pos.x;
    dst.y = texture->render_pos.y;
    dst.h = texture->height;
    dst.w = texture->width;
    SDL_RenderCopy(game->renderer,texture->texture,NULL,&dst);
}

void renderTextureAt(Game game,Texture texture,int x, int y){
    Vector2f new_pos = {x,y};
    texture->render_pos = new_pos;
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.h = texture->height;
    dst.w = texture->width;
    SDL_RenderCopy(game->renderer,texture->texture,NULL,&dst);
}

void renderPartOfTexture(Game game, Texture texture,SDL_Rect dst,int x, int y){
    if(!texture) return;
    SDL_Rect src;
    src.h = SCREEN_HEIGHT/3;
    src.w = SCREEN_WIDTH/4;
    src.x = x;
    src.y = y;
    SDL_RenderCopy(game->renderer,texture->texture,&dst,&src);
}

void renderButton(Game game,int x, int y, const char* text){
    int global_h = 50;
    int global_w = 100;
    SDL_Rect border;
    border.x = x;
    border.y = y;
    border.h = global_h;
    border.w = global_w;

    SDL_Rect inner;
    inner.x = x + 5;
    inner.y = y + 5;
    inner.h = global_h - 10;
    inner.w = global_w - 10;

    SDL_SetRenderDrawColor(game->renderer, 0,0,0,0);
    SDL_RenderFillRect(game->renderer, &border);
    SDL_SetRenderDrawColor(game->renderer, 255,255,255,0);
    SDL_RenderFillRect(game->renderer, &inner);
}
