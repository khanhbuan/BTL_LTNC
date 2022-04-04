#ifndef INIT_H
#define INIT_H
#include<iostream>
#include<SDL.h>
using namespace std;

void logSDLError(std::ostream& os, const std::string &msg, bool fatal);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void waitUntilKeyPressed();

#endif // INIT_H
