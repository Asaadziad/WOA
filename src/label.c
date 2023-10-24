#include "label.h"
#include "SDL2/SDL_ttf.h"
#include "game.h"

Label createLabel(Game game,const char* text, int x, int y){
    Label s = (Label)malloc(sizeof(*s));
    if(!s) return NULL;
    SDL_Color black = {0,0,0,0};
    SDL_Surface* surface = TTF_RenderText_Solid(game->global_font,text,black);
    if(!surface) return NULL;

    s->labelTexture = SDL_CreateTextureFromSurface(game->renderer , surface );
    if(!s->labelTexture) return NULL;

    s->height = surface->h;
    s->width = surface->w;

    SDL_FreeSurface( surface );

    return s;
}

void drawLabel(Game game,Label label){
    if(!label) return;
    SDL_Rect src;
    src.x = label->position.x;
    src.y = label->position.y;
    src.w = label->width;
    src.h = label->width;

    SDL_RenderCopy(game->renderer,label->labelTexture,&src,NULL);
}