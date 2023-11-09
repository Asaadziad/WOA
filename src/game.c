#include "game.h"
#include "stdlib.h"

#include "logic.h"
#include "memory.h"
#include "rendering.h"
#include "movementHandler.h"
#include "tile.h"
#include "components.h"
#include "logger.h"
#include "DS/list.h"
#include "lib/assets.h"
#include "task.h"
#include "Player/playerClick.h"

static void freeTexturePtr(void* elem){
    freeTexture((Texture)elem);
}

static void freeObjectPtr(void* elem){
    destroyObject((OBJECT)elem);
}

Game initGame(){
    Game new_g = (Game)malloc(sizeof(*new_g));
    if(!new_g) return NULL;
    new_g->state = MENU_STATE;
    new_g->textures = listCreate(freeTexturePtr,NULL);
    new_g->objects = listCreate(freeObjectPtr,NULL);
    new_g->task_manager = taskManagerInit();
    new_g->texture_manager = textureManagerInit();
    new_g->tiles = (Tile*) malloc(sizeof(Tile) * (TOTAL_TILES));
    if(!new_g->tiles) return NULL;
    new_g->map = NULL;
    new_g->handeled_event = 0;
    return new_g;
}

void loadTextures(Game game){
    //createMenuUI(game);
    load(game->texture_manager,game->renderer,"character.png",PLAYER_TEXTURE);
    load(game->texture_manager,game->renderer,"res/walls.png",TILE_TEXTURE);
    loadText(game->texture_manager,game->renderer,game->global_font,"Welcome to the world of asaad");
    loadText(game->texture_manager,game->renderer,game->global_font,"Press space to enter");
    //loadTileMap(game);
    char* size = int2string(getListSize(game->textures));
    LOG(size);
    free(size);
}

static void handleKey(Game game,SDL_Keycode code){
    Player asaad = game->players[0];
    switch(code){
        case SDLK_LEFT:
        asaad->face = WEST;
        handlePlayerMovement(asaad,MOVE_LEFT);
        break;
        case SDLK_RIGHT:
        asaad->face = EAST;
        handlePlayerMovement(asaad,MOVE_RIGHT);
        break;
        case SDLK_UP:
        asaad->face = NORTH;
        handlePlayerMovement(asaad,MOVE_UP);
        break;
        case SDLK_DOWN:
        asaad->face = SOUTH;
        handlePlayerMovement(asaad,MOVE_DOWN);
        break;
        case SDLK_SPACE:
            if(game->state == MENU_STATE){
                game->state = RUNNING_STATE;
            } else {
                LOG("Running state");
            }
        break;
        default:
        break;
    }
}

void handleEvents(SDL_Event* e,Game game){
    while(SDL_PollEvent(e) != 0){
        switch(e->type){
            case SDL_QUIT:
                game->state = QUIT_STATE;
            break;
            case SDL_KEYDOWN:
                handleKey(game,e->key.keysym.sym);
            break;
            case SDL_MOUSEBUTTONDOWN:
                int x,y;
                SDL_GetMouseState(&(x),&(y));
                handlePlayerClick(game,x,y);
                fprintf(stderr,"MOUSE-X: %d MOUSE-Y:%d\n",x,y);
            break;
            default: {}
        }
    }
}

void initEntities(Game game){
    game->players = ALLOCATE(Player, PLAYERS_COUNT);
    Player asaad = initPlayer(50,250,112,133);
    game->players[0] = asaad;
    OBJECT fish = createObject(50,50,50,50,FISHING_SPOT);
    listInsert(game->objects,fish);  
}

void renderEntities(Game game){
    playerDraw(game->texture_manager,game->players[0],game->renderer);

}


void initRendering(Game game){
    clearScreen(game);
        
    if(game->state == MENU_STATE){
        int actual_center_x = SCREEN_WIDTH/2 - 125;
        int actual_center_y = SCREEN_HEIGHT/2 - 50;
        drawText(game->texture_manager,0,actual_center_x,actual_center_y,250,50,game->renderer);
        drawText(game->texture_manager,1,actual_center_x,actual_center_y + 40,250,50,game->renderer);
    
    } else {
        drawFrame(game->texture_manager,TILE_TEXTURE,0,0,33,33,1,0,game->renderer,SDL_FLIP_NONE);
        drawFrame(game->texture_manager,TILE_TEXTURE,32,0,33,33,1,0,game->renderer,SDL_FLIP_NONE);
        drawFrame(game->texture_manager,TILE_TEXTURE,0,32,33,33,1,0,game->renderer,SDL_FLIP_NONE);
        drawFrame(game->texture_manager,TILE_TEXTURE,32,32,33,33,1,0,game->renderer,SDL_FLIP_NONE);
        drawFrame(game->texture_manager,TILE_TEXTURE,0,64,33,33,1,0,game->renderer,SDL_FLIP_NONE);
        drawFrame(game->texture_manager,TILE_TEXTURE,64,0,33,33,1,0,game->renderer,SDL_FLIP_NONE);
      
      
        renderEntities(game);
    }

    updateScreen(game);
}


void clearScreen(Game game){
    SDL_SetRenderDrawColor(game->renderer,0xff,0xff,0xff,0xff);
    SDL_RenderClear(game->renderer);
}
void updateScreen(Game game){
    SDL_RenderPresent(game->renderer);
}

void gameUpdate(Game game){
    playerUpdate(game->players[0]);
}


void quitGame(Game game){
    TTF_CloseFont(game->global_font);

    for(int i = 0; i < PLAYERS_COUNT;i++){
        destroyPlayer(game->players[i]);
    }
    //fclose(game->map);
    listDestroy(game->textures);
    free(game->players);
    free(game);
}
