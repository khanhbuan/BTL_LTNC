#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<thread>
#include<chrono>
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
const string starting = "START";
const string help = "HELP";
const string name = "WELCOME TO DINO IN THE DESERT";
const string get_back = "BACK";
const SDL_Color blue = {0, 0, 255};

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

void set_side(SDL_Rect &rect, int x, int y, int h, int w) {
    rect.x = x;
    rect.y = y;
    rect.h = h;
    rect.w = w;
}

int main(int argc, char* argv[]) {
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    SDL_Texture *background = loadTexture("desert.jpg", renderer);
    SDL_Rect space;
    space.x = 0;
    space.y = 0;
    space.w = SCREEN_WIDTH;
    space.h = SCREEN_HEIGHT;
    SDL_RenderCopy(renderer, background, NULL, &space);

    //set background color to white
    if(TTF_Init() == -1) printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    TTF_Font *gFont = NULL;
    gFont = TTF_OpenFont("Freedom-10eM.ttf", 40);
    TTF_Font *gFont2 = NULL;
    gFont2 = TTF_OpenFont("Lato-Semibold.ttf", 40);
    SDL_Rect banner, banner2, banner3, banner4, banner5;

    set_side(banner, 7*SCREEN_WIDTH/16, 7*SCREEN_HEIGHT/16, SCREEN_HEIGHT/8, SCREEN_WIDTH/8);
    set_side(banner2, SCREEN_WIDTH/4, SCREEN_HEIGHT/8, SCREEN_HEIGHT/5, SCREEN_WIDTH/2);
    set_side(banner3, 7*SCREEN_WIDTH/16, 9*SCREEN_HEIGHT/16, SCREEN_HEIGHT/8, SCREEN_WIDTH/8);
    set_side(banner4, 0, 0, SCREEN_HEIGHT, SCREEN_WIDTH);
    set_side(banner5, 0, 0, 50, 50);

    SDL_Texture *start = loadText(gFont, renderer, starting, blue);
    SDL_Texture *welcome = loadText(gFont, renderer, name, blue);
    SDL_Texture *helping = loadText(gFont, renderer, help, blue);
    SDL_Texture *instruct = loadTexture("instruct.png", renderer);
    SDL_Texture *getback = loadText(gFont2, renderer, get_back, blue);

    SDL_RenderCopy(renderer, start, NULL, &banner);
    SDL_RenderCopy(renderer, welcome, NULL, &banner2);
    SDL_RenderCopy(renderer, helping, NULL, &banner3);
    SDL_RenderPresent(renderer);

    bool main_back = false;
    SDL_Event e;
    while(true) {
        SDL_PollEvent(&e);
        if(e.type == SDL_QUIT) {
            quitSDL(window, renderer);
            return 0;
        }
        if(e.type == SDL_MOUSEBUTTONDOWN) {
            if(main_back == true) {
                if(0 < e.button.x && e.button.x < 50 && 0 < e.button.y && e.button.y < 50) {
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, background, NULL, &space);
                    SDL_RenderCopy(renderer, start, NULL, &banner);
                    SDL_RenderCopy(renderer, welcome, NULL, &banner2);
                    SDL_RenderCopy(renderer, helping, NULL, &banner3);
                    SDL_RenderPresent(renderer);
                    main_back = false;
                    continue;
                }
            }
            if(banner.x < e.button.x && e.button.x < banner.x + banner.w) {
                if(banner.y < e.button.y && e.button.y < banner.y + banner.h) {
                    break;
                }
            }
            if(banner3.x < e.button.x && e.button.x < banner3.x + banner3.w) {
                if(banner3.y < e.button.y && e.button.y < banner3.y + banner3.h) {
                    clear_renderer(renderer);
                    SDL_RenderCopy(renderer, background, NULL, &space);
                    SDL_RenderCopy(renderer, getback, NULL, &banner5);
                    SDL_RenderCopy(renderer, instruct, NULL, &banner4);
                    SDL_RenderPresent(renderer);
                    main_back = true;
                }
            }
        }
    }
    SDL_SetRenderDrawColor(renderer, 225, 225, 225, 0);
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
    //SDL_Texture *trap2 = loadTexture("cactus2.png", renderer);

    SDL_RenderCopy(renderer, trap, NULL, &rect2);

    draw_ground(renderer);

    SDL_RenderPresent(renderer);

    SDL_Event event;
    bool game_lose = false;

    while(true) {
        check = false;
        SDL_PollEvent(&event);
        if(event.type == SDL_QUIT /*|| event.key.keysym.sym == SDLK_ESCAPE*/) {
            quitSDL(window, renderer);
            return 0;
        }

        clear_renderer(renderer);
        SDL_RenderCopy(renderer, character, NULL, &rect);
        trap_run(rect2, renderer, trap);
        draw_ground(renderer);
        SDL_RenderPresent(renderer);

        if(SDL_HasIntersection(&rect, &rect2) == SDL_TRUE) {
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
                    if(SDL_HasIntersection(&rect, &rect2) == SDL_TRUE) {
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
                    if(SDL_HasIntersection(&rect, &rect2) == SDL_TRUE) {
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
        SDL_Texture *ending = loadText(gFont, renderer, text, blue);
        set_side(banner, SCREEN_WIDTH/3, SCREEN_HEIGHT/3, SCREEN_HEIGHT/3, SCREEN_WIDTH/3);
        SDL_RenderCopy(renderer, ending, NULL, &banner);
        SDL_RenderPresent(renderer);
        waitUntilKeyPressed();
    }
    quitSDL(window, renderer);
    return 0;
}
