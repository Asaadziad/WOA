#ifndef TIMER_H
#define TIMER_H

#include "stdint.h"

typedef struct timer_t {
    uint32_t start_time;
    uint32_t pause_time;
} Timer;

void startTimer(Timer timer);
void stopTimer(Timer timer);
void pauseTimer(Timer timer);
void unpauseTimer(Timer timer);

uint32_t getTime(Timer timer);

#endif