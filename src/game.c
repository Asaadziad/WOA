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
    new_g->handeled_event = 0;
    SDL_Rect camera;
    camera.x = 0;
    camera.y = 0;
    camera.w = SCREEN_WIDTH;
    camera.h = SCREEN_HEIGHT;
    new_g->camera = camera;
    int* new_map = (int*)malloc(sizeof(*new_map) * (MAX_WORLD_ROWS*MAX_WORLD_COLS));
    if(!new_map) return NULL;
    new_g->map = new_map;
    return new_g;
}

static char* readFileToBuffer(const char* map_path){
    FILE* map = fopen(map_path, "r");
    if(!map) {ERR("Couldn't open map");exit(1);}
    
    fseek(map,0,SEEK_END);
    size_t file_size = ftell(map);
    fseek(map,0,SEEK_SET);
    char* buffer = (char*)malloc(sizeof(char)* (file_size + 1));
    if(!buffer) exit(1);
    fread(buffer,file_size,1,map);
    buffer[file_size] = '\0';
    fprintf(stderr,"%ld\n",file_size);
    fclose(map);
    return buffer;
}


static void loadTilesMap(Game game, const char* map_path){
    char* tiles_string = readFileToBuffer(map_path);
    char* to_free = tiles_string;
    
    int i = 0;
    while(*tiles_string != '\0'){
        if(*tiles_string == ' ' || *tiles_string == '\n' || *tiles_string == '\r'){
            tiles_string++;
            continue;
        }
        game->map[i] = *tiles_string - '0';
        
        i++;
        tiles_string++;
    }
    free(to_free);
}

void loadTextures(Game game){
    //createMenuUI(game);
    load(game->texture_manager,game->renderer,"res/character.png",PLAYER_TEXTURE);
    load(game->texture_manager,game->renderer,"res/walls.png",TILE_TEXTURE);
    loadText(game->texture_manager,game->renderer,game->global_font,"Welcome to the world of asaad");
    loadText(game->texture_manager,game->renderer,game->global_font,"Press space to enter");
    loadTilesMap(game, "world.txt");
    
}

static void handleKey(Game game,SDL_Keycode code){
    Player asaad = game->players[0];
    switch(code){
        case SDLK_LEFT:
        
        handlePlayerMovement(asaad,MOVE_LEFT);
        break;
        case SDLK_RIGHT:
        
        handlePlayerMovement(asaad,MOVE_RIGHT);
        break;
        case SDLK_UP:
        
        handlePlayerMovement(asaad,MOVE_UP);
        break;
        case SDLK_DOWN:
        
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
    Player asaad = initPlayer(0,0,32,32);
    game->players[0] = asaad;
    OBJECT fish = createObject(50,50,50,50,FISHING_SPOT);
    listInsert(game->objects,fish);  
}

void renderEntities(Game game){
    playerDraw(game->texture_manager,game->players[0],game->renderer,game->camera);
}

static void drawMap(Game game){
    for(int row = 0 ; row < MAX_WORLD_ROWS;row++){
        for(int col = 0; col < MAX_WORLD_COLS;col++){
            int worldX = row * TILE_WIDTH;
            int worldY = col * TILE_HEIGHT;
            int screenX = worldX - game->players[0]->position.x + (game->camera.x);
            int screenY = worldY - game->players[0]->position.y + (game->camera.y);
           
            drawFrame(game->texture_manager,TILE_TEXTURE,screenX,screenY,32,32,(game->map[row * 50 + col]/2) + 1,game->map[row * 50 + col]%2,game->renderer,SDL_FLIP_NONE);


        }
    }
}


void initRendering(Game game){
    clearScreen(game);
        
    if(game->state == MENU_STATE){
        int actual_center_x = SCREEN_WIDTH/2 - 125;
        int actual_center_y = SCREEN_HEIGHT/2 - 50;
        drawText(game->texture_manager,0,actual_center_x,actual_center_y,250,50,game->renderer);
        drawText(game->texture_manager,1,actual_center_x,actual_center_y + 40,250,50,game->renderer);
    
    } else {
        drawMap(game);
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

static void checkCamera(SDL_Rect* camera){
    if(camera->x < 0){
        camera->x = 0;
    }
    if(camera->y < 0){
        camera->y = 0;
    }
    if(camera->x > WORLD_WIDTH - camera->w){
        camera->x = WORLD_WIDTH - camera->w;
    }
    if(camera->y > WORLD_HEIGHT - camera->h){
        camera->y = WORLD_HEIGHT - camera->h;
    }
}

void gameUpdate(Game game){
    playerUpdate(game->players[0]);
    game->camera.x = (game->players[0]->position.x + TILE_WIDTH - game->camera.w/2);
    game->camera.y = (game->players[0]->position.y + TILE_HEIGHT - game->camera.h/2);
    checkCamera(&game->camera);
    if(game->camera.x < 0){

    fprintf(stderr,"%d\n",game->camera.x);
    }
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
