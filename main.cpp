#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include "init.h"
#include "load_img.h"
#include "state.h"
using namespace std;

int BACK_STEP = 5;
bool main_back, game_lose, re_play, check, random_check, buff, was_collision;
int random_val;
SDL_Rect space, start_banner, welcome_banner, help_banner, instruct_banner, back_banner, point_banner, back_press, rect_shield;
SDL_Rect char_rect[2], trap_rect;
SDL_Texture *character[3], *trap[4];

void draw_ground(SDL_Renderer* &renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT/2 + height, SCREEN_WIDTH, SCREEN_HEIGHT/2 + height);
}

void update_point(SDL_Renderer* &renderer, TTF_Font* &gFont2, string &s, string &s2, SDL_Texture* &point, int &BACK_STEP) {
    s = add(s, s2);
    point = loadText(gFont2, renderer, "Your score: " + s, black);
    if(convert(s) % 1000 == 0 && convert(s) != 0) BACK_STEP = 12 * BACK_STEP / 10;
}

void random_trap(SDL_Renderer* &renderer, SDL_Rect &trap_rect, SDL_Texture* trap[3]) {
    if(random_check == true) {
        random_val = rand() % 5;
        random_check = false;
    }
    if(random_val % 2 == 0) SDL_RenderCopy(renderer, trap[0], NULL, &trap_rect);
    else if(random_val % 2 == 1 && random_val != 3) SDL_RenderCopy(renderer, trap[1], NULL, &trap_rect);
    else if(random_val == 3) SDL_RenderCopy(renderer, trap[2], NULL, &trap_rect);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    if(TTF_Init() == -1) printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    TTF_Font *gFont = TTF_OpenFont("Freedom-10eM.ttf", 40), *gFont2 = TTF_OpenFont("Lato-Semibold.ttf", 40);

    SDL_Texture *background = loadTexture("desert.jpg", renderer);
    SDL_Texture *background2 = loadTexture("background2.jpg", renderer);
    SDL_Texture *instruct = loadTexture("instruct.png", renderer);

    setTexture(renderer, character, trap);

    SDL_Texture *point = NULL;
    SDL_Texture *start = loadText(gFont, renderer, starting, blue);
    SDL_Texture *welcome = loadText(gFont, renderer, name, blue);
    SDL_Texture *helping = loadText(gFont, renderer, help, blue);
    SDL_Texture *ending = loadText(gFont, renderer, text, blue);
    SDL_Texture *getback = loadText(gFont, renderer, get_back, blue);
    SDL_Texture *instruct2 = loadText(gFont2, renderer, q_press, blue);

    SDL_Event e, event;
    string s, s2;

    do {
        re_play = false;
        main_back = false;
        game_lose = false;
        random_check = true;
        buff = false;
        was_collision = false;
        BACK_STEP = 5;

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
            if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
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
        SDL_RenderCopy(renderer, background2, NULL, &space);
        //load dino
        char_rect[0].x = SCREEN_WIDTH/4;
        char_rect[0].y = SCREEN_HEIGHT/2;
        SDL_QueryTexture(character[0], NULL, NULL, &char_rect[0].w, &char_rect[0].h);
        SDL_RenderCopy(renderer, character[0], NULL, &char_rect[0]);

        char_rect[1].x = SCREEN_WIDTH/4;
        char_rect[1].y = SCREEN_HEIGHT/2;
        SDL_QueryTexture(character[1], NULL, NULL, &char_rect[1].w, &char_rect[1].h);

        //load cactus
        trap_rect.h = char_rect[0].h;
        trap_rect.w = char_rect[0].w;
        trap_rect.x = SCREEN_WIDTH - trap_rect.w;
        trap_rect.y = SCREEN_HEIGHT/2;

        set_side(rect_shield, SCREEN_WIDTH - trap_rect.w, SCREEN_HEIGHT/2, char_rect[0].h, char_rect[0].w);

        random_trap(renderer, trap_rect, trap);

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
            update_point(renderer, gFont2, s, s2, point, BACK_STEP);

            clear_renderer(renderer);
            SDL_RenderCopy(renderer, background2, NULL, &space);
            SDL_RenderCopy(renderer, point, NULL, &point_banner);

            SDL_RenderCopy(renderer, character[int(buff)], NULL, &char_rect[int(buff)]);

            if(random_check == true) {
                random_val = rand() % 6;
                random_check = false;
            }
            if(random_val % 3 ==  0) trap_run(BACK_STEP, trap_rect, renderer, trap[0], random_check);
            else if(random_val % 3 == 1) trap_run(BACK_STEP, trap_rect, renderer, trap[1], random_check);
            else if(random_val % 3 == 2) trap_run(BACK_STEP, rect_shield, renderer, trap[2], random_check);

            draw_ground(renderer);
            SDL_RenderPresent(renderer);
            if(was_collision == true && trap_rect.w + trap_rect.x < char_rect[0].x) {
                buff = false;
                was_collision = false;
            }
            if(SDL_HasIntersection(&char_rect[0], &trap_rect) == SDL_TRUE) {
                if(buff == false) {
                    SDL_Delay(500);
                    game_lose = true;
                    break;
                }
                else was_collision = true;
            }
            if(SDL_HasIntersection(&rect_shield, &char_rect[0]) == SDL_TRUE || SDL_HasIntersection(&rect_shield, &char_rect[1]) == SDL_TRUE) buff = true;

            if(event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_SPACE) check = true;
                if(check) {
                    for(int i = 0 ; i <= JUMP_HEIGHT / JUMP_STEP ; i++) {
                        clear_renderer(renderer);
                        char_rect[0].y -= JUMP_STEP;
                        char_rect[1].y -= JUMP_STEP;

                        SDL_RenderCopy(renderer, background2, NULL, &space);

                        SDL_RenderCopy(renderer, character[int(buff)], NULL, &char_rect[int(buff)]);

                        if(random_check == true) {
                            random_val = rand() % 6;
                            random_check = false;
                        }
                        if(random_val % 3 ==  0) trap_run(BACK_STEP, trap_rect, renderer, trap[0], random_check);
                        else if(random_val % 3 == 1) trap_run(BACK_STEP, trap_rect, renderer, trap[1], random_check);
                        else if(random_val % 3 == 2) trap_run(BACK_STEP, rect_shield, renderer, trap[2], random_check);

                        draw_ground(renderer);

                        update_point(renderer, gFont2, s, s2, point, BACK_STEP);

                        SDL_RenderCopy(renderer, point, NULL, &point_banner);

                        SDL_RenderPresent(renderer);

                        if(was_collision == true && trap_rect.w + trap_rect.x < char_rect[0].x) {
                            buff = false;
                            was_collision = false;
                        }
                        if(SDL_HasIntersection(&char_rect[0], &trap_rect) == SDL_TRUE) {
                            if(buff == false) {
                                SDL_Delay(500);
                                game_lose = true;
                                break;
                            }
                            else was_collision = true;
                        }
                        if(SDL_HasIntersection(&rect_shield, &char_rect[0]) == SDL_TRUE || SDL_HasIntersection(&rect_shield, &char_rect[1]) == SDL_TRUE) buff = true;
                    }
                    if(game_lose == true) break;

                    for(int i = 0 ; i <= JUMP_HEIGHT / JUMP_STEP ; i++) {
                        clear_renderer(renderer);
                        char_rect[0].y += JUMP_STEP;
                        char_rect[1].y += JUMP_STEP;

                        update_point(renderer, gFont2, s, s2, point, BACK_STEP);

                        SDL_RenderCopy(renderer, background2, NULL, &space);
                        SDL_RenderCopy(renderer, point, NULL, &point_banner);

                        SDL_RenderCopy(renderer, character[int(buff)], NULL, &char_rect[int(buff)]);

                        if(random_check == true) {
                            random_val = rand() % 6;
                            random_check = false;
                        }
                        if(random_val % 3 ==  0) trap_run(BACK_STEP, trap_rect, renderer, trap[0], random_check);
                        else if(random_val % 3 == 1) trap_run(BACK_STEP, trap_rect, renderer, trap[1], random_check);
                        else if(random_val % 3 == 2) trap_run(BACK_STEP, rect_shield, renderer, trap[2], random_check);

                        draw_ground(renderer);
                        SDL_RenderPresent(renderer);

                        if(was_collision == true && trap_rect.w + trap_rect.x < char_rect[0].x) {
                            buff = false;
                            was_collision = false;
                        }
                        if(SDL_HasIntersection(&char_rect[0], &trap_rect) == SDL_TRUE) {
                            if(buff == false) {
                                SDL_Delay(500);
                                game_lose = true;
                                break;
                            }
                            else was_collision = true;
                        }
                        if(SDL_HasIntersection(&rect_shield, &char_rect[0]) == SDL_TRUE || SDL_HasIntersection(&rect_shield, &char_rect[1]) == SDL_TRUE) buff = true;
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
            set_side(back_press, SCREEN_WIDTH/6, 2*SCREEN_HEIGHT/3, SCREEN_HEIGHT/7, 2*SCREEN_WIDTH/3);

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
