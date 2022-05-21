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

#endif // INIT_H
