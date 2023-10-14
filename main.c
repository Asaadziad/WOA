#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "game.h"

static void initSDL(SDL_Window** window, SDL_Renderer** renderer);
static void quitSDL(SDL_Window** window);

int main(){
    SDL_Window* window = NULL;

    Game game = initGame();
    game->state = RUNNING_STATE;
    initSDL(&window,&game->renderer);
    loadTexture(game->renderer,game->current_texture,"sprites.png");
    initEntities(game);

    SDL_Event event;
    while(IS_RUNNING(game)){
        /*
        * This function keeps listening to events and handles it accordinlgy
        */
        handleEvent(&event, game);
        
        //render_game(game);   
        renderEntities(game);

    }

    freeTexture(game->current_texture);
    
    
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

