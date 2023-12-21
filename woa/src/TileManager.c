#include "TileManager.h"
#include "tile.h"
#include "stdlib.h"
#include "common.h"
#include "logger.h"

struct tilemanager_t {
    Tile** tiles; // double pointers = an array of array's = a matrix
};

TileManger initTileManager(){
    TileManger manager = (TileManger)malloc(sizeof(*manager));
    if(!manager) return NULL;
    Tile** big_array = (Tile**)malloc(sizeof(*big_array) * MAX_WORLD_ROWS);
    if(!big_array){ 
        ERR("failed here");
        return NULL;}
    for(int i = 0; i < MAX_WORLD_ROWS;i++){
        Tile* new_tiles = (Tile*)malloc(sizeof(Tile) * (MAX_WORLD_COLS));
        if(!new_tiles) {
            ERR("NO HERE");
            return NULL;}
        big_array[i] = new_tiles;
    }
    manager->tiles = big_array;
    return manager; 
}


static char* readFileToBuffer(const char* map_path){
    FILE* map = fopen(map_path, "r");
    if(!map) {ERR("Couldn't open map");exit(1);}
    
    fseek(map,0,SEEK_END);
    size_t file_size = ftell(map);
    fseek(map,0,SEEK_SET);
    char* buffer = (char*)malloc(sizeof(char)* (file_size + 1));
    if(!buffer) {ERR("Couldn't allocate buffer memory"); exit(1);}
    fread(buffer,file_size,1,map);
    buffer[file_size] = '\0';
    fclose(map);
    return buffer;
}


static void loadTilesMap(TileManger manager,const char* map_path){
    char* tiles_string = readFileToBuffer(map_path);
    char* to_free = tiles_string;
    
    int i = 0;
    int j = 0;
    while(*tiles_string != '\0'){
        if(*tiles_string == ' ' || *tiles_string == '\n' || *tiles_string == '\r' || *tiles_string == '\t'){
            tiles_string++;
            continue;
        }
        int type = *tiles_string - '0';
        manager->tiles[i][j] = createTile(j * TILE_WIDTH,i * TILE_HEIGHT,type);
        //game->map[i] = *tiles_string - '0'; // 0 1 2
        
        j++;
        if(j == 50){
            j = 0;
            i++;
        }
        tiles_string++;
    } 
    free(to_free);
}


void setupTiles(TileManger manager,const char* file_path){
    //manager->tiles[0][0] = createTile(0,0,EARTH_TILE);
    loadTilesMap(manager,"world.txt");
    fprintf(stderr, "hgello?");
}

void renderTiles(TileManger manager,TextureManager texture_manager,SDL_Renderer* renderer,SDL_Rect camera){
    for(int row = 0 ; row < MAX_WORLD_ROWS;row++){
        for(int col = 0; col < MAX_WORLD_COLS;col++){
            Tile tile = manager->tiles[row][col];
            int worldX = getTileWorldX(tile);
            int worldY = getTileWorldY(tile);

            int screenX = worldX - camera.x;
            int screenY = worldY - camera.y;

            int current_frame = getTileType(tile);
            //fprintf(stderr,"%d - %d\n",current_row,current_frame);
            drawFrame(texture_manager,0,screenX,screenY,TILE_WIDTH,TILE_WIDTH,TILE_WIDTH,TILE_WIDTH,1,current_frame,renderer,SDL_FLIP_NONE);


        }
    }
}

void destroyTileManager(TileManger manager){
    for(int i = 0;i < MAX_WORLD_ROWS;i++){
        for(int j = 0 ; j < MAX_WORLD_COLS;j++){
            destroyTile(manager->tiles[i][j]);
        }
        free(manager->tiles[i]);
    }
    free(manager->tiles);
}
