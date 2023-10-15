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
		renderQuad.w = clip->w / 3; // temporary magical number
		renderQuad.h = clip->h / 3;
	}
    //Render to screen
	SDL_RenderCopy( renderer, texture->texture, clip, &renderQuad );
}

// Rendering Textures / Sprites
void render_character(SDL_Renderer* renderer,Game game,int x,int y){
    Player asaad = game->players[0];
    //render to screen
    SDL_SetRenderDrawColor(game->renderer,0xff,0xff,0xff,0xff);
    SDL_RenderClear(game->renderer);
    SDL_Rect character_quad = {0,0,144,384};  
    
    if(asaad->state == WALKING_STATE){
        character_quad.x = 144 * (((int)(asaad->current_frame/8)));
        if(asaad->current_frame/8 >= asaad->walking_frames){
            asaad->current_frame = 0;
        }
        asaad->current_frame++;
    }

    
    render(renderer,game->current_texture,x,y,&character_quad);

    SDL_RenderPresent(game->renderer);
}

void render_game(Game game){
    //render to screen
    SDL_SetRenderDrawColor(game->renderer,0xff,0xff,0xff,0xff);
    SDL_RenderClear(game->renderer);
    
    //initiate character at some point (HOME POINT)
    render_character(game->renderer,game,0,0);

    SDL_RenderPresent(game->renderer);
}