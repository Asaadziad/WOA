#include "rendering.h"
#include "texture.h"

static void render(SDL_Renderer* renderer,Texture* texture,int x,int y,SDL_Rect* clip){
    if(!texture){
        fprintf(stderr,"Texture pointing to NULL : %s", SDL_GetError());
    }
    //Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, texture->width, texture->height };
    
    if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
    //Render to screen
	SDL_RenderCopy( renderer, texture->texture, clip, &renderQuad );
}

// Rendering Textures / Sprites
static void render_character(SDL_Renderer* renderer,Game game){
    SDL_Rect character_quad = {450,300,300,600};
    render(renderer,game->current_texture,0,0,&character_quad);
}

void render_game(SDL_Renderer* renderer, Game game){
    render_character(renderer,game);
}