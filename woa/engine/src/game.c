#include "stdlib.h"
#include "stdbool.h"

#include "../../headers/game.h"

//common
#include "../../headers/common.h"

// needed(maybe?) includes
#include "../../headers/memory.h"
#include "../../headers/movementHandler.h"
#include "../../headers/tile.h"
#include "../../headers/components.h"
#include "../../headers/logger.h"
#include "../../headers/list.h"
#include "../../headers/assets.h"
#include "../../headers/task.h"
#include "../../headers/playerClick.h"
#include "../../headers/CollisionDetection.h"
#include "../../headers/npcManager.h"
#include "../../headers/TileManager.h"
#include "../../headers/taskManager.h"
#include "../../headers/ObjectManager.h"
#include "../../headers/DialougeManager.h"

/* MEMORY CHUNKS HERE  */
struct game_managers {
    TaskManager     task_manager;
    TextureManager  texture_manager;
    ObjectManager   object_manager;
    NpcManager      npc_manager;
    DialougeManager dialouge_manager;
    TileManger      tile_manager;
};

struct game_window {
    TTF_Font*     global_font;
    SDL_Renderer* renderer;
    SDL_Rect      camera;
    int           mouse_x;
    int           mouse_y;
};

struct game_t {
    Player*    players;
    GameState  state;
    u8         handeled_event;
    int*       map;
    Managers   managers;
    Window     window;
    int*       updateStack; //an array of all update functions that needs to be called on gameUpdate
};



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

Game initGame(){
    Game new_g = (Game)malloc(sizeof(*new_g));
    if(!new_g) return NULL;
    new_g->state = MENU_STATE;
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

void setRenderer(Game game,Renderer renderer){
  game->window->renderer = renderer;
}

Renderer getRenderer(Game game){
   return ((game) && (game->window)) ? game->window->renderer : NULL;
}
TTF_Font* getGlobalFont(Game game){
  return ((game) && (game->window)) ? game->window->global_font : NULL;
}


GameState getCurrentState(Game game){
  if(!game) return 0;
  return game->state;
}

#define RENDERDIALOUGE(x, y, request) drawDialouge(game->managers->texture_manager,\
                  getRenderer(game), \
                  (x), (y),\
                  getGlobalFont(game),\
                  game->managers->dialouge_manager,\
                  (request)) 
 
void loadManagerResources(struct game_managers* managers,Renderer renderer){
#define TEXTURE_COUNT 7
  char* textures_res[TEXTURE_COUNT] = {
  [0] = "character.png",
  "walls.png",
  "uisheet.png",
  "woodcutting.png",
  "npc.png",
  "weapons.png",
  "fire.png"
};

  for(int i = 0; i < TEXTURE_COUNT;i++){
    load(managers->texture_manager, renderer, textures_res[i]);

  }
}

void loadTextures(Game game){
  
  loadManagerResources(game->managers, getRenderer(game));
  //setupDialouges(game->managers->dialouge_manager,"./data/dialouges.csv");
  setupTiles(game->managers->tile_manager,"./res/world.txt");
}

void loadGameFont(Game game,const char* font_file_path,int size){
    game->window->global_font = TTF_OpenFont(font_file_path,size);
    if(!game->window->global_font){
        fprintf(stderr,"Couldn't initiate Font: %s",TTF_GetError());
    }
}



static void handleKey(Game game,SDL_Keycode code){
    Player asaad = game->players[0];
    if(!asaad->isInDialouge) {

    if(code == SDLK_LEFT) {
      handlePlayerMovement(asaad, MOVE_LEFT);
    }
    if(code == SDLK_RIGHT) {
      handlePlayerMovement(asaad, MOVE_RIGHT);
    }
    if(code == SDLK_UP) {
      handlePlayerMovement(asaad, MOVE_UP);
    }
    if(code == SDLK_DOWN) {
      handlePlayerMovement(asaad, MOVE_DOWN);
    }
    }
    switch(code){
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
           game->state = RUNNING_STATE; 
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

static void resetPlayerState(Player p, SDL_Keycode code) {
  if(code == SDLK_LEFT || code == SDLK_RIGHT){
    p->vel.x = 0;
  }
  if(code == SDLK_DOWN || code == SDLK_UP) {
    p->vel.y = 0;
  }
  
}

void handleEvents(SDL_Event* e,Game game){
    while(SDL_PollEvent(e) != 0){
        switch(e->type){
            case SDL_QUIT:
                game->state = QUIT_STATE;
            break;
            case SDL_KEYDOWN:
                handleKey(game, e->key.keysym.sym);
            break;
            case SDL_KEYUP:
                resetPlayerState(game->players[0], e->key.keysym.sym);
            break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&(game->window->mouse_x),&(game->window->mouse_y));
                handlePlayerClick(game,game->window->mouse_x,game->window->mouse_y);
                SDL_Rect dst;
                dst.x = SCREEN_WIDTH/2;
                dst.y = SCREEN_HEIGHT;
                dst.w = 50;
                dst.h = 50;
                if(mouseInRect(game,dst)){
                    game->players[0]->isInInventory = !game->players[0]->isInInventory;
                }
                
                break;
            default: break;
        }
    }
}

void initEntities(Game game){
    game->players = ALLOCATE(Player, PLAYERS_COUNT);
    Player asaad = initPlayer(0,0,TILE_WIDTH,TILE_HEIGHT);
    game->players[0] = asaad; 
    setupObjects(game->managers->object_manager,"./res/objects.txt");
    setupNPCs(game->managers->npc_manager);
}

static void renderEntities(Game game){
    playerDraw(game->managers->texture_manager,game->players[0],getRenderer(game),game->window->camera);
    renderNPCs(game->managers->npc_manager,game->managers->texture_manager,getRenderer(game),game->window->camera);
}



static void drawHP(Game game,TextureManager manager,Renderer renderer,int playerHp){
    SDL_Rect rect;
    rect.x = 0;
    rect.y = SCREEN_HEIGHT - 50;
    rect.w = 200;
    rect.h = 50;
    drawRect(rect.x,rect.y,rect.h,rect.w,(SDL_Color){255,0,0,0},true,(float)((float)playerHp/100)*rect.w,renderer);
    RENDERDIALOUGE(rect.x + rect.w/2 - 20, rect.y + rect.h/2 - 20,((DialougeRequest){HP_TEXT, 0, 0, (SDL_Color){255,255,255,255}})); 
}


static void renderUI(Game game){
    SDL_Rect dst;
    dst.x = SCREEN_WIDTH/2;
    dst.y = SCREEN_HEIGHT;
    dst.w = 50;
    dst.h = 50;
    //fprintf(stderr,"MOUSE-MOTION-X: %d MOUSE-MOTION-Y: %d\n",game->mouse_x,game->mouse_y);
    if(mouseInRect(game,dst)){
        
        //drawFrame(game->managers->texture_manager,UI_INVENTORY_TEXTURE,dst.x,dst.y - dst.h,32,32,dst.w,dst.h,1,1,getRenderer(game),SDL_FLIP_NONE);
    } else {
        //drawFrame(game->managers->texture_manager,UI_INVENTORY_TEXTURE,dst.x,dst.y - dst.h,32,32,dst.w,dst.h,1,0,getRenderer(game),SDL_FLIP_NONE);
    }
    drawHP(game, game->managers->texture_manager,getRenderer(game),game->players[0]->hp);
}

static void renderInventory(Game game){
    SDL_Rect box;
    box.w = 400;
    box.h = 300;
    box.x = 200;
    box.y = 100;
    drawRect(box.x,box.y,box.h,box.w,(SDL_Color){0,0,0,0},false,box.w,getRenderer(game));
    for(int i = 0; i < game->players[0]->current_slot;i++){
       // OBJECT tmp = findObject(game->managers->object_manager,game->players[0]->inventory_objects[i]);
        //drawFrame(game->managers->texture_manager,WEAPONS_TEXTURE,box.x + 10,box.y + 10,TILE_WIDTH,TILE_HEIGHT,TILE_WIDTH,TILE_HEIGHT,1,getObjectFrame(tmp),getRenderer(game),SDL_FLIP_NONE);
    }
}

static void drawMap(Game game){
    renderTiles(game->managers->tile_manager,game->managers->texture_manager,getRenderer(game),game->window->camera);
}

void static renderGameOverScreen(Game game){
    SDL_Color black = {0,0,0,0};
    drawText(game->managers->texture_manager,6,SCREEN_WIDTH/2,SCREEN_HEIGHT/2,200,50,black,getRenderer(game));
    drawText(game->managers->texture_manager,7,SCREEN_WIDTH/2,SCREEN_HEIGHT/2 + 50,200,50,black,getRenderer(game));
}



void initRendering(Game game){
    clearScreen(game);
    
    switch(game->state){
        case MENU_STATE:
          RENDERDIALOUGE(400,300,((DialougeRequest){SWORD_DIALOUGE, 10,10, (SDL_Color){0,0,0,0}}));
        break;
        case RUNNING_STATE:
        drawMap(game);
        
        renderEntities(game);
        renderObjects(game->managers->object_manager,game->managers->texture_manager,getRenderer(game),game->window->camera);
        renderUI(game);
        if(game->players[0]->isInDialouge){
         RENDERDIALOUGE(400,300,((DialougeRequest){SWORD_DIALOUGE, 10,10, (SDL_Color){0,0,0,0}})); 
          // renderDialouge(game->managers->dialouge_manager,game->managers->texture_manager,getRenderer(game),game->players[0]->current_dialouge);
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
    SDL_SetRenderDrawColor(getRenderer(game),0xff,0xff,0xff,0xff);
    SDL_RenderClear(getRenderer(game));
}
void updateScreen(Game game){
    SDL_RenderPresent(getRenderer(game));
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

void gameRender(Game game) {
  /*
   * Calling rendering functions here
   * */
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
    //destroyDialogeManager(game->managers->dialouge_manager);
    destroyTileManager(game->managers->tile_manager);
    
    free(game->map);
    free(game->players);
    free(game);
}
