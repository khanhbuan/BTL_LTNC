#ifndef STATE_H
#define STATE_H
#include<iostream>
#include<SDL.h>
#include<SDL_ttf.h>
using namespace std;

void trap_run(SDL_Rect &rect, SDL_Renderer* &renderer, SDL_Texture* &character, bool &random_check);

void update_point(SDL_Renderer* &renderer, TTF_Font* &gFont2, string &s, string &s2, SDL_Texture* &point, int &BACK_STEP);

void random_trap(SDL_Renderer* &renderer, SDL_Rect &trap_rect, SDL_Texture* trap[3]);

#endif // STATE_H
