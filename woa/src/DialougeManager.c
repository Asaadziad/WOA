#include "DialougeManager.h"
#include "DS/list.h"
#include "stdlib.h"
#include "TextureManager.h"
#include "Dialouge.h"

struct dialougem_t {
    List dialouges;        
};

static void dialougeDestroyPtr(void* elem){
    destroyDialouge((DIALOUGE)elem);
}

DialougeManager initDialougeManager(){
    DialougeManager m = (DialougeManager)malloc(sizeof(*m));
    if(!m) return NULL;
    m->dialouges = listCreate(dialougeDestroyPtr,NULL,NULL);
    return m;
}

/*
* setting dialouges up manually until i need it automated
*/
void setupDialouges(DialougeManager manager,const char* file_path){
    /*
    * SWORD_DIALOUGE
    * Hello asaad,   - label_id : 3
    * Would you like to pickup this sword? - label_id
    * Yes - No
    * Note: Press space for YES and press v for NO
    */
   int* sword_labels = (int*)malloc(sizeof(*sword_labels) * 3);
   if(!sword_labels) return;
   sword_labels[0] = 3;
   sword_labels[1] = 4;
   sword_labels[2] = 5;
   DIALOUGE d = createDialouge(sword_labels,3,SWORD_DIALOUGE);
   listInsert(manager->dialouges,d);
}

static void drawDialougeBox(SDL_Renderer* renderer){
    SDL_Rect box;
    box.x = 50;
    box.y = 50;
    box.w = 400;
    box.h = 200;
    drawRect(box.x,box.y,box.h,box.w,(SDL_Color){0,0,0,0},true,box.w,renderer);
}

void renderDialouge(DialougeManager manager,TextureManager texture_manager,SDL_Renderer* renderer,DialougeKind dialouge_kind){
    SDL_Rect box;
    box.x = 50;
    box.y = 50;
    box.w = 400;
    box.h = 200;
    SDL_Color white = {255,255,255,255};
    drawDialougeBox(renderer);
    Node current = getHead(manager->dialouges);
    if(!current) return;
    for(int i = 0;i < getListSize(manager->dialouges);i++){
        DIALOUGE tmp = getNodeData(current);
        if(getDialougeKind(tmp) == dialouge_kind){
            int* labels = getDialougeLabels(tmp);
            int height = box.h / (getLabelsSize(tmp)+1);
            for(int j = 0; j < getLabelsSize(tmp);j++){
                drawText(texture_manager,labels[j],box.x + 5,box.y + 5 + j*height,box.w - 5,height,white,renderer);
            }
        }
    }

}

void sendDialouge(int dialouge_id){   
}

void destroyDialogeManager(DialougeManager manager){
    listDestroy(manager->dialouges);
    free(manager);
}