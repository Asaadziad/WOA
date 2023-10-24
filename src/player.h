#ifndef PLAYER_H
#define PLAYER_H

#include "stdbool.h"
#include "vector.h"
#include "tile.h"

typedef struct node_t {
    Tile tile;
    struct node_t* next;
} *Node;

typedef struct list_t {
    Node head;
    size_t size;
} *List;

typedef enum {
    NORTH,
    SOUTH,
    WEST,
    EAST,
} PlayerFace;

typedef struct player_t{
    Vector2f position;
    Vector2f vel;
    int height;
    int width;
    bool isMoving;
    List tile_list;  
    PlayerFace face;
} *Player;

Player initPlayer(int x,int y,int width,int height);
void destroyPlayer(Player p);

void insertTile(List list,Tile t);
void removeHead(List list);
void printList(List list);

#endif