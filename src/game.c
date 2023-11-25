#include "game.h"
#include "stdlib.h"
#include "stdbool.h"
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
#include "CollisionDetection.h"
#include "npcManager.h"
#include "TileManager.h"

Game initGame(){
    Game new_g = (Game)malloc(sizeof(*new_g));
    if(!new_g) return NULL;
    new_g->state = MENU_STATE;
    new_g->texture_manager = textureManagerInit();
    new_g->components_manager = initComponentsManager();
    new_g->object_manager = initObjectManager();
    new_g->npc_manager = initNPCManager();
    new_g->dialouge_manager = initDialougeManager();
    new_g->tile_manager = initTileManager();
    new_g->handeled_event = 0;
    SDL_Rect camera;
    camera.x = 0;
    camera.y = 0;
    camera.w = SCREEN_WIDTH;
    camera.h = SCREEN_HEIGHT;
    new_g->camera = camera;
    return new_g;
}

void loadTextures(Game game){
    //createMenuUI(game);
    load(game->texture_manager,game->renderer,"res/character.png",PLAYER_TEXTURE);
    load(game->texture_manager,game->renderer,"res/walls.png",TILE_TEXTURE);
    load(game->texture_manager,game->renderer,"res/uisheet.png",UI_INVENTORY_TEXTURE);
    load(game->texture_manager,game->renderer,"res/woodcutting.png",TREE_TEXTURE);
    load(game->texture_manager,game->renderer,"res/npc.png",NPC_TEXTURE);
    load(game->texture_manager,game->renderer,"res/weapons.png",WEAPONS_TEXTURE);
    SDL_Color black = {0,0,0,0};
    SDL_Color white = {255,255,255,255};
    loadText(game->texture_manager,game->renderer,game->global_font,"Welcome to the world of asaad",&black);
    loadText(game->texture_manager,game->renderer,game->global_font,"Press space to enter",&black);
    loadText(game->texture_manager,game->renderer,game->global_font,"HP",&white);
    loadText(game->texture_manager,game->renderer,game->global_font,"Hello asaad",&white);
    loadText(game->texture_manager,game->renderer,game->global_font,"Would you like to pickup this sword?",&white);
    loadText(game->texture_manager,game->renderer,game->global_font,"Yes No",&white);
    setupDialouges(game->dialouge_manager,NULL);
    setupTiles(game->tile_manager,"world.txt");
}

static void handleKey(Game game,SDL_Keycode code){
    Player asaad = game->players[0];
    switch(code){
        case SDLK_LEFT:
        if(asaad->isInDialouge) break;
        handlePlayerMovement(asaad,MOVE_LEFT);
        break;
        case SDLK_RIGHT:
        if(asaad->isInDialouge) break;

        handlePlayerMovement(asaad,MOVE_RIGHT);
        break;
        case SDLK_UP:
        if(asaad->isInDialouge) break;
        handlePlayerMovement(asaad,MOVE_UP);
        break;
        case SDLK_DOWN:
        if(asaad->isInDialouge) break;
        handlePlayerMovement(asaad,MOVE_DOWN);
        break;
        case SDLK_v:
            asaad->isInDialouge = !asaad->isInDialouge;
        break;
        case SDLK_i:
            asaad->isInInventory = !asaad->isInInventory;
        break;
        case SDLK_q:
            playerAttack(asaad);
        break;
        case SDLK_SPACE:
            if(game->state == MENU_STATE){
                game->state = RUNNING_STATE;
            } else {
                if(asaad->isInDialouge){
                    switch(asaad->current_dialouge){
                        case SWORD_DIALOUGE:
                            // pickup system
                            // pickup the object - remove it from the map
                            OBJECT o = findObject(game->object_manager,SWORD_OBJECT);
                            setObjectRenderable(o,false);
                            asaad->inventory_objects[asaad->current_slot] = SWORD_OBJECT;
                            asaad->current_slot++;
                            asaad->isInDialouge = false;
                        break;
                        default :break;
                    }
                }
            }
        break;
        default:
        break;
    }
}

static bool mouseInRect(Game game, SDL_Rect rect){
    if((game->mouse_x > (rect.x + rect.w)) || (game->mouse_x < rect.x)) {
        return false;
    }
    if((game->mouse_y > (rect.y)) || (game->mouse_y < rect.y - 50)) {
        return false;
    }
    return true;
}

void handleEvents(SDL_Event* e,Game game){
    while(SDL_PollEvent(e) != 0){
        SDL_GetMouseState(&(game->mouse_x),&(game->mouse_y));
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
                SDL_Rect dst;
                dst.x = SCREEN_WIDTH/2;
                dst.y = SCREEN_HEIGHT;
                dst.w = 50;
                dst.h = 50;
                if(mouseInRect(game,dst)){
                    game->players[0]->isInInventory = !game->players[0]->isInInventory;
                }
                fprintf(stderr,"MOUSE-X: %d MOUSE-Y:%d\n",x,y);
            break;
            default: break;
        }
    }
}

void initEntities(Game game){
    game->players = ALLOCATE(Player, PLAYERS_COUNT);
    Player asaad = initPlayer(0,0,32,32);
    game->players[0] = asaad; 
    setupObjects(game->object_manager,"objects.txt");
    setupNPCs(game->npc_manager);
}

static void renderEntities(Game game){
    playerDraw(game->texture_manager,game->players[0],game->renderer,game->camera);
    renderNPCs(game->npc_manager,game->texture_manager,game->renderer,game->camera);
}



static void drawHP(TextureManager manager,SDL_Renderer* renderer,int playerHp){
    SDL_Rect rect;
    rect.x = 0;
    rect.y = SCREEN_HEIGHT - 50;
    rect.w = 200;
    rect.h = 50;
    drawRect(rect.x,rect.y,rect.h,rect.w,(SDL_Color){255,0,0,0},true,(float)((float)playerHp/100)*rect.w,renderer);
    drawText(manager,2,rect.x + rect.w/2 - 25/2,rect.y + rect.h/2 - 25/2,25,25,(SDL_Color){255,255,255,255},renderer);
}


static void renderUI(Game game){
    SDL_Rect dst;
    dst.x = SCREEN_WIDTH/2;
    dst.y = SCREEN_HEIGHT;
    dst.w = 50;
    dst.h = 50;
    //fprintf(stderr,"MOUSE-MOTION-X: %d MOUSE-MOTION-Y: %d\n",game->mouse_x,game->mouse_y);
    if(mouseInRect(game,dst)){
        
        drawFrame(game->texture_manager,UI_INVENTORY_TEXTURE,dst.x,dst.y - dst.h,32,32,dst.w,dst.h,1,1,game->renderer,SDL_FLIP_NONE);
    } else {
        drawFrame(game->texture_manager,UI_INVENTORY_TEXTURE,dst.x,dst.y - dst.h,32,32,dst.w,dst.h,1,0,game->renderer,SDL_FLIP_NONE);
    }
    drawHP(game->texture_manager,game->renderer,game->players[0]->hp);
}

static void renderInventory(Game game){
    SDL_Rect box;
    box.w = 400;
    box.h = 300;
    box.x = 200;
    box.y = 100;
    drawRect(box.x,box.y,box.h,box.w,(SDL_Color){0,0,0,0},false,box.w,game->renderer);
    for(int i = 0; i < game->players[0]->current_slot;i++){
        OBJECT tmp = findObject(game->object_manager,game->players[0]->inventory_objects[i]);
        drawFrame(game->texture_manager,WEAPONS_TEXTURE,box.x + 10,box.y + 10,32,32,60,60,1,getObjectFrame(tmp),game->renderer,SDL_FLIP_NONE);
    }
}

static void drawMap(Game game){
    renderTiles(game->tile_manager,game->texture_manager,game->renderer,game->camera);
}


void initRendering(Game game){
    clearScreen(game);
    
    switch(game->state){
        case MENU_STATE:
        int actual_center_x = SCREEN_WIDTH/2 - 125;
        int actual_center_y = SCREEN_HEIGHT/2 - 50;
        drawText(game->texture_manager,0,actual_center_x,actual_center_y,250,50,(SDL_Color){0,0,0,0},game->renderer);
        drawText(game->texture_manager,1,actual_center_x,actual_center_y + 40,250,50,(SDL_Color){0,0,0,0},game->renderer);
        break;
        case RUNNING_STATE:
        drawMap(game);
        
        renderEntities(game);
        renderObjects(game->object_manager,game->texture_manager,game->renderer,game->camera);
        renderUI(game);
        if(game->players[0]->isInDialouge){
            renderDialouge(game->dialouge_manager,game->texture_manager,game->renderer,game->players[0]->current_dialouge);
        }
        if(game->players[0]->isInInventory){
            //draw the inventory
            renderInventory(game);
        }
        break;
        default:break;
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

static void checkCamera(SDL_Rect* camera){
    if(camera->x < 0){
        camera->x = 0;
    }
    if(camera->y < 0){
        camera->y = 0;
    }
    if(camera->x > WORLD_WIDTH - camera->w){
        camera->x =  WORLD_WIDTH - camera->w;
    }
    if(camera->y > WORLD_HEIGHT - camera->h){
        camera->y = WORLD_HEIGHT - camera->h;
    }
}

void gameUpdate(Game game){
    game->camera.x = (game->players[0]->position.x - game->camera.w/2);
    game->camera.y = (game->players[0]->position.y - game->camera.h/2);
    checkCamera(&game->camera);
    playerUpdate(game->players[0],game->camera);
    updateNPCs(game->npc_manager);
    checkPlayerCollisionWithObjects(game->object_manager,game->players[0]);
    checkPlayerCollisionWithNPCs(game->npc_manager,game->players[0]);
}


void quitGame(Game game){
    TTF_CloseFont(game->global_font);

    for(int i = 0; i < PLAYERS_COUNT;i++){
        destroyPlayer(game->players[i]);
    }
    destroyTaskManager(game->task_manager);
    destroyTextureManager(game->texture_manager);
    destroyComponentsManager(game->components_manager);
    destroyNPCManager(game->npc_manager);
    destroyObjectManager(game->object_manager);
    destroyDialogeManager(game->dialouge_manager);
    destroyTileManager(game->tile_manager);
    free(game->map);
    free(game->players);
    free(game);
}
