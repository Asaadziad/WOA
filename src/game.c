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

static void freeTexturePtr(void* elem){
    freeTexture((Texture)elem);
}

Game initGame(){
    Game new_g = (Game)malloc(sizeof(*new_g));
    if(!new_g) return NULL;
    
    new_g->state = MENU_STATE;
    new_g->textures = listCreate(freeTexturePtr,NULL);
    
    return new_g;
}

static void createMenuUI(Game game){
    Texture t = initTexture(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2);
    loadTextureFromText(game->renderer,game->global_font,t,"Hello world");
    Texture tt = initTexture(100,100);
    loadTextureFromText(game->renderer,game->global_font,tt,"LIGMABALLS");
    listInsert(game->textures,t);
    listInsert(game->textures,tt);
}

void loadTextures(Game game){
    if(game->state == MENU_STATE){
        createMenuUI(game);
    } else {
        LOG("ligma");
    }
    
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
                //game->players[0]->isMoving = true;
            break;
            default: {}
        }
    }
}

void initEntities(Game game){
    game->players = ALLOCATE(Player, PLAYERS_COUNT);
    Player asaad = initPlayer(50,50,100,100);
    Player monster = initPlayer(400,50,100,100);
    game->players[0] = asaad;
    game->players[1] = monster;
    
}

void renderEntities(Game game){
    renderPlayer(game,game->players[0]);
    renderPlayer(game,game->players[1]);
}

void initRendering(Game game){
    clearScreen(game);

   Node current = getHead(game->textures);
   while(current != NULL){
    Texture tmp = (Texture)getNodeData(current);
    renderTexture(game,tmp,0,0);
    current = getNextNode(current);
   }
   
   /* if(game->state == MENU_STATE){
       //drawLabel(game,helloLabel(game,"hello world"));
        //renderEntities(game);
        renderLabel(game);
    } else {
        renderEntities(game);
    }*/

    updateScreen(game);
}





void clearScreen(Game game){
    SDL_SetRenderDrawColor(game->renderer,0xff,0xff,0xff,0xff);
    SDL_RenderClear(game->renderer);
}
void updateScreen(Game game){
    SDL_RenderPresent(game->renderer);
}


void quitGame(Game game){
    TTF_CloseFont(game->global_font);

    for(int i = 0; i < PLAYERS_COUNT;i++){
        destroyPlayer(game->players[i]);
    }
    listDestroy(game->textures);
    free(game->players);
    free(game);
}
