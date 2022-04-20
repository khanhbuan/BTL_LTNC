#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<thread>
#include<chrono>
#include "game_continue.h"
#include "init.h"
#include "load_img.h"
using namespace std;

bool check = 0;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int JUMP_HEIGHT = 70;
const int JUMP_STEP = 5;
const int BACK_STEP = 5;
const int height = 34;
const string WINDOW_TITLE = "An Implementation of DINO";
const string text = "GAME OVER!";
const SDL_Color textColor = {0, 0, 0};

void clear_renderer(SDL_Renderer* &renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderClear(renderer);
}

void trap_run(SDL_Rect &rect, SDL_Renderer* &renderer, SDL_Texture* &character) {
    rect.x -= BACK_STEP;
    if(rect.x <= BACK_STEP) rect.x = SCREEN_WIDTH - rect.w;
    SDL_RenderCopy(renderer, character, NULL, &rect);
}

void draw_ground(SDL_Renderer* &renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT/2 + height, SCREEN_WIDTH, SCREEN_HEIGHT/2 + height);
}

int main(int argc, char* argv[]) {
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    //set background color to white
    clear_renderer(renderer);

    //load dino
    SDL_Texture* character = loadTexture("dino.png", renderer);
    SDL_Rect rect;
    rect.x = SCREEN_WIDTH/4;
    rect.y = SCREEN_HEIGHT/2;
    SDL_QueryTexture(character, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, character, NULL, &rect);

    //load cactus
    SDL_Texture* trap = loadTexture("cactus1.png", renderer);
    SDL_Rect rect2;
    rect2.h = rect.h;
    rect2.w = rect.w;
    rect2.x = SCREEN_WIDTH - rect2.w;
    rect2.y = SCREEN_HEIGHT/2;
    SDL_RenderCopy(renderer, trap, NULL, &rect2);

    draw_ground(renderer);

    //draw
    SDL_RenderPresent(renderer);

    SDL_Event event;
    bool game_lose = false;

    while(true) {
        check = false;
        SDL_PollEvent(&event);
        if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) break;

        clear_renderer(renderer);
        SDL_RenderCopy(renderer, character, NULL, &rect);
        trap_run(rect2, renderer, trap);
        draw_ground(renderer);
        SDL_RenderPresent(renderer);

        if(check_game_continue(rect, rect2) == false) {
            game_lose = true;
            break;
        }

        if(event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_SPACE:
                    check = true;
                    break;
                case SDLK_UP:
                    check = true;
                    break;
            }
            if(check) {
                for(int i = 0 ; i <= JUMP_HEIGHT / JUMP_STEP ; i++) {
                    clear_renderer(renderer);
                    rect.y -= JUMP_STEP;
                    SDL_RenderCopy(renderer, character, NULL, &rect);
                    trap_run(rect2, renderer, trap);
                    draw_ground(renderer);
                    SDL_RenderPresent(renderer);
                    if(check_game_continue(rect, rect2) == false) {
                        game_lose = true;
                        break;
                    }
                }
                if(game_lose == true) break;
                for(int i = 0 ; i <= JUMP_HEIGHT / JUMP_STEP ; i++) {
                    clear_renderer(renderer);
                    rect.y += JUMP_STEP;
                    SDL_RenderCopy(renderer, character, NULL, &rect);
                    trap_run(rect2, renderer, trap);
                    draw_ground(renderer);
                    SDL_RenderPresent(renderer);
                    if(check_game_continue(rect, rect2) == false) {
                        game_lose = true;
                        break;
                    }
                }
                if(game_lose == true) break;
            }
        }
    }
    if(game_lose == true) {
        clear_renderer(renderer);
        if(TTF_Init() == -1) printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        TTF_Font *gFont = NULL;
        gFont = TTF_OpenFont("Lato-Light.ttf", 30);
        SDL_Texture *ending = loadText(gFont, renderer, text, textColor);
        SDL_Rect banner;
        banner.x = SCREEN_WIDTH/3;
        banner.y = SCREEN_HEIGHT/3;
        banner.w = SCREEN_WIDTH/3;
        banner.h = SCREEN_HEIGHT/3;
        SDL_RenderCopy(renderer, ending, NULL, &banner);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
    }
    quitSDL(window, renderer);
    return 0;
}
