#include "TextureManager.h"

#include "DS/list.h"
#include "texture.h"

struct texturem_t{
    List textures;
    List labels;
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
    manager->textures = listCreate(freeTexturePtr,NULL,NULL);
    manager->labels = listCreate(freeTexturePtr,NULL,NULL);
    if(!manager->textures || !manager->labels) exit(1);
    return manager;
}

void load(TextureManager manager,SDL_Renderer* renderer,const char* file_name,TexType texture_type){
    Texture new_t = loadTextureFromFile(renderer,file_name,texture_type);
    if(!new_t) {exit(1);}
    new_t->label_id = getListSize(manager->textures);
    listInsert(manager->textures,new_t);
}

void loadText(TextureManager manager,SDL_Renderer* renderer,TTF_Font* font, const char* text,SDL_Color* color){
    SDL_Color* c = NULL;
    if(color){
        c = color;
    }
    Texture font_texture = loadTextureFromText(renderer,font,text,c);
    if(!font_texture) {
        fprintf(stderr,"Could'nt create texture");
        return;
    }
    font_texture->label_id = getListSize(manager->labels);
    listInsert(manager->labels,font_texture);
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

void drawFrame(TextureManager manager,TexType texture_type,int x,int y,int frame_width,
            int frame_height,int render_width,int render_height,int current_row,int current_frame,
            SDL_Renderer* renderer, SDL_RendererFlip flip){

    Texture to_render = loopAndFindTexture(manager,texture_type);
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

    SDL_RenderCopyEx(renderer,to_render->texture,&src,&dst,0,0,flip);
}

void drawText(TextureManager manager,int label_id,int x,int y,
            int width, int height, SDL_Color color,SDL_Renderer* renderer){
        
        Node current = getHead(manager->labels);
        while (current != NULL)
        {
            Texture tmp = getNodeData(current);
            if(tmp->label_id == label_id){
                SDL_Rect src;
                SDL_Rect dst;
                src.x = 0;
                src.y = 0;
                src.h = tmp->height;
                src.w = tmp->width; 
                dst.w = width;
                dst.h = height;
                dst.x = x;
                dst.y = y;
                SDL_RenderCopy(renderer,tmp->texture,&src, &dst);
            }
            current = getNextNode(current);
        }
                
}

void drawSprite(TextureManager manager, TexType texture_type,int x,int y, int width,int height, int sprite_x,int sprite_y,SDL_Renderer* renderer){
    Texture to_render = loopAndFindTexture(manager,texture_type);
    if(!to_render) return;
    
    SDL_Rect src;
    SDL_Rect dst;
    src.x = sprite_x;
    src.y = sprite_y;
    src.h = dst.h = height;
    src.w = dst.w = width;
    dst.x = x;
    dst.y = y;

    SDL_RenderCopy(renderer,to_render->texture,&src,&dst);
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