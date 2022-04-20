#include<iostream>
#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_image.h>
using namespace std;

SDL_Texture* loadTexture(string path, SDL_Renderer* &renderer) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) cout << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError() << endl;
    else {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 255, 255));
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if(newTexture == NULL)
            cout << "Unable to create texture from " << path << " SDL Error: "<< SDL_GetError() << endl;
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

SDL_Texture* loadText(TTF_Font* &gFont, SDL_Renderer* &renderer, string text, SDL_Color textColor) {
    SDL_Texture* mTexture = NULL;
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text.c_str(), textColor);
    if(textSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(mTexture == NULL) {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        SDL_FreeSurface(textSurface);
    }
    return mTexture;
}
