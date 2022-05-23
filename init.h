#ifndef INIT_H
#define INIT_H
#include<iostream>
#include<SDL.h>
#include<SDL_ttf.h>
#include "load_img.h"
using namespace std;

const SDL_Color blue = {0, 0, 255};
const SDL_Color black = {0, 0, 0};
const SDL_Color white = {255, 255, 255};

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int JUMP_HEIGHT = 70;
const int JUMP_STEP = 5;
const int height = 34;

const string WINDOW_TITLE = "An Implementation of DINO";
const string text = "GAME OVER";
const string starting = "START";
const string help = "HELP";
const string name = "WELCOME TO DINO IN THE DESERT";
const string get_back = "BACK";
const string q_press = "PRESS Q TO BACK TO MAIN MENU";
const string pause_game = "GAME PAUSE";
const string come_back = "CONTINUE";
const string easy_mode = "EASY";
const string hard_mode = "HARD";

extern int BACK_STEP;
extern bool main_back, game_lose, re_play, check, random_check, buff, was_collision, random_stone, hard;
extern int random_val1, random_val2;
extern SDL_Rect space, start_banner, welcome_banner, help_banner;
extern SDL_Rect instruct_banner, back_banner, point_banner, back_press, rect_shield, pause_rect, pause_screen, getback_screen;
extern SDL_Rect char_rect[2], trap_rect, stone_rect, mode[2];
extern SDL_Texture *character[3], *trap[4];

void logSDLError(std::ostream& os, const std::string &msg, bool fatal);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void waitUntilKeyPressed();

void clear_renderer(SDL_Renderer* &renderer);

void set_side(SDL_Rect &rect, int x, int y, int h, int w);

string add(string &s, string &s2);

int convert(string &s);

void trap_run(int &BACK_STEP, SDL_Rect &rect, SDL_Renderer* &renderer, SDL_Texture* &character, bool &random_check);

void setTexture(SDL_Renderer* &renderer, SDL_Texture* character[5], SDL_Texture* trap[5]);

void draw_ground(SDL_Renderer* &renderer);

void falling_stone(SDL_Renderer* &renderer, SDL_Rect &stone_rect, SDL_Texture* &stone, bool &random_stone);

void create();

void update_point(SDL_Renderer* &renderer, TTF_Font* &gFont2, string &s, string &s2, SDL_Texture* &point, int &BACK_STEP);

void random_trap(SDL_Renderer* &renderer, SDL_Rect &trap_rect, SDL_Texture* trap[3]);

void set_bool();
#endif // INIT_H
