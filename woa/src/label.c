#include "label.h"
#include "SDL2/SDL_ttf.h"
#include "game.h"

Label createLabel(Game game,const char* text, int x, int y){
    Label s = (Label)malloc(sizeof(*s));
    if(!s) return NULL;
    SDL_Color black = {0,0,0,0};
    SDL_Surface* surface = TTF_RenderText_Solid(game->window->global_font,text,black);
    if(!surface) return NULL;

    s->labelTexture = SDL_CreateTextureFromSurface(game->window->renderer , surface );
    if(!s->labelTexture) return NULL;

    s->height = surface->h;
    s->width = surface->w;

    SDL_FreeSurface( surface );

    return s;
}

