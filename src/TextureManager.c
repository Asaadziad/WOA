#include "TextureManager.h"

#include "DS/list.h"
#include "texture.h"

struct texturem_t{
    List textures;
};

static void freeTexturePtr(void* elem){
    freeTexture((Texture)elem);
}

static Texture loopAndFindTexture(TextureManager manager,TexType type){
    Node current = getHead(manager->textures);
    while(current != NULL){
        Texture tmp = getNodeData(current);
        if(tmp->type == type){
            return tmp;
        }
        current = getNextNode(current);
    }
    return NULL;
}

TextureManager textureManagerInit(){
    TextureManager manager = (TextureManager)malloc(sizeof(*manager));
    if(!manager) return NULL;
    manager->textures = listCreate(freeTexturePtr,NULL);
    return manager;
}

void load(TextureManager manager,SDL_Renderer* renderer,const char* file_name,TexType texture_type){
    Texture new_t = loadTextureFromFile(renderer,file_name,texture_type);
    if(!new_t) return;
    listInsert(manager->textures,new_t);
}

void draw(TextureManager manager,TexType texture_type,int x,int y,
            int width, int height, SDL_Renderer* renderer,
            SDL_RendererFlip flip){

    Texture to_render = loopAndFindTexture(manager,texture_type);
    if(!to_render) return;
    
    SDL_Rect src;
    SDL_Rect dst;
    src.x = 0;
    src.y = 0;
    src.h = dst.h = height;
    src.w = dst.w = width;
    dst.x = x;
    dst.y = y;

    SDL_RenderCopyEx(renderer,to_render->texture,&src,&dst,0,0,flip);
}

void drawFrame(TextureManager manager,TexType texture_type,int x,int y,int width,
            int height,int current_row,int current_frame,
            SDL_Renderer* renderer, SDL_RendererFlip flip){

    Texture to_render = loopAndFindTexture(manager,texture_type);
    if(!to_render) return;
    
    SDL_Rect src;
    SDL_Rect dst;
    src.x = width * current_frame;
    src.y = height * (current_row - 1);
    src.h = dst.h = height;
    src.w = dst.w = width;
    dst.x = x;
    dst.y = y;

    SDL_RenderCopyEx(renderer,to_render->texture,&src,&dst,0,0,flip);
}
