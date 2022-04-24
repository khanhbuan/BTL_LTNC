#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<thread>
#include<chrono>
#include "init.h"
#include "load_img.h"
using namespace std;

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
const string q_press = "PRESS Q TO BACK TO MAIN MENU";
const SDL_Color blue = {0, 0, 255};
const SDL_Color black = {0, 0, 0};
const SDL_Color white = {255, 255, 255};

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

string add(string &s, string &s2) {
    string s3 = "";
    while(s.length() < s2.length()) s = "0" + s;
    while(s2.length() < s.length()) s2 = "0" + s2;
    int num, div = 0;
    for(int i = s.length() - 1 ; i >= 0 ; i--) {
        num = (s[i] - '0') + (s2[i] - '0') + div;
        s3 = (char)(num % 10 + '0') + s3;;
        div = num / 10;
    }
    if(div != 0) s3 = (char)(div + '0') + s3;
    return s3;
}

int main(int argc, char* argv[]) {
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    if(TTF_Init() == -1) printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    TTF_Font *gFont = NULL, *gFont2 = NULL;
    gFont = TTF_OpenFont("Freedom-10eM.ttf", 40);
    gFont2 = TTF_OpenFont("Lato-Semibold.ttf", 40);
    SDL_Rect space, start_banner, welcome_banner, help_banner, instruct_banner, back_banner, point_banner, rect, rect2, back_press;

    SDL_Texture *background = loadTexture("desert.jpg", renderer);
    SDL_Texture *start = loadText(gFont, renderer, starting, blue);
    SDL_Texture *welcome = loadText(gFont, renderer, name, blue);
    SDL_Texture *helping = loadText(gFont, renderer, help, blue);
    SDL_Texture *instruct = loadTexture("instruct.png", renderer);
    SDL_Texture *getback = loadText(gFont2, renderer, get_back, blue);
    SDL_Texture *point = NULL;
    SDL_Texture* character = loadTexture("dino.png", renderer);
    SDL_Texture* trap = loadTexture("cactus1.png", renderer);
    SDL_Texture *ending = loadText(gFont2, renderer, text, blue);
    SDL_Texture *instruct2 = loadText(gFont2, renderer, q_press, blue);

    bool main_back, game_lose, re_play, check;
    SDL_Event e, event;
    string s, s2;

    do {
        re_play = false;
        main_back = false;
        game_lose = false;

        set_side(space, 0, 0, SCREEN_HEIGHT, SCREEN_WIDTH);
        set_side(start_banner, 7*SCREEN_WIDTH/16, 7*SCREEN_HEIGHT/16, SCREEN_HEIGHT/8, SCREEN_WIDTH/8);
        set_side(welcome_banner, SCREEN_WIDTH/4, SCREEN_HEIGHT/8, SCREEN_HEIGHT/5, SCREEN_WIDTH/2);
        set_side(help_banner, 7*SCREEN_WIDTH/16, 9*SCREEN_HEIGHT/16, SCREEN_HEIGHT/8, SCREEN_WIDTH/8);
        set_side(instruct_banner, 0, 0, SCREEN_HEIGHT, SCREEN_WIDTH);
        set_side(back_banner, 0, 0, 50, 50);
        set_side(point_banner, 2*SCREEN_WIDTH/3, 100, 20, 100);

        SDL_RenderCopy(renderer, background, NULL, &space);
        SDL_RenderCopy(renderer, start, NULL, &start_banner);
        SDL_RenderCopy(renderer, welcome, NULL, &welcome_banner);
        SDL_RenderCopy(renderer, helping, NULL, &help_banner);
        SDL_RenderPresent(renderer);

        while(true) {
            SDL_PollEvent(&e);
            if(e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {
                quitSDL(window, renderer);
                return 0;
            }
            if(e.type == SDL_MOUSEBUTTONDOWN) {
                if(main_back == false && start_banner.x < e.button.x && e.button.x < start_banner.x + start_banner.w) {
                    if(start_banner.y < e.button.y && e.button.y < start_banner.y + start_banner.h) break;
                }
                if(main_back == true) {
                    if(0 < e.button.x && e.button.x < 50 && 0 < e.button.y && e.button.y < 50) {
                        SDL_RenderClear(renderer);
                        SDL_RenderCopy(renderer, background, NULL, &space);
                        SDL_RenderCopy(renderer, start, NULL, &start_banner);
                        SDL_RenderCopy(renderer, welcome, NULL, &welcome_banner);
                        SDL_RenderCopy(renderer, helping, NULL, &help_banner);
                        SDL_RenderPresent(renderer);
                        main_back = false;
                        continue;
                    }
                }
                if(help_banner.x < e.button.x && e.button.x < help_banner.x + help_banner.w) {
                    if(help_banner.y < e.button.y && e.button.y < help_banner.y + help_banner.h) {
                        clear_renderer(renderer);
                        SDL_RenderCopy(renderer, background, NULL, &space);
                        SDL_RenderCopy(renderer, getback, NULL, &back_banner);
                        SDL_RenderCopy(renderer, instruct, NULL, &instruct_banner);
                        SDL_RenderPresent(renderer);
                        main_back = true;
                    }
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 225, 225, 225, 0);
        //load dino
        rect.x = SCREEN_WIDTH/4;
        rect.y = SCREEN_HEIGHT/2;
        SDL_QueryTexture(character, NULL, NULL, &rect.w, &rect.h);
        SDL_RenderCopy(renderer, character, NULL, &rect);

        //load cactus
        rect2.h = rect.h;
        rect2.w = rect.w;
        rect2.x = SCREEN_WIDTH - rect2.w;
        rect2.y = SCREEN_HEIGHT/2;

        SDL_RenderCopy(renderer, trap, NULL, &rect2);
        draw_ground(renderer);

        SDL_RenderPresent(renderer);

        s = "0", s2 = "1";

        while(true) {
            check = false;
            SDL_PollEvent(&event);
            if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
                quitSDL(window, renderer);
                return 0;
            }
            s = add(s, s2);
            point = loadText(gFont2, renderer, "Your score: " + s, black);

            clear_renderer(renderer);
            SDL_RenderCopy(renderer, point, NULL, &point_banner);
            SDL_RenderCopy(renderer, character, NULL, &rect);
            trap_run(rect2, renderer, trap);
            draw_ground(renderer);
            SDL_RenderPresent(renderer);

            if(SDL_HasIntersection(&rect, &rect2) == SDL_TRUE) {
                SDL_Delay(500);
                game_lose = true;
                break;
            }

            if(event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_SPACE) check = true;
                if(check) {
                    for(int i = 0 ; i <= JUMP_HEIGHT / JUMP_STEP ; i++) {
                        clear_renderer(renderer);
                        rect.y -= JUMP_STEP;
                        SDL_RenderCopy(renderer, character, NULL, &rect);
                        trap_run(rect2, renderer, trap);
                        draw_ground(renderer);

                        s = add(s, s2);
                        point = loadText(gFont2, renderer, "Your score: " + s, black);
                        SDL_RenderCopy(renderer, point, NULL, &point_banner);

                        SDL_RenderPresent(renderer);
                        if(SDL_HasIntersection(&rect, &rect2) == SDL_TRUE) {
                            SDL_Delay(500);
                            game_lose = true;
                            break;
                        }
                    }
                    if(game_lose == true) break;
                    for(int i = 0 ; i <= JUMP_HEIGHT / JUMP_STEP ; i++) {
                        clear_renderer(renderer);
                        rect.y += JUMP_STEP;

                        s = add(s, s2);
                        point = loadText(gFont2, renderer, "Your score: " + s, black);
                        SDL_RenderCopy(renderer, point, NULL, &point_banner);

                        SDL_RenderCopy(renderer, character, NULL, &rect);
                        trap_run(rect2, renderer, trap);
                        draw_ground(renderer);
                        SDL_RenderPresent(renderer);
                        if(SDL_HasIntersection(&rect, &rect2) == SDL_TRUE) {
                            SDL_Delay(500);
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
            point = loadText(gFont2, renderer, "Your final score: " + s, blue);
            set_side(point_banner, SCREEN_WIDTH/3, SCREEN_HEIGHT/2, SCREEN_HEIGHT/6, SCREEN_WIDTH/3);
            set_side(start_banner, 5*SCREEN_WIDTH/12, SCREEN_HEIGHT/3, SCREEN_HEIGHT/6, SCREEN_WIDTH/6);
            set_side(back_press, SCREEN_WIDTH/6, 2*SCREEN_HEIGHT/3, SCREEN_HEIGHT/6, 2*SCREEN_WIDTH/3);

            SDL_RenderCopy(renderer, background, NULL, &space);
            SDL_RenderCopy(renderer, point, NULL, &point_banner);
            SDL_RenderCopy(renderer, ending, NULL, &start_banner);
            SDL_RenderCopy(renderer, instruct2, NULL, &back_press);
            SDL_RenderPresent(renderer);
            while(true) {
                SDL_PollEvent(&event);
                if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
                    quitSDL(window, renderer);
                    return 0;
                }
                if(event.key.keysym.sym == SDLK_q) {
                    re_play = true;
                    break;
                }
            }
        }
    } while(re_play == true);

    quitSDL(window, renderer);
    return 0;
}
