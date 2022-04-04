#include<iostream>
#include<SDL.h>
#include<thread>
#include<chrono>
#include "init.h"
#include "load_img.h"
using namespace std;

bool check = 0;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int JUMP_HEIGHT = 60;
const int JUMP_STEP = 5;
const int height = 34;
const string WINDOW_TITLE = "An Implementation of Code.org Painter";

void display(SDL_Rect &rect, SDL_Renderer* &renderer, SDL_Texture* &character) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, character, NULL, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT/2 + height, SCREEN_WIDTH, SCREEN_HEIGHT/2 + height);
    SDL_RenderPresent(renderer);
}

void draw_up(SDL_Rect &rect, SDL_Renderer* &renderer, SDL_Texture* &character) {
    for(int i = 0 ; i < JUMP_HEIGHT/JUMP_STEP; i++) {
        rect.y -= JUMP_STEP;
        display(rect, renderer, character);
    }
}

void draw_down(SDL_Rect &rect, SDL_Renderer* &renderer, SDL_Texture* &character) {
    for(int i = 0 ; i < JUMP_HEIGHT/JUMP_STEP; i++) {
        rect.y += JUMP_STEP;
        display(rect, renderer, character);
    }
}

int main(int argc, char* argv[]) {
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderClear(renderer);

    SDL_Texture* character = loadTexture("dino.png", renderer);
    SDL_Rect rect;
    rect.x = SCREEN_WIDTH/4;
    rect.y = SCREEN_HEIGHT/2;
    SDL_QueryTexture(character, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, character, NULL, &rect);

    SDL_Texture* trap = loadTexture("cactus1.png", renderer);
    SDL_Rect rect2;
    rect2.h = rect.h;
    rect2.w = rect.w;
    rect2.x = SCREEN_WIDTH - rect2.w;
    rect2.y = SCREEN_HEIGHT/2;
    SDL_RenderCopy(renderer, trap, NULL, &rect2);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT/2 + height, SCREEN_WIDTH, SCREEN_HEIGHT/2 + height);
    SDL_RenderPresent(renderer);

    SDL_Event event;
    while(true) {
        check = 0;
        SDL_PollEvent(&event);
        if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) break;
        if(event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_SPACE:
                    check = 1;
                    break;
                case SDLK_UP:
                    check = 1;
                    break;
            }
            if(check) {
                draw_up(rect, renderer, character);
                draw_down(rect, renderer, character);
            }
        }
    }
    quitSDL(window, renderer);
    return 0;
}
