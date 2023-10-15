#ifndef PLAYER_H
#define PLAYER_H

typedef enum {
    STANDING_STATE,
    WALKING_STATE,
} PlayerState;

typedef struct player_t{
    int x;
    int y;
    int walk_to_x;
    int walk_to_y;
    PlayerState state;
    int walking_frames;
    int current_frame;
    int p_vel;
} *Player;

Player initPlayer(int x,int y);

#endif