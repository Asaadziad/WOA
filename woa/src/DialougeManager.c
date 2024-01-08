#include "../headers/DialougeManager.h"
#include "../headers/list.h"
#include "stdlib.h"
#include "../headers/TextureManager.h"
#include "../headers/Dialouge.h"

struct dialougem_t {
    int       size;       // Number of Dialouges
    DIALOUGE* dialouges;  // Array of Dialouges      
};


DialougeManager initDialougeManager(){
    DialougeManager m = (DialougeManager)malloc(sizeof(*m));
    if(!m) return NULL;
    m->dialouges = NULL;
    m->size = 0;
    return m;
}

/*
* args: this shall take a path to json file. 
*/
void setupDialouges(DialougeManager manager,const char* file_path){
    /*
    * SWORD_DIALOUGE
    * Hello asaad,   - label_id : 3
    * Would you like to pickup this sword? - label_id
    * Yes - No
    * Note: Press space for YES and press v for NO
    */
//    int current = manager->size;  
    // JSONObject* json_objects = parse(file_path); 
    // for each object in json_objects: createDialouge(object);
}

static void drawDialougeBox(SDL_Renderer* renderer){
    SDL_Rect box;
    box.x = 50;
    box.y = 50;
    box.w = 400;
    box.h = 200;
    drawRect(box.x,box.y,box.h,box.w,(SDL_Color){0,0,0,0},true,box.w,renderer);
}

void renderDialouge(DialougeManager manager,TextureManager texture_manager,SDL_Renderer* renderer,int dialouge_id){
    SDL_Rect box;
    box.x = 50;
    box.y = 50;
    box.w = 400;
    box.h = 200;
    drawDialougeBox(renderer);
    // Here draw text

}

void sendDialouge(int dialouge_id){   
}

void destroyDialogeManager(DialougeManager manager){
  if(manager->dialouges){
     for(int i = 0; i < manager->size;i++){
        destroyDialouge(manager->dialouges[i]);
      }  
  }
   
  free(manager);
}
