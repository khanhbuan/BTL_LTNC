#include<bits/stdc++.h>
#include "state.h"
#include "load_img.h"
#include "init.h"
using namespace std;

void trap_run(SDL_Rect &rect, SDL_Renderer* &renderer, SDL_Texture* &character, bool &random_check) {
    rect.x -= BACK_STEP;
    SDL_RenderCopy(renderer, character, NULL, &rect);
    if(rect.x <= BACK_STEP) {
        rect.x = SCREEN_WIDTH - rect.w;
        random_check = true;
    }
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
