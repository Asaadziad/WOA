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
		renderQuad.w = clip->w ; // temporary magical number
		renderQuad.h = clip->h ;
	}
    //Render to screen
	SDL_RenderCopy( renderer, texture->texture, clip, &renderQuad );
}

// Rendering Textures / Sprites
void render_character(SDL_Renderer* renderer,Game game,int x,int y,int camX,int camY){
    Player asaad = game->players[0];
    //render to screen
    SDL_Rect character_quad = {0,0,100,250};  
    
    if(asaad->state == WALKING_STATE){
        character_quad.x = 120 * (((int)(asaad->current_frame/8)));
        if(asaad->current_frame/8 >= asaad->walking_frames){
            asaad->current_frame = 0;
        }
        asaad->current_frame++;
    }
    asaad->height = character_quad.h;
    asaad->width = character_quad.w;
    
    render(renderer,game->current_texture,x ,y ,&character_quad);
}

void render_fence(Game game){
    SDL_Rect fence = {0,400,100,400};
    render(game->renderer, game->current_texture,fence.x,fence.y,&fence);
}

void render_monster(Game game){
    SDL_Rect monster = {0,700,200,300};
    render(game->renderer, game->current_texture,monster.x,monster.y,&monster);
}
