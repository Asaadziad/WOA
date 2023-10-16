#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "game.h"
#include "logic.h"
#include "timer.h"

static void initSDL(SDL_Window** window, SDL_Renderer** renderer);
static void quitSDL(SDL_Window** window);

int main(){
    

    const int SCREEN_FPS = 60;
    const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

    SDL_Window* window = NULL;

    Game game = initGame();
    game->state = RUNNING_STATE;
    initSDL(&window,&game->renderer);
    loadTexture(game->renderer,game->current_texture,"sprites.png");
    initEntities(game);

    
    int frameCounter = 0;

    SDL_Event event;
    while(IS_RUNNING(game)){
        uint32_t cap_time = SDL_GetTicks();
        /*
        * This function keeps listening to events and handles it accordinlgy
        */
        handleEvents(&event, game);

        handleLogic(game);

        /* Rendering */
        clearScreen(game);
         
        renderEntities(game);

        updateScreen(game);
        /* End of Rendering */

        ++frameCounter;
        
        int frameTicks = SDL_GetTicks() - cap_time;
        if( frameTicks < SCREEN_TICKS_PER_FRAME ){
            //Wait remaining time
            SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
        }
    }
    freeTexture(game->current_texture);
    freeTexture(game->world_texture);
    
    quitSDL(&window);
    quitGame(game);

    return 0;
}


/*  STATIC FUNCTIONS  IMPLEMENTATION  */

static void initSDL(SDL_Window** window, SDL_Renderer** renderer){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    *window = SDL_CreateWindow("World of Asaad",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600,SDL_WINDOW_SHOWN );
    if(!(*window)) {
        printf("Could'nt initiate window: %s \n", SDL_GetError());
        exit(1);
    }
    *renderer = SDL_CreateRenderer(*window,-1 ,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!(*renderer)) {
        printf("Could'nt initiate renderer: %s \n", SDL_GetError());
        exit(1);
    }

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) ){
        printf("Couldn't initialize images: %s\n", SDL_GetError());
        exit(1);
    }
}

void quitSDL(SDL_Window** window){
    SDL_DestroyWindow(*window);
    SDL_Quit();
}

