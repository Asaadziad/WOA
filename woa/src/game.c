#include "game.h"
#include "stdlib.h"
#include "stdbool.h"
#include "logic.h"
#include "memory.h"
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

internal
void initManagers(struct game_managers* managers){
    managers->texture_manager = textureManagerInit();
    managers->object_manager = initObjectManager();
    managers->npc_manager = initNPCManager();
    managers->dialouge_manager = initDialougeManager();
    managers->tile_manager = initTileManager();
}

internal
void initWindow(struct game_window* window){
    SDL_Rect camera;
    camera.x = 0;
    camera.y = 0;
    camera.w = SCREEN_WIDTH;
    camera.h = SCREEN_HEIGHT;
    window->camera = camera;
}

void allocate(void* asset,size_t nbytes) {
  asset = malloc(nbytes);
  if(!asset) {
    fprintf(stderr, "Could not allocate memory");
  }
}

Game initGame(){
    Game new_g = (Game)malloc(sizeof(*new_g));
    if(!new_g) return NULL;
    new_g->state = MENU_STATE;
    new_g->handeled_event = 0;
    new_g->managers = malloc(sizeof(*new_g->managers));
    new_g->window = malloc(sizeof(*new_g->window));
    if(!new_g->window || !new_g->managers){
      fprintf(stderr, "Could not allocate managers and window");
      return NULL;
    }
    initManagers(new_g->managers);
    initWindow(new_g->window);    
    return new_g;
}


/*
 *  We save this for now in a global variable
 *  later it will be saved in outside source / like a file
 */
/*global_var 
char*** textures[6] = {
  "res/character.png",
  "res/walls.png",
  "res/uisheet.png",
  "res/woodcutting.png",
  "res/npc.png",
  "res/weapons.png"
};

internal 
void loadManagerResources(struct game_managers* managers,SDL_Renderer* renderer){
#define textures_count 6
  for(int i = 0; i < textures_count;i++){
     qmanagers->texture_manager,renderer,textures[i],PLAYER_TEXTURE);

  }
}
*/
void loadTextures(Game game){
    //createMenuUI(game);
    load(game->managers->texture_manager,game->window->renderer,"res/character.png",PLAYER_TEXTURE);
    load(game->managers->texture_manager,game->window->renderer,"res/walls.png",TILE_TEXTURE);
    load(game->managers->texture_manager,game->window->renderer,"res/uisheet.png",UI_INVENTORY_TEXTURE);
    load(game->managers->texture_manager,game->window->renderer,"res/woodcutting.png",TREE_TEXTURE);
    load(game->managers->texture_manager,game->window->renderer,"res/npc.png",NPC_TEXTURE);
    load(game->managers->texture_manager,game->window->renderer,"res/weapons.png",WEAPONS_TEXTURE);
    SDL_Color black = {0,0,0,0};
    SDL_Color white = {255,255,255,255};
    loadText(game->managers->texture_manager,game->window->renderer,game->window->global_font,"Welcome to the world of asaad",&black);
    loadText(game->managers->texture_manager,game->window->renderer,game->window->global_font,"Press space to enter",&black);
    loadText(game->managers->texture_manager,game->window->renderer,game->window->global_font,"HP",&white);
    loadText(game->managers->texture_manager,game->window->renderer,game->window->global_font,"Hello asaad",&white);
    loadText(game->managers->texture_manager,game->window->renderer,game->window->global_font,"Would you like to pickup this sword?",&white);
    loadText(game->managers->texture_manager,game->window->renderer,game->window->global_font,"Yes No",&white);
    loadText(game->managers->texture_manager,game->window->renderer,game->window->global_font,"Game Over",&black);
    loadText(game->managers->texture_manager,game->window->renderer,game->window->global_font,"press space to restart",&black);
    setupDialouges(game->managers->dialouge_manager,NULL);
    setupTiles(game->managers->tile_manager,"world.txt");
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
            //Check if player has sword
            if(playerCheckInventory(asaad,SWORD_OBJECT)){
                playerAttack(asaad);
            } else {
                LOG("You dont have SWORD!");
            }
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
                            OBJECT o = findObject(game->managers->object_manager,SWORD_OBJECT);
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
    if((game->window->mouse_x > (rect.x + rect.w)) || (game->window->mouse_x < rect.x)) {
        return false;
    }
    if((game->window->mouse_y > (rect.y)) || (game->window->mouse_y < rect.y - 50)) {
        return false;
    }
    return true;
}

void handleEvents(SDL_Event* e,Game game){
    while(SDL_PollEvent(e) != 0){
        SDL_GetMouseState(&(game->window->mouse_x),&(game->window->mouse_y));
        switch(e->type){
            case SDL_QUIT:
                game->state = QUIT_STATE;
            break;
            case SDL_KEYDOWN:
                handleKey(game,e->key.keysym.sym);
            break;
            case SDL_MOUSEBUTTONDOWN:
                int x = 0;
				        int y = 0;
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
    Player asaad = initPlayer(0,0,TILE_WIDTH,TILE_HEIGHT);
    game->players[0] = asaad; 
    setupObjects(game->managers->object_manager,"objects.txt");
    setupNPCs(game->managers->npc_manager);
}

static void renderEntities(Game game){
    playerDraw(game->managers->texture_manager,game->players[0],game->window->renderer,game->window->camera);
    renderNPCs(game->managers->npc_manager,game->managers->texture_manager,game->window->renderer,game->window->camera);
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
        
        drawFrame(game->managers->texture_manager,UI_INVENTORY_TEXTURE,dst.x,dst.y - dst.h,32,32,dst.w,dst.h,1,1,game->window->renderer,SDL_FLIP_NONE);
    } else {
        drawFrame(game->managers->texture_manager,UI_INVENTORY_TEXTURE,dst.x,dst.y - dst.h,32,32,dst.w,dst.h,1,0,game->window->renderer,SDL_FLIP_NONE);
    }
    drawHP(game->managers->texture_manager,game->window->renderer,game->players[0]->hp);
}

static void renderInventory(Game game){
    SDL_Rect box;
    box.w = 400;
    box.h = 300;
    box.x = 200;
    box.y = 100;
    drawRect(box.x,box.y,box.h,box.w,(SDL_Color){0,0,0,0},false,box.w,game->window->renderer);
    for(int i = 0; i < game->players[0]->current_slot;i++){
        OBJECT tmp = findObject(game->managers->object_manager,game->players[0]->inventory_objects[i]);
        drawFrame(game->managers->texture_manager,WEAPONS_TEXTURE,box.x + 10,box.y + 10,TILE_WIDTH,TILE_HEIGHT,TILE_WIDTH,TILE_HEIGHT,1,getObjectFrame(tmp),game->window->renderer,SDL_FLIP_NONE);
    }
}

static void drawMap(Game game){
    renderTiles(game->managers->tile_manager,game->managers->texture_manager,game->window->renderer,game->window->camera);
}

void static renderGameOverScreen(Game game){
    SDL_Color black = {0,0,0,0};
    drawText(game->managers->texture_manager,6,SCREEN_WIDTH/2,SCREEN_HEIGHT/2,200,50,black,game->window->renderer);
    drawText(game->managers->texture_manager,7,SCREEN_WIDTH/2,SCREEN_HEIGHT/2 + 50,200,50,black,game->window->renderer);
}


void initRendering(Game game){
    clearScreen(game);
    
    switch(game->state){
        case MENU_STATE:
        int actual_center_x = SCREEN_WIDTH/2 - 125;
        int actual_center_y = SCREEN_HEIGHT/2 - 50;
        drawText(game->managers->texture_manager,0,actual_center_x,actual_center_y,250,50,(SDL_Color){0,0,0,0},game->window->renderer);
        drawText(game->managers->texture_manager,1,actual_center_x,actual_center_y + 40,250,50,(SDL_Color){0,0,0,0},game->window->renderer);
        break;
        case RUNNING_STATE:
        drawMap(game);
        
        renderEntities(game);
        renderObjects(game->managers->object_manager,game->managers->texture_manager,game->window->renderer,game->window->camera);
        renderUI(game);
        if(game->players[0]->isInDialouge){
            renderDialouge(game->managers->dialouge_manager,game->managers->texture_manager,game->window->renderer,game->players[0]->current_dialouge);
        }
        if(game->players[0]->isInInventory){
            //draw the inventory
            renderInventory(game);
        }
        if(game->state == GAME_OVER_STATE){
            renderGameOverScreen(game);
        }
        break;
        default:break;
    }

    updateScreen(game);
}


void clearScreen(Game game){
    SDL_SetRenderDrawColor(game->window->renderer,0xff,0xff,0xff,0xff);
    SDL_RenderClear(game->window->renderer);
}
void updateScreen(Game game){
    SDL_RenderPresent(game->window->renderer);
}

static void checkCamera(SDL_Rect* camera){
    if(camera->x < 0){
        camera->x = 0;
    }
    if(camera->y < 0){
        camera->y = 0;
    }
    if(camera->x > (TILE_WIDTH * MAX_WORLD_COLS) - camera->w){
        camera->x = (TILE_WIDTH * MAX_WORLD_COLS) - camera->w;
    }
    if(camera->y > (TILE_HEIGHT * MAX_WORLD_ROWS) - camera->h){
        camera->y = (TILE_HEIGHT * MAX_WORLD_ROWS) - camera->h;
    }
}

void gameUpdate(Game game){
    game->window->camera.x = (game->players[0]->position.x - game->window->camera.w/2);
    game->window->camera.y = (game->players[0]->position.y - game->window->camera.h/2);
    checkCamera(&game->window->camera);
    playerUpdate(game->players[0],game->window->camera);
    updateNPCs(game->managers->npc_manager);
    checkPlayerCollisionWithObjects(game->managers->object_manager,game->players[0]);
    checkPlayerCollisionWithNPCs(game->managers->npc_manager,game->players[0]);
    if(game->players[0]->hp <= 0){
        game->state = GAME_OVER_STATE;
    }
}


void quitGame(Game game){
    TTF_CloseFont(game->window->global_font);

    for(int i = 0; i < PLAYERS_COUNT;i++){
        destroyPlayer(game->players[i]);
    }
    destroyTaskManager(game->managers->task_manager);
    destroyTextureManager(game->managers->texture_manager);
    destroyNPCManager(game->managers->npc_manager);
    destroyObjectManager(game->managers->object_manager);
    destroyDialogeManager(game->managers->dialouge_manager);
    destroyTileManager(game->managers->tile_manager);
    free(game->map);
    free(game->players);
    free(game);
}
