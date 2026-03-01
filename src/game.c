#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>
// Importing my own headers
#include "Object.h"


#define WIDTH 640
#define HEIGHT 480

SDL_Window *window;
SDL_Renderer *renderer;

Object Player = {
    .name = "Player",
    .pos = {0,0},
    .size = {50,50},
    .texture_file = "./textures/player.png",
    .color = {0,0,0,255}
};

Game game = {
    .Input = {}
};

void Start() {
    /*
    Start function
    Works when starting the program
    */

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect texture_rect={0,0,1,1};
    Awake(renderer, &Player);
}

void Early_Update(float dt) {
    return;
}

void Update(float dt) {
    Vector2 directions = {game.Input[SDL_SCANCODE_D] - game.Input[SDL_SCANCODE_A], game.Input[SDL_SCANCODE_S] - game.Input[SDL_SCANCODE_W]};
    float mag = sqrt(pow(directions.x,2)+pow(directions.y,2));
    
    int speed = 50;
    if (mag>0){
        Vector2 norm = {directions.x/mag,directions.y/mag};
        Player.pos.x += speed*dt*norm.x/100;
        Player.pos.y += speed*dt*norm.y/100;
    }

    return;
}

void Late_Update(float dt) {
    Draw(renderer, &Player);
    return;
}

int main() {
    //Create window
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);

    //Checks if window pointer exists and if the renderer is valid
    if(!window && !renderer){
        printf("Failed to create window \n");
        return 0;
    }else{
        printf("Window created sucessfully \n");
    }

    //Start
    printf("Engine Start \n");
    Start();

    //Game logic
    Uint32 prev_tick = 0;
    printf("Starting program \n");
    uint8_t running = 1;
    while (running == 1){
        Uint64 ticks_now = SDL_GetTicks64();
        float delta_time = (ticks_now - prev_tick);

        SDL_Event event;
        
        if (SDL_PollEvent(&event))
        {
            //Check if it's quiting or pressing the escape key
            if (event.type == SDL_QUIT || game.Input[SDL_SCANCODE_ESCAPE] == 1){
                running = 0;
            }else 
            //Check if it's pressing a any key
            if(event.type == SDL_KEYDOWN){
                //printf("Key Down \n");
                game.Input[event.key.keysym.scancode] = 1;
            }else
            //Check if it's not pressing any key
            if (event.type == SDL_KEYUP){
                //printf("Key Up \n");
                game.Input[event.key.keysym.scancode] = 0;
            }
        }

        //Update frame functions, game logic goes here mostly
        Early_Update(delta_time);
        Update(delta_time);
        Late_Update(delta_time);

        //Render update
        SDL_RenderPresent(renderer);

        //Clear rendered screen for next frame
        SDL_RenderClear(renderer);

        prev_tick = ticks_now;
    }

    //Free memory when ending the program
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    
    return 0;
}