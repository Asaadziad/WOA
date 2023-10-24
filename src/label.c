#include "label.h"
#include "SDL2/SDL_ttf.h"

void drawLabel(const char* text,int x, int y){
    SDL_Color black = {0,0,0,0};
    TTF_Font* gFont = TTF_OpenFont( "16_true_type_fonts/lazy.ttf", 28 );
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, text, black );
}