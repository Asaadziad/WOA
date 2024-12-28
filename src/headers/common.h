#ifndef COMMON_H
#define COMMON_H

#include "stdint.h"
#include "stdbool.h"


#define KILOBYTES(x) (x * 1024)
#define MEGABYTES(x) ((KILOBYTES(x)) * 1024)
#define GIGABYTES(x) ((MEGABYTES(x)) * 1024)

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800
#define MAX_WORLD_COLS 50
#define MAX_WORLD_ROWS 50
#define WORLD_HEIGHT 1600
#define WORLD_WIDTH 1600
#define PLAYERS_COUNT 1

#define local_var static
#define internal static
#define global_var static

//typedef's
typedef uint8_t  u8;
typedef uint32_t u32;


#endif
