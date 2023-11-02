#include "playerClick.h"
#include "../object.h"
#include "SDL2/SDL.h"
#include "../logger.h"
#include "playerFishing.h"

static uint8_t isObjectClicked(int x, int y,SDL_Rect src){
    return (x >= src.x && x <= (src.x + src.w)) && ((y <= (src.y + src.h)) && (y >= src.y));
    
}

/*
* Need to walk through objects and check if the player clicked on one of them
*/
void handlePlayerClick(Game game){
    Node current = getHead(game->objects);
    while(current != NULL){
        OBJECT tmp = (OBJECT)getNodeData(current);
        SDL_Rect src = objectGetRect(tmp);
        if(isObjectClicked(game->mouse_x,game->mouse_y,src)){
            ObjectType type = objectGetType(tmp);
            if(!game->handeled_event){
                switch(type){
                    case FISHING_SPOT:
                        startFishing(game->players[0]);
                        game->handeled_event  = !game->handeled_event;
                    break;
                    default:break;
                }
            }
        }
        current = getNextNode(current);
    }
}