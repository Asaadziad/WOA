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
		renderQuad.w = clip->w / 4; // temporary magical number
		renderQuad.h = clip->h / 4;
	}
    //Render to screen
	SDL_RenderCopy( renderer, texture->texture, clip, &renderQuad );
}

// Rendering Textures / Sprites
void render_character(SDL_Renderer* renderer,Game game,int x,int y,int camX,int camY){
    Player asaad = game->players[0];
    //render to screen
    SDL_Rect character_quad = {100,0,100,270};  
    
    if(asaad->state == WALKING_STATE){
        character_quad.x = 100 * (((int)(asaad->current_frame/8)));
        if(asaad->current_frame/8 >= asaad->walking_frames){
            asaad->current_frame = 0;
        }
        asaad->current_frame++;
    }
    asaad->height = character_quad.h;
    asaad->width = character_quad.w;
    
    render(renderer,game->current_texture,x ,y ,&character_quad);
}


static const int fence_pix = 17;
static const int fence_sprite_posX = 401;
static const int fence_sprite_posY = 0;

static const int positions[][2] = {
    [0] = {520,0},
    [1] = {500,0},
    [2] = {520,112},
};

static SDL_Rect fences[] = {
    [0] = {fence_sprite_posX,fence_sprite_posY,fence_pix*3,fence_pix},
    [1] = {fence_sprite_posX + fence_pix*3 ,fence_sprite_posY, fence_pix,fence_pix*3},
    [2] = {fence_sprite_posX,fence_sprite_posY,fence_pix*3,fence_pix},
};
void render_fence(Game game,SDL_Rect* src,int i){
    SDL_Rect dst = {positions[i][0],positions[i][1],src->w * 2 ,src->h * 2};
    SDL_RenderCopy(game->renderer,game->current_texture->texture,src, &dst);
}

void build_monster_area(Game game) {
    
    render_fence(game,&fences[0],0);
    render_fence(game,&fences[1],1);
    render_fence(game,&fences[2],2);
}

const int monster_positions[][2] = {
    [0] = {600,40},
};

const int monster_rules[][1] = {
  [0] = {0},
  [1] = {40},
  [2] = {70},
  [3] = {105},  
};

void render_monster(Game game,int i){ 
    SDL_Rect monster = {monster_rules[i][0],340,30,69};
    SDL_Rect dst = {monster_positions[0][0],monster_positions[0][1],monster.w,monster.h};
    SDL_RenderCopy(game->renderer,game->current_texture->texture,&monster,&dst);
}

void animate(void (*renderFN)(Game game, int i),Game game,int current_anim, int num_of_sprites){
    int to_render = (current_anim+1)/(num_of_sprites*4);
    renderFN(game,to_render);
}
