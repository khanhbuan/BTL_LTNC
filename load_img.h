#ifndef LOAD_IMG_H
#define LOAD_IMG_H
#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
using namespace std;

SDL_Texture* loadTexture(string path, SDL_Renderer* &renderer);

#endif // LOAD_IMG_H
