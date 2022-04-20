#ifndef LOAD_IMG_H
#define LOAD_IMG_H
#include<iostream>
#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_image.h>
using namespace std;

SDL_Texture* loadTexture(string path, SDL_Renderer* &renderer);

SDL_Texture* loadText(TTF_Font* &gFont, SDL_Renderer* &renderer, string text, SDL_Color textColor);

#endif // LOAD_IMG_H
