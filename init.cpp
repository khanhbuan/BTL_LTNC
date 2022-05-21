#include "init.h"
#include "load_img.h"
#include<iostream>
#include<SDL_ttf.h>
#include<SDL_image.h>
#include<SDL.h>
using namespace std;

void logSDLError(std::ostream& os, const std::string &msg, bool fatal) {
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	//SDL_FlushEvents();
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}

void waitUntilKeyPressed() {
    SDL_Event Test_event;
    while(true) {
        SDL_PollEvent(&Test_event);
        if((Test_event.type == SDL_QUIT || Test_event.type == SDL_KEYDOWN)) return;
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);

    //Khi chay trong moi truong binh thuong (khong chay tren may ao)
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //Khi chay o may ao
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void clear_renderer(SDL_Renderer* &renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderClear(renderer);
}

void set_side(SDL_Rect &rect, int x, int y, int h, int w) {
    rect.x = x;
    rect.y = y;
    rect.h = h;
    rect.w = w;
}

string add(string &s, string &s2) {
    string s3 = "";
    while(s.length() < s2.length()) s = "0" + s;
    while(s2.length() < s.length()) s2 = "0" + s2;
    int num, div = 0;
    for(int i = s.length() - 1 ; i >= 0 ; i--) {
        num = (s[i] - '0') + (s2[i] - '0') + div;
        s3 = (char)(num % 10 + '0') + s3;;
        div = num / 10;
    }
    if(div != 0) s3 = (char)(div + '0') + s3;
    return s3;
}

int convert(string &s) {
    int num = 0, div = 1;
    int n = s.length();
    for(int i = n - 1 ; i >= 0 ; i--) {
        num += (s[i] - '0')* div;
        div *= 10;
    }
    return num;
}

void trap_run(int &BACK_STEP, SDL_Rect &rect, SDL_Renderer* &renderer, SDL_Texture* &character, bool &random_check) {
    rect.x -= BACK_STEP;
    SDL_RenderCopy(renderer, character, NULL, &rect);
    if(rect.x <= BACK_STEP) {
        rect.x = SCREEN_WIDTH - rect.w;
        random_check = true;
    }
}

void setTexture(SDL_Renderer* &renderer, SDL_Texture* character[5], SDL_Texture* trap[5]) {
    string head = "dino", tail = ".png";
    for(int i = 0 ; i <= 1 ; i++) character[i] = loadTexture(head + char(i + 1 + '0') + tail, renderer);

    head = "cactus", tail = ".png";
    for(int i = 0 ; i <= 2 ; i++) trap[i] = loadTexture(head + (char)(i + '0') + tail, renderer);
}

void draw_ground(SDL_Renderer* &renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT/2 + height, SCREEN_WIDTH, SCREEN_HEIGHT/2 + height);
}
