#include "player.h"
#include "stdlib.h"
#include "memory.h"

#define TILE_STARTER 10

static List createList(){
    List new_list = (List)malloc(sizeof(*new_list));
    if(!new_list) return NULL;
    new_list->head = NULL;
    new_list->size = 0;
    return new_list;
}

Player initPlayer(int x,int y,int width,int height){
    Player new_p = (Player)malloc(sizeof(*new_p));
    if(!new_p) return NULL;
    new_p->position.x = x;
    new_p->position.y = y;
    new_p->width = width;
    new_p->height = height;
    new_p->isMoving = false;
    Vector2f vel = {10,10};
    new_p->vel = vel;
    new_p->tile_list = createList();
    return new_p;
}

void destroyPlayer(Player p){
    free(p);
}

static Node createNode(Tile t){
    if(!t) return NULL;
    Node n = (Node)malloc(sizeof(*n));
    if(!n) return NULL;
    n->next = NULL;
    n->tile = t;
    return n;
}

void insertTile(List list,Tile t){
    if(!list || !t) return;
    Node new_node = createNode(t);
    if(!new_node) exit(1);

    Node current = list->head;
    if(!current){ // no elements in the list
        list->head = new_node;
        list->size = 1;
        return;
    }

    // walk the list
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = new_node;
    list->size++;
    
}
void removeHead(List list){
    if(!list) return;
    Node current = list->head;
    if(!current) return;
    list->head = current->next;
    list->size--;
    current->next = NULL;
    destroyTile(current->tile);
    free(current);
}

void printList(List list){
    Node current = list->head;
    int i = 0;
    while(current != NULL){
        fprintf(stderr,"%d -",i);
        i++;
        current = current->next;
    }
    fprintf(stderr,"\n");
}


