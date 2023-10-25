#include "rendering.h"
#include "texture.h"
#include "movementHandler.h"

static void renderPlayerTiles(Game game,List list){
    if(!list) return;
    Node current = list->head;
    if(!current) return;
    while(current != NULL){
        renderTile(game,current->tile);
        current = current->next;
    }

}

void renderPlayer(Game game,Player p){
    SDL_Rect rect;
        rect.x = p->position.x;
        rect.y = p->position.y;
        rect.w = p->width;
        rect.h = p->height;

    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(game->renderer,&rect);

    renderPlayerTiles(game,game->players[0]->tile_list);
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

void renderLabel(Game game,Label label){
    if(!label) return;
    SDL_Rect src;
    src.x = label->position.x;
    src.y = label->position.y;
    src.w = label->width;
    src.h = label->height;

    SDL_RenderCopy(game->renderer,label->labelTexture,NULL,&src);
}