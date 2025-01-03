#include "headers/label.h"
#include "SDL2/SDL_ttf.h"
#include "headers/game.h"

Label createLabel(Game game,const char* text, int x, int y){
    Label s = (Label)malloc(sizeof(*s));
    if(!s) return NULL;
    SDL_Color black = {0,0,0,0};

    
    SDL_Surface* surface = TTF_RenderText_Solid(getGlobalFont(game), text, black);
    if(!surface) return NULL;

    s->labelTexture = SDL_CreateTextureFromSurface((getRenderer(game)) , surface );
    if(!s->labelTexture) return NULL;

    s->height = surface->h;
    s->width = surface->w;

    SDL_FreeSurface( surface );

    return s;
}

