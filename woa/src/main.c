#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "game.h"
#include "logic.h"
#include "timer.h"

internal void initSDL(SDL_Window** window, SDL_Renderer** renderer);
internal void quitSDL(SDL_Window** window);

int main(){
    

    const int SCREEN_FPS = 60;
    const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

    SDL_Window* window = NULL;

    Game game = initGame();
    if(!game){
        exit(1);
    }
    initSDL(&window,&game->renderer);
    game->global_font = TTF_OpenFont("src/assets/AlbertText-Bold.ttf",28);
    if(!game->global_font){
        fprintf(stderr,"MAMA MIA");
        exit(1);
    }
    loadTextures(game);
    initEntities(game);
    
    int frameCounter = 0;

    SDL_Event event;
    while(IS_RUNNING(game)){
        uint32_t cap_time = SDL_GetTicks();
        /*
        * This function keeps listening to events and handles it accordinlgy
        */
        handleEvents(&event, game);
       
        gameUpdateAndRender(game);
        //gameUpdate(game);
        /* Rendering */
        //initRendering(game);
        /* End of Rendering */

        ++frameCounter;
        
        int frameTicks = SDL_GetTicks() - cap_time;
        if( frameTicks < SCREEN_TICKS_PER_FRAME ){
            //Wait remaining time
            SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
        }
    }
   
    
    quitGame(game);
    quitSDL(&window);

    return 0;
}


/*  STATIC FUNCTIONS  IMPLEMENTATION  */

static void initSDL(SDL_Window** window, SDL_Renderer** renderer){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr,"Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    *window = SDL_CreateWindow("World of Asaad",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN );
    if(!(*window)) {
        fprintf(stderr,"Could'nt initiate window: %s \n", SDL_GetError());
        exit(1);
    }
    *renderer = SDL_CreateRenderer(*window,-1 ,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!(*renderer)) {
        fprintf(stderr,"Could'nt initiate renderer: %s \n", SDL_GetError());
        exit(1);
    }
    
    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) ){
        fprintf(stderr,"Couldn't initialize images: %s\n", SDL_GetError());
        exit(1);
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 ){
        fprintf(stderr, "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        exit(1);
    }

}

void quitSDL(SDL_Window** window){
    SDL_DestroyWindow(*window);

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

