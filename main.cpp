#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include "init.h"
#include "load_img.h"
using namespace std;

int main(int argc, char* argv[]) {
    srand(time(0));
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    if(TTF_Init() == -1) printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    TTF_Font *gFont = TTF_OpenFont("Pixelletters-RLm3.ttf", 40), *gFont2 = TTF_OpenFont("Lato-Semibold.ttf", 40);

    SDL_Texture *background = loadTexture("desert.jpg", renderer);
    SDL_Texture *background2 = loadTexture("background2.jpg", renderer);
    SDL_Texture *instruct = loadTexture("instruct.png", renderer);
    SDL_Texture *pause = loadTexture("pause.png", renderer);
    SDL_Texture *stone = loadTexture("stone1.png", renderer);
    setTexture(renderer, character, trap);

    SDL_Texture *point = NULL;
    SDL_Texture *start = loadText(gFont, renderer, starting, blue);
    SDL_Texture *welcome = loadText(gFont, renderer, name, blue);
    SDL_Texture *helping = loadText(gFont, renderer, help, blue);
    SDL_Texture *ending = loadText(gFont, renderer, text, blue);
    SDL_Texture *getback = loadText(gFont, renderer, get_back, blue);
    SDL_Texture *instruct2 = loadText(gFont2, renderer, q_press, blue);
    SDL_Texture *rest = loadText(gFont, renderer, pause_game, black);
    SDL_Texture *comeback = loadText(gFont, renderer, come_back, black);
    SDL_Texture *easy_button = loadText(gFont, renderer, easy_mode, black);
    SDL_Texture *hard_button = loadText(gFont, renderer, hard_mode, black);

    SDL_Event e, event;
    string s, s2;

    do {
        set_bool();
        BACK_STEP = 5;

        create();

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
                int x, y;
                SDL_GetMouseState(&x, &y);
                if(main_back == false && start_banner.x < x && x < start_banner.x + start_banner.w) {
                    if(start_banner.y < y && y < start_banner.y + start_banner.h) break;
                }
                if(main_back == true) {
                    if(0 < x && x < 50 && 0 < y && y < 50) {
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
                if(help_banner.x < x && x < help_banner.x + help_banner.w) {
                    if(help_banner.y < y && y < help_banner.y + help_banner.h) {
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

        while(true) {
            clear_renderer(renderer);
            SDL_RenderCopy(renderer, easy_button, NULL, &mode[0]);
            SDL_RenderCopy(renderer, hard_button, NULL, &mode[1]);
            SDL_RenderPresent(renderer);
            SDL_PollEvent(&event);
            if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                quitSDL(window, renderer);
                return 0;
            }
            if(event.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if(mode[0].x < x && x < mode[0].x + mode[0].w) {
                    if(mode[0].y < y && y < mode[0].y + mode[0].h) {
                        hard = false;
                        clear_renderer(renderer);
                        break;
                    }
                }
                if(mode[1].x < x && x < mode[1].x + mode[1].w) {
                    if(mode[1].y < y && y < mode[1].y + mode[1].h) {
                        hard = true;
                        clear_renderer(renderer);
                        break;
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
            if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                quitSDL(window, renderer);
                return 0;
            }
            update_point(renderer, gFont2, s, s2, point, BACK_STEP);

            clear_renderer(renderer);
            SDL_RenderCopy(renderer, background2, NULL, &space);
            SDL_RenderCopy(renderer, point, NULL, &point_banner);
            SDL_RenderCopy(renderer, pause, NULL, &pause_rect);
            SDL_RenderCopy(renderer, character[int(buff)], NULL, &char_rect[int(buff)]);
            draw_ground(renderer);

            if(event.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if(0 < x && x < 50 && 0 < y && y < 50) {
                    while(true) {
                        clear_renderer(renderer);
                        SDL_RenderCopy(renderer, rest, NULL, &pause_screen);
                        SDL_RenderCopy(renderer, comeback, NULL, &getback_screen);
                        SDL_RenderPresent(renderer);
                        SDL_PollEvent(&event);
                        if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                            quitSDL(window, renderer);
                            return 0;
                        }
                        if(event.type == SDL_MOUSEBUTTONDOWN) {
                            SDL_GetMouseState(&x, &y);
                            if(getback_screen.x < x && x < getback_screen.x + getback_screen.w) {
                                if(getback_screen.y < y && y < getback_screen.y + getback_screen.h) {
                                    break;
                                }
                            }
                        }
                    }
                }
            }

            if(random_check == true) {
                random_val1 = rand() % 6;
                random_check = false;
            }
            if(random_val1 == 0 || random_val1 == 1) trap_run(BACK_STEP, trap_rect, renderer, trap[0], random_check);
            else if(random_val1 == 2 || random_val1 == 3) trap_run(BACK_STEP, trap_rect, renderer, trap[1], random_check);
            else trap_run(BACK_STEP, rect_shield, renderer, trap[2], random_check);

            if(hard == true) {
                if(random_stone == true) {
                    random_val2 = rand() % 6;
                    random_stone = false;
                }
                if(random_val2 == 1) falling_stone(renderer, stone_rect, stone, random_stone);
                else random_stone = true;
            }

            SDL_RenderPresent(renderer);

            if(was_collision == true) {
                if(trap_rect.w + trap_rect.x < char_rect[0].x) {
                    buff = false;
                    was_collision = false;
                }
                else if(hard == true && stone_rect.x + stone_rect.w < char_rect[0].x && stone_rect.y + stone_rect.h > char_rect[0].y) {
                    buff = false;
                    was_collision = false;
                }
            }
            if(SDL_HasIntersection(&char_rect[0], &trap_rect) == SDL_TRUE || (hard == true && SDL_HasIntersection(&char_rect[0], &stone_rect) == SDL_TRUE)) {
                if(buff == false) {
                    SDL_Delay(500);
                    game_lose = true;
                    break;
                }
                else {
                    was_collision = true;
                }
            }
            if(SDL_HasIntersection(&rect_shield, &char_rect[0]) == SDL_TRUE || SDL_HasIntersection(&rect_shield, &char_rect[1]) == SDL_TRUE) buff = true;

            if(event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_SPACE) check = true;
                if(check) {
                    for(int i = 0 ; i <= JUMP_HEIGHT / JUMP_STEP ; i++) {
                        SDL_PollEvent(&event);
                        if(event.type == SDL_MOUSEBUTTONDOWN) {
                            int x, y;
                            SDL_GetMouseState(&x, &y);
                            if(0 < x && x < 50 && 0 < y && y < 50) {
                                while(true) {
                                    clear_renderer(renderer);
                                    SDL_RenderCopy(renderer, rest, NULL, &pause_screen);
                                    SDL_RenderCopy(renderer, comeback, NULL, &getback_screen);
                                    SDL_RenderPresent(renderer);
                                    SDL_PollEvent(&event);
                                    if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                                        quitSDL(window, renderer);
                                        return 0;
                                    }
                                    if(event.type == SDL_MOUSEBUTTONDOWN) {
                                        SDL_GetMouseState(&x, &y);
                                        if(getback_screen.x < x && x < getback_screen.x + getback_screen.w) {
                                            if(getback_screen.y < y && y < getback_screen.y + getback_screen.h) {
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        clear_renderer(renderer);
                        char_rect[0].y -= JUMP_STEP;
                        char_rect[1].y -= JUMP_STEP;

                        SDL_RenderCopy(renderer, background2, NULL, &space);
                        SDL_RenderCopy(renderer, pause, NULL, &pause_rect);

                        SDL_RenderCopy(renderer, character[int(buff)], NULL, &char_rect[int(buff)]);

                        if(random_check == true) {
                            random_val1 = rand() % 6;
                            random_check = false;
                        }
                        if(random_val1 == 0 || random_val1 == 1) trap_run(BACK_STEP, trap_rect, renderer, trap[0], random_check);
                        else if(random_val1 == 2 || random_val1 == 3) trap_run(BACK_STEP, trap_rect, renderer, trap[1], random_check);
                        else trap_run(BACK_STEP, rect_shield, renderer, trap[2], random_check);

                        if(hard == true) {
                            if(random_stone == true) {
                                random_val2 = rand() % 6;
                                random_stone = false;
                            }
                            if(random_val2 == 1) falling_stone(renderer, stone_rect, stone, random_stone);
                            else random_stone = true;
                        }

                        draw_ground(renderer);

                        update_point(renderer, gFont2, s, s2, point, BACK_STEP);

                        SDL_RenderCopy(renderer, point, NULL, &point_banner);

                        SDL_RenderPresent(renderer);

                        if(was_collision == true) {
                            if(trap_rect.w + trap_rect.x < char_rect[0].x) {
                                buff = false;
                                was_collision = false;
                            }
                            else if(hard == true && stone_rect.x + stone_rect.w < char_rect[0].x && stone_rect.y + stone_rect.h > char_rect[0].y) {
                                buff = false;
                                was_collision = false;
                            }
                        }
                        if(SDL_HasIntersection(&char_rect[0], &trap_rect) == SDL_TRUE || (hard == true && SDL_HasIntersection(&char_rect[0], &stone_rect) == SDL_TRUE)) {
                            if(buff == false) {
                                SDL_Delay(500);
                                game_lose = true;
                                break;
                            }
                            else {
                                was_collision = true;
                            }
                        }
                        if(SDL_HasIntersection(&rect_shield, &char_rect[0]) == SDL_TRUE || SDL_HasIntersection(&rect_shield, &char_rect[1]) == SDL_TRUE) buff = true;
                    }
                    if(game_lose == true) break;

                    for(int i = 0 ; i <= JUMP_HEIGHT / JUMP_STEP ; i++) {
                        SDL_PollEvent(&event);
                        if(event.type == SDL_MOUSEBUTTONDOWN) {
                            int x, y;
                            SDL_GetMouseState(&x, &y);
                            if(0 < x && x < 50 && 0 < y && y < 50) {
                                while(true) {
                                    clear_renderer(renderer);
                                    SDL_RenderCopy(renderer, rest, NULL, &pause_screen);
                                    SDL_RenderCopy(renderer, comeback, NULL, &getback_screen);
                                    SDL_RenderPresent(renderer);
                                    SDL_PollEvent(&event);
                                    if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                                        quitSDL(window, renderer);
                                        return 0;
                                    }
                                    if(event.type == SDL_MOUSEBUTTONDOWN) {
                                        SDL_GetMouseState(&x, &y);
                                        if(getback_screen.x < x && x < getback_screen.x + getback_screen.w) {
                                            if(getback_screen.y < y && y < getback_screen.y + getback_screen.h) {
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        clear_renderer(renderer);
                        char_rect[0].y += JUMP_STEP;
                        char_rect[1].y += JUMP_STEP;

                        update_point(renderer, gFont2, s, s2, point, BACK_STEP);

                        SDL_RenderCopy(renderer, background2, NULL, &space);
                        SDL_RenderCopy(renderer, pause, NULL, &pause_rect);
                        SDL_RenderCopy(renderer, point, NULL, &point_banner);

                        SDL_RenderCopy(renderer, character[int(buff)], NULL, &char_rect[int(buff)]);

                        if(random_check == true) {
                            random_val1 = rand() % 6;
                            random_check = false;
                        }
                        if(random_val1 == 0 || random_val1 == 1) trap_run(BACK_STEP, trap_rect, renderer, trap[0], random_check);
                        else if(random_val1 == 2 || random_val1 == 3) trap_run(BACK_STEP, trap_rect, renderer, trap[1], random_check);
                        else trap_run(BACK_STEP, rect_shield, renderer, trap[2], random_check);

                        if(hard == true) {
                            if(random_stone == true) {
                                random_val2 = rand() % 6;
                                random_stone = false;
                            }
                            if(random_val2 == 1) falling_stone(renderer, stone_rect, stone, random_stone);
                            else random_stone = true;
                        }

                        draw_ground(renderer);
                        SDL_RenderPresent(renderer);

                        if(was_collision == true) {
                            if(trap_rect.w + trap_rect.x < char_rect[0].x) {
                                buff = false;
                                was_collision = false;
                            }
                            else if(hard == true && stone_rect.x + stone_rect.w < char_rect[0].x && stone_rect.y + stone_rect.h > char_rect[0].y) {
                                buff = false;
                                was_collision = false;
                            }
                        }
                        if(SDL_HasIntersection(&char_rect[0], &trap_rect) == SDL_TRUE || (hard == true && SDL_HasIntersection(&char_rect[0], &stone_rect) == SDL_TRUE)) {
                            if(buff == false) {
                                SDL_Delay(500);
                                game_lose = true;
                                break;
                            }
                            else {
                                was_collision = true;
                            }
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
            set_side(start_banner, 5*SCREEN_WIDTH/12, SCREEN_HEIGHT/3, SCREEN_HEIGHT/8, SCREEN_WIDTH/6);
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
