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

/*static void createMenuUI(Game game){
    Texture t = initTexture(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,LABEL_TEXTURE);
    loadTextureFromText(game->renderer,game->global_font,t,"World of asaad");
    Texture tt = initTexture(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 + t->height,LABEL_TEXTURE);
    loadTextureFromText(game->renderer,game->global_font,tt,"Press space to enter");
    listInsert(game->textures,t);
    listInsert(game->textures,tt);
}*/


static void getTileTypes(Game game){   
    for(int i = 0; i <TOTAL_TILES;i++){
        TileType type = game->tiles[i]->type;
        SDL_Rect dst;
        dst.h = TILE_HEIGHT;
        dst.w = TILE_WIDTH;
        switch(type){
            case WATER_TILE:
                dst.x = 0;
                dst.y = 60;
                break;
            case GRASS_TILE:
                dst.x = 0;
                dst.x = 80;
                break;
            case LAVA_TILE:
                dst.x = 0;
                dst.y = 0;
            break;
            case BLOCK_TILE:
                dst.x = 160;
                dst.y = 80;
                break;
        };
        game->tiles[i]->tile_box = dst;
    }
}

static char* fileToBuffer(FILE* file){
    int buffSize = 0;
    fseek(file,0L,SEEK_END);
    buffSize = ftell(file);
    char* result = (char*)malloc(sizeof(char) * (buffSize+1));
    if(!result) return NULL;
    fseek(file,0L,SEEK_SET);
    size_t new_len = fread(result,sizeof(char),buffSize,file);
    result[new_len] = '\0'; 
    return result;
}

static void setTiles(Game game){
    char* map = fileToBuffer(game->map);
    size_t len = strlen(map);
    int t_index = 0;
    for(int i = 0;i < len;i++){
        if(map[i] == ' ' || map[i] == '\n'){
            continue;
        }
        if(game->tiles){ 
            game->tiles[t_index] = createTile(0,0,map[i] - '0');
        } else {
            ERR("test");
        }
        t_index++;
    }
    free(map);
    getTileTypes(game);
}
void loadTileMap(Game game){
    Texture tiles = loadTextureFromFile(game->renderer,"tiles.jpg",TILE_TEXTURE);
    if(!tiles) {
        ERR("Tiles Couldn't create");
        exit(1);
    }
    listInsert(game->textures,tiles);
    FILE* map_f = fopen("src/assets/map.map","r");
    if(!map_f) {
        ERR("Couldn't open map");
        exit(1);
    }
    game->map = map_f;
    setTiles(game);
    
}

static void createPlayerTextures(Game game){
    Texture player = loadTextureFromFile(game->renderer,"character.png",PLAYER_TEXTURE);
    listInsert(game->textures,player);
}


void loadTextures(Game game){
    //createMenuUI(game);
    load(game->texture_manager,game->renderer,"character.png",PLAYER_TEXTURE);
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
                listEmpty(game->textures);
                game->state = RUNNING_STATE;
                
                createPlayerTextures(game);
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
        //createPlayerTextures(game);
        renderEntities(game);
        listEmpty(game->textures);
        
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
