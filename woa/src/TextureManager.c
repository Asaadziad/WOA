#include "TextureManager.h"

#include "DS/list.h"
#include "texture.h"
#include "common.h"
#include "logger.h"

struct texturem_t {
    Texture* textures_arr;
    int textures_top;
    Texture* labels_arr;
    int labels_top;
    List textures;
    List labels;
};

internal void freeTexturePtr(void* elem){
    freeTexture((Texture)elem);
}

internal Texture loopAndFindTexture(TextureManager manager,int id){
    Node current = getHead(manager->textures);
    while(current != NULL){
        Texture tmp = getNodeData(current);
        if(getTextureId(tmp) == id){
            return tmp;
        }
        current = getNextNode(current);
    }
    return NULL;
}

TextureManager textureManagerInit(){
    TextureManager manager = (TextureManager)malloc(sizeof(*manager));
    if(!manager) return NULL;
    manager->textures = listCreate(freeTexturePtr,NULL,NULL);
    manager->labels = listCreate(freeTexturePtr,NULL,NULL);
    if(!manager->textures || !manager->labels) exit(1);
    return manager;
}

internal
int loadTextureFromFile(SDL_Renderer* renderer,const char* path,int id){
    SDL_Texture* texture;

    SDL_Surface* surface = IMG_Load(path);
    if(!surface) {
        ERR("Couldn't load file");
        return -1;
    }

    texture = SDL_CreateTextureFromSurface( renderer, surface );
    if(!texture) {
        ERR("Couldn't create texture");
        return -1;
    }
    Texture t = initTexture(0,0,id);
    if(!t) return -1;
    setTexturePtr(t, texture);
    setTextureHeight(t, surface->h);
    setTextureWidth(t, surface->w);
    
    SDL_FreeSurface( surface );

    return getTextureId(t);
}

internal
int loadTextureFromText(SDL_Renderer* renderer,TTF_Font* font,const char* text,SDL_Color* color){
    SDL_Texture* label;

    SDL_Color black = {0,0,0,0};
    SDL_Surface* surface;
    if(color){
        surface = TTF_RenderText_Solid(font,text,*color);
    } else {
        surface = TTF_RenderText_Solid(font,text,black);
    }
    if(!surface) return -1;

    label = SDL_CreateTextureFromSurface(renderer , surface );

    Texture texture = initTexture(0,0,0);
    if(!texture) {
        SDL_FreeSurface( surface );
        return -1;
    }
    setTexturePtr(texture, label);
    setTextureHeight( texture, surface->h);
    setTextureWidth( texture, surface->w);
    SDL_FreeSurface( surface );

    return getTextureId(texture);
}

// TODO:: load shall return the id of the texture.
int load(TextureManager manager,SDL_Renderer* renderer,const char* file_name){
    int new_t_id = loadTextureFromFile(renderer,file_name, manager->textures_top++);
    if(new_t_id == -1) {
      ERR("Couldn't load texture");
      manager->textures_top--;
    }
    
    //TODO:: convert from list to array
    //listInsert(manager->textures,new_t);
    return new_t_id;
}

void loadText(TextureManager manager,SDL_Renderer* renderer,TTF_Font* font, const char* text,SDL_Color* color){}

void draw(TextureManager manager,int id,int x,int y,
            int width, int height, SDL_Renderer* renderer,
            SDL_RendererFlip flip){

    Texture to_render = loopAndFindTexture(manager, id);
    if(!to_render) return;
    
    SDL_Rect src;
    SDL_Rect dst;
    src.x = 0;
    src.y = 0;
    src.h = dst.h = height;
    src.w = dst.w = width;
    dst.x = x;
    dst.y = y;

    SDL_RenderCopyEx(renderer,getTexturePtr(to_render),&src,&dst,0,0,flip);
}

void drawFrame(TextureManager manager,int id,int x,int y,int frame_width,
            int frame_height,int render_width,int render_height,int current_row,int current_frame,
            SDL_Renderer* renderer, SDL_RendererFlip flip){

    Texture to_render = loopAndFindTexture(manager,id);
    if(!to_render) return;
    
    SDL_Rect src;
    SDL_Rect dst;
    src.x = frame_width * current_frame;
    src.y = frame_height * (current_row - 1);
    src.h = frame_height;
    src.w = frame_width;
    dst.w = render_width;
    dst.h = render_height;
    dst.x = x;
    dst.y = y;

    SDL_RenderCopyEx(renderer,
       getTexturePtr(to_render),
       &src, &dst,
       0,0, 
       flip);
}

void drawText(TextureManager manager,int label_id,int x,int y,
            int width, int height, SDL_Color color,SDL_Renderer* renderer){
        
        Node current = getHead(manager->labels);
        while (current != NULL)
        {
            Texture tmp = getNodeData(current);
            if(getTextureLabelId(tmp) == label_id){
                SDL_Rect src;
                SDL_Rect dst;
                src.x = 0;
                src.y = 0;
                src.h = getTextureHeight(tmp);
                src.w = getTextureWidth(tmp); 
                dst.w = width;
                dst.h = height;
                dst.x = x;
                dst.y = y;
                SDL_RenderCopy(renderer, 
                    getTexturePtr(tmp), 
                    &src, 
                    &dst);
            }
            current = getNextNode(current);
        }
                
}

void drawSprite(TextureManager manager, int id,int x,int y, int width,int height, int sprite_x,int sprite_y,SDL_Renderer* renderer){
    Texture to_render = loopAndFindTexture(manager,id);
    if(!to_render) return;
    
    SDL_Rect src;
    SDL_Rect dst;
    src.x = sprite_x;
    src.y = sprite_y;
    src.h = dst.h = height;
    src.w = dst.w = width;
    dst.x = x;
    dst.y = y;

    SDL_RenderCopy(renderer, 
                  getTexturePtr(to_render), 
                  &src, 
                  &dst);
}

void drawRect(int x,int y,int height,int width,SDL_Color color,bool isFill,float fill_width,SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer,color.r,color.g,color.b,color.a);
    SDL_Rect rect;
    rect.x =x;
    rect.y = y;
    rect.h = height;
    rect.w = width;
    if(isFill){
        SDL_RenderDrawRect(renderer,&rect);
        rect.w = fill_width - 2;
        rect.h -=2;
        rect.x +=1;
        rect.y += 1;
        SDL_RenderFillRect(renderer,&rect);
    } else {
        SDL_RenderDrawRect(renderer,&rect);

    }
}


void destroyTextureManager(TextureManager manager){
    if(!manager) return;
    listDestroy(manager->labels);
    listDestroy(manager->textures);
    free(manager);
}
