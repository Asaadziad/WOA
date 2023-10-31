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
    new_g->tiles = (Tile*) malloc(sizeof(Tile) * (TOTAL_TILES));
    return new_g;
}

static void createMenuUI(Game game){
    Texture t = initTexture(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,LABEL_TEXTURE);
    loadTextureFromText(game->renderer,game->global_font,t,"World of asaad");
    Texture tt = initTexture(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 + t->height,LABEL_TEXTURE);
    loadTextureFromText(game->renderer,game->global_font,tt,"Press space to enter");
    listInsert(game->textures,t);
    listInsert(game->textures,tt);
}

/*static void getTileTypes(Game game){
    FILE* map_file = game->map;
    
    TileType type = game->tiles[0]->type;
        SDL_Rect dst;
        dst.h = TILE_HEIGHT;
        dst.w = TILE_WIDTH;
        switch(type){
            case WATER_TILE:
                dst.x = 0;
                dst.y = 60;
                break;
            case BLOCK_TILE:
                dst.x = 160;
                dst.y = 80;
                break;
            case GRASS_TILE:
                dst.x = 0;
                dst.x = 80;
                break;
            case LAVA_TILE:
                dst.x = 0;
                dst.y = 0;
            break;
        };
        game->tiles[0]->tile_box = dst;
}*/

static char* fileToBuffer(FILE* file){
    int buffSize = 0;
    fseek(file,0L,SEEK_END);
    buffSize = ftell(file);
    char* result = (char*)malloc(sizeof(char) * (buffSize+1));
    if(!result) return NULL;

    size_t new_len = fread(result,sizeof(char),buffSize,file);
    result[new_len++] = '\0'; 
    fseek(file,0L,SEEK_SET);

    return result;
}

static void setTiles(Game game){
    char* map = fileToBuffer(game->map);
    char* token = strtok(map," ");
    LOG(token);
    free(map);
}
static void loadTileMap(Game game){
    Texture tiles = loadTextureFromFile(game->renderer,"tiles.jpg",TILE_TEXTURE);
    if(!tiles) return;
    listInsert(game->textures,tiles);
    FILE* map_f = fopen("src/assets/map.map","r");
    if(!map_f) return;
    game->map = map_f;
    setTiles(game);
}


void loadTextures(Game game){
    createMenuUI(game);
    loadTileMap(game);
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



static void renderMenu(Game game){
    int i = 0;
    Node current = getHead(game->textures);
    while(current != NULL){
        Texture t = (Texture)getNodeData(current);
        if(t->type == LABEL_TEXTURE){
            renderTexture(game,t);
        }
        current = getNextNode(current);
        i++;
    }
}

static void renderTiles(Game game){
    int i = 0;
    Node current = getHead(game->textures);
    Texture to_render = NULL;
    while(current != NULL){
        Texture t = (Texture)getNodeData(current);
        if(t->type == TILE_TEXTURE){
            to_render = t;
            break;
        }
        current = getNextNode(current);
        i++;
    }
    if(!to_render){
        ERR("TILE_TEXTURE is not found");
        return;
    }
    for(int i = 0 ; i < (TOTAL_TILES);i++){
        
        renderPartOfTexture(game,to_render,game->tiles[i]->tile_box);//need to change (0,0) depending on tile type
    }

}

void initRendering(Game game){
    clearScreen(game);
        
    if(game->state == MENU_STATE){
        renderMenu(game);
        renderTiles(game);
        //renderButton(game,100,100,"Click me");
    } else {
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


void quitGame(Game game){
    TTF_CloseFont(game->global_font);

    for(int i = 0; i < PLAYERS_COUNT;i++){
        destroyPlayer(game->players[i]);
    }
    fclose(game->map);
    listDestroy(game->textures);
    free(game->players);
    free(game);
}
