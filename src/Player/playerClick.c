#include "playerClick.h"
#include "../object.h"
#include "SDL2/SDL.h"
#include "../logger.h"
#include "playerFishing.h"
#include "playerWalk.h"

static uint8_t isObjectClicked(int x, int y,SDL_Rect src){
    return (x >= src.x && x <= (src.x + src.w)) && ((y <= (src.y + src.h)) && (y >= src.y));
    
}

/*
* Need to walk through objects and check if the player clicked on one of them
*/
void handlePlayerClick(Game game,int x, int y){
    Node current = getHead(game->objects);
    while(current != NULL){
        OBJECT tmp = (OBJECT)getNodeData(current);
        SDL_Rect src = objectGetRect(tmp);
        if(isObjectClicked(x,y,src)){
            game->players[0]->target_object = tmp;
            addTask(game->task_manager,0,PLAYER_WALK_2OBJECT_TASK);
            addTask(game->task_manager,1,FISHING_SKILL_TASK);
        } else {
            Vector2f pos = {x,y};
            game->players[0]->target_position = pos;
            addTask(game->task_manager,0,PLAYER_WALK_TASK);
        }
        current = getNextNode(current);
    }
}