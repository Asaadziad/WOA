#include "SDL2/SDL.h"
#include "headers/timer.h"


void startTimer(Timer timer){
    timer.start_time = SDL_GetTicks64();
    timer.pause_time = 0;
}
void stopTimer(Timer timer){
    timer.start_time = 0;
    timer.pause_time = 0;
}

void pauseTimer(Timer timer){
    timer.pause_time = SDL_GetTicks() - timer.start_time;
    timer.start_time = 0;
}
void unpauseTimer(Timer timer){
    timer.start_time = SDL_GetTicks() - timer.pause_time;
    timer.pause_time = 0; 
}

uint32_t getTime(Timer timer){
    return SDL_GetTicks() - timer.start_time;
}
